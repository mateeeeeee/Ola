#include "IRInterpreter.h"
#include "Core/Log.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/IRContext.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/BasicBlock.h"
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/IR/Constant.h"
#include "Backend/Custom/IR/IRType.h"
#include <cmath>

namespace ola
{
	IRInterpreter::IRInterpreter(IRModule& module)
		: module(module)
		, memory()
		, intrinsics(memory)
	{
	}

	Int IRInterpreter::Execute()
	{
		InitializeGlobals();
		Function* main_func = FindMainFunction();
		if (!main_func)
		{
			OLA_ERROR("No main function found!");
			return -1;
		}

		std::vector<InterpreterValue> args;
		ExecuteFunction(main_func, args);
		if (!call_stack.empty())
		{
			InterpreterValue ret = call_stack.top().GetReturnValue();
			return static_cast<Int>(ret.AsInt());
		}
		return 0;
	}

	Function* IRInterpreter::FindMainFunction()
	{
		for (GlobalValue* gv : module.Globals())
		{
			if (Function* func = dyn_cast<Function>(gv))
			{
				if (func->GetName() == "main")
				{
					return func;
				}
			}
		}
		return nullptr;
	}

	void IRInterpreter::InitializeGlobals()
	{
		for (GlobalValue* gv : module.Globals())
		{
			if (GlobalVariable* global_var = dyn_cast<GlobalVariable>(gv))
			{
				IRType* type = global_var->GetValueType();
				Uint8* addr = memory.AllocGlobal(global_var, type->GetSize(), type->GetAlign());

				if (Value* init = global_var->GetInitValue())
				{
					InitializeGlobalValue(addr, init);
				}
			}
		}
	}

	void IRInterpreter::InitializeGlobalValue(Uint8* addr, Value* init_val)
	{
		if (ConstantInt* ci = dyn_cast<ConstantInt>(init_val))
		{
			memory.StoreInt(addr, ci->GetValue(), ci->GetType()->GetSize());
		}
		else if (ConstantFloat* cf = dyn_cast<ConstantFloat>(init_val))
		{
			memory.StoreFloat(addr, cf->GetValue());
		}
		else if (ConstantString* cs = dyn_cast<ConstantString>(init_val))
		{
			std::string_view str = cs->GetValue();
			memory.Store(addr, str.data(), static_cast<Uint32>(str.size() + 1));
		}
		else if (ConstantArray* ca = dyn_cast<ConstantArray>(init_val))
		{
			IRArrayType* arr_type = ca->GetArrayType();
			IRType* elem_type = arr_type->GetElementType();
			Uint32 elem_size = elem_type->GetSize();
			for (Uint32 i = 0; i < ca->Values().size(); ++i)
			{
				InitializeGlobalValue(addr + i * elem_size, ca->Values()[i]);
			}
		}
		else if (ConstantStruct* cs = dyn_cast<ConstantStruct>(init_val))
		{
			IRStructType* struct_type = cs->GetStructType();
			Uint32 offset = 0;
			for (Uint32 i = 0; i < cs->Values().size(); ++i)
			{
				IRType* field_type = struct_type->GetMemberType(i);
				offset = (offset + field_type->GetAlign() - 1) & ~(field_type->GetAlign() - 1);
				InitializeGlobalValue(addr + offset, cs->Values()[i]);
				offset += field_type->GetSize();
			}
		}
		else if (isa<UndefValue>(init_val))
		{
		}
		else if (GlobalVariable* ref_gv = dyn_cast<GlobalVariable>(init_val))
		{
			Uint8* target_addr = memory.GetGlobalAddress(ref_gv);
			memory.StorePointer(addr, target_addr);
		}
		else if (Function* func = dyn_cast<Function>(init_val))
		{
			memory.StorePointer(addr, reinterpret_cast<Uint8*>(func));
		}
	}

	void IRInterpreter::ExecuteFunction(Function* func, std::vector<InterpreterValue> const& args)
	{
		memory.PushStackFrame();
		call_stack.emplace(func, args);
		InterpreterFrame& frame = call_stack.top();

		BasicBlock& entry_block = func->GetEntryBlock();
		frame.SetCurrentBlock(&entry_block);
		while (!frame.HasReturned())
		{
			BasicBlock* current_block = frame.GetCurrentBlock();
			ExecuteBasicBlock(current_block);
		}
	}

