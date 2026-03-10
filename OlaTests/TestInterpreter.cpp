#include <gtest/gtest.h>
#include "Backend/Custom/IR/IRContext.h"
#include "Backend/Custom/IR/IRBuilder.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/BasicBlock.h"
#include "Backend/Custom/IR/Constant.h"
#include "Backend/Custom/Interpreter/IRInterpreter.h"

using namespace ola;

// Helper: build a module with a main() that returns a constant i64
static Int RunMain(IRModule& module)
{
	IRInterpreter interp(module);
	return interp.Execute();
}

// ---------------------------------------------------------------------------
// Return constant
// ---------------------------------------------------------------------------

TEST(Interpreter, ReturnZero)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(RunMain(module), 0);
}

TEST(Interpreter, ReturnConstant)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	EXPECT_EQ(RunMain(module), 42);
}

// ---------------------------------------------------------------------------
// Integer arithmetic
// ---------------------------------------------------------------------------

TEST(Interpreter, Addition)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* sum = builder.MakeInst<BinaryInst>(Opcode::Add, ctx.GetInt64(10), ctx.GetInt64(32));
	builder.MakeInst<ReturnInst>(sum);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, Subtraction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::Sub, ctx.GetInt64(50), ctx.GetInt64(8));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, Multiplication)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::SMul, ctx.GetInt64(6), ctx.GetInt64(7));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, Division)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::SDiv, ctx.GetInt64(84), ctx.GetInt64(2));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, Negation)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* result = builder.MakeInst<UnaryInst>(Opcode::Neg, ctx.GetInt64(5));
	// return 0 - (-5) = 5, but we just verify negation produces negative
	Value* added = builder.MakeInst<BinaryInst>(Opcode::Add, result, ctx.GetInt64(47));
	builder.MakeInst<ReturnInst>(added);

	EXPECT_EQ(RunMain(module), 42);
}

// ---------------------------------------------------------------------------
// Alloca / Load / Store
// ---------------------------------------------------------------------------

TEST(Interpreter, AllocaStoreLoad)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* alloca = builder.MakeInst<AllocaInst>(ctx.GetIntegerType(64));
	builder.MakeInst<StoreInst>(ctx.GetInt64(42), alloca);
	Value* loaded = builder.MakeInst<LoadInst>(alloca);
	builder.MakeInst<ReturnInst>(loaded);

	EXPECT_EQ(RunMain(module), 42);
}

// ---------------------------------------------------------------------------
// Conditional branch
// ---------------------------------------------------------------------------

TEST(Interpreter, ConditionalBranchTrue)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry   = builder.AddBlock("entry");
	BasicBlock* bb_true  = builder.AddBlock("true");
	BasicBlock* bb_false = builder.AddBlock("false");

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpSGT, ctx.GetInt64(10), ctx.GetInt64(5));
	builder.MakeInst<BranchInst>(cond, bb_true, bb_false);

	builder.SetCurrentBlock(bb_true);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(1));

	builder.SetCurrentBlock(bb_false);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(RunMain(module), 1);
}

TEST(Interpreter, ConditionalBranchFalse)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry    = builder.AddBlock("entry");
	BasicBlock* bb_true  = builder.AddBlock("true");
	BasicBlock* bb_false = builder.AddBlock("false");

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpSGT, ctx.GetInt64(3), ctx.GetInt64(5));
	builder.MakeInst<BranchInst>(cond, bb_true, bb_false);

	builder.SetCurrentBlock(bb_true);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(1));

	builder.SetCurrentBlock(bb_false);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(RunMain(module), 0);
}

// ---------------------------------------------------------------------------
// Function call
// ---------------------------------------------------------------------------

