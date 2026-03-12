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

TEST(IR, SelectInstruction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* cond = builder.MakeInst<CompareInst>(Opcode::ICmpSGT, fn->GetArg(0), ctx.GetInt64(0));
	Value* sel = builder.MakeInst<SelectInst>(cond, ctx.GetInt64(1), ctx.GetInt64(-1));
	ASSERT_NE(sel, nullptr);
	EXPECT_TRUE(isa<SelectInst>(sel));
}

TEST(IR, PhiInstruction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	BasicBlock* merge = builder.AddBlock("merge");

	PhiInst* phi = new PhiInst(ctx.GetIntegerType(64));
	merge->AddPhiInst(phi);
	phi->AddIncoming(ctx.GetInt64(10), entry);

	EXPECT_TRUE(isa<PhiInst>(phi));
}

TEST(IR, CallInstruction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* callee_ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* callee = new Function("callee", callee_ft, Linkage::External);
	module.AddGlobal(callee);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("caller", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	std::vector<Value*> args;
	Value* call = builder.MakeInst<CallInst>(callee, std::span<Value*>(args));
	ASSERT_NE(call, nullptr);
	EXPECT_TRUE(isa<CallInst>(call));
}

TEST(IR, SwitchInstruction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetVoidType(), { ctx.GetIntegerType(64) });
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry  = builder.AddBlock("entry");
	BasicBlock* case0  = builder.AddBlock("case0");
	BasicBlock* deflt  = builder.AddBlock("default");

	builder.SetCurrentBlock(entry);
	Value* sw = builder.MakeInst<SwitchInst>(fn->GetArg(0), deflt);
	cast<SwitchInst>(sw)->AddCase(0, case0);

	EXPECT_TRUE(isa<SwitchInst>(sw));
}

TEST(IR, FunctionAttributes)
{
	IRContext ctx;
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetVoidType(), {});
	Function* fn = new Function("foo", ft, Linkage::External);

	EXPECT_FALSE(fn->IsForceInline());
	EXPECT_FALSE(fn->IsNoInline());
	EXPECT_FALSE(fn->IsNoOptimizations());

	fn->SetForceInline();
	EXPECT_TRUE(fn->IsForceInline());

	fn->SetNoInline();
	EXPECT_TRUE(fn->IsNoInline());

	fn->SetNoOptimizations();
	EXPECT_TRUE(fn->IsNoOptimizations());
}

TEST(IR, GlobalVariableReadOnly)
{
	IRContext ctx;
	ConstantInt* init = ctx.GetInt64(42);
	GlobalVariable* gv = new GlobalVariable("ro", ctx.GetIntegerType(64), Linkage::Internal, init);

	EXPECT_FALSE(gv->IsReadOnly());
	gv->SetReadOnly();
	EXPECT_TRUE(gv->IsReadOnly());
	delete gv;
}

TEST(IR, StructTypeInterning)
{
	IRContext ctx;
	std::vector<IRType*> members = { ctx.GetIntegerType(64) };
	IRStructType* a = ctx.GetStructType("Foo", members);
	IRStructType* b = ctx.GetStructType("Foo", members);
	// Same name should return the same interned type
	EXPECT_EQ(a, b);
}

TEST(IR, EmptyStructType)
{
	IRContext ctx;
	std::vector<IRType*> members = {};
	IRStructType* st = ctx.GetStructType("Empty", members);
	ASSERT_NE(st, nullptr);
	EXPECT_EQ(st->GetMemberCount(), 0u);
}

TEST(IR, UnaryInstruction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* neg = builder.MakeInst<UnaryInst>(Opcode::Neg, fn->GetArg(0));
	ASSERT_NE(neg, nullptr);
	EXPECT_TRUE(isa<UnaryInst>(neg));
}

TEST(IR, CastInstruction_ZExt)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), { ctx.GetIntegerType(8) });
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* zext = builder.MakeInst<CastInst>(Opcode::ZExt, ctx.GetIntegerType(64), fn->GetArg(0));
	ASSERT_NE(zext, nullptr);
	EXPECT_TRUE(isa<CastInst>(zext));
	auto* ci = cast<CastInst>(zext);
	EXPECT_EQ(ci->GetDestType(), ctx.GetIntegerType(64));
	EXPECT_EQ(ci->GetSrcType(), ctx.GetIntegerType(8));
}

