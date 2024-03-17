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
			return cast<IRIntType>(Ty)->GetWidth() == 1 ? ctx.GetInt8(0) : ctx.GetInt64(0);
		case IRTypeKind::Float:
			return ctx.GetZeroFloat();
		case IRTypeKind::Struct:
		case IRTypeKind::Array:
			OLA_ASSERT_MSG(false, "todo");
		default:
			OLA_ASSERT(false);
		}
		return nullptr;
	}
}