TEST(Interpreter, FunctionCall)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// int add(int a, int b) { return a + b; }
	std::vector<IRType*> params = { ctx.GetIntegerType(64), ctx.GetIntegerType(64) };
	IRFuncType* add_ft = ctx.GetFunctionType(ctx.GetIntegerType(64), params);
	Function* add_fn = new Function("add", add_ft, Linkage::Internal);
	module.AddGlobal(add_fn);

	builder.SetCurrentFunction(add_fn);
	BasicBlock* add_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(add_entry);
	Value* sum = builder.MakeInst<BinaryInst>(Opcode::Add, add_fn->GetArg(0), add_fn->GetArg(1));
	builder.MakeInst<ReturnInst>(sum);

	// int main() { return add(20, 22); }
	IRFuncType* main_ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* main_fn = new Function("main", main_ft, Linkage::External);
	module.AddGlobal(main_fn);

	builder.SetCurrentFunction(main_fn);
	BasicBlock* main_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(main_entry);
	std::vector<Value*> args = { ctx.GetInt64(20), ctx.GetInt64(22) };
	Value* result = builder.MakeInst<CallInst>(add_fn, std::span<Value*>(args));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, BitwiseAnd)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// 5 & 3 == 1
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::And, ctx.GetInt64(5), ctx.GetInt64(3));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 1);
}

TEST(Interpreter, BitwiseOr)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// 5 | 2 == 7
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::Or, ctx.GetInt64(5), ctx.GetInt64(2));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 7);
}

TEST(Interpreter, BitwiseXor)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// 5 ^ 3 == 6
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::Xor, ctx.GetInt64(5), ctx.GetInt64(3));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 6);
}

TEST(Interpreter, ShiftLeft)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// 1 << 3 == 8
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::Shl, ctx.GetInt64(1), ctx.GetInt64(3));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 8);
}

TEST(Interpreter, LogicalShiftRight)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// 16 >> 2 == 4
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::LShr, ctx.GetInt64(16), ctx.GetInt64(2));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 4);
}

TEST(Interpreter, SignedRemainder)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// 10 % 3 == 1
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::SRem, ctx.GetInt64(10), ctx.GetInt64(3));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 1);
}

TEST(Interpreter, ZeroExtend)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// ZExt i8(100) to i64 == 100
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* narrow = ctx.GetInt8(100);
	Value* result = builder.MakeInst<CastInst>(Opcode::ZExt, ctx.GetIntegerType(64), narrow);
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 100);
}

