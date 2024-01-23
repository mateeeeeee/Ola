#pragma once
#include "IRFwd.h"
#include "Backend/Custom/IRType.h"
#include "Utility/IntrusiveList.h"

namespace ola
{
	enum class ValueKind : uint32
	{
	#define HANDLE_VALUE(Name) Name,
	#include "Values.def"
	};

	class Value
	{
	public:
		OLA_NONCOPYABLE(Value)
			virtual ~Value() = default;

		ValueKind GetKind() const { return kind; }
		IRType* GetType() const { return type; }
		IRContext& GetContext() const { return type->GetContext(); }

		bool HasName() const { return !name.empty(); }
		std::string_view GetName() const { return name; }
		void SetName(std::string_view _name)
		{
			name = _name;
		}

		auto UseBegin() { return uses.begin(); }
		auto UseBegin() const { return uses.begin(); }
		auto UseEnd() { return uses.end(); }
		auto UseEnd() const { return uses.end(); }
		auto UseRBegin() { return uses.rbegin(); }
		auto UseRBegin() const { return uses.rbegin(); }
		auto UseREnd() { return uses.rend(); }
		auto UseREnd() const { return uses.rend(); }
		bool UseEmpty() const { return UseBegin() == UseEnd(); }
		uint64 UseSize() const;

		void AddUse(Use* u);
		void RemoveUse(Use* u);
		void ReplaceAllUseWith(Value* v);

		bool HasOneUse() const { return UseSize() == 1; }
		bool hasNUses(uint32 N) const { return UseSize() == N; }
		bool hasNUsesOrMore(unsigned N) const { return UseSize() >= N; }

		void* operator new(uint64) = delete;
		void* operator new(uint64 sz, IRModule&) { return ::operator new(sz); }

	protected:
		Value(ValueKind kind, IRType* type = nullptr) : kind(kind), type(type) {}

	private:
		ValueKind kind;
		IRType* type;
		std::string name;
		IList<Use> uses;
	};

}