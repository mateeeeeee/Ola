#pragma once
#include "Value.h"
#include "IRType.h"

namespace ola
{

	OLA_NODISCARD IRContext& Value::GetContext() const
	{
		return type->GetContext();
	}

}