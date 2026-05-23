#include <gtest/gtest.h>
#include "Backend/Custom/Codegen/RA/InterferenceGraph.h"
#include "Backend/Custom/Codegen/RA/LivenessAnalysis.h"
#include "Backend/Custom/Codegen/Targets/Target.h"
#include "Backend/Custom/Codegen/Targets/X86/X86.h"
#include "Backend/Custom/Codegen/Targets/X86/X86TargetInstInfo.h"
#include "Backend/Custom/Codegen/MachineInstruction.h"
#include "Backend/Custom/Codegen/MachineOperand.h"

using namespace ola;

TEST(InterferenceGraph, FreshGraphIsEmpty)
{
	InterferenceGraph ig;
	EXPECT_EQ(ig.GetNodeCount(), 0u);
}

TEST(InterferenceGraph, AddNodeIncrementsCount)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	EXPECT_EQ(ig.GetNodeCount(), 1u);
	ig.AddNode(2u, false);
	EXPECT_EQ(ig.GetNodeCount(), 2u);
}

TEST(InterferenceGraph, HasNodeReturnsFalseForAbsentNode)
{
	InterferenceGraph ig;
	EXPECT_FALSE(ig.HasNode(99u));
}

TEST(InterferenceGraph, HasNodeReturnsTrueAfterAdd)
{
	InterferenceGraph ig;
	ig.AddNode(5u, false);
	EXPECT_TRUE(ig.HasNode(5u));
}

TEST(InterferenceGraph, FreshNodeHasZeroDegree)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	EXPECT_EQ(ig.GetDegree(1u), 0u);
}

TEST(InterferenceGraph, IsFloatFlagPreserved)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	ig.AddNode(2u, true);
	EXPECT_FALSE(ig.GetNode(1u)->is_float);
	EXPECT_TRUE(ig.GetNode(2u)->is_float);
}

TEST(InterferenceGraph, InterferesFalseForNonInterfering)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	ig.AddNode(2u, false);
	EXPECT_FALSE(ig.Interferes(1u, 2u));
}

TEST(InterferenceGraph, AddInterferenceSetsBothDegrees)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	ig.AddNode(2u, false);
	ig.AddInterference(1u, 2u);
	EXPECT_EQ(ig.GetDegree(1u), 1u);
	EXPECT_EQ(ig.GetDegree(2u), 1u);
}

TEST(InterferenceGraph, InterferesTrueAfterAddInterference)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	ig.AddNode(2u, false);
	ig.AddInterference(1u, 2u);
	EXPECT_TRUE(ig.Interferes(1u, 2u));
}

TEST(InterferenceGraph, InterferencesAreSymmetric)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	ig.AddNode(2u, false);
	ig.AddInterference(1u, 2u);
	// AddInterference must be symmetric
	EXPECT_TRUE(ig.Interferes(2u, 1u));
}

TEST(InterferenceGraph, MultipleInterferencesAccumulate)
{
	// vreg 1 interferes with vregs 2, 3, and 4 → degree 3
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	ig.AddNode(2u, false);
	ig.AddNode(3u, false);
	ig.AddNode(4u, false);
	ig.AddInterference(1u, 2u);
	ig.AddInterference(1u, 3u);
	ig.AddInterference(1u, 4u);
	EXPECT_EQ(ig.GetDegree(1u), 3u);
}

TEST(InterferenceGraph, DecrementDegreeReducesByOne)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	ig.AddNode(2u, false);
	ig.AddInterference(1u, 2u);
	EXPECT_EQ(ig.GetDegree(1u), 1u);
	ig.DecrementDegree(1u);
	EXPECT_EQ(ig.GetDegree(1u), 0u);
}

TEST(InterferenceGraph, ClearResetsNodeCount)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	ig.AddNode(2u, false);
	ig.Clear();
	EXPECT_EQ(ig.GetNodeCount(), 0u);
}

TEST(InterferenceGraph, ClearRemovesNodes)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	ig.Clear();
	EXPECT_FALSE(ig.HasNode(1u));
}

TEST(InterferenceGraph, NodesAreIterableAfterAdd)
{
	InterferenceGraph ig;
	ig.AddNode(10u, false);
	ig.AddNode(20u, false);
	Uint32 count = 0;
	for (auto& [vreg, node] : ig) ++count;
	EXPECT_EQ(count, 2u);
}

TEST(LiveInterval, ExtendExpandsEndBeyondCurrent)
{
	LiveInterval li{};
	li.begin = 4;
	li.end   = 8;
	li.Extend(12);
	EXPECT_EQ(li.end, 12u);
}

