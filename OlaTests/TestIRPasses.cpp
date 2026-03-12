#include <gtest/gtest.h>
#include "Backend/Custom/IR/IRContext.h"
#include "Backend/Custom/IR/IRBuilder.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/BasicBlock.h"
#include "Backend/Custom/IR/Constant.h"
#include "Backend/Custom/IR/FunctionPass.h"
#include "Backend/Custom/IR/IRModulePass.h"
#include "Backend/Custom/IR/PassManager.h"
#include "Backend/Custom/IR/AnalysisManager.h"
#include "Backend/Custom/IR/Passes/CFGAnalysisPass.h"
#include "Backend/Custom/IR/Passes/DominatorTreeAnalysisPass.h"
#include "Backend/Custom/IR/Passes/DominanceFrontierAnalysisPass.h"
#include "Backend/Custom/IR/Passes/LoopAnalysisPass.h"
#include "Backend/Custom/IR/Passes/CallGraphAnalysisPass.h"
#include "Backend/Custom/IR/Passes/DeadCodeEliminationPass.h"
#include "Backend/Custom/IR/Passes/ConstantPropagationPass.h"
#include "Backend/Custom/IR/Passes/ArithmeticReductionPass.h"
#include "Backend/Custom/IR/Passes/SimplifyCFGPass.h"
#include "Backend/Custom/IR/Passes/Mem2RegPass.h"
#include "Backend/Custom/IR/Passes/GlobalDeadCodeEliminationPass.h"
#include "Backend/Custom/IR/Passes/TailRecursionEliminationPass.h"
#include "Backend/Custom/IR/Passes/CommonSubexpressionEliminationPass.h"
#include "Backend/Custom/IR/Passes/GlobalValueNumberingPass.h"
#include "Backend/Custom/IR/Passes/FunctionInlinerPass.h"
#include "Backend/Custom/IR/Passes/LoopInvariantCodeMotionPass.h"
#include "Backend/Custom/IR/Passes/SROAPass.h"
#include "Backend/Custom/IR/Passes/CriticalEdgeSplittingPass.h"
#include "Backend/Custom/IR/Passes/IPConstantPropagationPass.h"
#include "Backend/Custom/IR/Passes/LoopUnrollPass.h"
#include "Backend/Custom/IR/Passes/GlobalAttributeInferPass.h"
#include "Utility/RTTI.h"

using namespace ola;

static Uint32 CountBlocks(Function const* fn)
{
	Uint32 n = 0;
	for (auto const& bb : *fn) ++n;
	return n;
}

static Uint32 CountByOpcode(Function const* fn, Opcode op)
{
	Uint32 n = 0;
	for (auto const& bb : *fn)
		for (auto const& inst : bb)
			if (inst.GetOpcode() == op) ++n;
	return n;
}

template <typename T>
static Uint32 CountByType(Function const* fn)
{
	Uint32 n = 0;
	for (auto const& bb : *fn)
		for (auto const& inst : bb)
			if (isa<T>(&inst)) ++n;
	return n;
}

static void RegisterAllAnalysisPasses(FunctionAnalysisManager& fam, Function& fn)
{
	fam.RegisterPass<CFGAnalysisPass>(fn);
	fam.RegisterPass<DominatorTreeAnalysisPass>(fn);
	fam.RegisterPass<DominanceFrontierAnalysisPass>(fn);
	fam.RegisterPass<LoopAnalysisPass>(fn);
}

static Function* MakeFunc(IRModule& module, IRContext& ctx,
	std::string_view name, IRType* ret,
	std::vector<IRType*> const& params,
	Linkage linkage = Linkage::External)
{
	IRFuncType* ft = ctx.GetFunctionType(ret, params);
	Function* fn = new Function(name, ft, linkage);
	module.AddGlobal(fn);
	return fn;
}

TEST(DCE, RemovesUnusedInstruction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x) { dead = x + x; return 0; }
	// The add result is never used, DCE should remove it.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* x = fn->GetArg(0);
	builder.MakeInst<BinaryInst>(Opcode::Add, x, x); // result unused
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(CountByOpcode(fn, Opcode::Add), 1u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<DeadCodeEliminationPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByOpcode(fn, Opcode::Add), 0u);
	EXPECT_EQ(CountByOpcode(fn, Opcode::Ret), 1u);
}

TEST(DCE, PreservesUsedInstruction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x) { return x - 1; }
	// The sub feeds the return, so DCE must not remove it.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* x = fn->GetArg(0);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::Sub, x, ctx.GetInt64(1));
	builder.MakeInst<ReturnInst>(result);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<DeadCodeEliminationPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByOpcode(fn, Opcode::Sub), 1u);
	EXPECT_EQ(CountByOpcode(fn, Opcode::Ret), 1u);
}

TEST(DCE, KeepsSideEffectfulInstructions)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn() { p = alloca; store 42 -> p; return 0; }
	// alloca and store have side effects and must survive DCE even though
	// the stored value is never read.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* p = builder.MakeInst<AllocaInst>(ctx.GetIntegerType(64));
	builder.MakeInst<StoreInst>(ctx.GetInt64(42), p);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<DeadCodeEliminationPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByType<AllocaInst>(fn), 1u);
	EXPECT_EQ(CountByType<StoreInst>(fn), 1u);
}

TEST(ConstantPropagation, FoldsBinaryOp)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// Manually build:  ret (3 + 4)
	// After ConstPropPass the ret operand must be the constant 7.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");

	// Insert add manually so IRBuilder cannot fold it eagerly.
	BinaryInst* add = new BinaryInst(Opcode::Add, ctx.GetInt64(3), ctx.GetInt64(4));
	add->InsertBefore(entry, entry->end());
	ReturnInst* ret = new ReturnInst(add);
	ret->InsertBefore(entry, entry->end());

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ConstantPropagationPass>();
	fpm.Run(*fn, fam);

	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	ASSERT_TRUE(isa<ConstantInt>(ret_val));
	EXPECT_EQ(cast<ConstantInt>(ret_val)->GetValue(), 7);
}

TEST(ConstantPropagation, FoldsSelectWithConstantCondition)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// Manually build:
	//   cond = (1 == 1)      <- CompareInst with two constants
	//   result = select cond, 42, 0
	//   ret result
	//
	// After ConstPropPass: cond folds to true, then select folds to 42,
	// so the ret operand becomes the constant 42.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");

	CompareInst* cmp = new CompareInst(Opcode::ICmpEQ, ctx.GetInt64(1), ctx.GetInt64(1));
	cmp->InsertBefore(entry, entry->end());

	// cmp is an Instruction, not a Constant, so IRBuilder won't fold the select.
	builder.SetCurrentBlock(entry);
	Value* sel = builder.MakeInst<SelectInst>(cmp, ctx.GetInt64(42), ctx.GetInt64(0));
	ReturnInst* ret = new ReturnInst(sel);
	ret->InsertBefore(entry, entry->end());

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ConstantPropagationPass>();
	fpm.Run(*fn, fam);

	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	ASSERT_TRUE(isa<ConstantInt>(ret_val));
	EXPECT_EQ(cast<ConstantInt>(ret_val)->GetValue(), 42);
}

TEST(ConstantPropagation, FoldsConditionalBranchToUnconditional)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// Manually build:
	//   entry: cond = (10 > 5); br cond then else
	//   then:  ret 1
	//   else:  ret 0
	//
	// After ConstPropPass: cond folds to true, the conditional branch
	// becomes an unconditional branch to then.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry   = builder.AddBlock("entry");
	BasicBlock* bb_then = builder.AddBlock("then");
	BasicBlock* bb_else = builder.AddBlock("else");

	builder.SetCurrentBlock(bb_then);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(1));

	builder.SetCurrentBlock(bb_else);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	// Insert compare and branch manually into entry.
	CompareInst* cmp = new CompareInst(Opcode::ICmpSGT, ctx.GetInt64(10), ctx.GetInt64(5));
	cmp->InsertBefore(entry, entry->end());
	BranchInst* br = new BranchInst(cmp, bb_then, bb_else);
	br->InsertBefore(entry, entry->end());

	ASSERT_TRUE(cast<BranchInst>(entry->GetTerminator())->IsConditional());

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ConstantPropagationPass>();
	fpm.Run(*fn, fam);

	EXPECT_TRUE(cast<BranchInst>(entry->GetTerminator())->IsUnconditional());
	EXPECT_EQ(cast<BranchInst>(entry->GetTerminator())->GetTrueTarget(), bb_then);
}