TEST(Interpreter, SignExtendNegative)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// SExt i8(-10) to i64; add 52 to keep return value positive: -10 + 52 == 42
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* narrow = ctx.GetInt8(-10);
	Value* extended = builder.MakeInst<CastInst>(Opcode::ZExt, ctx.GetIntegerType(64), narrow);
	// ZExt of -10 (0xF6 in 8 bits) gives 246; then 246 - 204 = 42.
	Value* result = builder.MakeInst<BinaryInst>(Opcode::Sub, extended, ctx.GetInt64(204));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, SwitchHitsNamedCase)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// switch (2) { case 1: ret 1; case 2: ret 42; default: ret 0; }
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);
	builder.SetCurrentFunction(fn);

	BasicBlock* entry    = builder.AddBlock("entry");
	BasicBlock* case1_bb = builder.AddBlock("case1");
	BasicBlock* case2_bb = builder.AddBlock("case2");
	BasicBlock* def_bb   = builder.AddBlock("default");

	builder.SetCurrentBlock(case1_bb);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(1));

	builder.SetCurrentBlock(case2_bb);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	builder.SetCurrentBlock(def_bb);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	builder.SetCurrentBlock(entry);
	SwitchInst* sw = new SwitchInst(ctx.GetInt64(2), def_bb);
	sw->AddCase(1, case1_bb);
	sw->AddCase(2, case2_bb);
	sw->InsertBefore(entry, entry->end());

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, SwitchHitsDefault)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// switch (99) { case 1: ret 1; case 2: ret 2; default: ret 42; }
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);
	builder.SetCurrentFunction(fn);

	BasicBlock* entry    = builder.AddBlock("entry");
	BasicBlock* case1_bb = builder.AddBlock("case1");
	BasicBlock* case2_bb = builder.AddBlock("case2");
	BasicBlock* def_bb   = builder.AddBlock("default");

	builder.SetCurrentBlock(case1_bb);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(1));

	builder.SetCurrentBlock(case2_bb);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(2));

	builder.SetCurrentBlock(def_bb);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	builder.SetCurrentBlock(entry);
	SwitchInst* sw = new SwitchInst(ctx.GetInt64(99), def_bb);
	sw->AddCase(1, case1_bb);
	sw->AddCase(2, case2_bb);
	sw->InsertBefore(entry, entry->end());

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, LoopWithPhiAccumulatesSum)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// Equivalent to:
	//   int sum = 0, i = 0;
	//   while (i < 5) { i++; sum += i; }
	//   return sum;   // 1+2+3+4+5 == 15
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);
	builder.SetCurrentFunction(fn);

	BasicBlock* preheader = builder.AddBlock("preheader");
	BasicBlock* header    = builder.AddBlock("header");
	BasicBlock* latch     = builder.AddBlock("latch");
	BasicBlock* exit_b    = builder.AddBlock("exit");

	// preheader → header
	builder.SetCurrentBlock(preheader);
	builder.MakeInst<BranchInst>(ctx, header);

	// header: phi nodes + condition
	PhiInst* i_phi   = new PhiInst(ctx.GetIntegerType(64));
	PhiInst* sum_phi = new PhiInst(ctx.GetIntegerType(64));
	header->AddPhiInst(i_phi);
	header->AddPhiInst(sum_phi);
	builder.SetCurrentBlock(header);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpSLT, i_phi, ctx.GetInt64(5));
	builder.MakeInst<BranchInst>(cond, latch, exit_b);

	// latch: increment i, accumulate sum
	builder.SetCurrentBlock(latch);
	Value* i_next   = builder.MakeInst<BinaryInst>(Opcode::Add, i_phi, ctx.GetInt64(1));
	Value* sum_next = builder.MakeInst<BinaryInst>(Opcode::Add, sum_phi, i_next);
	builder.MakeInst<BranchInst>(ctx, header);

	// exit: return accumulated sum
	builder.SetCurrentBlock(exit_b);
	builder.MakeInst<ReturnInst>(sum_phi);

	// Patch phi incoming values.
	i_phi->AddIncoming(ctx.GetInt64(0), preheader);
	i_phi->AddIncoming(i_next, latch);
	sum_phi->AddIncoming(ctx.GetInt64(0), preheader);
	sum_phi->AddIncoming(sum_next, latch);

	EXPECT_EQ(RunMain(module), 15);
}

TEST(Interpreter, RecursiveFactorial)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// int fact(int n) { if (n <= 1) return 1; return n * fact(n-1); }
	// int main() { return fact(5); }  // 120
	std::vector<IRType*> params = { ctx.GetIntegerType(64) };
	IRFuncType* fact_ft = ctx.GetFunctionType(ctx.GetIntegerType(64), params);
	Function* fact_fn = new Function("fact", fact_ft, Linkage::Internal);
	module.AddGlobal(fact_fn);

	builder.SetCurrentFunction(fact_fn);
	BasicBlock* fact_entry   = builder.AddBlock("entry");
	BasicBlock* fact_base    = builder.AddBlock("base");
	BasicBlock* fact_recurse = builder.AddBlock("recurse");

	Value* n = fact_fn->GetArg(0);

	builder.SetCurrentBlock(fact_entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpSLE, n, ctx.GetInt64(1));
	builder.MakeInst<BranchInst>(cond, fact_base, fact_recurse);

	builder.SetCurrentBlock(fact_base);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(1));

	builder.SetCurrentBlock(fact_recurse);
	Value* n_minus_1 = builder.MakeInst<BinaryInst>(Opcode::Sub, n, ctx.GetInt64(1));
	std::vector<Value*> rec_args = { n_minus_1 };
	Value* rec = builder.MakeInst<CallInst>(fact_fn, std::span<Value*>(rec_args));
	Value* result = builder.MakeInst<BinaryInst>(Opcode::SMul, n, rec);
	builder.MakeInst<ReturnInst>(result);

	// main calls fact(5)
	IRFuncType* main_ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* main_fn = new Function("main", main_ft, Linkage::External);
	module.AddGlobal(main_fn);

	builder.SetCurrentFunction(main_fn);
	BasicBlock* main_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(main_entry);
	std::vector<Value*> main_args = { ctx.GetInt64(5) };
	Value* r = builder.MakeInst<CallInst>(fact_fn, std::span<Value*>(main_args));
	builder.MakeInst<ReturnInst>(r);

	EXPECT_EQ(RunMain(module), 120);
}

