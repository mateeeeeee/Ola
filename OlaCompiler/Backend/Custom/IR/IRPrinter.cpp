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

	}

	void IRPrinter::PrintFunction(Function const* F)
	{
		if (F->IsDeclaration())
		{
			EmitLn("declare @{} {}", F->GetName(), GetTypeAsString(F->GetType()));
			return;
		}

		std::string linkage = F->GetLinkage() == Linkage::External ? "external" : "internal";
		EmitLn("define @{} {} {} {{", F->GetName(), linkage, GetTypeAsString(F->GetType()));
		for (auto const& BB : F->Blocks())
		{
			PrintBasicBlock(BB);
		}
		EmitLn("}}");
	}

	void IRPrinter::PrintBasicBlock(BasicBlock const& BB)
	{

	}

	std::string IRPrinter::GetTypeAsString(IRType* type, bool space)
	{
		std::string type_string;
		switch (type->GetKind())
		{
		case IRTypeKind::Void:		type_string = "void"; break;
		case IRTypeKind::Float:		type_string = "f64";  break;
		case IRTypeKind::Pointer:	type_string = "ptr";  break;
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