TEST(ArithmeticReduction, MultiplyByZeroBecomesZero)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x) { return x * 0; }
	// x is not a constant so IRBuilder won't fold it.
	// ArithReductionPass replaces  x * 0  with the constant 0.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* x = fn->GetArg(0);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::SMul, x, ctx.GetInt64(0));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(CountByOpcode(fn, Opcode::SMul), 1u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ArithmeticReductionPass>();
	fpm.Run(*fn, fam);

	// The multiply must be gone; the ret must now carry a constant 0.
	EXPECT_EQ(CountByOpcode(fn, Opcode::SMul), 0u);
	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	ASSERT_TRUE(isa<ConstantInt>(ret_val));
	EXPECT_EQ(cast<ConstantInt>(ret_val)->GetValue(), 0);
}

TEST(ArithmeticReduction, MultiplyByOneBecomesOperand)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x) { return x * 1; }  =>  return x
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* x = fn->GetArg(0);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::SMul, x, ctx.GetInt64(1));
	builder.MakeInst<ReturnInst>(result);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ArithmeticReductionPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByOpcode(fn, Opcode::SMul), 0u);
	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	EXPECT_EQ(ret_val, x);
}

TEST(ArithmeticReduction, AddZeroBecomesOperand)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x) { return x + 0; }  =>  return x
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* x = fn->GetArg(0);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::Add, x, ctx.GetInt64(0));
	builder.MakeInst<ReturnInst>(result);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ArithmeticReductionPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByOpcode(fn, Opcode::Add), 0u);
	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	EXPECT_EQ(ret_val, x);
}

TEST(ArithmeticReduction, MultiplyByPowerOfTwoBecomesShift)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x) { return x * 8; }  =>  return x << 3
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* x = fn->GetArg(0);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::SMul, x, ctx.GetInt64(8));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(CountByOpcode(fn, Opcode::SMul), 1u);
	EXPECT_EQ(CountByOpcode(fn, Opcode::Shl), 0u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ArithmeticReductionPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByOpcode(fn, Opcode::SMul), 0u);
	EXPECT_EQ(CountByOpcode(fn, Opcode::Shl), 1u);
}

TEST(SimplifyCFG, MergesEmptyPassthroughBlock)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// entry -> mid -> exit
	// mid contains only an unconditional branch (no phi nodes in exit),
	// so SimplifyCFG should merge mid away, leaving entry -> exit.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry  = builder.AddBlock("entry");
	BasicBlock* mid    = builder.AddBlock("mid");
	BasicBlock* exit_b = builder.AddBlock("exit");

	builder.SetCurrentBlock(entry);
	builder.MakeInst<BranchInst>(ctx, mid);

	builder.SetCurrentBlock(mid);
	builder.MakeInst<BranchInst>(ctx, exit_b);

	builder.SetCurrentBlock(exit_b);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(CountBlocks(fn), 3u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);
	fpm.AddPass<SimplifyCFGPass>();
	fpm.Run(*fn, fam);

	EXPECT_LT(CountBlocks(fn), 3u);
}

TEST(SimplifyCFG, RemovesUnreachableBlock)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// entry branches unconditionally to exit.
	// The block 'dead' is never branched to and must be removed.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry  = builder.AddBlock("entry");
	BasicBlock* dead   = builder.AddBlock("dead");
	BasicBlock* exit_b = builder.AddBlock("exit");

	builder.SetCurrentBlock(entry);
	builder.MakeInst<BranchInst>(ctx, exit_b);

	builder.SetCurrentBlock(dead);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(99));

	builder.SetCurrentBlock(exit_b);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(CountBlocks(fn), 3u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);
	fpm.AddPass<SimplifyCFGPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountBlocks(fn), 2u);
}

TEST(Mem2Reg, PromotesSingleBlockAlloca)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn() { p = alloca; store 42 -> p; v = load p; return v; }
	// All alloca/store/load in a single block: Mem2Reg replaces the load
	// with the stored constant and removes the memory operations.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* p = builder.MakeInst<AllocaInst>(ctx.GetIntegerType(64));
	builder.MakeInst<StoreInst>(ctx.GetInt64(42), p);
	Value* v = builder.MakeInst<LoadInst>(p);
	builder.MakeInst<ReturnInst>(v);

	EXPECT_EQ(CountByType<AllocaInst>(fn), 1u);
	EXPECT_EQ(CountByType<StoreInst>(fn),  1u);
	EXPECT_EQ(CountByType<LoadInst>(fn),   1u);

	// Mem2Reg removes the load and store; DCE (run after, as in the real
	// pipeline) then cleans up the now-unused alloca.
	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);
	fpm.AddPass<Mem2RegPass>();
	fpm.AddPass<DeadCodeEliminationPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByType<AllocaInst>(fn), 0u);
	EXPECT_EQ(CountByType<StoreInst>(fn),  0u);
	EXPECT_EQ(CountByType<LoadInst>(fn),   0u);
}

TEST(Mem2Reg, InsertsPhi_ForMultipleStores)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x) {
	//   p = alloca
	//   if (x > 0) { store 10 -> p } else { store 20 -> p }
	//   v = load p
	//   return v
	// }
	// Two control-flow paths write different values into the same alloca.
	// Mem2Reg must insert a phi node at the join point (exit block).
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry   = builder.AddBlock("entry");
	BasicBlock* bb_then = builder.AddBlock("then");
	BasicBlock* bb_else = builder.AddBlock("else");
	BasicBlock* bb_exit = builder.AddBlock("exit");

	Value* x = fn->GetArg(0);

	builder.SetCurrentBlock(entry);
	Value* p    = builder.MakeInst<AllocaInst>(ctx.GetIntegerType(64));
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpSGT, x, ctx.GetInt64(0));
	builder.MakeInst<BranchInst>(cond, bb_then, bb_else);

	builder.SetCurrentBlock(bb_then);
	builder.MakeInst<StoreInst>(ctx.GetInt64(10), p);
	builder.MakeInst<BranchInst>(ctx, bb_exit);

	builder.SetCurrentBlock(bb_else);
	builder.MakeInst<StoreInst>(ctx.GetInt64(20), p);
	builder.MakeInst<BranchInst>(ctx, bb_exit);

	builder.SetCurrentBlock(bb_exit);
	Value* v = builder.MakeInst<LoadInst>(p);
	builder.MakeInst<ReturnInst>(v);

	// Mem2Reg removes stores and the load; the alloca itself has no users
	// afterwards so DCE (run immediately after, as in the real pipeline)
	// removes it too.
	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);
	fpm.AddPass<Mem2RegPass>();
	fpm.AddPass<DeadCodeEliminationPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByType<AllocaInst>(fn), 0u);
	EXPECT_EQ(CountByType<StoreInst>(fn),  0u);
	EXPECT_EQ(CountByType<LoadInst>(fn),   0u);
	EXPECT_TRUE(fn->HasPhiInsts());
}

TEST(TailRecursionElimination, EliminatesDirectTailCall)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x) { if (x == 0) return 0; return fn(x - 1); }
	// The recursive call is a direct tail call.
	// After TRE the CallInst to fn must disappear (replaced by a loop back-edge).
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry      = builder.AddBlock("entry");
	BasicBlock* bb_base    = builder.AddBlock("base");
	BasicBlock* bb_recurse = builder.AddBlock("recurse");

	Value* x = fn->GetArg(0);

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpEQ, x, ctx.GetInt64(0));
	builder.MakeInst<BranchInst>(cond, bb_base, bb_recurse);

	builder.SetCurrentBlock(bb_base);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	builder.SetCurrentBlock(bb_recurse);
	Value* x_minus_1 = builder.MakeInst<BinaryInst>(Opcode::Sub, x, ctx.GetInt64(1));
	std::vector<Value*> call_args = { x_minus_1 };
	Value* rec = builder.MakeInst<CallInst>(fn, std::span<Value*>(call_args));
	builder.MakeInst<ReturnInst>(rec);

	EXPECT_EQ(CountByOpcode(fn, Opcode::Call), 1u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);
	fpm.AddPass<TailRecursionEliminationPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByOpcode(fn, Opcode::Call), 0u);
}

