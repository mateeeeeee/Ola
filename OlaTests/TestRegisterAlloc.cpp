#include <gtest/gtest.h>
#include "Backend/Custom/Codegen/RA/InterferenceGraph.h"
#include "Backend/Custom/Codegen/RA/LivenessAnalysis.h"

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
