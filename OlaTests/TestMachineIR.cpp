#include <gtest/gtest.h>
#include "Backend/Custom/Codegen/MachineOperand.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineBasicBlock.h"
#include "Backend/Custom/Codegen/MachineFunction.h"

using namespace ola;

TEST(MachineOperand, ImmediateHoldsValue)
{
	MachineOperand op = MachineOperand::Immediate(42LL, MachineType::Int64);
	EXPECT_TRUE(op.IsImmediate());
	EXPECT_EQ(op.GetImmediate(), 42);
}

TEST(MachineOperand, ImmediateTypeIsPreserved)
{
	MachineOperand op = MachineOperand::Immediate(0LL, MachineType::Float64);
	EXPECT_EQ(op.GetType(), MachineType::Float64);
}

TEST(MachineOperand, ISARegIsRecognisedAsRegister)
{
	MachineOperand op = MachineOperand::ISAReg(0u, MachineType::Int64);
	EXPECT_TRUE(op.IsReg());
	EXPECT_FALSE(op.IsImmediate());
	EXPECT_FALSE(op.IsStackObject());
}

TEST(MachineOperand, ISARegHoldsCorrectRegisterNumber)
{
	MachineOperand op = MachineOperand::ISAReg(3u, MachineType::Int64);
	EXPECT_EQ(op.GetReg().reg, 3u);
}

TEST(MachineOperand, VirtualRegIsRecognisedAsRegister)
{
	MachineOperand op = MachineOperand::VirtualReg(0u, MachineType::Int64);
	EXPECT_TRUE(op.IsReg());
}

TEST(MachineOperand, VirtualRegIDIsInVirtualRange)
{
	MachineOperand op = MachineOperand::VirtualReg(5u, MachineType::Int64);
	EXPECT_TRUE(IsVirtualReg(op.GetReg().reg));
	EXPECT_FALSE(IsISAReg(op.GetReg().reg));
}

TEST(MachineOperand, VirtualRegIDsAreDistinctPerIndex)
{
	MachineOperand a = MachineOperand::VirtualReg(0u, MachineType::Int64);
	MachineOperand b = MachineOperand::VirtualReg(1u, MachineType::Int64);
	EXPECT_NE(a.GetReg().reg, b.GetReg().reg);
}

TEST(MachineOperand, StackObjectHoldsOffset)
{
	MachineOperand op = MachineOperand::StackObject(-8, MachineType::Int64);
	EXPECT_TRUE(op.IsStackObject());
	EXPECT_EQ(op.GetStackOffset(), -8);
}

TEST(MachineOperand, StackObjectIsMemoryOperand)
{
	MachineOperand op = MachineOperand::StackObject(-16, MachineType::Int64);
	EXPECT_TRUE(op.IsMemoryOperand());
}

TEST(MachineOperand, UndefinedIsUndefined)
{
	MachineOperand op = MachineOperand::Undefined();
	EXPECT_TRUE(op.IsUndefined());
	EXPECT_FALSE(op.IsReg());
	EXPECT_FALSE(op.IsImmediate());
	EXPECT_FALSE(op.IsStackObject());
	EXPECT_EQ(op.GetType(), MachineType::Undef);
}

TEST(MachineOperand, EqualImmediateOperandsCompareEqual)
{
	MachineOperand a = MachineOperand::Immediate(99LL, MachineType::Int64);
	MachineOperand b = MachineOperand::Immediate(99LL, MachineType::Int64);
	EXPECT_EQ(a, b);
}

TEST(MachineOperand, DifferentImmediateValuesCompareUnequal)
{
	MachineOperand a = MachineOperand::Immediate(1LL, MachineType::Int64);
	MachineOperand b = MachineOperand::Immediate(2LL, MachineType::Int64);
	EXPECT_NE(a, b);
}

TEST(MachineOperand, ISARegTypeIsPreserved)
{
	MachineOperand op = MachineOperand::ISAReg(0u, MachineType::Float64);
	EXPECT_EQ(op.GetType(), MachineType::Float64);
}

TEST(MachineOperand, SetTypeUpdatesType)
{
	MachineOperand op = MachineOperand::ISAReg(0u, MachineType::Int64);
	op.SetType(MachineType::Int8);
	EXPECT_EQ(op.GetType(), MachineType::Int8);
}

TEST(MachineOperand, ImmediateIsNotMemoryOperand)
{
	MachineOperand op = MachineOperand::Immediate(42LL, MachineType::Int64);
	EXPECT_FALSE(op.IsMemoryOperand());
}