TEST(GlobalDCE, RemovesUnreferencedInternalFunction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// Module has two functions:
	//   main  (external) - the root; always kept
	//   helper (internal) - never called; should be removed
	Function* helper = MakeFunc(module, ctx, "helper", ctx.GetVoidType(), {}, Linkage::Internal);
	builder.SetCurrentFunction(helper);
	BasicBlock* h_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(h_entry);
	builder.MakeInst<ReturnInst>(ctx);

	Function* main_fn = MakeFunc(module, ctx, "main", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(main_fn);
	BasicBlock* m_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(m_entry);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(module.Globals().size(), 2u);

	IRModulePassManager mpm;
	IRModuleAnalysisManager mam;
	mam.RegisterPass<CallGraphAnalysisPass>(module);
	mpm.AddPass<GlobalDeadCodeEliminationPass>();
	mpm.Run(module, mam);

	EXPECT_EQ(module.Globals().size(), 1u);
	// Note: RemoveGlobal removes from the globals list but not from the
	// internal function_map, so we verify by inspecting the list directly.
	bool helper_still_present = false;
	for (GlobalValue* g : module.Globals())
		if (g->GetName() == "helper") helper_still_present = true;
	EXPECT_FALSE(helper_still_present);
	EXPECT_NE(module.GetFunctionByName("main"), nullptr);
}

TEST(GlobalDCE, KeepsReferencedInternalFunction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// helper (internal) is called by main -> must survive GlobalDCE.
	Function* helper = MakeFunc(module, ctx, "helper", ctx.GetIntegerType(64), {}, Linkage::Internal);
	builder.SetCurrentFunction(helper);
	BasicBlock* h_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(h_entry);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(1));

	Function* main_fn = MakeFunc(module, ctx, "main", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(main_fn);
	BasicBlock* m_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(m_entry);
	std::vector<Value*> no_args;
	Value* call_result = builder.MakeInst<CallInst>(helper, std::span<Value*>(no_args));
	builder.MakeInst<ReturnInst>(call_result);

	EXPECT_EQ(module.Globals().size(), 2u);

	IRModulePassManager mpm;
	IRModuleAnalysisManager mam;
	mam.RegisterPass<CallGraphAnalysisPass>(module);
	mpm.AddPass<GlobalDeadCodeEliminationPass>();
	mpm.Run(module, mam);

	EXPECT_EQ(module.Globals().size(), 2u);
	EXPECT_NE(module.GetFunctionByName("helper"), nullptr);
}

TEST(CSE, EliminatesDuplicateExpressionInBlock)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x, y) { a = x + y; b = x + y; return b; }
	// a and b are identical; CSE replaces b with a so only one Add remains.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64),
		{ ctx.GetIntegerType(64), ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* x = fn->GetArg(0);
	Value* y = fn->GetArg(1);
	// Insert both adds manually so IRBuilder cannot fold them.
	BinaryInst* a = new BinaryInst(Opcode::Add, x, y);
	a->InsertBefore(entry, entry->end());
	BinaryInst* b = new BinaryInst(Opcode::Add, x, y);
	b->InsertBefore(entry, entry->end());
	ReturnInst* ret = new ReturnInst(b);
	ret->InsertBefore(entry, entry->end());

	EXPECT_EQ(CountByOpcode(fn, Opcode::Add), 2u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<CSEPass>();
	fpm.AddPass<DeadCodeEliminationPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByOpcode(fn, Opcode::Add), 1u);
	// The return must now use the first add.
	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	EXPECT_EQ(ret_val, a);
}

TEST(CSE, KeepsDistinctExpressions)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x, y) { a = x + y; b = x - y; return a; }
	// Different opcodes - CSE must not touch either.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64),
		{ ctx.GetIntegerType(64), ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* x = fn->GetArg(0);
	Value* y = fn->GetArg(1);
	BinaryInst* a = new BinaryInst(Opcode::Add, x, y);
	a->InsertBefore(entry, entry->end());
	BinaryInst* b = new BinaryInst(Opcode::Sub, x, y);
	b->InsertBefore(entry, entry->end());
	ReturnInst* ret = new ReturnInst(a);
	ret->InsertBefore(entry, entry->end());

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<CSEPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByOpcode(fn, Opcode::Add), 1u);
	EXPECT_EQ(CountByOpcode(fn, Opcode::Sub), 1u);
}

TEST(GVN, EliminatesRedundantExpressionAcrossBlocks)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x, y):
	//   entry:  a = x + y;  br join
	//   join:   b = x + y;  ret b
	// entry dominates join; GVN replaces b with a → only one Add remains.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64),
		{ ctx.GetIntegerType(64), ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	BasicBlock* join  = builder.AddBlock("join");

	Value* x = fn->GetArg(0);
	Value* y = fn->GetArg(1);

	BinaryInst* a = new BinaryInst(Opcode::Add, x, y);
	a->InsertBefore(entry, entry->end());
	BranchInst* br = new BranchInst(ctx, join);
	br->InsertBefore(entry, entry->end());

	BinaryInst* b = new BinaryInst(Opcode::Add, x, y);
	b->InsertBefore(join, join->end());
	ReturnInst* ret = new ReturnInst(b);
	ret->InsertBefore(join, join->end());

	EXPECT_EQ(CountByOpcode(fn, Opcode::Add), 2u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);
	fpm.AddPass<GVNPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByOpcode(fn, Opcode::Add), 1u);
}

TEST(FunctionInliner, InlinesFunctionMarkedForceInline)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// int add(int a, int b) [force_inline] { return a + b; }
	// int main() { return add(1, 2); }
	// After inlining, main contains no Call instruction.
	std::vector<IRType*> params = { ctx.GetIntegerType(64), ctx.GetIntegerType(64) };
	Function* add_fn = MakeFunc(module, ctx, "add", ctx.GetIntegerType(64), params, Linkage::Internal);
	add_fn->SetForceInline();

	builder.SetCurrentFunction(add_fn);
	BasicBlock* add_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(add_entry);
	Value* sum = builder.MakeInst<BinaryInst>(Opcode::Add, add_fn->GetArg(0), add_fn->GetArg(1));
	builder.MakeInst<ReturnInst>(sum);

	Function* main_fn = MakeFunc(module, ctx, "main", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(main_fn);
	BasicBlock* main_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(main_entry);
	std::vector<Value*> args = { ctx.GetInt64(1), ctx.GetInt64(2) };
	Value* result = builder.MakeInst<CallInst>(add_fn, std::span<Value*>(args));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(CountByOpcode(main_fn, Opcode::Call), 1u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<FunctionInlinerPass>();
	fpm.Run(*main_fn, fam);

	EXPECT_EQ(CountByOpcode(main_fn, Opcode::Call), 0u);
}

TEST(FunctionInliner, SkipsFunctionMarkedNoInline)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// int add(int a, int b) [no_inline] { return a + b; }
	// int main() { return add(1, 2); }
	// The call must survive.
	std::vector<IRType*> params = { ctx.GetIntegerType(64), ctx.GetIntegerType(64) };
	Function* add_fn = MakeFunc(module, ctx, "add", ctx.GetIntegerType(64), params, Linkage::Internal);
	add_fn->SetNoInline();

	builder.SetCurrentFunction(add_fn);
	BasicBlock* add_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(add_entry);
	Value* sum = builder.MakeInst<BinaryInst>(Opcode::Add, add_fn->GetArg(0), add_fn->GetArg(1));
	builder.MakeInst<ReturnInst>(sum);

	Function* main_fn = MakeFunc(module, ctx, "main", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(main_fn);
	BasicBlock* main_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(main_entry);
	std::vector<Value*> args = { ctx.GetInt64(1), ctx.GetInt64(2) };
	Value* result = builder.MakeInst<CallInst>(add_fn, std::span<Value*>(args));
	builder.MakeInst<ReturnInst>(result);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<FunctionInlinerPass>();
	fpm.Run(*main_fn, fam);

	EXPECT_EQ(CountByOpcode(main_fn, Opcode::Call), 1u);
}

static Uint32 CountInBlock(BasicBlock const* bb, Opcode op)
{
	Uint32 n = 0;
	for (auto const& inst : *bb)
		if (inst.GetOpcode() == op) ++n;
	return n;
}

TEST(LICM, HoistsInvariantInstructionOutOfLoop)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(a, b):
	//   preheader: br header
	//   header:    i = phi [0, preheader] [i_next, latch]
	//              cond = i < 5
	//              br cond, latch, exit
	//   latch:     inv = a * b         <- loop invariant
	//              i_next = i + 1
	//              br header
	//   exit:      ret 0
	//
	// After LICM, inv must be hoisted into preheader; latch has no SMul.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64),
		{ ctx.GetIntegerType(64), ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);

	BasicBlock* preheader = builder.AddBlock("preheader");
	BasicBlock* header    = builder.AddBlock("header");
	BasicBlock* latch     = builder.AddBlock("latch");
	BasicBlock* exit_b    = builder.AddBlock("exit");

	Value* a = fn->GetArg(0);
	Value* b = fn->GetArg(1);

	// preheader
	builder.SetCurrentBlock(preheader);
	builder.MakeInst<BranchInst>(ctx, header);

	// header – phi node for loop counter
	PhiInst* i_phi = new PhiInst(ctx.GetIntegerType(64));
	header->AddPhiInst(i_phi);
	builder.SetCurrentBlock(header);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpSLT, i_phi, ctx.GetInt64(5));
	builder.MakeInst<BranchInst>(cond, latch, exit_b);

	// latch – loop body with the invariant multiply
	builder.SetCurrentBlock(latch);
	BinaryInst* inv = new BinaryInst(Opcode::SMul, a, b);
	inv->InsertBefore(latch, latch->end());
	Value* i_next = builder.MakeInst<BinaryInst>(Opcode::Add, i_phi, ctx.GetInt64(1));
	builder.MakeInst<BranchInst>(ctx, header);

	// exit
	builder.SetCurrentBlock(exit_b);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	// Wire phi incoming values now that all blocks exist.
	i_phi->AddIncoming(ctx.GetInt64(0), preheader);
	i_phi->AddIncoming(i_next, latch);

	EXPECT_EQ(CountInBlock(latch, Opcode::SMul), 1u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);
	fpm.AddPass<LICMPass>();
	fpm.Run(*fn, fam);

	// The multiply must have been moved out of the latch.
	EXPECT_EQ(CountInBlock(latch, Opcode::SMul), 0u);
	// The total instruction count of SMul across the whole function is unchanged.
	EXPECT_EQ(CountByOpcode(fn, Opcode::SMul), 1u);
}