	void IRInterpreter::ExecuteBasicBlock(BasicBlock* bb)
	{
		InterpreterFrame& frame = call_stack.top();

		std::vector<std::pair<PhiInst*, InterpreterValue>> phi_results;
		for (Instruction& inst : bb->Instructions())
		{
			if (PhiInst* phi = dyn_cast<PhiInst>(&inst))
			{
				InterpreterValue val = ExecutePhi(phi);
				phi_results.emplace_back(phi, val);
			}
		}

		for (auto& [phi, val] : phi_results)
		{
			frame.SetValue(phi, val);
		}

		for (Instruction& inst : bb->Instructions())
		{
			if (isa<PhiInst>(&inst)) continue;

			ExecuteInstruction(&inst);

			if (inst.IsTerminator() || frame.HasReturned())
			{
				break;
			}
		}
	}

	void IRInterpreter::ExecuteInstruction(Instruction* inst)
	{
		InterpreterFrame& frame = call_stack.top();
		InterpreterValue result = InterpreterValue::MakeVoid();
		Opcode const opcode = inst->GetOpcode();
		if (inst->IsTerminator())
		{
			result = ExecuteTerminator(inst);
		}
		else if (inst->IsBinaryOp())
		{
			result = ExecuteBinaryOp(inst);
		}
		else if (inst->IsUnaryOp())
		{
			result = ExecuteUnaryOp(inst);
		}
		else if (inst->IsCompareOp())
		{
			result = ExecuteCompareOp(inst);
		}
		else if (inst->IsCastOp())
		{
			result = ExecuteCastOp(inst);
		}
		else if (opcode == Opcode::Load || opcode == Opcode::Store)
		{
			result = ExecuteMemoryOp(inst);
		}
		else if (opcode == Opcode::Alloca)
		{
			result = ExecuteAlloca(inst);
		}
		else if (opcode == Opcode::GetElementPtr)
		{
			result = ExecuteGetElementPtr(inst);
		}
		else if (opcode == Opcode::PtrAdd)
		{
			result = ExecutePtrAdd(inst);
		}
		else if (opcode == Opcode::Select)
		{
			result = ExecuteSelect(inst);
		}
		else if (opcode == Opcode::Call)
		{
			result = ExecuteCall(inst);
		}

		if (inst->CanBeOperand())
		{
			frame.SetValue(inst, result);
		}
	}

	InterpreterValue IRInterpreter::ExecuteTerminator(Instruction* inst)
	{
		InterpreterFrame& frame = call_stack.top();
		switch (inst->GetOpcode())
		{
		case Opcode::Ret:
		{
			ReturnInst* ret = cast<ReturnInst>(inst);
			if (!ret->IsVoid())
			{
				frame.SetReturnValue(GetOperandValue(ret->GetReturnValue()));
			}
			else
			{
				frame.SetReturnValue(InterpreterValue::MakeVoid());
			}
			return frame.GetReturnValue();
		}
		case Opcode::Branch:
		{
			BranchInst* br = cast<BranchInst>(inst);
			if (br->IsUnconditional())
			{
				frame.SetCurrentBlock(br->GetTrueTarget());
			}
			else
			{
				InterpreterValue cond = GetOperandValue(br->GetCondition());
				BasicBlock* target = cond.IsZero() ? br->GetFalseTarget() : br->GetTrueTarget();
				frame.SetCurrentBlock(target);
			}
			return InterpreterValue::MakeVoid();
		}
		case Opcode::Switch:
		{
			return ExecuteSwitch(inst);
		}
		default:
			OLA_ASSERT_MSG(false, "Unknown terminator opcode");
		}

		return InterpreterValue::MakeVoid();
	}

	InterpreterValue IRInterpreter::ExecuteSwitch(Instruction* inst)
	{
		SwitchInst* sw = cast<SwitchInst>(inst);
		InterpreterValue cond_val = GetOperandValue(sw->GetCondition());
		Int64 switch_val = cond_val.AsInt();
		BasicBlock* target = sw->GetDefaultCase();
		for (auto const& case_entry : sw->Cases())
		{
			if (case_entry.GetCaseValue() == switch_val)
			{
				target = case_entry.GetCaseBlock();
				break;
			}
		}

		call_stack.top().SetCurrentBlock(target);
		return InterpreterValue::MakeVoid();
	}