TEST(IR, CastInstruction_F2S)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), { ctx.GetFloatType() });
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* f2s = builder.MakeInst<CastInst>(Opcode::F2S, ctx.GetIntegerType(64), fn->GetArg(0));
	ASSERT_NE(f2s, nullptr);
	auto* ci = cast<CastInst>(f2s);
	EXPECT_EQ(ci->GetOpcode(), Opcode::F2S);
}

TEST(IR, CastInstruction_S2F)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetFloatType(), { ctx.GetIntegerType(64) });
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* s2f = builder.MakeInst<CastInst>(Opcode::S2F, ctx.GetFloatType(), fn->GetArg(0));
	ASSERT_NE(s2f, nullptr);
	auto* ci = cast<CastInst>(s2f);
	EXPECT_EQ(ci->GetOpcode(), Opcode::S2F);
}

TEST(IR, ReturnInstVoid)
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

	builder.MakeInst<ReturnInst>(ctx);
	auto* ret = cast<ReturnInst>(entry->GetTerminator());
	EXPECT_TRUE(ret->IsVoid());
	EXPECT_EQ(ret->GetReturnValue(), nullptr);
}

TEST(IR, ReturnInstWithValue)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	builder.MakeInst<ReturnInst>(ctx.GetInt64(99));
	auto* ret = cast<ReturnInst>(entry->GetTerminator());
	EXPECT_FALSE(ret->IsVoid());
	ASSERT_NE(ret->GetReturnValue(), nullptr);
}

TEST(IR, BinaryInst_Add)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), { ctx.GetIntegerType(64), ctx.GetIntegerType(64) });
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* add = builder.MakeInst<BinaryInst>(Opcode::Add, fn->GetArg(0), fn->GetArg(1));
	ASSERT_NE(add, nullptr);
	EXPECT_TRUE(isa<BinaryInst>(add));
	auto* bin = cast<BinaryInst>(add);
	EXPECT_EQ(bin->GetOpcode(), Opcode::Add);
	EXPECT_EQ(bin->GetLHS(), fn->GetArg(0));
	EXPECT_EQ(bin->GetRHS(), fn->GetArg(1));
}

TEST(IR, FloatBinaryInst)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetFloatType(), { ctx.GetFloatType(), ctx.GetFloatType() });
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* fadd = builder.MakeInst<BinaryInst>(Opcode::FAdd, fn->GetArg(0), fn->GetArg(1));
	ASSERT_NE(fadd, nullptr);
	EXPECT_EQ(cast<Instruction>(fadd)->GetOpcode(), Opcode::FAdd);
}

TEST(IR, CompareInstruction)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* cmp = builder.MakeInst<CompareInst>(Opcode::ICmpEQ, fn->GetArg(0), ctx.GetInt64(0));
	ASSERT_NE(cmp, nullptr);
	EXPECT_TRUE(isa<CompareInst>(cmp));
	auto* ci = cast<CompareInst>(cmp);
	EXPECT_EQ(ci->GetCompareOp(), CompareOp::ICmpEQ);
}

TEST(IR, PtrAddInstruction)
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
	Value* ptr_add = builder.MakeInst<PtrAddInst>(alloca, ctx.GetInt64(8), ctx.GetIntegerType(64));
	ASSERT_NE(ptr_add, nullptr);
	EXPECT_TRUE(isa<PtrAddInst>(ptr_add));
}

TEST(IR, InstructionClone)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), { ctx.GetIntegerType(64), ctx.GetIntegerType(64) });
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* add = builder.MakeInst<BinaryInst>(Opcode::Add, fn->GetArg(0), fn->GetArg(1));
	auto* addInst = cast<Instruction>(add);
	Instruction* clone = addInst->Clone();
	ASSERT_NE(clone, nullptr);
	EXPECT_EQ(clone->GetOpcode(), Opcode::Add);
	delete clone;
}