TEST(MachineInstruction, HoldsInitialOpcode)
{
	MachineInstruction inst(InstAdd);
	EXPECT_EQ(inst.GetOpcode(), static_cast<Uint32>(InstAdd));
}

TEST(MachineInstruction, OpcodeCanBeUpdated)
{
	MachineInstruction inst(InstAdd);
	inst.SetOpcode(InstSub);
	EXPECT_EQ(inst.GetOpcode(), static_cast<Uint32>(InstSub));
}

TEST(MachineInstruction, SetOpcodeReturnsRef)
{
	MachineInstruction inst(InstAdd);
	MachineInstruction& ref = inst.SetOpcode(InstSub);
	EXPECT_EQ(&ref, &inst);
}

TEST(MachineInstruction, OperandRoundtripViaTemplateIndex)
{
	MachineInstruction inst(InstMove);
	MachineOperand imm = MachineOperand::Immediate(7LL, MachineType::Int64);
	inst.SetOp<0>(imm);
	EXPECT_EQ(inst.GetOp<0>(), imm);
}

TEST(MachineInstruction, OperandRoundtripViaNumericIndex)
{
	MachineInstruction inst(InstMove);
	MachineOperand reg = MachineOperand::ISAReg(2u, MachineType::Int64);
	inst.SetOperand(1, reg);
	EXPECT_EQ(inst.GetOperand(1), reg);
}

TEST(MachineInstruction, FreshInstructionIsNotDead)
{
	MachineInstruction inst(InstAdd);
	EXPECT_FALSE(inst.IsDead());
}

TEST(MachineInstruction, SetDeadMarksDead)
{
	MachineInstruction inst(InstAdd);
	inst.SetDead();
	EXPECT_TRUE(inst.IsDead());
}

TEST(MachineInstruction, SetFlagQueryRoundtrip)
{
	MachineInstruction inst(InstAdd);
	inst.SetFlag(MachineInstFlag_Dead);
	EXPECT_TRUE(inst.HasFlag(MachineInstFlag_Dead));
}

TEST(MachineInstruction, EqualityRequiresSameOpcodeAndOperands)
{
	MachineInstruction a(InstAdd);
	MachineInstruction b(InstAdd);
	MachineOperand imm = MachineOperand::Immediate(1LL, MachineType::Int64);
	a.SetOp<0>(imm);
	b.SetOp<0>(imm);
	EXPECT_EQ(a, b);
}

TEST(MachineInstruction, InequalityOnDifferentOpcode)
{
	MachineInstruction a(InstAdd);
	MachineInstruction b(InstSub);
	EXPECT_NE(a, b);
}

TEST(MachineInstruction, InequalityOnDifferentOperand)
{
	MachineInstruction a(InstMove);
	MachineInstruction b(InstMove);
	a.SetOp<0>(MachineOperand::Immediate(1LL, MachineType::Int64));
	b.SetOp<0>(MachineOperand::Immediate(2LL, MachineType::Int64));
	EXPECT_NE(a, b);
}

TEST(MachineBasicBlock, LabelIsPreserved)
{
	MachineBasicBlock mbb(nullptr, "entry");
	EXPECT_EQ(mbb.GetSymbol(), "entry");
}

TEST(MachineBasicBlock, InitiallyHasNoSuccessors)
{
	MachineBasicBlock mbb(nullptr, "bb");
	EXPECT_TRUE(mbb.Successors().empty());
}

TEST(MachineBasicBlock, InitiallyHasNoPredecessors)
{
	MachineBasicBlock mbb(nullptr, "bb");
	EXPECT_TRUE(mbb.Predecessors().empty());
}

TEST(MachineBasicBlock, AddSuccessorLinksSymmetrically)
{
	MachineBasicBlock a(nullptr, "a");
	MachineBasicBlock b(nullptr, "b");
	a.AddSuccessor(&b);
	EXPECT_TRUE(a.Successors().count(&b));
	EXPECT_TRUE(b.Predecessors().count(&a));
}

TEST(MachineBasicBlock, AddPredecessorLinksSymmetrically)
{
	MachineBasicBlock a(nullptr, "a");
	MachineBasicBlock b(nullptr, "b");
	b.AddPredecessor(&a);
	EXPECT_TRUE(b.Predecessors().count(&a));
	EXPECT_TRUE(a.Successors().count(&b));
}

TEST(MachineBasicBlock, MultipleSuccessorsAreTracked)
{
	MachineBasicBlock entry(nullptr, "entry");
	MachineBasicBlock then_bb(nullptr, "then");
	MachineBasicBlock else_bb(nullptr, "else");
	entry.AddSuccessor(&then_bb);
	entry.AddSuccessor(&else_bb);
	EXPECT_EQ(entry.Successors().size(), 2u);
}

