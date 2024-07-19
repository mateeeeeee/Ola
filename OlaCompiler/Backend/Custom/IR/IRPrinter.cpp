#include <ostream>
#include "IRPrinter.h"
#include "IRModule.h"
#include "GlobalValue.h"

namespace ola
{
	void IRPrinter::PrintModule(IRModule const& M)
	{
		std::string_view module_id = M.GetModuleId();

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
			EmitSpace();
			PrintType(GV->GetType());
			EmitNewline();
			return;
		}
		std::string linkage = GV->GetLinkage() == Linkage::External ? "external" : "internal";
		Emit("define {} ", linkage);
		PrintFullName(GV);
		EmitSpace();
		PrintType(GV->GetType());
		EmitSpace();
		PrintConstant(dyn_cast<Constant>(GV->GetInitValue()));
		EmitNewline();
	}

	void IRPrinter::PrintFunction(Function const* F)
	{
		if (F->IsDeclaration())
		{
			Emit("declare ");
			PrintFullName(F);
			EmitSpace();
			PrintType(F->GetFunctionType());
			return;
		}
		std::string linkage = F->GetLinkage() == Linkage::External ? "external" : "internal";
		Emit("define {} ", linkage);
		PrintFullName(F);
		EmitSpace();
		PrintType(F->GetFunctionType());
		EmitLn(" {{");
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
			PrintType(AI->GetAllocatedType());
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
		else if (I.GetNumOperands() > 0)
		{
			IRType* type = I.GetOperand(0)->GetType(); 
			if (LoadInst const* LI = dyn_cast<LoadInst>(&I))
			{
				PrintType(LI->GetType());
				Emit(", ");
			}

			bool print_all_types = false;
			if (isa<SelectInst>(&I) || isa<StoreInst>(&I)) 
			{
				print_all_types = true;
			}

			if (!print_all_types)
			{
				PrintType(type);
				EmitSpace();
			}
			for (auto& Op : I.Operands())
			{
				PrintOperand(Op.GetValue(), print_all_types);
				Emit(", ");
			}
			if(I.GetNumOperands() > 0) PopOutput<2>();
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

		Constant const* C = dyn_cast<Constant>(V);
		if (C && !isa<GlobalValue>(C))
		{
			PrintConstant(C);
			return;
		}

		if (print_type && V->GetType())
		{
			PrintType(V->GetType());
			EmitSpace();
		}
		PrintFullName(V);
	}

	void IRPrinter::PrintConstant(Constant const* V)
	{
		if (!V) return;
		OLA_ASSERT(isa<Constant>(V));
		Constant const* C = cast<Constant>(V);
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

	void IRPrinter::PrintType(IRType* type)
	{
		std::string type_string;
		switch (type->GetKind())
		{
		case IRTypeKind::Void:		Emit("void"); break;
		case IRTypeKind::Float:		Emit("f64");  break;
		case IRTypeKind::Pointer:	Emit("ptr");  break;
		case IRTypeKind::Label:		Emit("label");  break;
		case IRTypeKind::Integer:
		{
			IRIntType* int_type = cast<IRIntType>(type);
			switch (int_type->GetWidth())
			{
			case 1: Emit("i8");  break;
			case 8: Emit("i64"); break;
			}
		}
		break;
		case IRTypeKind::Array:
		{
			IRArrayType* array_type = cast<IRArrayType>(type);
			PrintType(array_type->GetBaseType());
			Emit("[{}]", array_type->GetArraySize());
		}
		break;
		case IRTypeKind::Function:
		{
			IRFuncType* func_type = cast<IRFuncType>(type);
			PrintType(func_type->GetReturnType());
			Emit("(");
			uint32 const param_count = func_type->GetParamCount();
			for (uint32 i = 0; i < param_count; ++i)
			{
				PrintType(func_type->GetParamType(i));
				Emit(",");
			}
			if(param_count > 0) PopOutput<1>();
			Emit(")");
		}
		break;
		case IRTypeKind::Struct: OLA_ASSERT_MSG(false, "Not implemented yet"); break;
		}
	}
}

