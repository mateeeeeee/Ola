#include "Constant.h"
#include "Backend/Custom/IR/IRContext.h"

namespace ola
{

	ConstantFloat::ConstantFloat(IRContext& ctx, double V) : ConstantFloat(ctx.GetFloatType(), V)
	{

	}

}

