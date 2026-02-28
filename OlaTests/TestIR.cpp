#include <gtest/gtest.h>
#include "Backend/Custom/IR/IRContext.h"
#include "Backend/Custom/IR/IRBuilder.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Value.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/BasicBlock.h"
#include "Backend/Custom/IR/Constant.h"
#include "Utility/RTTI.h"

using namespace ola;

TEST(IR, BuiltinTypes)
{
	IRContext ctx;
	EXPECT_NE(ctx.GetVoidType(),  nullptr);
	EXPECT_NE(ctx.GetFloatType(), nullptr);
	EXPECT_NE(ctx.GetLabelType(), nullptr);
}

TEST(IR, IntegerTypes)
{
	IRContext ctx;
	IRIntType* i64 = ctx.GetIntegerType(64);
	IRIntType* i8  = ctx.GetIntegerType(8);

	ASSERT_NE(i64, nullptr);
	ASSERT_NE(i8,  nullptr);
	EXPECT_NE(i64, i8);
}

TEST(IR, IntegerTypeInterning)
{
	IRContext ctx;
	EXPECT_EQ(ctx.GetIntegerType(64), ctx.GetIntegerType(64));
	EXPECT_EQ(ctx.GetIntegerType(8),  ctx.GetIntegerType(8));
}

TEST(IR, PointerType)
{
	IRContext ctx;
	IRPtrType* p = ctx.GetPointerType(ctx.GetIntegerType(64));
	ASSERT_NE(p, nullptr);
	EXPECT_EQ(p->GetPointeeType(), ctx.GetIntegerType(64));
}

TEST(IR, PointerTypeInterning)
{
	IRContext ctx;
	IRType* i64 = ctx.GetIntegerType(64);
	EXPECT_EQ(ctx.GetPointerType(i64), ctx.GetPointerType(i64));
}

TEST(IR, ArrayType)
{
	IRContext ctx;
	IRArrayType* arr = ctx.GetArrayType(ctx.GetIntegerType(8), 10);
	ASSERT_NE(arr, nullptr);
	EXPECT_EQ(arr->GetArraySize(), 10u);
	EXPECT_EQ(arr->GetElementType(), ctx.GetIntegerType(8));
}

TEST(IR, ArrayTypeInterning)
{
	IRContext ctx;
	IRType* i8 = ctx.GetIntegerType(8);
	EXPECT_EQ(ctx.GetArrayType(i8, 10), ctx.GetArrayType(i8, 10));
	EXPECT_NE(ctx.GetArrayType(i8, 10), ctx.GetArrayType(i8, 20));
}

TEST(IR, FunctionType)
{
	IRContext ctx;
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetVoidType(), {});
	ASSERT_NE(ft, nullptr);
	EXPECT_EQ(ft->GetReturnType(), ctx.GetVoidType());
	EXPECT_EQ(ft->GetParamCount(), 0u);
}

TEST(IR, FunctionTypeWithParams)
{
	IRContext ctx;
	std::vector<IRType*> params = { ctx.GetIntegerType(64), ctx.GetIntegerType(64) };
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), params);
	ASSERT_NE(ft, nullptr);
	EXPECT_EQ(ft->GetParamCount(), 2u);
	EXPECT_EQ(ft->GetParamType(0), ctx.GetIntegerType(64));
	EXPECT_EQ(ft->GetParamType(1), ctx.GetIntegerType(64));
}

TEST(IR, StructType)
{
	IRContext ctx;
	std::vector<IRType*> members = { ctx.GetIntegerType(8), ctx.GetFloatType() };
	IRStructType* st = ctx.GetStructType("MyStruct", members);
	ASSERT_NE(st, nullptr);
	EXPECT_EQ(st->GetName(), "MyStruct");
	EXPECT_EQ(st->GetMemberCount(), 2u);
}

TEST(IR, IntConstants)
{
	IRContext ctx;
	ConstantInt* c42 = ctx.GetInt64(42);
	ConstantInt* c0  = ctx.GetInt64(0);
	ConstantInt* neg = ctx.GetInt64(-1);

	ASSERT_NE(c42, nullptr);
	EXPECT_EQ(c42->GetValue(), 42);
	EXPECT_EQ(c0->GetValue(), 0);
	EXPECT_EQ(neg->GetValue(), -1);
}