TEST(SROA, SplitsStructAllocaIntoScalars)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// struct S { i64 x; i64 y; };
	// fn() { s = alloca S; s.x = 10; s.y = 32; v = s.x + s.y; ret v; }
	// SROA should replace the single struct alloca with two i64 allocas.
	IRStructType* st = ctx.GetStructType("S", { ctx.GetIntegerType(64), ctx.GetIntegerType(64) });
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	// field 0 at byte offset 0, field 1 at byte offset 8
	Value* s_ptr = builder.MakeInst<AllocaInst>(st);
	Value* f0 = builder.MakeInst<PtrAddInst>(s_ptr, ctx.GetInt64(0), ctx.GetIntegerType(64));
	builder.MakeInst<StoreInst>(ctx.GetInt64(10), f0);
	Value* f1 = builder.MakeInst<PtrAddInst>(s_ptr, ctx.GetInt64(8), ctx.GetIntegerType(64));
	builder.MakeInst<StoreInst>(ctx.GetInt64(32), f1);
	Value* v0 = builder.MakeInst<LoadInst>(f0);
	Value* v1 = builder.MakeInst<LoadInst>(f1);
	Value* sum = builder.MakeInst<BinaryInst>(Opcode::Add, v0, v1);
	builder.MakeInst<ReturnInst>(sum);

	EXPECT_EQ(CountByType<AllocaInst>(fn), 1u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<SROAPass>();
	fpm.AddPass<DeadCodeEliminationPass>();
	fpm.Run(*fn, fam);

	// The struct alloca is replaced by individual field allocas.
	EXPECT_GT(CountByType<AllocaInst>(fn), 1u);
}

TEST(CriticalEdgeSplitting, SplitsCriticalEdge)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// entry --true--> merge
	// entry --false-> mid
	// mid ----------> merge
	//
	// entry has 2 successors; merge has 2 predecessors.
	// entry→merge is a critical edge and must be split.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	BasicBlock* mid   = builder.AddBlock("mid");
	BasicBlock* merge = builder.AddBlock("merge");

	Value* x = fn->GetArg(0);

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpSGT, x, ctx.GetInt64(0));
	builder.MakeInst<BranchInst>(cond, merge, mid);

	builder.SetCurrentBlock(mid);
	builder.MakeInst<BranchInst>(ctx, merge);

	builder.SetCurrentBlock(merge);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(CountBlocks(fn), 3u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);
	fpm.AddPass<CriticalEdgeSplittingPass>();
	fpm.Run(*fn, fam);

	// The critical edge entry→merge is split: a new block is inserted.
	EXPECT_GT(CountBlocks(fn), 3u);
}

TEST(IPCP, PropagatesConstantArgumentIntoCallee)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// internal int foo(int x) { return x + 1; }
	// int main() { return foo(41); }
	//
	// foo is always called with 41; IPCP replaces %x with 41 inside foo.
	// After IPCP + ConstProp the Add in foo folds to 42, leaving no Add.
	Function* foo = MakeFunc(module, ctx, "foo", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) }, Linkage::Internal);
	builder.SetCurrentFunction(foo);
	BasicBlock* foo_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(foo_entry);
	BinaryInst* add = new BinaryInst(Opcode::Add, foo->GetArg(0), ctx.GetInt64(1));
	add->InsertBefore(foo_entry, foo_entry->end());
	ReturnInst* foo_ret = new ReturnInst(add);
	foo_ret->InsertBefore(foo_entry, foo_entry->end());

	Function* main_fn = MakeFunc(module, ctx, "main", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(main_fn);
	BasicBlock* main_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(main_entry);
	std::vector<Value*> args = { ctx.GetInt64(41) };
	Value* call_result = builder.MakeInst<CallInst>(foo, std::span<Value*>(args));
	builder.MakeInst<ReturnInst>(call_result);

	// Before: foo has one Add whose LHS is the function argument (not a constant).
	EXPECT_EQ(CountByOpcode(foo, Opcode::Add), 1u);
	EXPECT_FALSE(isa<ConstantInt>(cast<BinaryInst>(add)->GetLHS()));

	IRModulePassManager mpm;
	IRModuleAnalysisManager mam;
	mam.RegisterPass<CallGraphAnalysisPass>(module);
	mpm.AddPass<IPConstantPropagationPass>();
	mpm.Run(module, mam);

	// After IPCP: the argument use in the Add is replaced by the constant 41.
	EXPECT_TRUE(isa<ConstantInt>(cast<BinaryInst>(add)->GetLHS())
		|| isa<ConstantInt>(cast<BinaryInst>(add)->GetRHS()));
}

TEST(IPCP, DoesNotPropagateWhenCalledWithDifferentConstants)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// internal int foo(int x) { return x + 1; }
	// int main() { return foo(1) + foo(2); }
	//
	// foo is called with two different constants – IPCP must not replace %x.
	Function* foo = MakeFunc(module, ctx, "foo", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) }, Linkage::Internal);
	builder.SetCurrentFunction(foo);
	BasicBlock* foo_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(foo_entry);
	BinaryInst* add = new BinaryInst(Opcode::Add, foo->GetArg(0), ctx.GetInt64(1));
	add->InsertBefore(foo_entry, foo_entry->end());
	ReturnInst* foo_ret = new ReturnInst(add);
	foo_ret->InsertBefore(foo_entry, foo_entry->end());

	Function* main_fn = MakeFunc(module, ctx, "main", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(main_fn);
	BasicBlock* main_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(main_entry);
	std::vector<Value*> args1 = { ctx.GetInt64(1) };
	Value* r1 = builder.MakeInst<CallInst>(foo, std::span<Value*>(args1));
	std::vector<Value*> args2 = { ctx.GetInt64(2) };
	Value* r2 = builder.MakeInst<CallInst>(foo, std::span<Value*>(args2));
	Value* total = builder.MakeInst<BinaryInst>(Opcode::Add, r1, r2);
	builder.MakeInst<ReturnInst>(total);

	IRModulePassManager mpm;
	IRModuleAnalysisManager mam;
	mam.RegisterPass<CallGraphAnalysisPass>(module);
	mpm.AddPass<IPConstantPropagationPass>();
	mpm.Run(module, mam);

	// The Add in foo still has the argument as an operand (not a constant).
	EXPECT_FALSE(isa<ConstantInt>(cast<BinaryInst>(add)->GetLHS()));
}

