#include "DevirtualizationPass.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/IR/Constant.h"
#include <algorithm>

namespace ola
{
	Bool DevirtualizationPass::RunOn(IRModule& M, IRModuleAnalysisManager& MAM)
	{
		BuildVTableMap(M);

		Bool changed = false;
		for (GlobalValue* G : M.Globals())
		{
			if (Function* F = dyn_cast<Function>(G); F && !F->IsDeclaration())
			{
				changed |= RunOnFunction(*F);
			}
		}
		return changed;
	}

	void DevirtualizationPass::BuildVTableMap(IRModule& M)
	{
		vtable_slot_map.clear();
		vtable_to_class.clear();
		for (GlobalValue* GV : M.Globals())
		{
			GlobalVariable* G = dyn_cast<GlobalVariable>(GV);
			if (!G)
			{
				continue;
			}

			std::string_view name = G->GetName();
			if (!name.starts_with("VTable_"))
			{
				continue;
			}

			std::string class_name(name.substr(7));
			vtable_to_class[G] = class_name;

			if (ConstantArray* arr = dyn_cast<ConstantArray>(G->GetInitValue()))
			{
				std::vector<Constant*> const& values = arr->Values();
				for (Uint32 i = 0; i < values.size(); ++i)
				{
					if (Function* F = dyn_cast<Function>(values[i]))
					{
						vtable_slot_map[i].emplace_back(G, F);
					}
				}
			}
		}
	}

	std::optional<std::pair<LoadInst*, Uint32>> DevirtualizationPass::MatchVTablePattern(CallInst* CI)
	{
		LoadInst* func_load = dyn_cast<LoadInst>(CI->GetCallee());
		if (!func_load)
		{
			return std::nullopt;
		}

		Value* func_ptr_addr = func_load->GetAddressOp();
		Uint32 vtable_idx = 0;
		LoadInst* vtable_load = nullptr;
		if (PtrAddInst* ptr_add = dyn_cast<PtrAddInst>(func_ptr_addr))
		{
			ConstantInt* offset = dyn_cast<ConstantInt>(ptr_add->GetOffset());
			if (!offset)
			{
				return std::nullopt;
			}
			OLA_ASSERT(offset->GetValue() % 8 == 0);
			vtable_idx = static_cast<Uint32>(offset->GetValue() / 8);
			vtable_load = dyn_cast<LoadInst>(ptr_add->GetBase());
		}
		else if (GetElementPtrInst* gep = dyn_cast<GetElementPtrInst>(func_ptr_addr))
		{
			if (gep->GetNumIndices() != 1)
			{
				return std::nullopt;
			}
			ConstantInt* idx = dyn_cast<ConstantInt>(gep->GetIndex(0));
			if (!idx)
			{
				return std::nullopt;
			}
			vtable_idx = static_cast<Uint32>(idx->GetValue());
			vtable_load = dyn_cast<LoadInst>(gep->GetBaseOperand());
		}
		else
		{
			return std::nullopt;
		}

		if (!vtable_load)
		{
			return std::nullopt;
		}
		return std::make_pair(vtable_load, vtable_idx);
	}