TEST(IR, IntConstantInterning)
{
	IRContext ctx;
	EXPECT_EQ(ctx.GetInt64(42), ctx.GetInt64(42));
	EXPECT_NE(ctx.GetInt64(42), ctx.GetInt64(43));
}

TEST(IR, BoolConstants)
{
	IRContext ctx;
	ASSERT_NE(ctx.GetTrueValue(),  nullptr);
	ASSERT_NE(ctx.GetFalseValue(), nullptr);
	EXPECT_NE(ctx.GetTrueValue(),  ctx.GetFalseValue());
	EXPECT_EQ(ctx.GetTrueValue()->GetValue(),  1);
	EXPECT_EQ(ctx.GetFalseValue()->GetValue(), 0);
}

TEST(IR, FloatConstants)
{
	IRContext ctx;
	ConstantFloat* f = ctx.GetFloat(3.14);
	ASSERT_NE(f, nullptr);
	EXPECT_NEAR(f->GetValue(), 3.14, 1e-9);
}

TEST(IR, ZeroFloat)
{
	IRContext ctx;
	ASSERT_NE(ctx.GetZeroFloat(), nullptr);
	EXPECT_NEAR(ctx.GetZeroFloat()->GetValue(), 0.0, 1e-9);
}

TEST(IR, StringConstant)
{
	IRContext ctx;
	ConstantString* s = ctx.GetString("hello");
	ASSERT_NE(s, nullptr);
	EXPECT_EQ(s->GetValue(), "hello");
}

// ---------------------------------------------------------------------------
// Functions and basic blocks
// ---------------------------------------------------------------------------

TEST(IR, FunctionCreation)
{
	IRContext ctx;
	IRModule module(ctx, "test");

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetVoidType(), {});
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	EXPECT_EQ(fn->GetName(), "foo");
	EXPECT_TRUE(fn->IsFunction());
	EXPECT_TRUE(fn->IsDeclaration()); // no body yet
	EXPECT_EQ(fn->GetArgCount(), 0u);
}

TEST(IR, FunctionWithArgs)
{
	IRContext ctx;
	IRModule module(ctx, "test");

	std::vector<IRType*> params = { ctx.GetIntegerType(64), ctx.GetIntegerType(64) };
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), params);
	Function* fn = new Function("add", ft, Linkage::External);
	module.AddGlobal(fn);

	EXPECT_EQ(fn->GetArgCount(), 2u);
}

TEST(IR, BasicBlockInsertion)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetVoidType(), {});
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	ASSERT_NE(entry, nullptr);

	EXPECT_FALSE(fn->IsDeclaration()); 
	EXPECT_EQ(fn->Size(), 1u);
}

TEST(IR, MultipleBasicBlocks)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetVoidType(), {});
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	builder.AddBlock("entry");
	builder.AddBlock("then");
	builder.AddBlock("end");

	EXPECT_EQ(fn->Size(), 3u);
}

TEST(IR, ModuleFunctionLookup)
{
	IRContext ctx;
	IRModule module(ctx, "test");

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetVoidType(), {});
	Function* fn = new Function("myFunc", ft, Linkage::External);
	module.AddGlobal(fn);

	EXPECT_EQ(module.GetFunctionByName("myFunc"), fn);
	EXPECT_EQ(module.GetFunctionByName("nope"), nullptr);
}

TEST(IR, GlobalVariable)
{
	IRContext ctx;
	IRModule module(ctx, "test");

	ConstantInt* init = ctx.GetInt64(0);
	GlobalVariable* gv = new GlobalVariable("counter", ctx.GetIntegerType(64), Linkage::Internal, init);
	module.AddGlobal(gv);

	EXPECT_EQ(gv->GetName(), "counter");
	EXPECT_FALSE(gv->IsFunction());
	EXPECT_EQ(gv->GetInitValue(), init);
}