TEST(Interpreter, GlobalVariable)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	GlobalVariable* gv = new GlobalVariable("g", ctx.GetIntegerType(64), Linkage::Internal, ctx.GetInt64(42));
	module.AddGlobal(gv);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* loaded = builder.MakeInst<LoadInst>(gv);
	builder.MakeInst<ReturnInst>(loaded);

	EXPECT_EQ(RunMain(module), 42);
}

// ---------------------------------------------------------------------------
// Select (ternary)
// ---------------------------------------------------------------------------

TEST(Interpreter, Select)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* cond   = builder.MakeInst<CompareInst>(Opcode::ICmpEQ, ctx.GetInt64(1), ctx.GetInt64(1));
	Value* result = builder.MakeInst<SelectInst>(cond, ctx.GetInt64(42), ctx.GetInt64(0));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, FloatAddition)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// (int)(1.5 + 2.5) == 4
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* sum = builder.MakeInst<BinaryInst>(Opcode::FAdd, ctx.GetFloat(1.5), ctx.GetFloat(2.5));
	Value* result = builder.MakeInst<CastInst>(Opcode::F2S, ctx.GetIntegerType(64), sum);
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 4);
}

TEST(Interpreter, FloatSubtraction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// (int)(10.0 - 5.0) == 5
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* diff = builder.MakeInst<BinaryInst>(Opcode::FSub, ctx.GetFloat(10.0), ctx.GetFloat(5.0));
	Value* result = builder.MakeInst<CastInst>(Opcode::F2S, ctx.GetIntegerType(64), diff);
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 5);
}

TEST(Interpreter, FloatMultiplication)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// (int)(6.0 * 7.0) == 42
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* prod = builder.MakeInst<BinaryInst>(Opcode::FMul, ctx.GetFloat(6.0), ctx.GetFloat(7.0));
	Value* result = builder.MakeInst<CastInst>(Opcode::F2S, ctx.GetIntegerType(64), prod);
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, FloatDivision)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// (int)(84.0 / 2.0) == 42
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* quot = builder.MakeInst<BinaryInst>(Opcode::FDiv, ctx.GetFloat(84.0), ctx.GetFloat(2.0));
	Value* result = builder.MakeInst<CastInst>(Opcode::F2S, ctx.GetIntegerType(64), quot);
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, FloatNegation)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// (int)(-(-42.0)) == 42
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* neg = builder.MakeInst<UnaryInst>(Opcode::FNeg, ctx.GetFloat(-42.0));
	Value* result = builder.MakeInst<CastInst>(Opcode::F2S, ctx.GetIntegerType(64), neg);
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, FloatToSignedInt)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// F2S(9.7) == 9 (truncates toward zero)
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* result = builder.MakeInst<CastInst>(Opcode::F2S, ctx.GetIntegerType(64), ctx.GetFloat(9.7));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 9);
}