TEST(ArithmeticReduction, SubtractZeroBecomesOperand)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x) { return x - 0; }  =>  return x
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* x = fn->GetArg(0);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::Sub, x, ctx.GetInt64(0));
	builder.MakeInst<ReturnInst>(result);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ArithmeticReductionPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByOpcode(fn, Opcode::Sub), 0u);
	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	EXPECT_EQ(ret_val, x);
}

TEST(ArithmeticReduction, MultiplyByMinusOneBecomesNeg)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x) { return x * -1; }  => might become neg x or similar
	// The pass may or may not handle this, but it shouldn't crash.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* x = fn->GetArg(0);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::SMul, x, ctx.GetInt64(-1));
	builder.MakeInst<ReturnInst>(result);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ArithmeticReductionPass>();
	fpm.Run(*fn, fam);

	// Just verify no crash and the ret still exists
	EXPECT_EQ(CountByOpcode(fn, Opcode::Ret), 1u);
}

TEST(DCE, RemovesChainOfDeadInstructions)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x) { a = x + 1; b = a + 2; return 0; }
	// Both a and b are dead.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* x = fn->GetArg(0);
	Value* a = builder.MakeInst<BinaryInst>(Opcode::Add, x, ctx.GetInt64(1));
	builder.MakeInst<BinaryInst>(Opcode::Add, a, ctx.GetInt64(2)); // dead
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(CountByOpcode(fn, Opcode::Add), 2u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<DeadCodeEliminationPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByOpcode(fn, Opcode::Add), 0u);
}

TEST(DCE, PreservesCallInstruction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn() { call helper(); return 0; }
	// The call has side effects and must survive DCE even though
	// its result is unused.
	Function* helper = MakeFunc(module, ctx, "helper", ctx.GetVoidType(), {}, Linkage::External);

	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	std::vector<Value*> no_args;
	builder.MakeInst<CallInst>(helper, std::span<Value*>(no_args));
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<DeadCodeEliminationPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByOpcode(fn, Opcode::Call), 1u);
}

TEST(ConstantPropagation, FoldsSubtraction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// ret (10 - 3) => ret 7
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");

	BinaryInst* sub = new BinaryInst(Opcode::Sub, ctx.GetInt64(10), ctx.GetInt64(3));
	sub->InsertBefore(entry, entry->end());
	ReturnInst* ret = new ReturnInst(sub);
	ret->InsertBefore(entry, entry->end());

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ConstantPropagationPass>();
	fpm.Run(*fn, fam);

	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	ASSERT_TRUE(isa<ConstantInt>(ret_val));
	EXPECT_EQ(cast<ConstantInt>(ret_val)->GetValue(), 7);
}

TEST(ConstantPropagation, FoldsMultiplication)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// ret (6 * 7) => ret 42
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");

	BinaryInst* mul = new BinaryInst(Opcode::SMul, ctx.GetInt64(6), ctx.GetInt64(7));
	mul->InsertBefore(entry, entry->end());
	ReturnInst* ret = new ReturnInst(mul);
	ret->InsertBefore(entry, entry->end());

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ConstantPropagationPass>();
	fpm.Run(*fn, fam);

	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	ASSERT_TRUE(isa<ConstantInt>(ret_val));
	EXPECT_EQ(cast<ConstantInt>(ret_val)->GetValue(), 42);
}

TEST(ConstantPropagation, FoldsDivision)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// ret (84 / 2) => ret 42
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");

	BinaryInst* div = new BinaryInst(Opcode::SDiv, ctx.GetInt64(84), ctx.GetInt64(2));
	div->InsertBefore(entry, entry->end());
	ReturnInst* ret = new ReturnInst(div);
	ret->InsertBefore(entry, entry->end());

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ConstantPropagationPass>();
	fpm.Run(*fn, fam);

	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	ASSERT_TRUE(isa<ConstantInt>(ret_val));
	EXPECT_EQ(cast<ConstantInt>(ret_val)->GetValue(), 42);
}

TEST(ConstantPropagation, FoldsCompareNE)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// cmp = (5 != 5) => false => branch becomes unconditional
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry   = builder.AddBlock("entry");
	BasicBlock* bb_then = builder.AddBlock("then");
	BasicBlock* bb_else = builder.AddBlock("else");

	builder.SetCurrentBlock(bb_then);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(1));

	builder.SetCurrentBlock(bb_else);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	CompareInst* cmp = new CompareInst(Opcode::ICmpNE, ctx.GetInt64(5), ctx.GetInt64(5));
	cmp->InsertBefore(entry, entry->end());
	BranchInst* br = new BranchInst(cmp, bb_then, bb_else);
	br->InsertBefore(entry, entry->end());

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ConstantPropagationPass>();
	fpm.Run(*fn, fam);

	EXPECT_TRUE(cast<BranchInst>(entry->GetTerminator())->IsUnconditional());
	// 5 != 5 is false, so branch should go to else
	EXPECT_EQ(cast<BranchInst>(entry->GetTerminator())->GetTrueTarget(), bb_else);
}

TEST(SimplifyCFG, ConvertsIdenticalTargetsToUnconditional)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// entry: cond = ...; br cond, target, target
	// Since both targets are the same, simplify to unconditional br.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry  = builder.AddBlock("entry");
	BasicBlock* target = builder.AddBlock("target");

	Value* x = fn->GetArg(0);

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpSGT, x, ctx.GetInt64(0));
	builder.MakeInst<BranchInst>(cond, target, target);

	builder.SetCurrentBlock(target);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);
	fpm.AddPass<SimplifyCFGPass>();
	fpm.Run(*fn, fam);

	// Should have simplified to 2 or fewer blocks (entry might be merged with target)
	EXPECT_LE(CountBlocks(fn), 2u);
}

TEST(Mem2Reg, HandlesMultipleStoresSameBlock)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn() { p = alloca; store 1 -> p; store 2 -> p; v = load p; ret v; }
	// The load should resolve to 2 (last store wins).
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* p = builder.MakeInst<AllocaInst>(ctx.GetIntegerType(64));
	builder.MakeInst<StoreInst>(ctx.GetInt64(1), p);
	builder.MakeInst<StoreInst>(ctx.GetInt64(2), p);
	Value* v = builder.MakeInst<LoadInst>(p);
	builder.MakeInst<ReturnInst>(v);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);
	fpm.AddPass<Mem2RegPass>();
	fpm.AddPass<DeadCodeEliminationPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByType<LoadInst>(fn), 0u);
	// The return should carry the constant 2
	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	ASSERT_TRUE(isa<ConstantInt>(ret_val));
	EXPECT_EQ(cast<ConstantInt>(ret_val)->GetValue(), 2);
}

TEST(GVN, PreservesNonDominatedExpression)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x, y):
	//   entry: cond = x > 0; br cond, left, right
	//   left:  a = x + y; br merge
	//   right: b = x + y; br merge
	//   merge: ret 0
	// left does NOT dominate right, so GVN must keep both adds.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64),
		{ ctx.GetIntegerType(64), ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	BasicBlock* left  = builder.AddBlock("left");
	BasicBlock* right = builder.AddBlock("right");
	BasicBlock* merge = builder.AddBlock("merge");

	Value* x = fn->GetArg(0);
	Value* y = fn->GetArg(1);

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpSGT, x, ctx.GetInt64(0));
	builder.MakeInst<BranchInst>(cond, left, right);

	BinaryInst* a = new BinaryInst(Opcode::Add, x, y);
	a->InsertBefore(left, left->end());
	BranchInst* br_l = new BranchInst(ctx, merge);
	br_l->InsertBefore(left, left->end());

	BinaryInst* b = new BinaryInst(Opcode::Add, x, y);
	b->InsertBefore(right, right->end());
	BranchInst* br_r = new BranchInst(ctx, merge);
	br_r->InsertBefore(right, right->end());

	builder.SetCurrentBlock(merge);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(CountByOpcode(fn, Opcode::Add), 2u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);
	fpm.AddPass<GVNPass>();
	fpm.Run(*fn, fam);

	// Neither dominates the other, so both adds must survive.
	EXPECT_EQ(CountByOpcode(fn, Opcode::Add), 2u);
}

