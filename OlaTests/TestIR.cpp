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

TEST(IR, NestedPointerType)
{
	IRContext ctx;
	IRPtrType* p  = ctx.GetPointerType(ctx.GetIntegerType(64));
	IRPtrType* pp = ctx.GetPointerType(p);
	ASSERT_NE(pp, nullptr);
	EXPECT_NE(p, pp);
	EXPECT_EQ(pp->GetPointeeType(), p);
}

TEST(IR, PointerToVoid)
{
	IRContext ctx;
	IRPtrType* vp = ctx.GetPointerType(ctx.GetVoidType());
	ASSERT_NE(vp, nullptr);
	EXPECT_EQ(vp->GetPointeeType(), ctx.GetVoidType());
}

TEST(IR, ArrayOfPointers)
{
	IRContext ctx;
	IRPtrType* p = ctx.GetPointerType(ctx.GetIntegerType(64));
	IRArrayType* arr = ctx.GetArrayType(p, 5);
	ASSERT_NE(arr, nullptr);
	EXPECT_EQ(arr->GetArraySize(), 5u);
	EXPECT_EQ(arr->GetElementType(), p);
}

TEST(IR, FunctionTypeInterning)
{
	IRContext ctx;
	IRFuncType* a = ctx.GetFunctionType(ctx.GetVoidType(), {});
	IRFuncType* b = ctx.GetFunctionType(ctx.GetVoidType(), {});
	EXPECT_EQ(a, b);
}

TEST(IR, FunctionTypeWithDifferentReturnTypes)
{
	IRContext ctx;
	IRFuncType* a = ctx.GetFunctionType(ctx.GetVoidType(), {});
	IRFuncType* b = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	EXPECT_NE(a, b);
}

TEST(IR, StructTypeDifferentNames)
{
	IRContext ctx;
	std::vector<IRType*> members = { ctx.GetIntegerType(64) };
	IRStructType* a = ctx.GetStructType("Foo", members);
	IRStructType* b = ctx.GetStructType("Bar", members);
	EXPECT_NE(a, b);
}

TEST(IR, StructTypeMemberAccess)
{
	IRContext ctx;
	std::vector<IRType*> members = { ctx.GetIntegerType(8), ctx.GetIntegerType(64), ctx.GetFloatType() };
	IRStructType* st = ctx.GetStructType("Triple", members);
	ASSERT_NE(st, nullptr);
	EXPECT_EQ(st->GetMemberCount(), 3u);
	EXPECT_EQ(st->GetMemberType(0), ctx.GetIntegerType(8));
	EXPECT_EQ(st->GetMemberType(1), ctx.GetIntegerType(64));
	EXPECT_EQ(st->GetMemberType(2), ctx.GetFloatType());
}

TEST(IR, IntegerTypeBitWidths)
{
	IRContext ctx;
	IRIntType* i8  = ctx.GetIntegerType(8);
	IRIntType* i64 = ctx.GetIntegerType(64);

	ASSERT_NE(i8, nullptr);
	ASSERT_NE(i64, nullptr);
	EXPECT_NE(i8, i64);
}

TEST(IR, FloatConstantInterning)
{
	IRContext ctx;
	ConstantFloat* a = ctx.GetFloat(3.14);
	ConstantFloat* b = ctx.GetFloat(3.14);
	EXPECT_EQ(a, b);
}

TEST(IR, FloatConstantDifferentValues)
{
	IRContext ctx;
	ConstantFloat* a = ctx.GetFloat(1.0);
	ConstantFloat* b = ctx.GetFloat(2.0);
	EXPECT_NE(a, b);
}

TEST(IR, NegativeIntConstant)
{
	IRContext ctx;
	ConstantInt* neg = ctx.GetInt64(-42);
	ASSERT_NE(neg, nullptr);
	EXPECT_EQ(neg->GetValue(), -42);
}

TEST(IR, Int8Constants)
{
	IRContext ctx;
	ConstantInt* c = ctx.GetInt8(127);
	ASSERT_NE(c, nullptr);
	EXPECT_EQ(c->GetValue(), 127);
}

TEST(IR, StringConstantInterning)
{
	IRContext ctx;
	ConstantString* a = ctx.GetString("hello");
	ConstantString* b = ctx.GetString("hello");
	EXPECT_EQ(a, b);
}

TEST(IR, StringConstantDifferentValues)
{
	IRContext ctx;
	ConstantString* a = ctx.GetString("hello");
	ConstantString* b = ctx.GetString("world");
	EXPECT_NE(a, b);
}

TEST(IR, EmptyStringConstant)
{
	IRContext ctx;
	ConstantString* s = ctx.GetString("");
	ASSERT_NE(s, nullptr);
	EXPECT_EQ(s->GetValue(), "");
}

TEST(IR, AllocaInstruction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetVoidType(), {});
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* alloca = builder.MakeInst<AllocaInst>(ctx.GetIntegerType(64));
	ASSERT_NE(alloca, nullptr);
	EXPECT_TRUE(isa<AllocaInst>(alloca));
}

TEST(IR, StoreLoadInstructions)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetVoidType(), {});
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* alloca = builder.MakeInst<AllocaInst>(ctx.GetIntegerType(64));
	Value* store = builder.MakeInst<StoreInst>(ctx.GetInt64(42), alloca);
	Value* load = builder.MakeInst<LoadInst>(alloca);

	EXPECT_TRUE(isa<StoreInst>(store));
	EXPECT_TRUE(isa<LoadInst>(load));
}

TEST(IR, BranchInstructions)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetVoidType(), {});
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry  = builder.AddBlock("entry");
	BasicBlock* target = builder.AddBlock("target");

	builder.SetCurrentBlock(entry);
	builder.MakeInst<BranchInst>(ctx, target);

	auto* br = cast<BranchInst>(entry->GetTerminator());
	EXPECT_TRUE(br->IsUnconditional());
	EXPECT_EQ(br->GetTrueTarget(), target);
}

TEST(IR, ConditionalBranch)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetVoidType(), { ctx.GetIntegerType(64) });
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	BasicBlock* then_bb = builder.AddBlock("then");
	BasicBlock* else_bb = builder.AddBlock("else");

	builder.SetCurrentBlock(entry);
	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpSGT, fn->GetArg(0), ctx.GetInt64(0));
	builder.MakeInst<BranchInst>(cond, then_bb, else_bb);

	auto* br = cast<BranchInst>(entry->GetTerminator());
	EXPECT_TRUE(br->IsConditional());
	EXPECT_EQ(br->GetTrueTarget(), then_bb);
	EXPECT_EQ(br->GetFalseTarget(), else_bb);
}

TEST(IR, ModuleMultipleGlobals)
{
	IRContext ctx;
	IRModule module(ctx, "test");

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetVoidType(), {});
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	GlobalVariable* gv = new GlobalVariable("g", ctx.GetIntegerType(64), Linkage::Internal, ctx.GetInt64(0));
	module.AddGlobal(gv);

	EXPECT_EQ(module.Globals().size(), 2u);
	EXPECT_NE(module.GetFunctionByName("foo"), nullptr);
}

TEST(IR, FunctionDeclarationVsDefinition)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetVoidType(), {});
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	EXPECT_TRUE(fn->IsDeclaration());

	builder.SetCurrentFunction(fn);
	builder.AddBlock("entry");

	EXPECT_FALSE(fn->IsDeclaration());
}