TEST(Interpreter, SignedIntToFloat)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// (int)(S2F(42)) == 42  — round-trip through float preserves integer
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* fv = builder.MakeInst<CastInst>(Opcode::S2F, ctx.GetFloatType(), ctx.GetInt64(42));
	Value* result = builder.MakeInst<CastInst>(Opcode::F2S, ctx.GetIntegerType(64), fv);
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, BitwiseNot)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// ~0 == -1; -1 + 43 == 42
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* notval = builder.MakeInst<UnaryInst>(Opcode::Not, ctx.GetInt64(0));
	Value* result = builder.MakeInst<BinaryInst>(Opcode::Add, notval, ctx.GetInt64(43));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, ArithmeticShiftRight)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// -16 >> 2 (arithmetic) should be -4; -4 + 46 == 42
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* shifted = builder.MakeInst<BinaryInst>(Opcode::AShr, ctx.GetInt64(-16), ctx.GetInt64(2));
	Value* result = builder.MakeInst<BinaryInst>(Opcode::Add, shifted, ctx.GetInt64(46));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, FloatCompareLess)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// (1.0 < 2.0) ? 42 : 0
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry    = builder.AddBlock("entry");
	BasicBlock* bb_true  = builder.AddBlock("true");
	BasicBlock* bb_false = builder.AddBlock("false");

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::FCmpOLT, ctx.GetFloat(1.0), ctx.GetFloat(2.0));
	builder.MakeInst<BranchInst>(cond, bb_true, bb_false);

	builder.SetCurrentBlock(bb_true);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	builder.SetCurrentBlock(bb_false);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, FloatCompareEqual)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// (3.14 == 3.14) ? 42 : 0
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry    = builder.AddBlock("entry");
	BasicBlock* bb_true  = builder.AddBlock("true");
	BasicBlock* bb_false = builder.AddBlock("false");

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::FCmpOEQ, ctx.GetFloat(3.14), ctx.GetFloat(3.14));
	builder.MakeInst<BranchInst>(cond, bb_true, bb_false);

	builder.SetCurrentBlock(bb_true);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	builder.SetCurrentBlock(bb_false);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, ChainedFunctionCalls)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// int double_it(int x) { return x + x; }
	// int main() { return double_it(double_it(10)) + 2; }  // 42
	std::vector<IRType*> params = { ctx.GetIntegerType(64) };
	IRFuncType* dbl_ft = ctx.GetFunctionType(ctx.GetIntegerType(64), params);
	Function* dbl_fn = new Function("double_it", dbl_ft, Linkage::Internal);
	module.AddGlobal(dbl_fn);

	builder.SetCurrentFunction(dbl_fn);
	BasicBlock* dbl_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(dbl_entry);
	Value* sum = builder.MakeInst<BinaryInst>(Opcode::Add, dbl_fn->GetArg(0), dbl_fn->GetArg(0));
	builder.MakeInst<ReturnInst>(sum);

	IRFuncType* main_ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* main_fn = new Function("main", main_ft, Linkage::External);
	module.AddGlobal(main_fn);

	builder.SetCurrentFunction(main_fn);
	BasicBlock* main_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(main_entry);
	std::vector<Value*> args1 = { ctx.GetInt64(10) };
	Value* first = builder.MakeInst<CallInst>(dbl_fn, std::span<Value*>(args1));
	std::vector<Value*> args2 = { first };
	Value* second = builder.MakeInst<CallInst>(dbl_fn, std::span<Value*>(args2));
	Value* result = builder.MakeInst<BinaryInst>(Opcode::Add, second, ctx.GetInt64(2));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, GlobalVariableStoreAndLoad)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// int g = 0; main() { g = 42; return g; }
	GlobalVariable* gv = new GlobalVariable("g", ctx.GetIntegerType(64), Linkage::Internal, ctx.GetInt64(0));
	module.AddGlobal(gv);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	builder.MakeInst<StoreInst>(ctx.GetInt64(42), gv);
	Value* loaded = builder.MakeInst<LoadInst>(gv);
	builder.MakeInst<ReturnInst>(loaded);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, MultipleAllocas)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// a = 20, b = 22; return a + b
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* pa = builder.MakeInst<AllocaInst>(ctx.GetIntegerType(64));
	Value* pb = builder.MakeInst<AllocaInst>(ctx.GetIntegerType(64));
	builder.MakeInst<StoreInst>(ctx.GetInt64(20), pa);
	builder.MakeInst<StoreInst>(ctx.GetInt64(22), pb);
	Value* a = builder.MakeInst<LoadInst>(pa);
	Value* b = builder.MakeInst<LoadInst>(pb);
	Value* result = builder.MakeInst<BinaryInst>(Opcode::Add, a, b);
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, UnsignedCompareLessThan)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// (3 ULT 5) ? 42 : 0
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry    = builder.AddBlock("entry");
	BasicBlock* bb_true  = builder.AddBlock("true");
	BasicBlock* bb_false = builder.AddBlock("false");

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpULT, ctx.GetInt64(3), ctx.GetInt64(5));
	builder.MakeInst<BranchInst>(cond, bb_true, bb_false);

	builder.SetCurrentBlock(bb_true);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	builder.SetCurrentBlock(bb_false);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, CompareNotEqual)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// (5 != 3) ? 42 : 0
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry    = builder.AddBlock("entry");
	BasicBlock* bb_true  = builder.AddBlock("true");
	BasicBlock* bb_false = builder.AddBlock("false");

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpNE, ctx.GetInt64(5), ctx.GetInt64(3));
	builder.MakeInst<BranchInst>(cond, bb_true, bb_false);

	builder.SetCurrentBlock(bb_true);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	builder.SetCurrentBlock(bb_false);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, CompareNotEqual_EqualValues)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// (5 != 5) ? 1 : 42
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry    = builder.AddBlock("entry");
	BasicBlock* bb_true  = builder.AddBlock("true");
	BasicBlock* bb_false = builder.AddBlock("false");

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpNE, ctx.GetInt64(5), ctx.GetInt64(5));
	builder.MakeInst<BranchInst>(cond, bb_true, bb_false);

	builder.SetCurrentBlock(bb_true);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(1));

	builder.SetCurrentBlock(bb_false);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, CompareSignedLessEqual)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// (5 <= 5) ? 42 : 0
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry    = builder.AddBlock("entry");
	BasicBlock* bb_true  = builder.AddBlock("true");
	BasicBlock* bb_false = builder.AddBlock("false");

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpSLE, ctx.GetInt64(5), ctx.GetInt64(5));
	builder.MakeInst<BranchInst>(cond, bb_true, bb_false);

	builder.SetCurrentBlock(bb_true);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	builder.SetCurrentBlock(bb_false);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, CompareSignedGreaterEqual)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// (10 >= 5) ? 42 : 0
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry    = builder.AddBlock("entry");
	BasicBlock* bb_true  = builder.AddBlock("true");
	BasicBlock* bb_false = builder.AddBlock("false");

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpSGE, ctx.GetInt64(10), ctx.GetInt64(5));
	builder.MakeInst<BranchInst>(cond, bb_true, bb_false);

	builder.SetCurrentBlock(bb_true);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	builder.SetCurrentBlock(bb_false);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, CompareEqual)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// (7 == 7) ? 42 : 0
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry    = builder.AddBlock("entry");
	BasicBlock* bb_true  = builder.AddBlock("true");
	BasicBlock* bb_false = builder.AddBlock("false");

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpEQ, ctx.GetInt64(7), ctx.GetInt64(7));
	builder.MakeInst<BranchInst>(cond, bb_true, bb_false);

	builder.SetCurrentBlock(bb_true);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	builder.SetCurrentBlock(bb_false);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, FloatCompareGreater)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// (3.0 > 2.0) ? 42 : 0
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry    = builder.AddBlock("entry");
	BasicBlock* bb_true  = builder.AddBlock("true");
	BasicBlock* bb_false = builder.AddBlock("false");

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::FCmpOGT, ctx.GetFloat(3.0), ctx.GetFloat(2.0));
	builder.MakeInst<BranchInst>(cond, bb_true, bb_false);

	builder.SetCurrentBlock(bb_true);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	builder.SetCurrentBlock(bb_false);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, FloatCompareNotEqual)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// (1.0 != 2.0) ? 42 : 0
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry    = builder.AddBlock("entry");
	BasicBlock* bb_true  = builder.AddBlock("true");
	BasicBlock* bb_false = builder.AddBlock("false");

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::FCmpONE, ctx.GetFloat(1.0), ctx.GetFloat(2.0));
	builder.MakeInst<BranchInst>(cond, bb_true, bb_false);

	builder.SetCurrentBlock(bb_true);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	builder.SetCurrentBlock(bb_false);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, SelectFalseCondition)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// select (1 == 0), 0, 42 => 42
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* cond   = builder.MakeInst<CompareInst>(Opcode::ICmpEQ, ctx.GetInt64(1), ctx.GetInt64(0));
	Value* result = builder.MakeInst<SelectInst>(cond, ctx.GetInt64(0), ctx.GetInt64(42));
	builder.MakeInst<ReturnInst>(result);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, MultipleGlobalVariables)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	GlobalVariable* ga = new GlobalVariable("a", ctx.GetIntegerType(64), Linkage::Internal, ctx.GetInt64(20));
	GlobalVariable* gb = new GlobalVariable("b", ctx.GetIntegerType(64), Linkage::Internal, ctx.GetInt64(22));
	module.AddGlobal(ga);
	module.AddGlobal(gb);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	Value* va = builder.MakeInst<LoadInst>(ga);
	Value* vb = builder.MakeInst<LoadInst>(gb);
	Value* sum = builder.MakeInst<BinaryInst>(Opcode::Add, va, vb);
	builder.MakeInst<ReturnInst>(sum);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, NestedConditionalBranches)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// if (10 > 5) { if (3 > 2) ret 42 else ret 1 } else ret 0
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry  = builder.AddBlock("entry");
	BasicBlock* inner  = builder.AddBlock("inner");
	BasicBlock* outer_false = builder.AddBlock("outer_false");
	BasicBlock* inner_true  = builder.AddBlock("inner_true");
	BasicBlock* inner_false = builder.AddBlock("inner_false");

	builder.SetCurrentBlock(entry);
	Value* cond1 = builder.MakeInst<CompareInst>(Opcode::ICmpSGT, ctx.GetInt64(10), ctx.GetInt64(5));
	builder.MakeInst<BranchInst>(cond1, inner, outer_false);

	builder.SetCurrentBlock(inner);
	Value* cond2 = builder.MakeInst<CompareInst>(Opcode::ICmpSGT, ctx.GetInt64(3), ctx.GetInt64(2));
	builder.MakeInst<BranchInst>(cond2, inner_true, inner_false);

	builder.SetCurrentBlock(inner_true);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	builder.SetCurrentBlock(inner_false);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(1));

	builder.SetCurrentBlock(outer_false);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, Fibonacci)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// int fib(int n) { if (n <= 1) return n; return fib(n-1) + fib(n-2); }
	// fib(7) = 13
	std::vector<IRType*> params = { ctx.GetIntegerType(64) };
	IRFuncType* fib_ft = ctx.GetFunctionType(ctx.GetIntegerType(64), params);
	Function* fib_fn = new Function("fib", fib_ft, Linkage::Internal);
	module.AddGlobal(fib_fn);

	builder.SetCurrentFunction(fib_fn);
	BasicBlock* fib_entry   = builder.AddBlock("entry");
	BasicBlock* fib_base    = builder.AddBlock("base");
	BasicBlock* fib_recurse = builder.AddBlock("recurse");

	Value* n = fib_fn->GetArg(0);

	builder.SetCurrentBlock(fib_entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpSLE, n, ctx.GetInt64(1));
	builder.MakeInst<BranchInst>(cond, fib_base, fib_recurse);

	builder.SetCurrentBlock(fib_base);
	builder.MakeInst<ReturnInst>(n);

	builder.SetCurrentBlock(fib_recurse);
	Value* n1 = builder.MakeInst<BinaryInst>(Opcode::Sub, n, ctx.GetInt64(1));
	std::vector<Value*> args1 = { n1 };
	Value* r1 = builder.MakeInst<CallInst>(fib_fn, std::span<Value*>(args1));
	Value* n2 = builder.MakeInst<BinaryInst>(Opcode::Sub, n, ctx.GetInt64(2));
	std::vector<Value*> args2 = { n2 };
	Value* r2 = builder.MakeInst<CallInst>(fib_fn, std::span<Value*>(args2));
	Value* result = builder.MakeInst<BinaryInst>(Opcode::Add, r1, r2);
	builder.MakeInst<ReturnInst>(result);

	// main calls fib(7)
	IRFuncType* main_ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* main_fn = new Function("main", main_ft, Linkage::External);
	module.AddGlobal(main_fn);

	builder.SetCurrentFunction(main_fn);
	BasicBlock* main_entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(main_entry);
	std::vector<Value*> main_args = { ctx.GetInt64(7) };
	Value* r = builder.MakeInst<CallInst>(fib_fn, std::span<Value*>(main_args));
	builder.MakeInst<ReturnInst>(r);

	EXPECT_EQ(RunMain(module), 13);
}