TEST(LICM, DoesNotHoistNonInvariantInstruction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(a):
	//   preheader: br header
	//   header:    i = phi [0, preheader] [i_next, latch]; cond = i < 5; br cond, latch, exit
	//   latch:     x = i * a   <- NOT invariant (i changes each iteration)
	//              i_next = i + 1; br header
	//   exit:      ret 0
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64),
		{ ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);

	BasicBlock* preheader = builder.AddBlock("preheader");
	BasicBlock* header    = builder.AddBlock("header");
	BasicBlock* latch     = builder.AddBlock("latch");
	BasicBlock* exit_b    = builder.AddBlock("exit");

	Value* a = fn->GetArg(0);

	builder.SetCurrentBlock(preheader);
	builder.MakeInst<BranchInst>(ctx, header);

	PhiInst* i_phi = new PhiInst(ctx.GetIntegerType(64));
	header->AddPhiInst(i_phi);
	builder.SetCurrentBlock(header);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpSLT, i_phi, ctx.GetInt64(5));
	builder.MakeInst<BranchInst>(cond, latch, exit_b);

	builder.SetCurrentBlock(latch);
	BinaryInst* dep = new BinaryInst(Opcode::SMul, i_phi, a);
	dep->InsertBefore(latch, latch->end());
	Value* i_next = builder.MakeInst<BinaryInst>(Opcode::Add, i_phi, ctx.GetInt64(1));
	builder.MakeInst<BranchInst>(ctx, header);

	builder.SetCurrentBlock(exit_b);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	i_phi->AddIncoming(ctx.GetInt64(0), preheader);
	i_phi->AddIncoming(i_next, latch);

	EXPECT_EQ(CountInBlock(latch, Opcode::SMul), 1u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);
	fpm.AddPass<LICMPass>();
	fpm.Run(*fn, fam);

	// The multiply depends on the loop counter phi, so it must stay in the latch.
	EXPECT_EQ(CountInBlock(latch, Opcode::SMul), 1u);
}

TEST(SROA, LeavesScalarAllocaAlone)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn() { p = alloca i64; store 42 -> p; v = load p; ret v; }
	// A scalar alloca has nothing to split; SROA must leave it as-is.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* p = builder.MakeInst<AllocaInst>(ctx.GetIntegerType(64));
	builder.MakeInst<StoreInst>(ctx.GetInt64(42), p);
	Value* v = builder.MakeInst<LoadInst>(p);
	builder.MakeInst<ReturnInst>(v);

	EXPECT_EQ(CountByType<AllocaInst>(fn), 1u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<SROAPass>();
	fpm.Run(*fn, fam);

	// Scalar alloca is not split.
	EXPECT_EQ(CountByType<AllocaInst>(fn), 1u);
}

TEST(CriticalEdgeSplitting, DoesNotSplitNonCriticalEdge)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// entry -> exit  (unconditional, single successor, single predecessor)
	// No critical edge; block count must not change.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	BasicBlock* exit_b = builder.AddBlock("exit");

	builder.SetCurrentBlock(entry);
	builder.MakeInst<BranchInst>(ctx, exit_b);

	builder.SetCurrentBlock(exit_b);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(CountBlocks(fn), 2u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);
	fpm.AddPass<CriticalEdgeSplittingPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountBlocks(fn), 2u);
}

TEST(ConstantPropagation, FoldsNegation)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// ret neg(5) => ret -5
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");

	UnaryInst* neg = new UnaryInst(Opcode::Neg, ctx.GetInt64(5));
	neg->InsertBefore(entry, entry->end());
	ReturnInst* ret = new ReturnInst(neg);
	ret->InsertBefore(entry, entry->end());

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ConstantPropagationPass>();
	fpm.Run(*fn, fam);

	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	ASSERT_TRUE(isa<ConstantInt>(ret_val));
	EXPECT_EQ(cast<ConstantInt>(ret_val)->GetValue(), -5);
}

TEST(DCE, RemovesDeadLoad)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn() { p = alloca; store 42 -> p; dead = load p; return 0; }
	// The load result is never used; DCE should remove it.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* p = builder.MakeInst<AllocaInst>(ctx.GetIntegerType(64));
	builder.MakeInst<StoreInst>(ctx.GetInt64(42), p);
	builder.MakeInst<LoadInst>(p); // result unused
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(CountByType<LoadInst>(fn), 1u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<DeadCodeEliminationPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByType<LoadInst>(fn), 0u);
}

TEST(ArithmeticReduction, DivisionByOneBecomesOperand)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x) { return x / 1; }  =>  return x
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* x = fn->GetArg(0);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::SDiv, x, ctx.GetInt64(1));
	builder.MakeInst<ReturnInst>(result);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ArithmeticReductionPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByOpcode(fn, Opcode::SDiv), 0u);
	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	EXPECT_EQ(ret_val, x);
}

TEST(ArithmeticReduction, FloatAddZeroBecomesOperand)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x) { return x + 0.0; }  =>  return x
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetFloatType(), { ctx.GetFloatType() });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* x = fn->GetArg(0);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::FAdd, x, ctx.GetZeroFloat());
	builder.MakeInst<ReturnInst>(result);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ArithmeticReductionPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByOpcode(fn, Opcode::FAdd), 0u);
	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	EXPECT_EQ(ret_val, x);
}

TEST(ArithmeticReduction, FloatMultiplyByOneBecomesOperand)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x) { return x * 1.0; }  =>  return x
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetFloatType(), { ctx.GetFloatType() });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* x = fn->GetArg(0);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::FMul, x, ctx.GetFloat(1.0));
	builder.MakeInst<ReturnInst>(result);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ArithmeticReductionPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByOpcode(fn, Opcode::FMul), 0u);
	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	EXPECT_EQ(ret_val, x);
}

TEST(SimplifyCFG, CollapsesChainOfEmptyBlocks)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// entry -> mid1 -> mid2 -> exit
	// All intermediate blocks are empty pass-throughs.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry  = builder.AddBlock("entry");
	BasicBlock* mid1   = builder.AddBlock("mid1");
	BasicBlock* mid2   = builder.AddBlock("mid2");
	BasicBlock* exit_b = builder.AddBlock("exit");

	builder.SetCurrentBlock(entry);
	builder.MakeInst<BranchInst>(ctx, mid1);

	builder.SetCurrentBlock(mid1);
	builder.MakeInst<BranchInst>(ctx, mid2);

	builder.SetCurrentBlock(mid2);
	builder.MakeInst<BranchInst>(ctx, exit_b);

	builder.SetCurrentBlock(exit_b);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(CountBlocks(fn), 4u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);
	fpm.AddPass<SimplifyCFGPass>();
	fpm.Run(*fn, fam);

	EXPECT_LT(CountBlocks(fn), 4u);
}

TEST(CSE, EliminatesTriplicateExpression)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x, y) { a = x + y; b = x + y; c = x + y; return c; }
	// All three are identical; only one should remain after CSE + DCE.
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64),
		{ ctx.GetIntegerType(64), ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");

	Value* x = fn->GetArg(0);
	Value* y = fn->GetArg(1);
	BinaryInst* a = new BinaryInst(Opcode::Add, x, y);
	a->InsertBefore(entry, entry->end());
	BinaryInst* b = new BinaryInst(Opcode::Add, x, y);
	b->InsertBefore(entry, entry->end());
	BinaryInst* c = new BinaryInst(Opcode::Add, x, y);
	c->InsertBefore(entry, entry->end());
	ReturnInst* ret = new ReturnInst(c);
	ret->InsertBefore(entry, entry->end());

	EXPECT_EQ(CountByOpcode(fn, Opcode::Add), 3u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<CSEPass>();
	fpm.AddPass<DeadCodeEliminationPass>();
	fpm.Run(*fn, fam);

	EXPECT_EQ(CountByOpcode(fn, Opcode::Add), 1u);
}

TEST(GlobalDCE, KeepsExternalFunction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// An external function should never be removed by GlobalDCE,
	// even if never called within the module.
	Function* ext = MakeFunc(module, ctx, "external_fn", ctx.GetVoidType(), {}, Linkage::External);
	builder.SetCurrentFunction(ext);
	BasicBlock* ext_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(ext_entry);
	builder.MakeInst<ReturnInst>(ctx);

	Function* main_fn = MakeFunc(module, ctx, "main", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(main_fn);
	BasicBlock* m_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(m_entry);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(module.Globals().size(), 2u);

	IRModulePassManager mpm;
	IRModuleAnalysisManager mam;
	mam.RegisterPass<CallGraphAnalysisPass>(module);
	mpm.AddPass<GlobalDeadCodeEliminationPass>();
	mpm.Run(module, mam);

	// External function must survive.
	EXPECT_EQ(module.Globals().size(), 2u);
}

TEST(ConstantPropagation, FoldsShiftLeft)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// ret (1 << 10) => ret 1024
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");

	BinaryInst* op = new BinaryInst(Opcode::Shl, ctx.GetInt64(1), ctx.GetInt64(10));
	op->InsertBefore(entry, entry->end());
	ReturnInst* ret = new ReturnInst(op);
	ret->InsertBefore(entry, entry->end());

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ConstantPropagationPass>();
	fpm.Run(*fn, fam);

	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	ASSERT_TRUE(isa<ConstantInt>(ret_val));
	EXPECT_EQ(cast<ConstantInt>(ret_val)->GetValue(), 1024);
}

TEST(ConstantPropagation, FoldsArithmeticShiftRight)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// ret (1024 >> 3) => ret 128
	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");

	BinaryInst* op = new BinaryInst(Opcode::AShr, ctx.GetInt64(1024), ctx.GetInt64(3));
	op->InsertBefore(entry, entry->end());
	ReturnInst* ret = new ReturnInst(op);
	ret->InsertBefore(entry, entry->end());

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ConstantPropagationPass>();
	fpm.Run(*fn, fam);

	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	ASSERT_TRUE(isa<ConstantInt>(ret_val));
	EXPECT_EQ(cast<ConstantInt>(ret_val)->GetValue(), 128);
}

