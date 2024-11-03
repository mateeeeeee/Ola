#pragma once
#include <vector>
#include <variant>
#include "MachineRelocable.h"

namespace ola
{
	class MachineZeroStorage final : public MachineRelocable
	{
	public:
		explicit MachineZeroStorage(std::string_view symbol, Uint64 size) : MachineRelocable(symbol), size(size) {}

		Uint64 GetSize() const { return size; }

		virtual RelocableKind GetRelocableKind() const override
		{
			return RelocableKind::ZeroStorage;
		}

	private:
		Uint64 size;
	};

	class MachineDataStorage final : public MachineRelocable
	{
	public:
		using Storage = std::vector<std::variant<Uint8, Uint16, Uint32, Uint64, std::string>>;
	public:
		MachineDataStorage(std::string_view symbol, Bool read_only) : MachineRelocable(symbol), read_only(read_only) {}

		Bool IsReadOnly() const
		{
			return read_only;
		}
		Storage const& GetStorage() const { return data; }

		Uint32 AppendByte(Uint8 val)
		{
			return Append(val);
		}
		Uint32 AppendWord(Uint16 val)
		{
			return Append(val);
		}
		Uint32 AppendDWord(Uint32 val)
		{
			return Append(val);
		}
		Uint32 AppendQWord(Uint64 val)
		{
			return Append(val);
		}

		Uint32 AppendString(std::string_view str)
		{
			return Append(std::string(str));
		}

		virtual RelocableKind GetRelocableKind() const override
		{
			return RelocableKind::DataStorage;
		}

	private:
		Storage data;
		Bool read_only;

	private:
		template<typename T>
		Uint32 Append(T val)
		{
			Uint32 idx = (Uint32)data.size();
			data.push_back(val);
			return idx;
		}
	};

}