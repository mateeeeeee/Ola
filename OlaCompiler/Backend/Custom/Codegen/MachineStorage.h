#pragma once
#include <vector>
#include <variant>
#include "MachineRelocable.h"

namespace ola
{
	class MachineZeroStorage final : public MachineRelocable
	{
	public:
		explicit MachineZeroStorage(std::string_view symbol, uint64 size) : MachineRelocable(symbol), size(size) {}

		uint64 GetSize() const { return size; }

		virtual RelocableKind GetRelocableKind() const override
		{
			return RelocableKind::ZeroStorage;
		}

	private:
		uint64 size;
	};

	class MachineDataStorage final : public MachineRelocable
	{
	public:
		using Storage = std::vector<std::variant<uint8, uint16, uint32, uint64>>;
	public:
		MachineDataStorage(std::string_view symbol, bool read_only) : MachineRelocable(symbol), read_only(read_only) {}

		bool IsReadOnly() const
		{
			return read_only;
		}
		Storage const& GetStorage() const { return data; }

		uint32 AppendByte(uint8 val)
		{
			return Append(val);
		}
		uint32 AppendWord(uint16 val)
		{
			return Append(val);
		}
		uint32 AppendDWord(uint32 val)
		{
			return Append(val);
		}
		uint32 AppendQWord(uint64 val)
		{
			return Append(val);
		}

		virtual RelocableKind GetRelocableKind() const override
		{
			return RelocableKind::DataStorage;
		}

	private:
		Storage data;
		bool read_only;

	private:
		template<typename T>
		uint32 Append(T val)
		{
			uint32 idx = (uint32)data.size();
			data.push_back(val);
			return idx;
		}
	};

}