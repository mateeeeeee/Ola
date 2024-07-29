#pragma once
#include <string>

namespace ola
{
	enum class RelocableKind : uint8
	{
		Function,
		ZeroStorage,
		DataStorage,
		Block
	};

	class MachineRelocable
	{
	public:
		explicit MachineRelocable(std::string_view symbol) : symbol(symbol) {}
		virtual ~MachineRelocable() = default;

		std::string_view GetSymbol() const { return symbol; }
		virtual RelocableKind GetRelocableKind() const = 0;

		bool IsFunction() const { return GetRelocableKind() == RelocableKind::Function; }
		bool IsZeroStorage() const { return GetRelocableKind() == RelocableKind::ZeroStorage; }
		bool IsDataStorage() const { return GetRelocableKind() == RelocableKind::DataStorage; }
		bool IsBlock() const { return GetRelocableKind() == RelocableKind::Block; }

	private:
		std::string symbol;
	};

}