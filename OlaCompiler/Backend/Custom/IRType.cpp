#include "IRType.h"
#include "IRContext.h"

namespace ola
{
	VoidType* VoidType::Get(IRContext* ctx)
	{
		return ctx->GetVoidType();
	}

	PointerType* PointerType::Get(IRContext* ctx, IRType* pointee_type)
	{
		return ctx->GetPointerType(pointee_type);
	}

	IntegerType* IntegerType::Get(IRContext* ctx, uint32 width)
	{
		return ctx->GetIntegerType(width);
	}

	FloatType* FloatType::Get(IRContext* ctx)
	{
		return ctx->GetFloatType();
	}

	ArrayType* ArrayType::Get(IRContext* ctx, IRType* base_type, uint32 array_size)
	{
		return ctx->GetArrayType(base_type, array_size);
	}

	FunctionType* FunctionType::Get(IRContext* ctx, IRType* return_type, std::vector<IRType*> const& param_types)
	{
		return ctx->GetFunctionType(return_type, param_types);
	}

	StructType* StructType::Get(IRContext* ctx, std::string_view name, std::vector<IRType*> const& member_types)
	{
		return ctx->GetStructType(name, member_types);
	}

	StructType::StructType(std::string_view name, std::vector<IRType*> const& member_types) : IRType(IRTypeKind::Struct, 0, 0), name(name), member_types(member_types)
	{
		auto AlignTo = []<typename T>(T n, T align) { return (n + align - 1) / align * align; };
		uint32 offset = 0;

		for (IRType* member_type : this->member_types)
		{
			offset = AlignTo(offset, member_type->GetAlign());
			offset += member_type->GetSize();
			if (GetAlign() < member_type->GetAlign()) SetAlign(member_type->GetAlign());
		}
		if (offset == 0) offset = 1;
		if (GetAlign()) offset = AlignTo(offset, GetAlign());
		SetSize(offset);
	}

	LabelType* LabelType::Get(IRContext* ctx)
	{
		return ctx->GetLabelType();
	}

}