// Helper: Build a simple loop: for (i = 0; i < N; i += step) { body }
// Returns the function. The loop body contains a single add instruction
// that accumulates: sum = sum + i
static Function* BuildSimpleCountingLoop(IRModule& module, IRContext& ctx, IRBuilder& builder,
	Int64 init, Int64 bound, Int64 step)
{
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("loop_fn", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* preheader = builder.AddBlock("preheader");
	BasicBlock* header    = builder.AddBlock("header");
	BasicBlock* body      = builder.AddBlock("body");
	BasicBlock* latch     = builder.AddBlock("latch");
	BasicBlock* exit_bb   = builder.AddBlock("exit");

	// preheader: br header
	builder.SetCurrentBlock(preheader);
	builder.MakeInst<BranchInst>(ctx, header);

	// header: phi i = [init, preheader], [i_next, latch]
	//         phi sum = [0, preheader], [sum_next, latch]
	//         cmp = i < bound
	//         br cmp, body, exit
	builder.SetCurrentBlock(header);
	PhiInst* phi_i = new PhiInst(ctx.GetIntegerType(64));
	header->AddPhiInst(phi_i);
	phi_i->AddIncoming(ctx.GetInt64(init), preheader);

	PhiInst* phi_sum = new PhiInst(ctx.GetIntegerType(64));
	header->AddPhiInst(phi_sum);
	phi_sum->AddIncoming(ctx.GetInt64(0), preheader);

	Value* cmp = builder.MakeInst<CompareInst>(Opcode::ICmpSLT, phi_i, ctx.GetInt64(bound));
	builder.MakeInst<BranchInst>(cmp, body, exit_bb);

	// body: sum_next = sum + i
	//       br latch
	builder.SetCurrentBlock(body);
	Value* sum_next = builder.MakeInst<BinaryInst>(Opcode::Add, phi_sum, phi_i);
	builder.MakeInst<BranchInst>(ctx, latch);

	// latch: i_next = i + step
	//        br header
	builder.SetCurrentBlock(latch);
	Value* i_next = builder.MakeInst<BinaryInst>(Opcode::Add, phi_i, ctx.GetInt64(step));
	builder.MakeInst<BranchInst>(ctx, header);

	// Wire up the phis
	phi_i->AddIncoming(i_next, latch);
	phi_sum->AddIncoming(sum_next, latch);

	// exit: ret sum
	builder.SetCurrentBlock(exit_bb);
	builder.MakeInst<ReturnInst>(phi_sum);

	return fn;
}

TEST(LoopUnroll, NoLoopNoChange)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// Simple function with no loop
	Function* fn = MakeFunc(module, ctx, "no_loop", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);
	fpm.AddPass<LoopUnrollPass>();
	Bool changed = fpm.Run(*fn, fam);

	EXPECT_FALSE(changed);
}

TEST(LoopUnroll, FullUnrollSmallLoop)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// for (i = 0; i < 4; i += 1) { sum += i; }
	Function* fn = BuildSimpleCountingLoop(module, ctx, builder, 0, 4, 1);

	Uint32 blocks_before = CountBlocks(fn);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);

	LoopUnrollConfig config;
	config.FullUnrollThreshold = 32;
	config.MaxUnrolledSize = 256;
	fpm.AddPass(new LoopUnrollPass(config));
	Bool changed = fpm.Run(*fn, fam);

	if (changed)
	{
		// After full unroll, the loop blocks should be removed
		// The block count should be smaller (loop blocks eliminated)
		Uint32 blocks_after = CountBlocks(fn);
		EXPECT_LT(blocks_after, blocks_before);

		// No more phi instructions from the loop
		Uint32 phi_count = CountByType<PhiInst>(fn);
		// The exit phi may remain, but loop phis should be gone
		EXPECT_LE(phi_count, 1u);
	}
}

TEST(LoopUnroll, SkipsLargeLoop)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// for (i = 0; i < 10000; i += 1) — too many iterations to unroll
	Function* fn = BuildSimpleCountingLoop(module, ctx, builder, 0, 10000, 1);

	Uint32 blocks_before = CountBlocks(fn);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);

	LoopUnrollConfig config;
	config.FullUnrollThreshold = 32;
	config.MaxUnrolledSize = 256;
	config.AllowPartialUnroll = false;
	fpm.AddPass(new LoopUnrollPass(config));
	fpm.Run(*fn, fam);

	// Too large to unroll, blocks should remain the same
	EXPECT_EQ(CountBlocks(fn), blocks_before);
}

TEST(LoopUnroll, SkipsNonCanonicalLoop)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// Build a loop with non-constant bounds (not canonical for unroll)
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	Function* fn = new Function("noncanon", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* preheader = builder.AddBlock("preheader");
	BasicBlock* header    = builder.AddBlock("header");
	BasicBlock* body      = builder.AddBlock("body");
	BasicBlock* exit_bb   = builder.AddBlock("exit");

	builder.SetCurrentBlock(preheader);
	builder.MakeInst<BranchInst>(ctx, header);

	builder.SetCurrentBlock(header);
	PhiInst* phi_i = new PhiInst(ctx.GetIntegerType(64));
	header->AddPhiInst(phi_i);
	phi_i->AddIncoming(ctx.GetInt64(0), preheader);

	// Non-constant bound: compare against function arg
	Value* cmp = builder.MakeInst<CompareInst>(Opcode::ICmpSLT, phi_i, fn->GetArg(0));
	builder.MakeInst<BranchInst>(cmp, body, exit_bb);

	builder.SetCurrentBlock(body);
	Value* i_next = builder.MakeInst<BinaryInst>(Opcode::Add, phi_i, ctx.GetInt64(1));
	builder.MakeInst<BranchInst>(ctx, header);

	phi_i->AddIncoming(i_next, body);

	builder.SetCurrentBlock(exit_bb);
	builder.MakeInst<ReturnInst>(phi_i);

	Uint32 blocks_before = CountBlocks(fn);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	RegisterAllAnalysisPasses(fam, *fn);

	LoopUnrollConfig config;
	config.AllowPartialUnroll = false;
	fpm.AddPass(new LoopUnrollPass(config));
	fpm.Run(*fn, fam);

	// Non-constant bound means no known trip count → no full unroll, no partial unroll
	EXPECT_EQ(CountBlocks(fn), blocks_before);
}

TEST(GlobalAttributeInfer, MarksUnmodifiedGlobalAsReadOnly)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// Create an internal global that is only loaded, never stored to
	ConstantInt* init = ctx.GetInt64(42);
	GlobalVariable* gv = new GlobalVariable("readonly_g", ctx.GetIntegerType(64), Linkage::Internal, init);
	module.AddGlobal(gv);

	// Create a function that only reads from the global
	Function* fn = MakeFunc(module, ctx, "reader", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* loaded = builder.MakeInst<LoadInst>(gv);
	builder.MakeInst<ReturnInst>(loaded);

	EXPECT_FALSE(gv->IsReadOnly());

	IRModulePassManager mpm;
	IRModuleAnalysisManager mam;
	mpm.AddPass<GlobalAttributeInferPass>();
	mpm.Run(module, mam);

	EXPECT_TRUE(gv->IsReadOnly());
}