	InterpreterValue IRInterpreter::ExecuteBinaryOp(Instruction* inst)
	{
		BinaryInst* bin = cast<BinaryInst>(inst);
		InterpreterValue lhs = GetOperandValue(bin->GetLHS());
		InterpreterValue rhs = GetOperandValue(bin->GetRHS());
		switch (inst->GetOpcode())
		{
		case Opcode::Add:  return InterpreterValue::MakeInt(lhs.AsInt() + rhs.AsInt());
		case Opcode::Sub:  return InterpreterValue::MakeInt(lhs.AsInt() - rhs.AsInt());
		case Opcode::SMul: return InterpreterValue::MakeInt(lhs.AsInt() * rhs.AsInt());
		case Opcode::SDiv:
			OLA_ASSERT_MSG(rhs.AsInt() != 0, "Division by zero!");
			return InterpreterValue::MakeInt(lhs.AsInt() / rhs.AsInt());
		case Opcode::SRem:
			OLA_ASSERT_MSG(rhs.AsInt() != 0, "Division by zero!");
			return InterpreterValue::MakeInt(lhs.AsInt() % rhs.AsInt());
		case Opcode::And:  return InterpreterValue::MakeInt(lhs.AsInt() & rhs.AsInt());
		case Opcode::Or:   return InterpreterValue::MakeInt(lhs.AsInt() | rhs.AsInt());
		case Opcode::Xor:  return InterpreterValue::MakeInt(lhs.AsInt() ^ rhs.AsInt());
		case Opcode::Shl:  return InterpreterValue::MakeInt(lhs.AsInt() << rhs.AsInt());
		case Opcode::LShr: return InterpreterValue::MakeInt(static_cast<Int64>(static_cast<Uint64>(lhs.AsInt()) >> rhs.AsInt()));
		case Opcode::AShr: return InterpreterValue::MakeInt(lhs.AsInt() >> rhs.AsInt());

		case Opcode::FAdd: return InterpreterValue::MakeFloat(lhs.AsFloat() + rhs.AsFloat());
		case Opcode::FSub: return InterpreterValue::MakeFloat(lhs.AsFloat() - rhs.AsFloat());
		case Opcode::FMul: return InterpreterValue::MakeFloat(lhs.AsFloat() * rhs.AsFloat());
		case Opcode::FDiv: return InterpreterValue::MakeFloat(lhs.AsFloat() / rhs.AsFloat());
		case Opcode::FFma:
		{
			return InterpreterValue::MakeFloat(lhs.AsFloat() * rhs.AsFloat());
		}
		default:
			OLA_ASSERT_MSG(false, "Unknown binary opcode");
		}

		return InterpreterValue::MakeVoid();
	}

	InterpreterValue IRInterpreter::ExecuteUnaryOp(Instruction* inst)
	{
		UnaryInst* un = cast<UnaryInst>(inst);
		InterpreterValue operand = GetOperandValue(un->GetOperand());
		switch (inst->GetOpcode())
		{
		case Opcode::Neg:  return InterpreterValue::MakeInt(-operand.AsInt());
		case Opcode::Not:  return InterpreterValue::MakeInt(~operand.AsInt());
		case Opcode::FNeg: return InterpreterValue::MakeFloat(-operand.AsFloat());
		default:
			OLA_ASSERT_MSG(false, "Unknown unary opcode");
		}
		return InterpreterValue::MakeVoid();
	}