TEST(IR, OpcodePredicates)
{
	EXPECT_TRUE(IsOpcodeTerminator(Opcode::Ret));
	EXPECT_TRUE(IsOpcodeTerminator(Opcode::Branch));
	EXPECT_TRUE(IsOpcodeTerminator(Opcode::Switch));
	EXPECT_FALSE(IsOpcodeTerminator(Opcode::Add));

	EXPECT_TRUE(IsOpcodeMemoryOp(Opcode::Load));
	EXPECT_TRUE(IsOpcodeMemoryOp(Opcode::Store));
	EXPECT_FALSE(IsOpcodeMemoryOp(Opcode::Add));

	EXPECT_TRUE(IsOpcodeIntegerOp(Opcode::Add));
	EXPECT_TRUE(IsOpcodeIntegerOp(Opcode::Sub));
	EXPECT_TRUE(IsOpcodeIntegerOp(Opcode::Shl));
	EXPECT_FALSE(IsOpcodeIntegerOp(Opcode::FAdd));

	EXPECT_TRUE(IsOpcodeFloatOp(Opcode::FAdd));
	EXPECT_TRUE(IsOpcodeFloatOp(Opcode::FMul));
	EXPECT_FALSE(IsOpcodeFloatOp(Opcode::Add));

	EXPECT_TRUE(IsOpcodeCastOp(Opcode::ZExt));
	EXPECT_TRUE(IsOpcodeCastOp(Opcode::F2S));
	EXPECT_TRUE(IsOpcodeCastOp(Opcode::S2F));
	EXPECT_FALSE(IsOpcodeCastOp(Opcode::Add));
}

TEST(IR, OpcodeCommutative)
{
	EXPECT_TRUE(IsOpcodeCommutative(Opcode::Add));
	EXPECT_TRUE(IsOpcodeCommutative(Opcode::SMul));
	EXPECT_TRUE(IsOpcodeCommutative(Opcode::And));
	EXPECT_TRUE(IsOpcodeCommutative(Opcode::Or));
	EXPECT_TRUE(IsOpcodeCommutative(Opcode::Xor));
	EXPECT_TRUE(IsOpcodeCommutative(Opcode::FAdd));
	EXPECT_TRUE(IsOpcodeCommutative(Opcode::FMul));

	EXPECT_FALSE(IsOpcodeCommutative(Opcode::Sub));
	EXPECT_FALSE(IsOpcodeCommutative(Opcode::SDiv));
	EXPECT_FALSE(IsOpcodeCommutative(Opcode::Shl));
}

TEST(IR, OpcodeSideEffects)
{
	EXPECT_TRUE(HasOpcodeSideEffects(Opcode::Alloca));
	EXPECT_TRUE(HasOpcodeSideEffects(Opcode::Store));
	EXPECT_TRUE(HasOpcodeSideEffects(Opcode::Call));
	EXPECT_FALSE(HasOpcodeSideEffects(Opcode::Add));
	EXPECT_FALSE(HasOpcodeSideEffects(Opcode::Load));
}

TEST(IR, ConstantNullPtr)
{
	IRContext ctx;
	IRPtrType* pt = ctx.GetPointerType(ctx.GetIntegerType(64));
	ConstantNullPtr* np = new ConstantNullPtr(pt);
	ASSERT_NE(np, nullptr);
	EXPECT_TRUE(isa<ConstantNullPtr>(np));
	delete np;
}

TEST(IR, UndefValue)
{
	IRContext ctx;
	UndefValue* uv = new UndefValue(ctx.GetIntegerType(64));
	ASSERT_NE(uv, nullptr);
	EXPECT_TRUE(isa<UndefValue>(uv));
	delete uv;
}

