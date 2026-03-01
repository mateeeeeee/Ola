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
