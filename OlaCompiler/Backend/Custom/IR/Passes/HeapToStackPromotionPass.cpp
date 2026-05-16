#include <unordered_set>
#include "HeapToStackPromotionPass.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/Constant.h"

namespace ola
{
	Bool HeapToStackPromotionPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		std::vector<HeapAllocation> allocations = FindHeapAllocations(F);
		if (allocations.empty()) 
		{
			return false;
		}

		Bool changed = false;
		for (HeapAllocation const& alloc : allocations)
		{
			Value* ptr = alloc.bitcast ? static_cast<Value*>(alloc.bitcast) : static_cast<Value*>(alloc.alloc_call);
			if (!PointerEscapes(ptr, F))
			{
				changed |= PromoteAllocation(alloc, F);
			}
		}
		return changed;
	}

	std::vector<HeapToStackPromotionPass::HeapAllocation> HeapToStackPromotionPass::FindHeapAllocations(Function& F)
	{
		std::vector<HeapAllocation> result;
		for (BasicBlock& BB : F)
		{
			for (Instruction& I : BB)
			{
				CallInst* call = dyn_cast<CallInst>(&I);
				if (!call) 
				{
					continue;
				}

				Function* callee = call->GetCalleeAsFunction();
				if (!callee || callee->GetName() != "__ola_new") 
				{
					continue;
				}

				HeapAllocation alloc{};
				alloc.alloc_call = call;
				alloc.bitcast = nullptr;
				alloc.allocated_type = nullptr;
				alloc.alloc_size = 0;
				if (call->ArgSize() > 0)
				{
					Value const* size_arg = call->GetArgOp(0);
					if (ConstantInt const* size_const = dyn_cast<ConstantInt>(size_arg))
					{
						alloc.alloc_size = size_const->GetValue();
					}
					else if (Instruction* size_inst = dyn_cast<Instruction>(const_cast<Value*>(size_arg)))
					{
						if (BinaryInst* mul = dyn_cast<BinaryInst>(size_inst);
							mul && mul->GetOpcode() == Opcode::SMul)
						{
							ConstantInt* lhs = dyn_cast<ConstantInt>(mul->GetLHS());
							ConstantInt* rhs = dyn_cast<ConstantInt>(mul->GetRHS());
							if (lhs && rhs)
							{
								alloc.alloc_size = lhs->GetValue() * rhs->GetValue();
							}
							else if (lhs && lhs->GetValue() == 1 && rhs)
							{
								alloc.alloc_size = rhs->GetValue();
							}
							else if (rhs && rhs->GetValue() == 1 && lhs)
							{
								alloc.alloc_size = lhs->GetValue();
							}
						}
					}
				}

				if (!call->HasOneUse())
				{
					continue;
				}
				for (Use* U : call->Users())
				{
					if (CastInst* cast_inst = dyn_cast<CastInst>(U->GetUser()))
					{
						if (cast_inst->GetOpcode() == Opcode::Bitcast)
						{
							alloc.bitcast = cast_inst;
							IRType* dest_type = cast_inst->GetDestType();
							if (IRPtrType* ptr_type = dyn_cast<IRPtrType>(dest_type))
							{
								alloc.allocated_type = ptr_type->GetPointeeType();
							}
							break;
						}
					}
				}

				if (alloc.allocated_type && alloc.alloc_size > 0)
				{
					result.push_back(alloc);
				}
			}
		}
		return result;
	}

	void HeapToStackPromotionPass::CollectDerivedPointers(Value* root, std::vector<Value*>& derived)
	{
		std::vector<Value*> worklist = { root };
		std::unordered_set<Value*> visited;
		while (!worklist.empty())
		{
			Value* current = worklist.back();
			worklist.pop_back();
			if (!visited.insert(current).second)
			{
				continue;
			}
			derived.push_back(current);

			TrackableValue* tv = dyn_cast<TrackableValue>(current);
			if (!tv)
			{
				continue;
			}
			for (Use* U : tv->Users())
			{
				Instruction* user = U->GetUser();
				if (isa<GetElementPtrInst>(user) || isa<PtrAddInst>(user))
				{
					worklist.push_back(user);
				}
				else if (CastInst* cast_inst = dyn_cast<CastInst>(user))
				{
					if (cast_inst->GetOpcode() == Opcode::Bitcast)
					{
						worklist.push_back(cast_inst);
					}
				}
				else if (StoreInst* store = dyn_cast<StoreInst>(user))
				{
					if (store->GetValueOp() == current)
					{
						if (AllocaInst* alloca = dyn_cast<AllocaInst>(store->GetAddressOp()))
						{
							for (Use* AU : alloca->Users())
							{
								if (LoadInst* load = dyn_cast<LoadInst>(AU->GetUser()))
								{
									worklist.push_back(load);
								}
							}
						}
					}
				}
			}
		}
	}

	Bool HeapToStackPromotionPass::PointerEscapes(Value* ptr, Function& F)
	{
		std::vector<Value*> derived;
		CollectDerivedPointers(ptr, derived);
		for (Value* v : derived)
		{
			TrackableValue* tv = dyn_cast<TrackableValue>(v);
			if (!tv) 
			{
				continue;
			}

			for (Use* U : tv->Users())
			{
				Instruction* user = U->GetUser();
				if (isa<GetElementPtrInst>(user) || isa<PtrAddInst>(user))
				{
					continue;
				}
				if (CastInst* cast_inst = dyn_cast<CastInst>(user);
					cast_inst && cast_inst->GetOpcode() == Opcode::Bitcast)
				{
					continue;
				}

				if (isa<LoadInst>(user))
				{
					continue;
				}

				if (StoreInst* store = dyn_cast<StoreInst>(user))
				{
					if (store->GetAddressOp() == v)
					{
						continue;
					}
					Value* store_addr = store->GetAddressOp();
					if (AllocaInst* alloca_dst = dyn_cast<AllocaInst>(store_addr))
					{
						Bool alloca_address_escapes = false;
						for (Use* AU : alloca_dst->Users())
						{
							Instruction* alloca_user = AU->GetUser();
							if (isa<LoadInst>(alloca_user))
							{
								continue;
							}
							if (StoreInst* alloca_store = dyn_cast<StoreInst>(alloca_user);
								alloca_store && alloca_store->GetAddressOp() == alloca_dst)
							{
								continue;
							}
							alloca_address_escapes = true;
							break;
						}
						if (alloca_address_escapes)
						{
							return true;
						}
						continue;
					}
					if (dyn_cast<GetElementPtrInst>(store_addr))
					{
						std::vector<Value*> addr_derived;
						CollectDerivedPointers(ptr, addr_derived);
						Bool store_to_self = false;
						for (Value* d : addr_derived)
						{
							if (d == store_addr) 
							{ 
								store_to_self = true; 
								break; 
							}
						}
						if (store_to_self) 
						{
							continue;
						}
					}
					return true;
				}

				if (isa<ReturnInst>(user))
				{
					return true;
				}

				if (CallInst* call = dyn_cast<CallInst>(user))
				{
					Function* callee = call->GetCalleeAsFunction();
					if (callee && callee->GetName() == "__ola_delete")
					{
						continue;
					}
					if (callee && !callee->IsDeclaration())
					{
						Bool ptr_is_arg = false;
						for (auto const& arg_use : call->Args())
						{
							if (arg_use.GetValue() == v) { ptr_is_arg = true; break; }
						}
						if (ptr_is_arg) return true;
					}
					else if (callee && callee->IsDeclaration())
					{
						return true;
					}
					else
					{
						return true;
					}
					continue;
				}

				if (isa<PhiInst>(user) || isa<SelectInst>(user))
				{
					return true;
				}
			}
		}
		return false;
	}

	Bool HeapToStackPromotionPass::PromoteAllocation(HeapAllocation const& alloc, Function& F)
	{
		Uint64 type_size = alloc.allocated_type->GetSize();
		if (type_size == 0 || alloc.alloc_size > type_size)
		{
			return false;
		}

		BasicBlock& entry = F.GetEntryBlock();
		AllocaInst* stack_slot = new AllocaInst(alloc.allocated_type);
		stack_slot->InsertBefore(&entry, entry.begin());

		Instruction* old_ptr = alloc.bitcast ? static_cast<Instruction*>(alloc.bitcast) : static_cast<Instruction*>(alloc.alloc_call);
		old_ptr->ReplaceAllUsesWith(stack_slot);
		RemoveMatchingDeletes(stack_slot, F);
		if (alloc.bitcast)
		{
			alloc.bitcast->EraseFromParent();
		}
		alloc.alloc_call->EraseFromParent();
		return true;
	}

	void HeapToStackPromotionPass::RemoveMatchingDeletes(Value* ptr, Function& F)
	{
		std::vector<Instruction*> to_remove;

		std::vector<Value*> derived;
		CollectDerivedPointers(ptr, derived);
		for (Value* v : derived)
		{
			TrackableValue* tv = dyn_cast<TrackableValue>(v);
			if (!tv) 
			{
				continue;
			}

			for (Use* U : tv->Users())
			{
				CallInst* call = dyn_cast<CallInst>(U->GetUser());
				if (!call) continue;
				Function* callee = call->GetCalleeAsFunction();
				if (!callee || callee->GetName() != "__ola_delete") 
				{
					continue;
				}

				to_remove.push_back(call);
				if (Instruction* v_inst = dyn_cast<Instruction>(v))
				{
					if (isa<CastInst>(v_inst) && v_inst->HasOneUse())
					{
						to_remove.push_back(v_inst);
					}
				}
			}
		}

		for (auto it = to_remove.rbegin(); it != to_remove.rend(); ++it)
		{
			(*it)->EraseFromParent();
		}
	}
}