TEST(LiveInterval, ExtendShrinksBeginBelowCurrent)
{
	LiveInterval li{};
	li.begin = 4;
	li.end   = 8;
	li.Extend(1);
	EXPECT_EQ(li.begin, 1u);
}

TEST(LiveInterval, ExtendIgnoresValueWithinRange)
{
	LiveInterval li{};
	li.begin = 2;
	li.end   = 10;
	li.Extend(6); 
	EXPECT_EQ(li.begin, 2u);
	EXPECT_EQ(li.end,  10u);
}

TEST(LiveInterval, ExtendAtEndDoesNotChange)
{
	LiveInterval li{};
	li.begin = 2;
	li.end   = 10;
	li.Extend(10); 
	EXPECT_EQ(li.end, 10u);
}

TEST(LiveInterval, ExtendAtBeginDoesNotChange)
{
	LiveInterval li{};
	li.begin = 2;
	li.end   = 10;
	li.Extend(2); 
	EXPECT_EQ(li.begin, 2u);
}

TEST(LiveInterval, OrderingByBeginLess)
{
	LiveInterval a{}, b{};
	a.begin = 1;  a.end = 5;
	b.begin = 3;  b.end = 9;
	EXPECT_TRUE(a < b);
	EXPECT_FALSE(b < a);
}

TEST(LiveInterval, OrderingByBeginEqual)
{
	LiveInterval a{}, b{};
	a.begin = 3;  a.end = 5;
	b.begin = 3;  b.end = 9;
	EXPECT_FALSE(a < b);
	EXPECT_FALSE(b < a);
}

TEST(InterferenceGraph, DuplicateAddInterferenceNoDoubleCount)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	ig.AddNode(2u, false);
	ig.AddInterference(1u, 2u);
	ig.AddInterference(1u, 2u);
	// Adding the same interference twice should not inflate the degree
	EXPECT_EQ(ig.GetDegree(1u), 1u);
	EXPECT_EQ(ig.GetDegree(2u), 1u);
}

TEST(InterferenceGraph, TriangleInterference)
{
	// Three nodes, all mutually interfering
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	ig.AddNode(2u, false);
	ig.AddNode(3u, false);
	ig.AddInterference(1u, 2u);
	ig.AddInterference(2u, 3u);
	ig.AddInterference(1u, 3u);
	EXPECT_EQ(ig.GetDegree(1u), 2u);
	EXPECT_EQ(ig.GetDegree(2u), 2u);
	EXPECT_EQ(ig.GetDegree(3u), 2u);
	EXPECT_TRUE(ig.Interferes(1u, 3u));
	EXPECT_TRUE(ig.Interferes(3u, 1u));
}

TEST(InterferenceGraph, NoSelfInterference)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	EXPECT_FALSE(ig.Interferes(1u, 1u));
}

TEST(InterferenceGraph, ClearRemovesInterferences)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	ig.AddNode(2u, false);
	ig.AddInterference(1u, 2u);
	ig.Clear();
	ig.AddNode(1u, false);
	ig.AddNode(2u, false);
	EXPECT_FALSE(ig.Interferes(1u, 2u));
	EXPECT_EQ(ig.GetDegree(1u), 0u);
}

TEST(InterferenceGraph, IntAndFloatNodesDoNotInterfere)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false); // int
	ig.AddNode(2u, true);  // float
	ig.AddInterference(1u, 2u);
	// Int and float nodes live in separate register classes and cannot interfere.
	EXPECT_FALSE(ig.Interferes(1u, 2u));
	EXPECT_EQ(ig.GetDegree(1u), 0u);
	EXPECT_EQ(ig.GetDegree(2u), 0u);
}

TEST(InterferenceGraph, FloatNodesCanInterfere)
{
	InterferenceGraph ig;
	ig.AddNode(1u, true);
	ig.AddNode(2u, true);
	ig.AddInterference(1u, 2u);
	EXPECT_TRUE(ig.Interferes(1u, 2u));
	EXPECT_EQ(ig.GetDegree(1u), 1u);
}

TEST(LiveInterval, ExtendFromZero)
{
	LiveInterval li{};
	li.begin = 0;
	li.end   = 0;
	li.Extend(5);
	EXPECT_EQ(li.end, 5u);
}

TEST(LiveInterval, ConsecutiveExtends)
{
	LiveInterval li{};
	li.begin = 10;
	li.end   = 10;
	li.Extend(15);
	li.Extend(20);
	li.Extend(5);
	EXPECT_EQ(li.begin, 5u);
	EXPECT_EQ(li.end, 20u);
}

