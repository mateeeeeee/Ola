#include "IRType.h"

namespace ola::ir
{
	UnknownType* UnknownType::Get(IRContext* ctx)
	{
		return nullptr;
	}

	VoidType* VoidType::Get(IRContext* ctx)
	{
		return nullptr;
	}

	IntegerType* IntegerType::Get(IRContext* ctx, uint32 width)
	{
		return nullptr;
	}

	FloatType* FloatType::Get(IRContext* ctx)
	{
		return nullptr;
	}

	ArrayType* ArrayType::Get(IRContext* ctx, IRType* base_type, uint32 array_size)
	{
		return nullptr;
	}

	FunctionType* FunctionType::Get(IRContext* ctx, IRType* return_type, std::vector<IRType*> const& param_types)
	{
		return nullptr;
	}

	StructType* StructType::Get(IRContext* ctx, std::string_view name, std::vector<IRType*> const& members)
	{
		return nullptr;
	}

	StructType::StructType(std::string_view name, std::vector<IRType*> const& members) : IRType(IRTypeKind::Struct, 0, 0), name(name)
	{
		auto AlignTo = []<typename T>(T n, T align) { return (n + align - 1) / align * align; };
		uint32 offset = 0;

		for (IRType* member_type : this->members)
		{
			offset = AlignTo(offset, member_type->GetAlign());
			offset += member_type->GetSize();
			if (GetAlign() < member_type->GetAlign()) SetAlign(member_type->GetAlign());
		}
		if (offset == 0) offset = 1;
		if (GetAlign()) offset = AlignTo(offset, GetAlign());
		SetSize(offset);
	}

}