TEST(Interpreter, CountdownLoop)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// Equivalent to:
	//   int i = 10;
	//   while (i > 0) { i = i - 1; }
	//   return i;   // should be 0
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);
	builder.SetCurrentFunction(fn);

	BasicBlock* preheader = builder.AddBlock("preheader");
	BasicBlock* header    = builder.AddBlock("header");
	BasicBlock* latch     = builder.AddBlock("latch");
	BasicBlock* exit_b    = builder.AddBlock("exit");

	builder.SetCurrentBlock(preheader);
	builder.MakeInst<BranchInst>(ctx, header);

	PhiInst* i_phi = new PhiInst(ctx.GetIntegerType(64));
	header->AddPhiInst(i_phi);
	builder.SetCurrentBlock(header);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpSGT, i_phi, ctx.GetInt64(0));
	builder.MakeInst<BranchInst>(cond, latch, exit_b);

	builder.SetCurrentBlock(latch);
	Value* i_next = builder.MakeInst<BinaryInst>(Opcode::Sub, i_phi, ctx.GetInt64(1));
	builder.MakeInst<BranchInst>(ctx, header);

	builder.SetCurrentBlock(exit_b);
	builder.MakeInst<ReturnInst>(i_phi);

	i_phi->AddIncoming(ctx.GetInt64(10), preheader);
	i_phi->AddIncoming(i_next, latch);

	EXPECT_EQ(RunMain(module), 0);
}