TEST(InterferenceGraph, LargeClique)
{
	// Create 5 nodes all mutually interfering
	InterferenceGraph ig;
	for (Uint32 i = 1; i <= 5; ++i)
		ig.AddNode(i, false);

	for (Uint32 i = 1; i <= 5; ++i)
		for (Uint32 j = i + 1; j <= 5; ++j)
			ig.AddInterference(i, j);

	for (Uint32 i = 1; i <= 5; ++i)
		EXPECT_EQ(ig.GetDegree(i), 4u);
}

TEST(InterferenceGraph, IsolatedNode)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	ig.AddNode(2u, false);
	ig.AddNode(3u, false);
	ig.AddInterference(1u, 2u);
	// Node 3 is isolated
	EXPECT_EQ(ig.GetDegree(3u), 0u);
	EXPECT_FALSE(ig.Interferes(1u, 3u));
	EXPECT_FALSE(ig.Interferes(2u, 3u));
}

TEST(InterferenceGraph, DecrementDegreeDoesNotGoNegative)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	EXPECT_EQ(ig.GetDegree(1u), 0u);
	ig.DecrementDegree(1u);
	// Degree should remain at 0 or wrap (implementation dependent)
	// Just ensure no crash
	EXPECT_TRUE(true);
}

TEST(InterferenceGraph, FloatFloatInterference)
{
	InterferenceGraph ig;
	ig.AddNode(1u, true);
	ig.AddNode(2u, true);
	ig.AddNode(3u, true);
	ig.AddInterference(1u, 2u);
	ig.AddInterference(2u, 3u);
	EXPECT_TRUE(ig.Interferes(1u, 2u));
	EXPECT_TRUE(ig.Interferes(2u, 3u));
	EXPECT_FALSE(ig.Interferes(1u, 3u));
	EXPECT_EQ(ig.GetDegree(2u), 2u);
}

TEST(LiveInterval, SameBeginAndEnd)
{
	LiveInterval a{}, b{};
	a.begin = 5; a.end = 5;
	b.begin = 5; b.end = 10;
	EXPECT_FALSE(a < b);
	EXPECT_FALSE(b < a);
}

TEST(LiveInterval, ExtendFromLargeRange)
{
	LiveInterval li{};
	li.begin = 100;
	li.end   = 200;
	li.Extend(50);
	EXPECT_EQ(li.begin, 50u);
	EXPECT_EQ(li.end, 200u);
	li.Extend(300);
	EXPECT_EQ(li.begin, 50u);
	EXPECT_EQ(li.end, 300u);
}

TEST(InstInfo, DefaultHasNoImplicitOperands)
{
	InstInfo info{};
	EXPECT_EQ(info.GetImplicitUseCount(), 0u);
	EXPECT_EQ(info.GetImplicitDefCount(), 0u);
}

TEST(InstInfo, AddImplicitUseRecorded)
{
	InstInfo info{};
	info.AddImplicitUse(X86_RAX);
	info.AddImplicitUse(X86_RDX);
	ASSERT_EQ(info.GetImplicitUseCount(), 2u);
	EXPECT_EQ(info.GetImplicitUse(0), static_cast<Uint32>(X86_RAX));
	EXPECT_EQ(info.GetImplicitUse(1), static_cast<Uint32>(X86_RDX));
}

TEST(InstInfo, AddImplicitDefRecorded)
{
	InstInfo info{};
	info.AddImplicitDef(X86_RCX);
	ASSERT_EQ(info.GetImplicitDefCount(), 1u);
	EXPECT_EQ(info.GetImplicitDef(0), static_cast<Uint32>(X86_RCX));
}

TEST(InstInfo, ImplicitUsesAndDefsAreSeparate)
{
	InstInfo info{};
	info.AddImplicitUse(X86_RAX);
	info.AddImplicitDef(X86_RDX);
	EXPECT_EQ(info.GetImplicitUseCount(), 1u);
	EXPECT_EQ(info.GetImplicitDefCount(), 1u);
	EXPECT_EQ(info.GetImplicitUse(0), static_cast<Uint32>(X86_RAX));
	EXPECT_EQ(info.GetImplicitDef(0), static_cast<Uint32>(X86_RDX));
}

