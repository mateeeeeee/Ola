#include <ostream>
#include "IRPrinter.h"
#include "IRModule.h"
#include "GlobalValue.h"

namespace ola
{
	void IRPrinter::PrintModule(IRModule const& M)
	{
		std::vector<GlobalValue*> const& globals = M.Globals();

		for (GlobalValue const* global : globals)
		{
			if (GlobalVariable const* GV = dyn_cast<GlobalVariable>(global))
			{
				EmitLn("");
				PrintGlobalVariable(GV);
				EmitLn("");
			}
			else if (Function const* F = dyn_cast<Function>(global))
			{
				EmitLn("");
				PrintFunction(F);
				EmitLn("");
			}
		}
		os << output;
	}

	void IRPrinter::PrintGlobalVariable(GlobalVariable const* GV)
	{
		if (GV->IsDeclaration())
		{
			Emit("declare ");
			PrintFullName(GV);
			EmitLn(" {}", GetTypeAsString(GV->GetType()));
			return;
		}
		std::string linkage = GV->GetLinkage() == Linkage::External ? "external" : "internal";
		Emit("define {} ", linkage);
		PrintFullName(GV);
		Emit(" {} ", GetTypeAsString(GV->GetValueType()));
		PrintConstant(GV->GetInitValue());
		EmitLn("");
	}

	void IRPrinter::PrintFunction(Function const* F)
	{
		if (F->IsDeclaration())
		{
			Emit("declare ");
			PrintFullName(F);
			EmitLn(" {}", GetTypeAsString(F->GetFunctionType()));
			return;
		}
		std::string linkage = F->GetLinkage() == Linkage::External ? "external" : "internal";
		Emit("define {} ", linkage);
		PrintFullName(F);
		EmitLn(" {} {{", GetTypeAsString(F->GetFunctionType()));
		for (auto const& BB : F->Blocks())
		{
			PrintBasicBlock(BB);
		}
		EmitLn("}}");
	}

	void IRPrinter::PrintBasicBlock(BasicBlock const& BB)
	{
		PrintFullName(&BB);
		Emit(":");
		EmitLn("");
		for (Instruction const& I : BB.Instructions())
		{
			PrintInstruction(I);
		}
	}

	void IRPrinter::PrintInstruction(Instruction const& I)
	{
		IRType* type = I.GetType();
		if (!type->IsVoidType())
		{
			PrintFullName(&I);
			Emit(" = ");
		}
		Emit("{} ", I.GetOpcodeName());

		if (isa<AllocaInst>(&I))
		{
			AllocaInst const* AI = cast<AllocaInst>(&I);
			IRType* allocated_type = AI->GetAllocatedType();
			Emit("{}", GetTypeAsString(allocated_type, false));
		}
		else if (isa<BranchInst>(&I))
		{
			BranchInst const* BI = cast<BranchInst>(&I);
			if (BI->IsConditional())
			{
				PrintOperand(BI->GetCondition(), true);
				Emit(", ");
				PrintOperand(BI->GetTrueTarget(), true);
				Emit(", ");
				PrintOperand(BI->GetFalseTarget(), true);
			}
			else
			{
				PrintOperand(BI->GetTrueTarget(), true);
			}
		}
		else
		{
			if (!type->IsVoidType())
			{
				Emit("{}, ", GetTypeAsString(type, false));
			}
			for (auto& Op : I.Operands())
			{
				PrintOperand(Op.GetValue());
				Emit(", ");
			}
			if(I.GetNumOperands() > 0) OutputPopBack<2>();
		}
		EmitLn("");
	}

	void IRPrinter::PrintOperand(Value const* V, bool print_type)
	{
		if (!V)
		{
			Emit("null operand");
			return;
		}
		if (print_type && V->GetType())
		{
			Emit("{}", GetTypeAsString(V->GetType()));
		}
		PrintFullName(V);
	}

	void IRPrinter::PrintConstant(Value* V)
	{
		if (!V) return;
		OLA_ASSERT(isa<Constant>(V));
		Constant* C = cast<Constant>(V);
		ConstantID const_id = C->GetConstantID();
		switch (const_id)
		{
		case ConstantID::Float:		Emit("{}", cast<ConstantFloat>(C)->GetValue()); break;
		case ConstantID::Integer:	Emit("{}", cast<ConstantInt>(C)->GetValue()); break;
		default: OLA_ASSERT_MSG(false, "not yet implemented");
		}
	}

	std::string IRPrinter::GetPrefixedName(Value const* V)
	{
		if (isa<BasicBlock>(V))			return GetPrefixedName(V->GetName(), NamePrefix::Label);
		else if (isa<GlobalValue>(V))   return GetPrefixedName(V->GetName(), NamePrefix::Global);
		else							return GetPrefixedName(V->GetName(), NamePrefix::Local);
	}

	std::string IRPrinter::GetPrefixedName(std::string_view name, NamePrefix prefix)
	{
		std::string str_prefix = "";
		switch (prefix)
		{
			break;
		case NamePrefix::Global:
			str_prefix = "@";
			break;
		case NamePrefix::Local:
			str_prefix = "%";
			break;
		case NamePrefix::None:
		case NamePrefix::Label:
		default:
			break;
		}
		return str_prefix + std::string(name);
	}

	void IRPrinter::PrintFullName(Value const* V)
	{
		if (unique_names.contains(V))
		{
			Emit("{}", unique_names[V]);
			return;
		}

		std::string prefixed_name = GetPrefixedName(V);
		if (names_count.contains(prefixed_name))
		{
			uint32 count = names_count[prefixed_name]++;
			unique_names[V] = prefixed_name + std::to_string(count);
		}
		else
		{
			names_count[prefixed_name]++;
			unique_names[V] = prefixed_name;
			if (prefixed_name.size() <= 1) unique_names[V] += "0";
		}
		PrintFullName(V);
	}

	std::string IRPrinter::GetTypeAsString(IRType* type, bool space)
	{
		std::string type_string;
		switch (type->GetKind())
		{
		case IRTypeKind::Void:		type_string = "void"; break;
		case IRTypeKind::Float:		type_string = "f64";  break;
		case IRTypeKind::Pointer:	type_string = "ptr";  break;
		case IRTypeKind::Label:		type_string = "label";  break;
		case IRTypeKind::Integer:
		{
			IRIntType* int_type = cast<IRIntType>(type);
			switch (int_type->GetWidth())
			{
			case 1: type_string = "i8";  break;
			case 8: type_string = "i64"; break;
			}
		}
		break;
		case IRTypeKind::Array:
		{
			IRArrayType* array_type = cast<IRArrayType>(type);
			std::string base_type_string = GetTypeAsString(array_type->GetBaseType(), false);
			base_type_string += "[";
			base_type_string += std::to_string(array_type->GetArraySize());
			base_type_string += "]";
		}
		break;
		case IRTypeKind::Function:
		{
			IRFuncType* func_type = cast<IRFuncType>(type);
			type_string = GetTypeAsString(func_type->GetReturnType());
			type_string += "(";
			uint32 const param_count = (uint32)func_type->GetParamCount();
			for (uint32 i = 0; i < param_count; ++i)
			{
				type_string += GetTypeAsString(func_type->GetParamType(i));
				if (i != param_count - 1) type_string += ",";
			}
			type_string += ")";
		}
		break;
		case IRTypeKind::Struct: OLA_ASSERT_MSG(false, "Not implemented yet"); break;
		}

		if (space) type_string += " ";
		return type_string;
	}
}

