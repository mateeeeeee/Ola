#include "IRType.h"
#include "IRContext.h"

namespace ola
{
	IRVoidType* IRVoidType::Get(IRContext& ctx)
	{
		return ctx.GetVoidType();
	}

	IRPtrType* IRPtrType::Get(IRType* pointee_type)
	{
		return pointee_type->GetContext().GetPointerType(pointee_type);
	}

	IRPtrType* IRPtrType::Get(IRContext& ctx, IRType* pointee_type)
	{
		return ctx.GetPointerType(pointee_type);
	}

	IRIntType* IRIntType::Get(IRContext& ctx, Uint32 width)
	{
		return ctx.GetIntegerType(width);
	}

	IRFloatType* IRFloatType::Get(IRContext& ctx)
	{
		return ctx.GetFloatType();
	}

	IRArrayType* IRArrayType::Get(IRContext& ctx, IRType* base_type, Uint32 array_size)
	{
		return ctx.GetArrayType(base_type, array_size);
	}

	IRArrayType* IRArrayType::Get(IRType* base_type, Uint32 array_size)
	{
		return base_type->GetContext().GetArrayType(base_type, array_size);
	}

	IRFuncType* IRFuncType::Get(IRContext& ctx, IRType* return_type, std::vector<IRType*> const& param_types)
	{
		return ctx.GetFunctionType(return_type, param_types);
	}

	IRFuncType* IRFuncType::Get(IRType* return_type, std::vector<IRType*> const& param_types)
	{
		return return_type->GetContext().GetFunctionType(return_type, param_types);
	}

	IRStructType* IRStructType::Get(IRContext& ctx, std::string_view name, std::vector<IRType*> const& member_types)
	{
		return ctx.GetStructType(name, member_types);
	}

	IRStructType::IRStructType(IRContext& ctx, std::string_view name, std::vector<IRType*> const& member_types) : IRType(ctx, IRTypeKind::Struct, 0, 0), name(name), member_types(member_types)
	{
		Uint32 offset = 0;

		for (IRType* member_type : this->member_types)
		{
			offset = OLA_ALIGN_UP(offset, member_type->GetAlign());
			offset += member_type->GetSize();
			if (GetAlign() < member_type->GetAlign())
			{
				SetAlign(member_type->GetAlign());
			}
		}
		if (offset == 0)
		{
			offset = 1;
		}
		if (GetAlign())
		{
			offset = OLA_ALIGN_UP(offset, GetAlign());
		}
		SetSize(offset);
	}

	IRLabelType* IRLabelType::Get(IRContext& ctx)
	{
		return ctx.GetLabelType();
	}

}