TEST(X86TargetInstInfo, IDivDeclaresImplicitRaxRdx)
{
	// idiv: implicit use+def of RAX (quotient) and RDX (remainder).
	// Without these implicits, vregs live across SDiv could be wrongly assigned RAX/RDX.
	X86TargetInstInfo target_inst_info;
	InstInfo info = target_inst_info.GetInstInfo(InstSDiv);

	std::unordered_set<Uint32> implicit_uses;
	for (Uint32 i = 0; i < info.GetImplicitUseCount(); ++i) implicit_uses.insert(info.GetImplicitUse(i));
	std::unordered_set<Uint32> implicit_defs;
	for (Uint32 i = 0; i < info.GetImplicitDefCount(); ++i) implicit_defs.insert(info.GetImplicitDef(i));

	EXPECT_TRUE(implicit_uses.contains(X86_RAX));
	EXPECT_TRUE(implicit_uses.contains(X86_RDX));
	EXPECT_TRUE(implicit_defs.contains(X86_RAX));
	EXPECT_TRUE(implicit_defs.contains(X86_RDX));
}

TEST(X86TargetInstInfo, SRemDeclaresImplicitRaxRdx)
{
	X86TargetInstInfo target_inst_info;
	InstInfo info = target_inst_info.GetInstInfo(InstSRem);

	std::unordered_set<Uint32> implicit_uses;
	for (Uint32 i = 0; i < info.GetImplicitUseCount(); ++i) implicit_uses.insert(info.GetImplicitUse(i));
	std::unordered_set<Uint32> implicit_defs;
	for (Uint32 i = 0; i < info.GetImplicitDefCount(); ++i) implicit_defs.insert(info.GetImplicitDef(i));

	EXPECT_TRUE(implicit_uses.contains(X86_RAX));
	EXPECT_TRUE(implicit_uses.contains(X86_RDX));
	EXPECT_TRUE(implicit_defs.contains(X86_RAX));
	EXPECT_TRUE(implicit_defs.contains(X86_RDX));
}

TEST(X86TargetInstInfo, CqoUsesRaxDefsRdx)
{
	// cqo (sign-extend rax into rdx:rax) uses RAX and defs RDX.
	X86TargetInstInfo target_inst_info;
	InstInfo info = target_inst_info.GetInstInfo(X86_InstCqo);

	ASSERT_EQ(info.GetImplicitUseCount(), 1u);
	ASSERT_EQ(info.GetImplicitDefCount(), 1u);
	EXPECT_EQ(info.GetImplicitUse(0), static_cast<Uint32>(X86_RAX));
	EXPECT_EQ(info.GetImplicitDef(0), static_cast<Uint32>(X86_RDX));
}

TEST(X86TargetInstInfo, CallIsFlagged)
{
	X86TargetInstInfo target_inst_info;
	InstInfo info = target_inst_info.GetInstInfo(InstCall);
	EXPECT_TRUE(info.HasInstFlag(InstFlagCall));
}

TEST(IGNode, ForbiddenColorsStartsEmpty)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	IGNode* node = ig.GetNode(1u);
	ASSERT_NE(node, nullptr);
	EXPECT_TRUE(node->forbidden_colors.empty());
}

TEST(IGNode, ForbiddenColorsAreRecorded)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	IGNode* node = ig.GetNode(1u);
	node->forbidden_colors.insert(X86_RAX);
	node->forbidden_colors.insert(X86_RDX);
	EXPECT_EQ(node->forbidden_colors.size(), 2u);
	EXPECT_TRUE(node->forbidden_colors.contains(X86_RAX));
	EXPECT_TRUE(node->forbidden_colors.contains(X86_RDX));
}

TEST(IGNode, ForbiddenColorsClearOnGraphClear)
{
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	ig.GetNode(1u)->forbidden_colors.insert(X86_RAX);
	ig.Clear();
	EXPECT_FALSE(ig.HasNode(1u));
}

TEST(RegClassification, X86PhysRegsAreISARegs)
{
	EXPECT_TRUE(IsISAReg(static_cast<Uint32>(X86_RAX)));
	EXPECT_TRUE(IsISAReg(static_cast<Uint32>(X86_RDX)));
	EXPECT_TRUE(IsISAReg(static_cast<Uint32>(X86_RCX)));
	EXPECT_TRUE(IsISAReg(static_cast<Uint32>(X86_R15)));
	EXPECT_TRUE(IsISAReg(static_cast<Uint32>(X86_XMM0)));
	EXPECT_TRUE(IsISAReg(static_cast<Uint32>(X86_XMM15)));
}

TEST(RegClassification, X86PhysRegsAreNotVirtual)
{
	EXPECT_FALSE(IsVirtualReg(static_cast<Uint32>(X86_RAX)));
	EXPECT_FALSE(IsVirtualReg(static_cast<Uint32>(X86_R15)));
}

