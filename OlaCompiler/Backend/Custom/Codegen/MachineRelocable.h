#pragma once
#include <string>

namespace ola
{
	enum class RelocableKind : Uint8
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

		Bool IsFunction() const 	{ return GetRelocableKind() == RelocableKind::Function; }
		Bool IsZeroStorage() const  { return GetRelocableKind() == RelocableKind::ZeroStorage; }
		Bool IsDataStorage() const  { return GetRelocableKind() == RelocableKind::DataStorage; }
		Bool IsBlock() const 		{ return GetRelocableKind() == RelocableKind::Block; }

	private:
		std::string symbol;
	};

}