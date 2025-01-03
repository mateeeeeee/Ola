#include "IRType.h"
#include "Instruction.h"
#include "BasicBlock.h"
#include "GlobalValue.h"
#include "Constant.h"

namespace ola
{
	static Char const* OpcodeNames[] =
	{
		"none",

		"ret",
		"br",
		"switch",

		"load",
		"store",

		"add",
		"sub",
		"smul",
		"sdiv",
		"srem",
		"neg",

		"not",
		"and",
		"or",
		"xor",
		"shl",
		"lshr",
		"ashr",

		"fadd",
		"fsub",
		"fmul",
		"fdiv",
		"fneg",
		"ffma",

		"icmp eq",
		"icmp ne",
		"icmp slt",
		"icmp sle",
		"icmp sgt",
		"icmp sge",
		"icmp ult",
		"icmp ule",
		"icmp ugt",
		"icmp uge",

		"fcmp oeq",
		"fcmp one",
		"fcmp olt",
		"fcmp ole",
		"fcmp ogt",
		"fcmp oge",
		"fcmp ueq",
		"fcmp une",
		"fcmp ult",
		"fcmp ule",
		"fcmp ugt",
		"fcmp uge",

		"zext",
		"bitcast",
		"f2s",
		"s2f",

		"alloca",
		"gep",
		"ptr add",
		"select",
		"call",
		"phi"
	};
	static_assert((Uint32)Opcode::Count == std::size(OpcodeNames));

	Use::Use(Value* val, Instruction* user) : value(val), user(user)
	{
		if (TrackableValue* trackable_value = dyn_cast<TrackableValue>(value))
		{
			trackable_value->AddUse(this);
		}
	}

	Use::~Use() {}

	void Use::Set(Value* V)
	{
		if (TrackableValue* trackable_value = dyn_cast<TrackableValue>(value))
		{
			trackable_value->RemoveUse(this);
		}
		value = V;
		if (TrackableValue* trackable_value = dyn_cast<TrackableValue>(value))
		{
			trackable_value->AddUse(this);
		}
	}

	Char const* Instruction::GetOpcodeName() const
	{
		return OpcodeNames[(Uint32)GetOpcode()];
	}

	IListIterator<Instruction> Instruction::InsertBefore(BasicBlock* BB, Instruction* I)
	{
		return InsertBefore(BB, I->GetIterator());
	}

	IListIterator<Instruction> Instruction::InsertBefore(BasicBlock* BB, IListIterator<Instruction> IT)
	{
		if (basic_block) 
		{
			basic_block->Instructions().Remove(this);
		}
		basic_block = BB;
		return BB->Instructions().Insert(IT, this);
	}

	void Instruction::RemoveFromParent()
	{
		basic_block->Instructions().Remove(this);
	}

	IListIterator<Instruction> Instruction::EraseFromParent()
	{
		return basic_block->Instructions().Erase(this);
	}

	Bool Instruction::CanBeOperand() const
	{
		return true;
	}

	LoadInst::LoadInst(Value* address) 
		: Instruction( Opcode::Load, cast<IRPtrType>(address->GetType())->GetPointeeType(), {address})
	{
		OLA_ASSERT(isa<IRPtrType>(address->GetType()));
	}

	LoadInst::LoadInst(Value* address, IRType* type)
		: Instruction(Opcode::Load, type, { address })
	{
		OLA_ASSERT(isa<IRPtrType>(address->GetType()));
	}

	StoreInst::StoreInst(Value* value, Value* address) : Instruction(Opcode::Store, IRVoidType::Get(value->GetContext()), { value, address })
	{
	}

	BranchInst::BranchInst(IRContext& C, BasicBlock* target) 
		: Instruction(Opcode::Branch, IRVoidType::Get(C), { target }), true_target(target), false_target(nullptr)
	{
	}

	BranchInst::BranchInst(Value* condition, BasicBlock* true_target, BasicBlock* false_target) 
		: Instruction(Opcode::Branch, IRVoidType::Get(condition->GetContext()), { true_target, false_target, condition }),
		true_target(true_target), false_target(false_target)
	{
	}

	ReturnInst::ReturnInst(IRContext& C) : Instruction(Opcode::Ret, IRVoidType::Get(C), {})
	{
	}

	ReturnInst::ReturnInst(Value* ret_value) : Instruction(Opcode::Ret, IRVoidType::Get(ret_value->GetContext()), { ret_value })
	{
	}

	SwitchInst::SwitchInst(Value* val, BasicBlock* default_block) : Instruction{ Opcode::Switch, IRVoidType::Get(val->GetContext()), { val } }, default_block{ default_block }
	{

	}

	CallInst::CallInst(Value* callee, std::span<Value*> args) : Instruction(Opcode::Call, cast<Function>(callee)->GetReturnType(), {})
	{
		for (Value* arg : args) AddOperand(arg);
		AddOperand(callee);
	}

	Function* CallInst::GetCalleeAsFunction() const
	{
		if (Function* F = dyn_cast<Function>(GetCallee())) return F;
		else return nullptr;
	}

	Function* CallInst::GetCaller() const
	{
		return GetBasicBlock()->GetFunction();
	}

	AllocaInst::AllocaInst(IRType* type) : Instruction(Opcode::Alloca, IRPtrType::Get(type), {}), allocated_type(type)
	{
	}

	IRPtrType* AllocaInst::GetPtrType() const
	{
		return cast<IRPtrType>(GetType());
	}

	IRType* GetElementPtrInst::GetValueType(Value* base, std::span<Value*> indices)
	{
		OLA_ASSERT(base->GetType()->IsPointer());
		IRType* current_type = base->GetType();
		for (Value* index : indices)
		{
			if (index->GetType()->IsInteger()) 
			{
				if (IRArrayType* array_type = dyn_cast<IRArrayType>(current_type)) 
				{
					current_type = array_type->GetElementType();
				}
				else if (IRPtrType* pointer_type = dyn_cast<IRPtrType>(current_type))
				{
					current_type = pointer_type->GetPointeeType();
				}
				else OLA_ASSERT(false);
			}
			else OLA_ASSERT(false);
		}
		return current_type;
	}

	GetElementPtrInst::GetElementPtrInst(Value* base, std::span<Value*> indices)
		: Instruction{ Opcode::GetElementPtr, base->GetType(), {} },
		result_element_type(GetValueType(base, indices))
	{
		OLA_ASSERT(base->GetType()->IsPointer());
		source_element_type = cast<IRPtrType>(base->GetType())->GetPointeeType(); 

		AddOperand(base);
		for (Value* index : indices) AddOperand(index);
	}

	CompareInst::CompareInst(Opcode id, Value* lhs, Value* rhs) : Instruction(id, IRIntType::Get(lhs->GetContext(), 1), {lhs, rhs})
	{
		Uint32 id_int = (Uint32)id;
		OLA_ASSERT(id_int >= (Uint32)Opcode::CompareOpBegin && id_int <= (Uint32)Opcode::CompareOpEnd);
		cmp = (CompareOp)(id_int - (Uint32)Opcode::CompareOpBegin);
	}

	PtrAddInst::PtrAddInst(Value* base, Value* offset, IRType* result_element_type) : Instruction(Opcode::PtrAdd, base->GetType(), { base, offset }),
		result_element_type(result_element_type)
	{
		OLA_ASSERT(base->GetType()->IsPointer());
		OLA_ASSERT(isa<ConstantInt>(offset));
	}

	void TrackableValue::ReplaceAllUsesWith(Value* V)
	{
		while (!users.empty())
		{
			Use* const& U = *users.begin();
			U->Set(V);
		}
	}

}