#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include "MIRGlobal.h"
#include "MIROperand.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	class MIRRelocable
	{
	public:
		explicit MIRRelocable(std::string_view symbol) : symbol(symbol) {}
		virtual ~MIRRelocable() = default;

		std::string_view GetSymbol() const { return symbol; }
		virtual bool IsFunction() const
		{
			return false;
		}

	private:
		std::string symbol;
	};

	class MIRBasicBlock;
	class MIRFunction final : public MIRRelocable
	{
	public:
		explicit MIRFunction(std::string_view symbol);
		~MIRFunction();

		auto& Blocks() { return blocks; }
		auto const& Blocks() const { return blocks; }

		std::vector<MIROperand>& Args()
		{
			return args;
		}
		
		MIROperand& AllocateStack(uint32 size)
		{
			MIROperand stack_object = MIROperand::StackObject(stack_offset, MIROperandType::Other);
			stack_objects.push_back(stack_object);
			stack_offset += size;
			return stack_objects.back();
		}

		virtual bool IsFunction() const
		{
			return true;
		}

	private:
		std::list<std::unique_ptr<MIRBasicBlock>> blocks;
		std::vector<MIROperand> args;
		int32 stack_offset = 0;
		std::vector<MIROperand> stack_objects;
	};

	class MIRZeroStorage : public MIRRelocable
	{

	public:
		explicit MIRZeroStorage(std::string_view symbol, uint64 size) : MIRRelocable(symbol), size(size) {}

		uint64 GetSize() const { return size; }

	private:
		uint64 size;
	};

	class MIRDataStorage final : public MIRRelocable 
	{
	public:
		using Storage = std::vector<std::variant<uint8, uint16, uint32, uint64>>;
	public:
		MIRDataStorage(std::string_view symbol, bool read_only) : MIRRelocable(symbol),  read_only(read_only) {}
		
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

	class MIRGlobal 
	{
	public:
		MIRGlobal(MIRRelocable* relocable, Linkage linkage, uint32 alignment = 0)
			: relocable(relocable), linkage(linkage), alignment(alignment) {}

		Linkage GetLinkage() const { return linkage; }
		uint32  GetAlignment() const { return alignment; }
		MIRRelocable* GetRelocable() const { return relocable.get(); }

	private:
		std::unique_ptr<MIRRelocable> relocable;
		Linkage linkage;
		uint32 alignment;
	};
}