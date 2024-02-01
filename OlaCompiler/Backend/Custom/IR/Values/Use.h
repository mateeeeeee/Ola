#pragma once
#include "IRFwd.h"
#include "Value.h"
#include "Utility/IntrusiveList.h"

namespace ola
{
	class Use : public IListNode<Use>
	{
		friend Value;
		friend User;

	public:
		Use(User* u, Value* v = nullptr) : value(v), user(u)
		{
			if (value) value->AddUse(this);
		}
		Use const& operator=(Use const& rhs)
		{
			Set(rhs.value);
			return *this;
		}
		~Use()
		{
			if (value) value->RemoveUse(this);
		}

		operator Value* () const { return value; }
		Value* Get() const { return value; }
		void Set(Value* v)
		{
			if (value) value->RemoveUse(this);
			value = v;
			if (v) v->AddUse(this);
		}

		Value* operator=(Value* rhs)
		{
			Set(rhs);
			return rhs;
		}
		Value* operator->() { return value; }
		Value const* operator->() const { return value; }

	private:
		User* user;
		Value* value;
	};

}