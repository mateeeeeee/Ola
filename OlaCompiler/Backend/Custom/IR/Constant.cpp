#include "Constant.h"
#include "IRType.h"
#include "IRContext.h"

namespace ola
{
	Constant* Constant::GetNullValue(IRType* Ty)
	{
		IRContext& ctx = Ty->GetContext();
		switch (Ty->GetKind())
		{
		case IRTypeKind::Integer:
			return cast<IRIntType>(Ty)->GetWidth() == 8 ? ctx.GetInt8(0) : ctx.GetInt64(0);
		case IRTypeKind::Float:
			return ctx.GetZeroFloat();
		case IRTypeKind::Struct:
		{
			IRStructType* struct_type = cast<IRStructType>(Ty);
			std::vector<Constant*> null_members;
			for (Uint64 i = 0; i < struct_type->GetMemberCount(); ++i)
			{
				null_members.push_back(GetNullValue(struct_type->GetMemberType(i)));
			}
			return new ConstantStruct(struct_type, null_members);
		}
		case IRTypeKind::Array:
		{
			IRArrayType* array_type = cast<IRArrayType>(Ty);
			return ctx.GetNullArray(array_type);
		}
		case IRTypeKind::Pointer:
		{
			return ctx.GetNullPtr(cast<IRPtrType>(Ty));
		}
		default:
			OLA_ASSERT(false);
		}
		return nullptr;
	}
}
