#pragma once
#include <vector>
#include <memory>
#include <unordered_map>

namespace ola
{
	class Function;
	class CallInst;
	class IRModule;
	class CallGraphNode;

	// From LLVM CallGraph.h
	// A pair of the calling instruction (a call or invoke)
    // and the call graph node being called.
    // Call graph node may have two types of call records which represent an edge
    // in the call graph - reference or a call edge. Reference edges are not
    // associated with any call instruction and are created with the first field
    // set to `None`, while real call edges have instruction address in this
    // field. Therefore, all real call edges are expected to have a value in the
    // first field and it is not supposed to be `nullptr`.
    // Reference edges, for example, are used for connecting broker function
    // caller to the callback function for callback call sites.
    // using CallRecord = std::pair<std::optional<WeakTrackingVH>, CallGraphNode *>;
	struct CallRecord
	{
		CallInst* call_site;      
		CallGraphNode* callee;    
		CallRecord(CallInst* cs, CallGraphNode* node) : call_site(cs), callee(node) {}
	};

	/// From LLVM CallGraph.h
	/// A node in the call graph for a module.
	/// Typically represents a function in the call graph. There are also special
	/// "null" nodes used to represent theoretical entries in the call graph.
	class CallGraphNode
	{
		friend class CallGraph;
	public:
		using iterator = std::vector<CallRecord>::iterator;
		using const_iterator = std::vector<CallRecord>::const_iterator;

		explicit CallGraphNode(Function* F) : function(F), num_references(0) {}
		Function* GetFunction() const { return function; }

		Uint32 GetNumReferences() const { return num_references; }

		iterator begin() { return call_records.begin(); }
		iterator end() { return call_records.end(); }
		const_iterator begin() const { return call_records.begin(); }
		const_iterator end() const { return call_records.end(); }
		Uint64 size() const { return call_records.size(); }
		Bool empty() const { return call_records.empty(); }

		void AddCalledFunction(CallInst* CI, CallGraphNode* Callee)
		{
			call_records.emplace_back(CI, Callee);
			if (Callee) 
			{
				Callee->num_references++;
			}
		}

		void RemoveCallRecord(CallInst* CI)
		{
			for (auto it = call_records.begin(); it != call_records.end(); ++it)
			{
				if (it->call_site == CI)
				{
					if (it->callee) 
					{
						it->callee->num_references--;
					}
					call_records.erase(it);
					return;
				}
			}
		}

		void RemoveAllCallsTo(CallGraphNode* Callee)
		{
			auto it = call_records.begin();
			while (it != call_records.end())
			{
				if (it->callee == Callee)
				{
					Callee->num_references--;
					it = call_records.erase(it);
				}
				else
				{
					++it;
				}
			}
		}

	private:
		Function* function;
		std::vector<CallRecord> call_records;
		Uint32 num_references;
	};

	class CallGraph
	{
	public:
		using iterator = std::unordered_map<Function const*, std::unique_ptr<CallGraphNode>>::iterator;
		using const_iterator = std::unordered_map<Function const*, std::unique_ptr<CallGraphNode>>::const_iterator;

		explicit CallGraph(IRModule& M);
		~CallGraph() = default;

		IRModule& GetModule() const { return *module; }

		CallGraphNode* GetOrCreateNode(Function* F);
		CallGraphNode* GetNode(Function const* F) const
		{
			auto it = function_map.find(F);
			return it != function_map.end() ? it->second.get() : nullptr;
		}

		CallGraphNode& operator[](Function const* F) const
		{
			auto it = function_map.find(F);
			OLA_ASSERT(it != function_map.end());
			return *it->second;
		}

		CallGraphNode* GetExternalCallingNode() const { return external_calling_node.get(); }
		CallGraphNode* GetCallsExternalNode() const { return calls_external_node.get(); }

		CallGraphNode* AddFunction(Function* F);
		void RemoveFunction(Function* F);
		std::vector<CallInst*> GetCallSitesTo(Function const* F) const;

		iterator begin() { return function_map.begin(); }
		iterator end() { return function_map.end(); }
		const_iterator begin() const { return function_map.begin(); }
		const_iterator end() const { return function_map.end(); }
		Uint64 size() const { return function_map.size(); }

	private:
		IRModule* module;
		std::unordered_map<Function const*, std::unique_ptr<CallGraphNode>> function_map;
		std::unique_ptr<CallGraphNode> external_calling_node; 
		std::unique_ptr<CallGraphNode> calls_external_node;    

	private:
		void BuildCallGraph();
		void AddToCallGraph(Function* F);
	};
}