	GlobalVariable* DevirtualizationPass::TraceVTableSource(LoadInst* vtable_load)
	{
		Value* vtable_ptr_addr = vtable_load->GetAddressOp();
		AllocaInst* alloca = nullptr;
		if (PtrAddInst* ptr_add = dyn_cast<PtrAddInst>(vtable_ptr_addr))
		{
			ConstantInt* offset = dyn_cast<ConstantInt>(ptr_add->GetOffset());
			if (!offset || offset->GetValue() != 0)
			{
				return nullptr;
			}
			alloca = dyn_cast<AllocaInst>(ptr_add->GetBase());
		}
		else if (GetElementPtrInst* gep = dyn_cast<GetElementPtrInst>(vtable_ptr_addr))
		{
			if (gep->GetNumIndices() != 2)
			{
				return nullptr;
			}
			ConstantInt* idx0 = dyn_cast<ConstantInt>(gep->GetIndex(0));
			ConstantInt* idx1 = dyn_cast<ConstantInt>(gep->GetIndex(1));
			if (!idx0 || !idx1)
			{
				return nullptr;
			}
			if (idx0->GetValue() != 0 || idx1->GetValue() != 0)
			{
				return nullptr;
			}
			alloca = dyn_cast<AllocaInst>(gep->GetBaseOperand());
		}

		if (!alloca)
		{
			return nullptr;
		}

		GlobalVariable* found_vtable = nullptr;
		for (Use* use : alloca->Users())
		{
			Instruction* user = dyn_cast<Instruction>(use->GetUser());
			if (!user)
			{
				continue;
			}

			if (PtrAddInst* ptr_add = dyn_cast<PtrAddInst>(user))
			{
				ConstantInt* offset = dyn_cast<ConstantInt>(ptr_add->GetOffset());
				if (!offset || offset->GetValue() != 0)
				{
					continue;
				}

				for (Use* ptr_add_use : ptr_add->Users())
				{
					if (StoreInst* store = dyn_cast<StoreInst>(ptr_add_use->GetUser()))
					{
						if (store->GetAddressOp() != ptr_add)
						{
							continue;
						}

						GlobalVariable* vtable = dyn_cast<GlobalVariable>(store->GetValueOp());
						if (!vtable || !vtable->GetName().starts_with("VTable_"))
						{
							return nullptr;
						}

						if (found_vtable && found_vtable != vtable)
						{
							return nullptr;
						}

						found_vtable = vtable;
					}
				}
			}
			else if (GetElementPtrInst* gep = dyn_cast<GetElementPtrInst>(user))
			{
				if (gep->GetNumIndices() != 2)
				{
					continue;
				}
				ConstantInt* idx0 = dyn_cast<ConstantInt>(gep->GetIndex(0));
				ConstantInt* idx1 = dyn_cast<ConstantInt>(gep->GetIndex(1));
				if (!idx0 || !idx1)
				{
					continue;
				}
				if (idx0->GetValue() != 0 || idx1->GetValue() != 0)
				{
					continue;
				}

				for (Use* gep_use : gep->Users())
				{
					if (StoreInst* store = dyn_cast<StoreInst>(gep_use->GetUser()))
					{
						GlobalVariable* vtable = dyn_cast<GlobalVariable>(store->GetValueOp());
						if (!vtable || !vtable->GetName().starts_with("VTable_"))
						{
							return nullptr;
						}
						if (found_vtable && found_vtable != vtable)
						{
							return nullptr;
						}
						found_vtable = vtable;
					}
				}
			}
		}
		return found_vtable;
	}

	Bool DevirtualizationPass::DevirtualizeCall(CallInst* CI, Function* target)
	{
		CI->SetOperand(CI->GetNumOperands() - 1, target);
		return true;
	}

	Bool DevirtualizationPass::RunOnFunction(Function& F)
	{
		Bool changed = false;
		std::vector<std::pair<CallInst*, Function*>> to_devirtualize;
		for (BasicBlock& BB : F)
		{
			for (Instruction& I : BB)
			{
				CallInst* CI = dyn_cast<CallInst>(&I);
				if (!CI || !CI->IsIndirect())
				{
					continue;
				}

				auto pattern = MatchVTablePattern(CI);
				if (!pattern)
				{
					continue;
				}

				auto [vtable_load, vtable_idx] = *pattern;
				if (GlobalVariable* vtable = TraceVTableSource(vtable_load))
				{
					if (ConstantArray* arr = dyn_cast<ConstantArray>(vtable->GetInitValue()))
					{
						std::vector<Constant*> const& values = arr->Values();
						if (vtable_idx < values.size())
						{
							if (Function* target = dyn_cast<Function>(values[vtable_idx]))
							{
								to_devirtualize.push_back({ CI, target });
								continue;
							}
						}
					}
				}

				auto it = vtable_slot_map.find(vtable_idx);
				if (it != vtable_slot_map.end() && !it->second.empty())
				{
					Function* first = it->second[0].func;
					Bool all_same = std::all_of(it->second.begin(), it->second.end(),
						[first](VTableEntry const& e) { return e.func == first; });

					if (all_same && first)
					{
						to_devirtualize.push_back({ CI, first });
					}
				}
			}
		}

		for (auto& [CI, target] : to_devirtualize)
		{
			changed |= DevirtualizeCall(CI, target);
		}

		return changed;
	}
}
