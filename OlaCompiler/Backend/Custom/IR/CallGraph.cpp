#include "CallGraph.h"
#include "IRModule.h"
#include "GlobalValue.h"
#include "Instruction.h"

namespace ola
{
	CallGraph::CallGraph(IRModule& M) : module(&M)
	{
		external_calling_node = std::make_unique<CallGraphNode>(nullptr);
		calls_external_node = std::make_unique<CallGraphNode>(nullptr);
		BuildCallGraph();
	}

	void CallGraph::BuildCallGraph()
	{
		for (GlobalValue* G : module->Globals())
		{
			if (Function* F = dyn_cast<Function>(G))
			{
				GetOrCreateNode(F);
			}
		}

		for (GlobalValue* G : module->Globals())
		{
			if (Function* F = dyn_cast<Function>(G))
			{
				AddToCallGraph(F);
			}
		}
	}

	void CallGraph::AddToCallGraph(Function* F)
	{
		CallGraphNode* CallerNode = GetNode(F);
		OLA_ASSERT(CallerNode);

		if (F->GetLinkage() != Linkage::Internal)
		{
			external_calling_node->AddCalledFunction(nullptr, CallerNode);
		}

		if (F->IsDeclaration())
		{
			return;
		}

		for (BasicBlock& BB : *F)
		{
			for (Instruction& I : BB)
			{
				if (CallInst* CI = dyn_cast<CallInst>(&I))
				{
					Function* Callee = CI->GetCalleeAsFunction();
					if (Callee)
					{
						CallGraphNode* CalleeNode = GetOrCreateNode(Callee);
						CallerNode->AddCalledFunction(CI, CalleeNode);
					}
					else
					{
						CallerNode->AddCalledFunction(CI, calls_external_node.get());
					}
				}
			}
		}
	}

	CallGraphNode* CallGraph::GetOrCreateNode(Function* F)
	{
		auto& NodePtr = function_map[F];
		if (!NodePtr)
		{
			NodePtr = std::make_unique<CallGraphNode>(F);
		}
		return NodePtr.get();
	}

	CallGraphNode* CallGraph::AddFunction(Function* F)
	{
		CallGraphNode* Node = GetOrCreateNode(F);
		AddToCallGraph(F);
		return Node;
	}

	void CallGraph::RemoveFunction(Function* F)
	{
		CallGraphNode* Node = GetNode(F);
		if (!Node) 
		{
			return;
		}

		for (CallRecord& CR : *Node)
		{
			if (CR.callee)
			{
				CR.callee->num_references--;
			}
		}

		for (auto& [Func, FuncNode] : function_map)
		{
			if (FuncNode.get() != Node)
			{
				FuncNode->RemoveAllCallsTo(Node);
			}
		}
		external_calling_node->RemoveAllCallsTo(Node);
		function_map.erase(F);
	}

	std::vector<CallInst*> CallGraph::GetCallSitesTo(Function const* F) const
	{
		std::vector<CallInst*> CallSites;
		CallGraphNode* TargetNode = GetNode(F);
		if (!TargetNode) 
		{
			return CallSites;
		}

		for (auto const& [Func, FuncNode] : function_map)
		{
			for (CallRecord const& CR : *FuncNode)
			{
				if (CR.callee == TargetNode && CR.call_site)
				{
					CallSites.push_back(CR.call_site);
				}
			}
		}
		return CallSites;
	}
}