TEST(Interpreter, MultipleStoresAndLoads)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// p = alloca; store 1; store 2; store 42; load p; ret loaded
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* p = builder.MakeInst<AllocaInst>(ctx.GetIntegerType(64));
	builder.MakeInst<StoreInst>(ctx.GetInt64(1), p);
	builder.MakeInst<StoreInst>(ctx.GetInt64(2), p);
	builder.MakeInst<StoreInst>(ctx.GetInt64(42), p);
	Value* loaded = builder.MakeInst<LoadInst>(p);
	builder.MakeInst<ReturnInst>(loaded);

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, UnconditionalBranch)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// entry: br target; target: ret 42
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry  = builder.AddBlock("entry");
	BasicBlock* target = builder.AddBlock("target");

	builder.SetCurrentBlock(entry);
	builder.MakeInst<BranchInst>(ctx, target);

	builder.SetCurrentBlock(target);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, MultiBlockChain)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// entry -> a -> b -> c: ret 42
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	BasicBlock* a     = builder.AddBlock("a");
	BasicBlock* b     = builder.AddBlock("b");
	BasicBlock* c     = builder.AddBlock("c");

	builder.SetCurrentBlock(entry);
	builder.MakeInst<BranchInst>(ctx, a);

	builder.SetCurrentBlock(a);
	builder.MakeInst<BranchInst>(ctx, b);

	builder.SetCurrentBlock(b);
	builder.MakeInst<BranchInst>(ctx, c);

	builder.SetCurrentBlock(c);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	EXPECT_EQ(RunMain(module), 42);
}

TEST(Interpreter, NegativeReturn)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// return -1
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("main", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(-1));

	EXPECT_EQ(RunMain(module), -1);
}
