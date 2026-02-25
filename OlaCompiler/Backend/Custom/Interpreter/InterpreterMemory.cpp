#include "InterpreterMemory.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/GlobalValue.h"
#include "Backend/Custom/IR/Constant.h"
#include <cstring>

namespace ola
{
	InterpreterMemory::InterpreterMemory(Usize stack_size, Usize heap_size)
		: stack(stack_size), heap(heap_size)
	{
		stack_base = stack.data();
		stack_ptr = stack_base;

		heap_base = heap.data();
		heap_ptr = heap_base;
	}

	Uint8* InterpreterMemory::AlignPointer(Uint8* ptr, Uint32 alignment)
	{
		if (alignment == 0) 
		{
			alignment = 1;
		}
		Uintptr addr = reinterpret_cast<Uintptr>(ptr);
		Uintptr aligned = (addr + alignment - 1) & ~(static_cast<Uintptr>(alignment) - 1);
		return reinterpret_cast<Uint8*>(aligned);
	}

	Uint8* InterpreterMemory::StackAlloc(Uint32 size, Uint32 alignment)
	{
		stack_ptr = AlignPointer(stack_ptr, alignment);
		Uint8* result = stack_ptr;
		stack_ptr += size;
		OLA_ASSERT_MSG(stack_ptr < stack_base + stack.size(), "Stack overflow!");
		return result;
	}

	void InterpreterMemory::PushStackFrame()
	{
		frame_pointers.push_back(stack_ptr);
	}

	void InterpreterMemory::PopStackFrame()
	{
		OLA_ASSERT(!frame_pointers.empty());
		stack_ptr = frame_pointers.back();
		frame_pointers.pop_back();
	}

	void InterpreterMemory::Store(Uint8* addr, void const* data, Uint32 size)
	{
		std::memcpy(addr, data, size);
	}

	void InterpreterMemory::Load(Uint8* addr, void* data, Uint32 size)
	{
		std::memcpy(data, addr, size);
	}

	void InterpreterMemory::StoreInt(Uint8* addr, Int64 val, Uint32 byte_width)
	{
		switch (byte_width)
		{
		case 1: *reinterpret_cast<Int8*>(addr) = static_cast<Int8>(val); break;
		case 2: *reinterpret_cast<Int16*>(addr) = static_cast<Int16>(val); break;
		case 4: *reinterpret_cast<Int32*>(addr) = static_cast<Int32>(val); break;
		case 8: *reinterpret_cast<Int64*>(addr) = val; break;
		default: OLA_ASSERT_MSG(false, "Invalid integer byte width");
		}
	}

	void InterpreterMemory::StoreFloat(Uint8* addr, Float64 val)
	{
		*reinterpret_cast<Float64*>(addr) = val;
	}

	void InterpreterMemory::StorePointer(Uint8* addr, Uint8* ptr)
	{
		*reinterpret_cast<Uint8**>(addr) = ptr;
	}

	Int64 InterpreterMemory::LoadInt(Uint8* addr, Uint32 byte_width)
	{
		switch (byte_width)
		{
		case 1: return *reinterpret_cast<Int8*>(addr);
		case 2: return *reinterpret_cast<Int16*>(addr);
		case 4: return *reinterpret_cast<Int32*>(addr);
		case 8: return *reinterpret_cast<Int64*>(addr);
		default: OLA_ASSERT_MSG(false, "Invalid integer byte width"); return 0;
		}
	}

	Float64 InterpreterMemory::LoadFloat(Uint8* addr)
	{
		return *reinterpret_cast<Float64*>(addr);
	}

	Uint8* InterpreterMemory::LoadPointer(Uint8* addr)
	{
		return *reinterpret_cast<Uint8**>(addr);
	}

	Uint8* InterpreterMemory::AllocGlobal(GlobalVariable* gv, Uint32 size, Uint32 alignment)
	{
		heap_ptr = AlignPointer(heap_ptr, alignment);
		Uint8* result = heap_ptr;
		heap_ptr += size;
		OLA_ASSERT_MSG(heap_ptr < heap_base + heap.size(), "Heap overflow!");
		global_addresses[gv] = result;
		std::memset(result, 0, size);
		return result;
	}

	Uint8* InterpreterMemory::GetGlobalAddress(GlobalVariable* gv)
	{
		auto it = global_addresses.find(gv);
		if (it != global_addresses.end())
		{
			return it->second;
		}
		return nullptr;
	}

	Uint8* InterpreterMemory::AllocString(std::string_view str)
	{
		auto it = string_pool.find(str);
		if (it != string_pool.end())
		{
			return it->second;
		}

		Uint32 size = static_cast<Uint32>(str.size() + 1);
		Uint8* result = heap_ptr;
		heap_ptr += size;
		OLA_ASSERT_MSG(heap_ptr < heap_base + heap.size(), "Heap overflow!");
		std::memcpy(result, str.data(), str.size());
		result[str.size()] = '\0';
		string_pool[str] = result;
		return result;
	}

	Uint8* InterpreterMemory::HeapAlloc(Uint32 size)
	{
		heap_ptr = AlignPointer(heap_ptr, 8);
		Uint8* result = heap_ptr;
		heap_ptr += size;
		OLA_ASSERT_MSG(heap_ptr < heap_base + heap.size(), "Heap overflow!");
		std::memset(result, 0, size);
		return result;
	}

	void InterpreterMemory::HeapFree(Uint8* ptr)
	{
		(void)ptr;
	}

	Bool InterpreterMemory::IsValidStackAddress(Uint8* addr) const
	{
		return addr >= stack_base && addr < stack_base + stack.size();
	}

	Bool InterpreterMemory::IsValidHeapAddress(Uint8* addr) const
	{
		return addr >= heap_base && addr < heap_base + heap.size();
	}

}
