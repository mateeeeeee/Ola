#include "PassManager.h"
#include "Pass.h"

namespace ola
{

	Pass* PassManagerBase::FindPass(void const* ID) const
	{
		for (auto& pass : passes)
		{
			if (pass->GetPassID() == ID) return pass.get();
		}
		return nullptr;
	}
}