TEST(MachineBasicBlock, InitiallyHasNoInstructions)
{
	MachineBasicBlock mbb(nullptr, "bb");
	EXPECT_TRUE(mbb.Instructions().empty());
}

TEST(MachineBasicBlock, InstructionCanBeAppended)
{
	MachineBasicBlock mbb(nullptr, "bb");
	mbb.Instructions().push_back(MachineInstruction(InstRet));
	EXPECT_EQ(mbb.Instructions().size(), 1u);
}

TEST(MachineBasicBlock, IsBlock)
{
	MachineBasicBlock mbb(nullptr, "bb");
	EXPECT_TRUE(mbb.IsBlock());
	EXPECT_FALSE(mbb.IsFunction());
}

TEST(MachineFunction, DeclarationFlagPreservedTrue)
{
	MachineFunction mf("foo", true);
	EXPECT_TRUE(mf.IsDeclaration());
}

TEST(MachineFunction, DeclarationFlagPreservedFalse)
{
	MachineFunction mf("bar", false);
	EXPECT_FALSE(mf.IsDeclaration());
}

TEST(MachineFunction, SymbolIsPreserved)
{
	MachineFunction mf("my_func", false);
	EXPECT_EQ(mf.GetSymbol(), "my_func");
}

TEST(MachineFunction, InitialStackSizeIsZero)
{
	MachineFunction mf("f", false);
	EXPECT_EQ(mf.GetStackAllocationSize(), 0);
	EXPECT_EQ(mf.GetLocalStackAllocationSize(), 0);
}

TEST(MachineFunction, LocalStackGrowsByTypeSizeInt64)
{
	MachineFunction mf("f", false);
	mf.AllocateLocalStack(MachineType::Int64);
	EXPECT_EQ(mf.GetLocalStackAllocationSize(), 8);
}

TEST(MachineFunction, LocalStackGrowsByTypeSizeInt8)
{
	MachineFunction mf("f", false);
	mf.AllocateLocalStack(MachineType::Int8);
	EXPECT_EQ(mf.GetLocalStackAllocationSize(), 1);
}

TEST(MachineFunction, LocalStackAllocReturnsStackObject)
{
	MachineFunction mf("f", false);
	MachineOperand& op = mf.AllocateLocalStack(MachineType::Int64);
	EXPECT_TRUE(op.IsStackObject());
}

TEST(MachineFunction, LocalStackAllocOffsetIsNegative)
{
	MachineFunction mf("f", false);
	MachineOperand& op = mf.AllocateLocalStack(MachineType::Int64);
	EXPECT_LT(op.GetStackOffset(), 0);
}

TEST(MachineFunction, MultipleAllocsAccumulate)
{
	MachineFunction mf("f", false);
	mf.AllocateLocalStack(MachineType::Int64); // 8 bytes
	mf.AllocateLocalStack(MachineType::Int64); // 8 bytes
	EXPECT_EQ(mf.GetLocalStackAllocationSize(), 16);
}

TEST(MachineFunction, ArgumentStackAddsToTotalSize)
{
	MachineFunction mf("f", false);
	mf.AllocateArgumentStack(16);
	EXPECT_EQ(mf.GetStackAllocationSize(), 16);
	EXPECT_EQ(mf.GetLocalStackAllocationSize(), 0);
}

TEST(MachineFunction, HasFrameDefaultsFalse)
{
	MachineFunction mf("f", false);
	EXPECT_FALSE(mf.HasFrame());
}

TEST(MachineFunction, HasFrameRoundtrip)
{
	MachineFunction mf("f", false);
	mf.SetHasFrame(true);
	EXPECT_TRUE(mf.HasFrame());
}

TEST(MachineFunction, HasCallInstructionsDefaultsFalse)
{
	MachineFunction mf("f", false);
	EXPECT_FALSE(mf.HasCallInstructions());
}

TEST(MachineFunction, AddCallInstructionSetsFlag)
{
	MachineFunction mf("f", false);
	mf.AddCallInstructionArgCount(3);
	EXPECT_TRUE(mf.HasCallInstructions());
}

TEST(MachineFunction, MaxCallArgCountTracksMaximum)
{
	MachineFunction mf("f", false);
	mf.AddCallInstructionArgCount(3);
	mf.AddCallInstructionArgCount(7);
	mf.AddCallInstructionArgCount(2);
	EXPECT_EQ(mf.GetMaxCallArgCount(), 7u);
}

