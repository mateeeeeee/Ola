#include <gtest/gtest.h>
#include "Backend/Custom/IR/IRContext.h"
#include "Backend/Custom/IR/IRBuilder.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/BasicBlock.h"
#include "Backend/Custom/IR/Constant.h"
#include "Backend/Custom/IR/IRVerifier.h"
#include "Utility/RTTI.h"

using namespace ola;

static Function* MakeTestFunc(IRModule& module, IRContext& ctx,
	std::string_view name, IRType* ret,
	std::vector<IRType*> const& params)
{
	IRFuncType* ft = ctx.GetFunctionType(ret, params);
	Function* fn = new Function(name, ft, Linkage::External);
	module.AddGlobal(fn);
	return fn;
}

TEST(IRVerifier, ValidSimpleFunction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn(x: i64) -> i64 { return x; }
	Function* fn = MakeTestFunc(module, ctx, "identity",
		ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);
	builder.MakeInst<ReturnInst>(fn->GetArg(0));

	IRVerifier v;
	EXPECT_TRUE(v.Verify(*fn));
	EXPECT_FALSE(v.HasErrors());
}

TEST(IRVerifier, MissingTerminator)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// fn() -> void { /* no terminator */ }
	Function* fn = MakeTestFunc(module, ctx, "no_term",
		ctx.GetVoidType(), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	// Add a non-terminator instruction but no return/branch
	Value* p = builder.MakeInst<AllocaInst>(ctx.GetIntegerType(64));

	IRVerifier v;
	EXPECT_FALSE(v.Verify(*fn));
	EXPECT_TRUE(v.HasErrors());
}

TEST(IRVerifier, InstructionAfterTerminator)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	Function* fn = MakeTestFunc(module, ctx, "bad_order",
		ctx.GetVoidType(), {});
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	// Insert return, then add another instruction after it
	builder.MakeInst<ReturnInst>(ctx);

	// Manually insert an instruction after the terminator
	AllocaInst* dead = new AllocaInst(ctx.GetIntegerType(64));
	dead->InsertBefore(entry, entry->end());

	IRVerifier v;
	EXPECT_FALSE(v.Verify(*fn));
	EXPECT_TRUE(v.HasErrors());
}

TEST(IRVerifier, ValidBranch)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	Function* fn = MakeTestFunc(module, ctx, "branch_test",
		ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);

	BasicBlock* entry = builder.AddBlock("entry");
	BasicBlock* then_bb = builder.AddBlock("then");
	BasicBlock* else_bb = builder.AddBlock("else");

	// entry: if (x > 0) goto then else goto else
	builder.SetCurrentBlock(entry);
	Value* x = fn->GetArg(0);
	Value* cmp = builder.MakeInst<CompareInst>(Opcode::ICmpSGT, x, ctx.GetInt64(0));
	builder.MakeInst<BranchInst>(cmp, then_bb, else_bb);

	// then: return 1
	builder.SetCurrentBlock(then_bb);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(1));

	// else: return 0
	builder.SetCurrentBlock(else_bb);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	IRVerifier v;
	EXPECT_TRUE(v.Verify(*fn));
	EXPECT_FALSE(v.HasErrors());
}

TEST(IRVerifier, BinaryOpTypeMismatch)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	Function* fn = MakeTestFunc(module, ctx, "type_mismatch",
		ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	// Manually create a binary op with mismatched types
	Value* x = fn->GetArg(0);
	Value* bad_rhs = ctx.GetInt8(1); // i8 vs i64
	BinaryInst* bad_add = new BinaryInst(Opcode::Add, x, x);
	bad_add->InsertBefore(entry, entry->end());
	// Now corrupt the operand to have mismatched types
	bad_add->SetOperand(1, bad_rhs);

	builder.MakeInst<ReturnInst>(ctx.GetInt64(0));

	IRVerifier v;
	EXPECT_FALSE(v.Verify(*fn));
	EXPECT_TRUE(v.HasErrors());
}

TEST(IRVerifier, ValidModuleVerification)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// Two valid functions in a module
	Function* fn1 = MakeTestFunc(module, ctx, "f1",
		ctx.GetVoidType(), {});
	builder.SetCurrentFunction(fn1);
	BasicBlock* entry1 = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry1);
	builder.MakeInst<ReturnInst>(ctx);

	Function* fn2 = MakeTestFunc(module, ctx, "f2",
		ctx.GetIntegerType(64), {});
	builder.SetCurrentFunction(fn2);
	BasicBlock* entry2 = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry2);
	builder.MakeInst<ReturnInst>(ctx.GetInt64(42));

	IRVerifier v;
	EXPECT_TRUE(v.Verify(module));
	EXPECT_FALSE(v.HasErrors());
}

TEST(IRVerifier, ModuleReportsErrorsAcrossFunctions)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	// First function: invalid (missing terminator)
	Function* fn1 = MakeTestFunc(module, ctx, "bad_func",
		ctx.GetVoidType(), {});
	builder.SetCurrentFunction(fn1);
	BasicBlock* entry1 = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry1);
	builder.MakeInst<AllocaInst>(ctx.GetIntegerType(64));

	// Second function: valid
	Function* fn2 = MakeTestFunc(module, ctx, "good_func",
		ctx.GetVoidType(), {});
	builder.SetCurrentFunction(fn2);
	BasicBlock* entry2 = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry2);
	builder.MakeInst<ReturnInst>(ctx);

	IRVerifier v;
	EXPECT_FALSE(v.Verify(module));
	EXPECT_TRUE(v.HasErrors());
}

TEST(IRVerifier, DeclarationSkipped)
{
	IRContext ctx;
	IRModule module(ctx, "test");

	// A declaration (no body) should not trigger errors
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetVoidType(), {});
	Function* decl = new Function("external_fn", ft, Linkage::External);
	// Don't add any blocks — it's a declaration
	module.AddGlobal(decl);

	IRVerifier v;
	EXPECT_TRUE(v.Verify(module));
	EXPECT_FALSE(v.HasErrors());
}