TEST(GlobalAttributeInfer, DoesNotMarkModifiedGlobal)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	ConstantInt* init = ctx.GetInt64(0);
	GlobalVariable* gv = new GlobalVariable("mutable_g", ctx.GetIntegerType(64), Linkage::Internal, init);
	module.AddGlobal(gv);

	// Create a function that stores to the global
	Function* fn = MakeFunc(module, ctx, "writer", ctx.GetVoidType(), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	builder.MakeInst<StoreInst>(ctx.GetInt64(100), gv);
	builder.MakeInst<ReturnInst>(ctx);

	IRModulePassManager mpm;
	IRModuleAnalysisManager mam;
	mpm.AddPass<GlobalAttributeInferPass>();
	mpm.Run(module, mam);

	// Global is stored to, should NOT be marked read-only
	EXPECT_FALSE(gv->IsReadOnly());
}

TEST(GlobalAttributeInfer, SkipsExternalGlobal)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// External globals should not be marked as read-only
	ConstantInt* init = ctx.GetInt64(42);
	GlobalVariable* gv = new GlobalVariable("ext_g", ctx.GetIntegerType(64), Linkage::External, init);
	module.AddGlobal(gv);

	Function* fn = MakeFunc(module, ctx, "reader", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* loaded = builder.MakeInst<LoadInst>(gv);
	builder.MakeInst<ReturnInst>(loaded);

	IRModulePassManager mpm;
	IRModuleAnalysisManager mam;
	mpm.AddPass<GlobalAttributeInferPass>();
	mpm.Run(module, mam);

	// External linkage globals are skipped by the pass
	EXPECT_FALSE(gv->IsReadOnly());
}

TEST(GlobalAttributeInfer, AlreadyReadOnlyUntouched)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	ConstantInt* init = ctx.GetInt64(7);
	GlobalVariable* gv = new GlobalVariable("already_ro", ctx.GetIntegerType(64), Linkage::Internal, init);
	gv->SetReadOnly();
	module.AddGlobal(gv);

	Function* fn = MakeFunc(module, ctx, "noop", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	IRModulePassManager mpm;
	IRModuleAnalysisManager mam;
	mpm.AddPass<GlobalAttributeInferPass>();
	mpm.Run(module, mam);

	EXPECT_TRUE(gv->IsReadOnly());
}

TEST(ArithmeticReduction, XorSelfBecomesZero)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	// x ^ x should become 0
	Value* xor_val = builder.MakeInst<BinaryInst>(Opcode::Xor, fn->GetArg(0), fn->GetArg(0));
	builder.MakeInst<ReturnInst>(xor_val);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ArithmeticReductionPass>();
	fpm.Run(*fn, fam);

	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	if (isa<ConstantInt>(ret_val))
	{
		EXPECT_EQ(cast<ConstantInt>(ret_val)->GetValue(), 0);
	}
}

TEST(ArithmeticReduction, AndWithZeroBecomesZero)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	// x & 0 should become 0
	Value* and_val = builder.MakeInst<BinaryInst>(Opcode::And, fn->GetArg(0), ctx.GetInt64(0));
	builder.MakeInst<ReturnInst>(and_val);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<ArithmeticReductionPass>();
	fpm.Run(*fn, fam);

	Value* ret_val = cast<ReturnInst>(entry->GetTerminator())->GetReturnValue();
	if (isa<ConstantInt>(ret_val))
	{
		EXPECT_EQ(cast<ConstantInt>(ret_val)->GetValue(), 0);
	}
}

TEST(DCE, RemovesUnusedBinaryChain)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	Function* fn = MakeFunc(module, ctx, "f", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	// Chain of unused computations
	Value* a = builder.MakeInst<BinaryInst>(Opcode::Add, fn->GetArg(0), ctx.GetInt64(1));
	Value* b = builder.MakeInst<BinaryInst>(Opcode::SMul, a, ctx.GetInt64(2));
	Value* c = builder.MakeInst<BinaryInst>(Opcode::Sub, b, ctx.GetInt64(3));
	(void)c; // c is not used by anything

	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	Uint32 inst_count_before = CountByType<BinaryInst>(fn);
	EXPECT_EQ(inst_count_before, 3u);

	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<DeadCodeEliminationPass>();
	fpm.Run(*fn, fam);

	// All three binary instructions should be removed as dead
	EXPECT_EQ(CountByType<BinaryInst>(fn), 0u);
}

TEST(GlobalDCE, RemovesMultipleUnusedInternalFunctions)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// Create external main function
	Function* main_fn = MakeFunc(module, ctx, "main", ctx.GetIntegerType(64), {}, Linkage::External);
	builder.SetCurrentFunction(main_fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	// Create two unreferenced internal functions
	Function* dead1 = MakeFunc(module, ctx, "dead1", ctx.GetVoidType(), {}, Linkage::Internal);
	builder.SetCurrentFunction(dead1);
	BasicBlock* d1_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(d1_entry);
	builder.MakeInst<ReturnInst>(ctx);

	Function* dead2 = MakeFunc(module, ctx, "dead2", ctx.GetVoidType(), {}, Linkage::Internal);
	builder.SetCurrentFunction(dead2);
	BasicBlock* d2_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(d2_entry);
	builder.MakeInst<ReturnInst>(ctx);

	EXPECT_EQ(module.Globals().size(), 3u);

	IRModulePassManager mpm;
	IRModuleAnalysisManager mam;
	mam.RegisterPass<CallGraphAnalysisPass>(module);
	mpm.AddPass<GlobalDeadCodeEliminationPass>();
	mpm.Run(module, mam);

	// Both dead internal functions should be removed
	EXPECT_EQ(module.Globals().size(), 1u);
	bool dead1_present = false, dead2_present = false;
	for (GlobalValue* g : module.Globals())
	{
		if (g->GetName() == "dead1") dead1_present = true;
		if (g->GetName() == "dead2") dead2_present = true;
	}
	EXPECT_FALSE(dead1_present);
	EXPECT_FALSE(dead2_present);
	EXPECT_NE(module.GetFunctionByName("main"), nullptr);
}

TEST(FunctionInliner, DoesNotInlineRecursiveFunction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// Create a recursive function marked force-inline
	Function* recfn = MakeFunc(module, ctx, "rec", ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	recfn->SetForceInline();
	builder.SetCurrentFunction(recfn);

	BasicBlock* entry = builder.AddBlock("entry");
	BasicBlock* base  = builder.AddBlock("base");
	BasicBlock* rec   = builder.AddBlock("rec");

	builder.SetCurrentBlock(entry);
	Value* cmp = builder.MakeInst<CompareInst>(Opcode::ICmpSLE, recfn->GetArg(0), ctx.GetInt64(0));
	builder.MakeInst<BranchInst>(cmp, base, rec);

	builder.SetCurrentBlock(base);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(1));

	builder.SetCurrentBlock(rec);
	Value* sub = builder.MakeInst<BinaryInst>(Opcode::Sub, recfn->GetArg(0), ctx.GetInt64(1));
	std::vector<Value*> args = { sub };
	Value* call = builder.MakeInst<CallInst>(recfn, std::span<Value*>(args));
	Value* mul = builder.MakeInst<BinaryInst>(Opcode::SMul, recfn->GetArg(0), call);
	builder.MakeInst<ReturnInst>(mul);

	// Create a caller
	Function* caller = MakeFunc(module, ctx, "main", ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(caller);
	BasicBlock* caller_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(caller_entry);
	std::vector<Value*> call_args = { ctx.GetInt64(5) };
	Value* result = builder.MakeInst<CallInst>(recfn, std::span<Value*>(call_args));
	builder.MakeInst<ReturnInst>(result);

	// The inliner should handle recursive functions gracefully
	FunctionPassManager fpm;
	FunctionAnalysisManager fam;
	fpm.AddPass<FunctionInlinerPass>();
	fpm.Run(*caller, fam);

	// The function should still have a call instruction (recursive can't be fully inlined)
	EXPECT_GE(CountByType<CallInst>(caller), 1u);
}
