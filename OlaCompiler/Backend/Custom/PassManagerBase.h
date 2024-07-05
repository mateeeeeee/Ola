#pragma once
#include <vector>
#include <memory>

namespace ola
{
	class Pass;
	class PassManagerBase
	{
	public:
		PassManagerBase() = default;
		virtual ~PassManagerBase() = default;

		template<typename PassT>
		PassT& GetPass() const
		{
			return *FindPass(&PassT::ID);
		}

		template<typename PassT>
		PassT* GetPassIfExists() const
		{
			return FindPass(&PassT::ID);
		}

	protected:
		std::vector<std::unique_ptr<Pass>> passes;

	private:
		Pass* FindPass(void const* ID) const;
	};
}