	InterpreterValue IRInterpreter::ExecuteCompareOp(Instruction* inst)
	{
		CompareInst* cmp = cast<CompareInst>(inst);
		InterpreterValue lhs = GetOperandValue(cmp->GetLHS());
		InterpreterValue rhs = GetOperandValue(cmp->GetRHS());
		Bool result = false;
		switch (inst->GetOpcode())
		{
		case Opcode::ICmpEQ:  result = (lhs.AsInt() == rhs.AsInt()); break;
		case Opcode::ICmpNE:  result = (lhs.AsInt() != rhs.AsInt()); break;
		case Opcode::ICmpSLT: result = (lhs.AsInt() < rhs.AsInt()); break;
		case Opcode::ICmpSLE: result = (lhs.AsInt() <= rhs.AsInt()); break;
		case Opcode::ICmpSGT: result = (lhs.AsInt() > rhs.AsInt()); break;
		case Opcode::ICmpSGE: result = (lhs.AsInt() >= rhs.AsInt()); break;

		case Opcode::ICmpULT: result = (static_cast<Uint64>(lhs.AsInt()) < static_cast<Uint64>(rhs.AsInt())); break;
		case Opcode::ICmpULE: result = (static_cast<Uint64>(lhs.AsInt()) <= static_cast<Uint64>(rhs.AsInt())); break;
		case Opcode::ICmpUGT: result = (static_cast<Uint64>(lhs.AsInt()) > static_cast<Uint64>(rhs.AsInt())); break;
		case Opcode::ICmpUGE: result = (static_cast<Uint64>(lhs.AsInt()) >= static_cast<Uint64>(rhs.AsInt())); break;

		case Opcode::FCmpOEQ: result = (lhs.AsFloat() == rhs.AsFloat()); break;
		case Opcode::FCmpONE: result = (lhs.AsFloat() != rhs.AsFloat()); break;
		case Opcode::FCmpOLT: result = (lhs.AsFloat() < rhs.AsFloat()); break;
		case Opcode::FCmpOLE: result = (lhs.AsFloat() <= rhs.AsFloat()); break;
		case Opcode::FCmpOGT: result = (lhs.AsFloat() > rhs.AsFloat()); break;
		case Opcode::FCmpOGE: result = (lhs.AsFloat() >= rhs.AsFloat()); break;

		case Opcode::FCmpUEQ: result = std::isnan(lhs.AsFloat()) || std::isnan(rhs.AsFloat()) || (lhs.AsFloat() == rhs.AsFloat()); break;
		case Opcode::FCmpUNE: result = std::isnan(lhs.AsFloat()) || std::isnan(rhs.AsFloat()) || (lhs.AsFloat() != rhs.AsFloat()); break;
		case Opcode::FCmpULT: result = std::isnan(lhs.AsFloat()) || std::isnan(rhs.AsFloat()) || (lhs.AsFloat() < rhs.AsFloat()); break;
		case Opcode::FCmpULE: result = std::isnan(lhs.AsFloat()) || std::isnan(rhs.AsFloat()) || (lhs.AsFloat() <= rhs.AsFloat()); break;
		case Opcode::FCmpUGT: result = std::isnan(lhs.AsFloat()) || std::isnan(rhs.AsFloat()) || (lhs.AsFloat() > rhs.AsFloat()); break;
		case Opcode::FCmpUGE: result = std::isnan(lhs.AsFloat()) || std::isnan(rhs.AsFloat()) || (lhs.AsFloat() >= rhs.AsFloat()); break;

		default:
			OLA_ASSERT_MSG(false, "Unknown compare opcode");
		}

		return InterpreterValue::MakeInt(result ? 1 : 0);
	}

	InterpreterValue IRInterpreter::ExecuteCastOp(Instruction* inst)
	{
		CastInst* cast_inst = cast<CastInst>(inst);
		InterpreterValue src = GetOperandValue(cast_inst->GetSrc());
		IRType* dest_type = cast_inst->GetDestType();
		switch (inst->GetOpcode())
		{
		case Opcode::ZExt:
		{
			Int64 val = src.AsInt();
			IRIntType* src_int_type = dyn_cast<IRIntType>(cast_inst->GetSrcType());
			if (src_int_type)
			{
				Uint32 src_bits = src_int_type->GetWidth();
				if (src_bits < 64)
				{
					Uint64 mask = (1ULL << src_bits) - 1;
					val &= mask;
				}
			}
			return InterpreterValue::MakeInt(val);
		}
		case Opcode::Bitcast:
		{
			return src.Bitcast(dest_type);
		}
		case Opcode::F2S:
		{
			return InterpreterValue::MakeInt(static_cast<Int64>(src.AsFloat()));
		}
		case Opcode::S2F:
		{
			return InterpreterValue::MakeFloat(static_cast<Float64>(src.AsInt()));
		}
		default:
			OLA_ASSERT_MSG(false, "Unknown cast opcode");
		}
		return InterpreterValue::MakeVoid();
	}

