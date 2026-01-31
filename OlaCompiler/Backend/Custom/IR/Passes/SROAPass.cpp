#include "SROAPass.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/IRType.h"
#include "Backend/Custom/IR/Constant.h"

namespace ola
{
	std::vector<SROAPass::FieldInfo> SROAPass::ComputeFieldLayout(IRStructType* struct_type)
	{
		std::vector<FieldInfo> layout;
		Uint32 offset = 0;
		for (Uint32 i = 0; i < struct_type->GetMemberCount(); ++i)
		{
			IRType* field_type = struct_type->GetMemberType(i);
			offset = OLA_ALIGN_UP(offset, field_type->GetAlign());
			layout.push_back({ i, offset, field_type });
			offset += field_type->GetSize();
		}
		return layout;
	}

	Bool SROAPass::IsAllocaSROACandidate(AllocaInst* AI)
	{
		IRType* alloc_type = AI->GetAllocatedType();
		if (!alloc_type->IsStruct())
		{
			return false;
		}

		for (Use* U : AI->Users())
		{
			Value* user = U->GetUser();
			if (PtrAddInst* ptr_add = dyn_cast<PtrAddInst>(user))
			{
				if (!isa<ConstantInt>(ptr_add->GetOffset()))
				{
					return false;
				}

				for (Use* ptr_use : ptr_add->Users())
				{
					Value* ptr_user = ptr_use->GetUser();
					if (!isa<LoadInst>(ptr_user) && !isa<StoreInst>(ptr_user))
					{
						return false;
					}
					if (StoreInst* SI = dyn_cast<StoreInst>(ptr_user))
					{
						if (SI->GetValueOp() == ptr_add)
						{
							return false;
						}
					}
				}
			}
			else if (isa<LoadInst>(user) || isa<StoreInst>(user))
			{
				return false;
			}
			else
			{
				return false;
			}
		}
		return true;
	}

	Bool SROAPass::TryScalarizeAlloca(AllocaInst* AI, BasicBlock& entry_block)
	{
		IRStructType* struct_type = cast<IRStructType>(AI->GetAllocatedType());
		std::vector<FieldInfo> layout = ComputeFieldLayout(struct_type);

		std::unordered_map<Uint32, AllocaInst*> offset_to_alloca;
		Instruction* insert_point = AI->GetNextNode();
		for (FieldInfo const& field : layout)
		{
			AllocaInst* field_alloca = new AllocaInst(field.type);
			if (insert_point)
			{
				field_alloca->InsertBefore(&entry_block, insert_point);
			}
			else
			{
				field_alloca->InsertBefore(&entry_block, entry_block.end());
			}
			offset_to_alloca[field.offset] = field_alloca;
		}

		std::vector<PtrAddInst*> ptr_adds;
		for (Use* U : AI->Users())
		{
			if (PtrAddInst* ptr_add = dyn_cast<PtrAddInst>(U->GetUser()))
			{
				ptr_adds.push_back(ptr_add);
			}
		}

		for (PtrAddInst* ptr_add : ptr_adds)
		{
			ConstantInt* offset_const = cast<ConstantInt>(ptr_add->GetOffset());
			Uint32 offset = static_cast<Uint32>(offset_const->GetValue());

			auto it = offset_to_alloca.find(offset);
			if (it == offset_to_alloca.end())
			{
				return false;
			}

			AllocaInst* field_alloca = it->second;
			ptr_add->ReplaceAllUsesWith(field_alloca);
			ptr_add->EraseFromParent();
		}

		AI->EraseFromParent();
		return true;
	}

	Bool SROAPass::RunOn(Function& F, FunctionAnalysisManager& FAM)
	{
		Bool changed = false;
		BasicBlock& entry_block = F.GetEntryBlock();

		std::vector<AllocaInst*> candidates;
		for (Instruction& I : entry_block)
		{
			if (AllocaInst* AI = dyn_cast<AllocaInst>(&I))
			{
				if (IsAllocaSROACandidate(AI))
				{
					candidates.push_back(AI);
				}
			}
		}

		for (AllocaInst* AI : candidates)
		{
			changed |= TryScalarizeAlloca(AI, entry_block);
		}

		return changed;
	}
}