TEST(IR, SwitchWithMultipleCases)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetVoidType(), { ctx.GetIntegerType(64) });
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry  = builder.AddBlock("entry");
	BasicBlock* case0  = builder.AddBlock("case0");
	BasicBlock* case1  = builder.AddBlock("case1");
	BasicBlock* case2  = builder.AddBlock("case2");
	BasicBlock* deflt  = builder.AddBlock("default");

	builder.SetCurrentBlock(entry);
	Value* sw = builder.MakeInst<SwitchInst>(fn->GetArg(0), deflt);
	auto* swi = cast<SwitchInst>(sw);
	swi->AddCase(0, case0);
	swi->AddCase(1, case1);
	swi->AddCase(42, case2);

	EXPECT_EQ(swi->GetNumCases(), 3u);
	EXPECT_EQ(swi->GetCaseValue(0), 0);
	EXPECT_EQ(swi->GetCaseValue(1), 1);
	EXPECT_EQ(swi->GetCaseValue(2), 42);
}

TEST(IR, PhiMultipleIncoming)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), {});
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	BasicBlock* left  = builder.AddBlock("left");
	BasicBlock* right = builder.AddBlock("right");
	BasicBlock* merge = builder.AddBlock("merge");

	PhiInst* phi = new PhiInst(ctx.GetIntegerType(64));
	merge->AddPhiInst(phi);
	phi->AddIncoming(ctx.GetInt64(10), left);
	phi->AddIncoming(ctx.GetInt64(20), right);

	EXPECT_EQ(phi->GetNumIncomingValues(), 2u);
	EXPECT_EQ(phi->GetIncomingValue(0), ctx.GetInt64(10));
	EXPECT_EQ(phi->GetIncomingValue(1), ctx.GetInt64(20));
	EXPECT_EQ(phi->GetIncomingBlock(0), left);
	EXPECT_EQ(phi->GetIncomingBlock(1), right);
	EXPECT_EQ(phi->GetIncomingValueForBlock(left), ctx.GetInt64(10));
	EXPECT_EQ(phi->GetIncomingValueForBlock(right), ctx.GetInt64(20));
	EXPECT_EQ(phi->GetIncomingValueForBlock(entry), nullptr);
}

TEST(IR, FunctionArgTypes)
{
	IRContext ctx;
	IRModule module(ctx, "test");

	std::vector<IRType*> params = { ctx.GetIntegerType(8), ctx.GetFloatType(), ctx.GetIntegerType(64) };
	IRFuncType* ft = ctx.GetFunctionType(ctx.GetVoidType(), params);
	Function* fn = new Function("multi", ft, Linkage::External);
	module.AddGlobal(fn);

	EXPECT_EQ(fn->GetArgCount(), 3u);
	EXPECT_EQ(fn->GetArg(0)->GetType(), ctx.GetIntegerType(8));
	EXPECT_EQ(fn->GetArg(1)->GetType(), ctx.GetFloatType());
	EXPECT_EQ(fn->GetArg(2)->GetType(), ctx.GetIntegerType(64));
}

TEST(IR, InstructionIsUsed)
{
	IRContext ctx;
	IRModule module(ctx, "test");
	IRBuilder builder(ctx);

	IRFuncType* ft = ctx.GetFunctionType(ctx.GetIntegerType(64), { ctx.GetIntegerType(64) });
	Function* fn = new Function("foo", ft, Linkage::External);
	module.AddGlobal(fn);

	builder.SetCurrentFunction(fn);
	BasicBlock* entry = builder.AddBlock("entry");
	builder.SetCurrentBlock(entry);

	Value* alloca = builder.MakeInst<AllocaInst>(ctx.GetIntegerType(64));
	// Before storing, alloca has no uses from other instructions
	builder.MakeInst<StoreInst>(fn->GetArg(0), alloca);
	// After storing, alloca is used by the store
	EXPECT_TRUE(cast<Instruction>(alloca)->IsUsed());
}

TEST(IR, GlobalVariableLinkage)
{
	IRContext ctx;
	ConstantInt* init = ctx.GetInt64(0);
	GlobalVariable* gv_internal = new GlobalVariable("internal_g", ctx.GetIntegerType(64), Linkage::Internal, init);
	GlobalVariable* gv_external = new GlobalVariable("external_g", ctx.GetIntegerType(64), Linkage::External, init);

	EXPECT_EQ(gv_internal->GetLinkage(), Linkage::Internal);
	EXPECT_EQ(gv_external->GetLinkage(), Linkage::External);

	delete gv_internal;
	delete gv_external;
}