	InterpreterValue IRInterpreter::ExecuteMemoryOp(Instruction* inst)
	{
		switch (inst->GetOpcode())
		{
		case Opcode::Load:
		{
			LoadInst* load = cast<LoadInst>(inst);
			InterpreterValue addr_val = GetOperandValue(load->GetAddressOp());
			Uint8* addr = addr_val.AsPointer();
			IRType* load_type = load->GetType();
			if (load_type->IsInteger())
			{
				Uint32 byte_width = load_type->GetSize();
				Int64 val = memory.LoadInt(addr, byte_width);
				return InterpreterValue::MakeInt(val);
			}
			else if (load_type->IsFloat())
			{
				Float64 val = memory.LoadFloat(addr);
				return InterpreterValue::MakeFloat(val);
			}
			else if (load_type->IsPointer())
			{
				Uint8* ptr = memory.LoadPointer(addr);
				return InterpreterValue::MakePointer(ptr);
			}
			break;
		}

		case Opcode::Store:
		{
			StoreInst* store = cast<StoreInst>(inst);
			InterpreterValue val = GetOperandValue(store->GetValueOp());
			InterpreterValue addr_val = GetOperandValue(store->GetAddressOp());
			Uint8* addr = addr_val.AsPointer();
			IRType* store_type = store->GetValueOp()->GetType();
			if (store_type->IsInteger())
			{
				memory.StoreInt(addr, val.AsInt(), store_type->GetSize());
			}
			else if (store_type->IsFloat())
			{
				memory.StoreFloat(addr, val.AsFloat());
			}
			else if (store_type->IsPointer())
			{
				memory.StorePointer(addr, val.AsPointer());
			}
			return InterpreterValue::MakeVoid();
		}
		}
		return InterpreterValue::MakeVoid();
	}

	InterpreterValue IRInterpreter::ExecuteAlloca(Instruction* inst)
	{
		AllocaInst* alloca_inst = cast<AllocaInst>(inst);
		IRType* alloc_type = alloca_inst->GetAllocatedType();
		Uint32 size = alloc_type->GetSize();
		Uint32 align = alloc_type->GetAlign();
		Uint8* ptr = memory.StackAlloc(size, align);
		return InterpreterValue::MakePointer(ptr);
	}

	Uint32 IRInterpreter::GetFieldOffset(IRType* type, Uint32 field_index)
	{
		IRStructType* struct_type = dyn_cast<IRStructType>(type);
		if (!struct_type) 
		{
			return 0;
		}
		Uint32 offset = 0;
		for (Uint32 i = 0; i < field_index && i < struct_type->GetMemberCount(); ++i)
		{
			IRType* field_type = struct_type->GetMemberType(i);
			offset = (offset + field_type->GetAlign() - 1) & ~(field_type->GetAlign() - 1);
			offset += field_type->GetSize();
		}
		if (field_index < struct_type->GetMemberCount())
		{
			IRType* target_field = struct_type->GetMemberType(field_index);
			offset = (offset + target_field->GetAlign() - 1) & ~(target_field->GetAlign() - 1);
		}
		return offset;
	}

	InterpreterValue IRInterpreter::ExecuteGetElementPtr(Instruction* inst)
	{
		GetElementPtrInst* gep = cast<GetElementPtrInst>(inst);
		InterpreterValue base_val = GetOperandValue(gep->GetBaseOperand());
		Uint8* base_ptr = base_val.AsPointer();
		IRType* current_type = gep->GetSourceElementType();
		Uint64 offset = 0;
		for (Uint32 i = 0; i < gep->GetNumIndices(); ++i)
		{
			InterpreterValue idx_val = GetOperandValue(gep->GetIndex(i));
			Int64 idx = idx_val.AsInt();
			if (IRArrayType* arr_type = dyn_cast<IRArrayType>(current_type))
			{
				IRType* elem_type = arr_type->GetElementType();
				offset += idx * elem_type->GetSize();
				current_type = elem_type;
			}
			else if (IRPtrType* ptr_type = dyn_cast<IRPtrType>(current_type))
			{
				IRType* pointee_type = ptr_type->GetPointeeType();
				if (pointee_type)
				{
					offset += idx * pointee_type->GetSize();
					current_type = pointee_type;
				}
			}
			else if (IRStructType* struct_type = dyn_cast<IRStructType>(current_type))
			{
				offset += GetFieldOffset(struct_type, static_cast<Uint32>(idx));
				if (idx < static_cast<Int64>(struct_type->GetMemberCount()))
				{
					current_type = struct_type->GetMemberType(static_cast<Uint32>(idx));
				}
			}
			else
			{
				offset += idx * current_type->GetSize();
			}
		}
		return InterpreterValue::MakePointer(base_ptr + offset);
	}

