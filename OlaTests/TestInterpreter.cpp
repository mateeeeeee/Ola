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

// ---------------------------------------------------------------------------
// Global variable
// ---------------------------------------------------------------------------

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