TEST(MachineFunction, IsFunction)
{
	MachineFunction mf("f", false);
	EXPECT_TRUE(mf.IsFunction());
	EXPECT_FALSE(mf.IsBlock());
}

TEST(MachineOperand, NegativeImmediate)
{
	MachineOperand op = MachineOperand::Immediate(-100LL, MachineType::Int64);
	EXPECT_TRUE(op.IsImmediate());
	EXPECT_EQ(op.GetImmediate(), -100);
}

TEST(MachineOperand, ZeroImmediate)
{
	MachineOperand op = MachineOperand::Immediate(0LL, MachineType::Int64);
	EXPECT_TRUE(op.IsImmediate());
	EXPECT_EQ(op.GetImmediate(), 0);
}

TEST(MachineOperand, ISARegIsNotStackObject)
{
	MachineOperand op = MachineOperand::ISAReg(0u, MachineType::Int64);
	EXPECT_FALSE(op.IsStackObject());
	EXPECT_FALSE(op.IsImmediate());
}

TEST(MachineOperand, VirtualRegTypePreserved)
{
	MachineOperand op = MachineOperand::VirtualReg(0u, MachineType::Float64);
	EXPECT_EQ(op.GetType(), MachineType::Float64);
	EXPECT_TRUE(op.IsReg());
}

TEST(MachineOperand, StackObjectNotReg)
{
	MachineOperand op = MachineOperand::StackObject(-32, MachineType::Int64);
	EXPECT_FALSE(op.IsReg());
	EXPECT_FALSE(op.IsImmediate());
	EXPECT_TRUE(op.IsStackObject());
}

TEST(MachineOperand, LargeStackOffset)
{
	MachineOperand op = MachineOperand::StackObject(-1024, MachineType::Int64);
	EXPECT_EQ(op.GetStackOffset(), -1024);
}

TEST(MachineInstruction, MultipleOperandRoundtrip)
{
	MachineInstruction inst(InstAdd);
	MachineOperand dst = MachineOperand::VirtualReg(0u, MachineType::Int64);
	MachineOperand src1 = MachineOperand::VirtualReg(1u, MachineType::Int64);
	MachineOperand src2 = MachineOperand::Immediate(42LL, MachineType::Int64);
	inst.SetOp<0>(dst);
	inst.SetOp<1>(src1);
	inst.SetOp<2>(src2);
	EXPECT_EQ(inst.GetOp<0>(), dst);
	EXPECT_EQ(inst.GetOp<1>(), src1);
	EXPECT_EQ(inst.GetOp<2>(), src2);
}

TEST(MachineInstruction, FlagCombinations)
{
	MachineInstruction inst(InstAdd);
	inst.SetFlag(MachineInstFlag_Dead);
	EXPECT_TRUE(inst.HasFlag(MachineInstFlag_Dead));
	EXPECT_TRUE(inst.IsDead());
}

TEST(MachineBasicBlock, MultipleInstructions)
{
	MachineBasicBlock mbb(nullptr, "bb");
	mbb.Instructions().push_back(MachineInstruction(InstAdd));
	mbb.Instructions().push_back(MachineInstruction(InstSub));
	mbb.Instructions().push_back(MachineInstruction(InstRet));
	EXPECT_EQ(mbb.Instructions().size(), 3u);
}

TEST(MachineBasicBlock, MultiplePredecessors)
{
	MachineBasicBlock merge(nullptr, "merge");
	MachineBasicBlock left(nullptr, "left");
	MachineBasicBlock right(nullptr, "right");
	merge.AddPredecessor(&left);
	merge.AddPredecessor(&right);
	EXPECT_EQ(merge.Predecessors().size(), 2u);
	EXPECT_TRUE(left.Successors().count(&merge));
	EXPECT_TRUE(right.Successors().count(&merge));
}

TEST(MachineFunction, LocalStackMultipleTypes)
{
	MachineFunction mf("f", false);
	mf.AllocateLocalStack(MachineType::Int64);  // 8 bytes
	mf.AllocateLocalStack(MachineType::Int8);    // 1 byte
	mf.AllocateLocalStack(MachineType::Float64); // 8 bytes
	EXPECT_EQ(mf.GetLocalStackAllocationSize(), 17);
}

TEST(MachineFunction, TotalStackIncludesArgumentAndLocal)
{
	MachineFunction mf("f", false);
	mf.AllocateLocalStack(MachineType::Int64);
	mf.AllocateArgumentStack(32);
	// Total should include both local (8) and argument (32)
	EXPECT_EQ(mf.GetStackAllocationSize(), 40);
}