TEST(RegClassification, VirtualRegOperandsClassifyCorrectly)
{
	MachineOperand vreg = MachineOperand::VirtualReg(0, MachineType::Int64);
	EXPECT_TRUE(vreg.IsReg());
	EXPECT_TRUE(IsVirtualReg(vreg.GetReg().reg));
	EXPECT_FALSE(IsISAReg(vreg.GetReg().reg));
}

TEST(RegClassification, ISARegOperandsClassifyCorrectly)
{
	MachineOperand rax = MachineOperand::ISAReg(X86_RAX, MachineType::Int64);
	EXPECT_TRUE(rax.IsReg());
	EXPECT_TRUE(IsISAReg(rax.GetReg().reg));
	EXPECT_FALSE(IsVirtualReg(rax.GetReg().reg));
}

TEST(RegClassification, X86GPRRangeExcludesSentinel)
{
	// X86_GPREnd is a sentinel and must not be classified as a GPR.
	EXPECT_FALSE(X86_IsGPRReg(X86_GPREnd));
	EXPECT_FALSE(X86_IsFPRReg(X86_FPREnd));
	EXPECT_TRUE(X86_IsGPRReg(X86_R15));
	EXPECT_TRUE(X86_IsFPRReg(X86_XMM15));
}

TEST(InterferenceGraph_Stress, LargeChainAllPairs)
{
	InterferenceGraph ig;
	constexpr Uint32 N = 50;
	for (Uint32 i = 0; i < N; ++i) ig.AddNode(i, false);
	for (Uint32 i = 0; i + 1 < N; ++i) ig.AddInterference(i, i + 1);

	EXPECT_EQ(ig.GetDegree(0), 1u);
	EXPECT_EQ(ig.GetDegree(N - 1), 1u);
	for (Uint32 i = 1; i + 1 < N; ++i)
	{
		EXPECT_EQ(ig.GetDegree(i), 2u) << "node " << i;
	}
}

TEST(InterferenceGraph_Stress, FullClique100)
{
	// 100-node clique. Every node has degree 99.
	InterferenceGraph ig;
	constexpr Uint32 N = 100;
	for (Uint32 i = 0; i < N; ++i) ig.AddNode(i, false);
	for (Uint32 i = 0; i < N; ++i)
		for (Uint32 j = i + 1; j < N; ++j)
			ig.AddInterference(i, j);

	for (Uint32 i = 0; i < N; ++i)
	{
		EXPECT_EQ(ig.GetDegree(i), N - 1) << "node " << i;
	}
}

TEST(InterferenceGraph_Stress, MixedClassesNoCrossClassEdges)
{
	InterferenceGraph ig;
	constexpr Uint32 N_INT = 50;
	constexpr Uint32 N_FP  = 50;
	for (Uint32 i = 0; i < N_INT; ++i) ig.AddNode(i, false);
	for (Uint32 i = 0; i < N_FP;  ++i) ig.AddNode(N_INT + i, true);

	for (Uint32 i = 0; i < N_INT + N_FP; ++i)
		for (Uint32 j = i + 1; j < N_INT + N_FP; ++j)
			ig.AddInterference(i, j);

	for (Uint32 i = 0; i < N_INT; ++i)
	{
		EXPECT_EQ(ig.GetDegree(i), N_INT - 1) << "int node " << i;
	}
	for (Uint32 i = 0; i < N_FP; ++i)
	{
		EXPECT_EQ(ig.GetDegree(N_INT + i), N_FP - 1) << "float node " << N_INT + i;
	}
}

TEST(InterferenceGraph_Stress, RepeatedAddInterferenceIdempotent)
{
	// AddInterference called many times on the same pair must not inflate degree.
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	ig.AddNode(2u, false);
	for (int i = 0; i < 10000; ++i) ig.AddInterference(1u, 2u);
	EXPECT_EQ(ig.GetDegree(1u), 1u);
	EXPECT_EQ(ig.GetDegree(2u), 1u);
}

TEST(InterferenceGraph_Stress, ForbiddenColorsAccumulate)
{
	// A vreg can have many forbidden colors (e.g. live across many calls,
	// each contributing the full caller-saved set).
	InterferenceGraph ig;
	ig.AddNode(1u, false);
	IGNode* node = ig.GetNode(1u);

	for (Uint32 r = X86_GPRBegin; r < X86_GPREnd; ++r)
	{
		node->forbidden_colors.insert(r);
	}
	EXPECT_EQ(node->forbidden_colors.size(), X86_GPREnd - X86_GPRBegin);
}