	InterpreterValue IRInterpreter::ExecutePtrAdd(Instruction* inst)
	{
		PtrAddInst* ptr_add = cast<PtrAddInst>(inst);
		InterpreterValue base_val = GetOperandValue(ptr_add->GetBase());
		InterpreterValue offset_val = GetOperandValue(ptr_add->GetOffset());
		Uint8* result = base_val.AsPointer() + offset_val.AsInt();
		return InterpreterValue::MakePointer(result);
	}

	InterpreterValue IRInterpreter::ExecuteSelect(Instruction* inst)
	{
		SelectInst* select = cast<SelectInst>(inst);
		InterpreterValue pred = GetOperandValue(select->GetPredicate());
		InterpreterValue true_val = GetOperandValue(select->GetTrueValue());
		InterpreterValue false_val = GetOperandValue(select->GetFalseValue());
		return pred.IsZero() ? false_val : true_val;
	}

	InterpreterValue IRInterpreter::ExecuteCall(Instruction* inst)
	{
		CallInst* call = cast<CallInst>(inst);
		std::vector<InterpreterValue> args;
		for (auto& arg_use : call->Args())
		{
			args.push_back(GetOperandValue(arg_use.Get()));
		}

		Function* callee = call->GetCalleeAsFunction();
		if (!callee)
		{
			InterpreterValue callee_val = GetOperandValue(call->GetCallee());
			callee = reinterpret_cast<Function*>(callee_val.AsPointer());
			OLA_ASSERT_MSG(callee, "Indirect call target is null");
		}

		if (callee->IsDeclaration())
		{
			std::string_view func_name = callee->GetName();
			if (intrinsics.IsIntrinsic(func_name))
			{
				return intrinsics.Call(func_name, args);
			}
			else
			{
				OLA_WARN("Unknown external function: {}", func_name);
				return InterpreterValue::MakeVoid();
			}
		}

		ExecuteFunction(callee, args);

		InterpreterValue ret_val = call_stack.top().GetReturnValue();
		call_stack.pop();
		memory.PopStackFrame();

		return ret_val;
	}

	InterpreterValue IRInterpreter::ExecutePhi(Instruction* inst)
	{
		PhiInst* phi = cast<PhiInst>(inst);
		InterpreterFrame& frame = call_stack.top();
		BasicBlock* prev_block = frame.GetPreviousBlock();
		if (!prev_block)
		{
			return InterpreterValue::MakeInt(0);
		}

		Value* incoming_value = phi->GetIncomingValueForBlock(prev_block);
		if (!incoming_value)
		{
			OLA_WARN("No incoming value for phi from previous block!");
			return InterpreterValue::MakeInt(0);
		}
		return GetOperandValue(incoming_value);
	}

	InterpreterValue IRInterpreter::GetOperandValue(Value* v)
	{
		InterpreterFrame& frame = call_stack.top();
		if (frame.HasValue(v))
		{
			return frame.GetValue(v);
		}

		if (ConstantInt* ci = dyn_cast<ConstantInt>(v))
		{
			return InterpreterValue::MakeInt(ci->GetValue());
		}

		if (ConstantFloat* cf = dyn_cast<ConstantFloat>(v))
		{
			return InterpreterValue::MakeFloat(cf->GetValue());
		}

		if (GlobalVariable* gv = dyn_cast<GlobalVariable>(v))
		{
			Uint8* addr = memory.GetGlobalAddress(gv);
			return InterpreterValue::MakePointer(addr);
		}

		if (Function* f = dyn_cast<Function>(v))
		{
			return InterpreterValue::MakePointer(reinterpret_cast<Uint8*>(f));
		}

		if (isa<UndefValue>(v))
		{
			return InterpreterValue::MakeInt(0);
		}

		if (isa<ConstantNullPtr>(v))
		{
			return InterpreterValue::MakePointer(nullptr);
		}

		if (ConstantString* cs = dyn_cast<ConstantString>(v))
		{
			Uint8* addr = memory.AllocString(cs->GetValue());
			return InterpreterValue::MakePointer(addr);
		}

		OLA_WARN("Unknown value type in GetOperandValue");
		return InterpreterValue::MakeVoid();
	}
}
