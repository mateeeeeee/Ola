#pragma once
#include <vector>
#include <unordered_map>
#include <string_view>

namespace ola
{
	class IRModule;
	class GlobalVariable;

	class InterpreterMemory
	{
	public:
		static constexpr Usize DEFAULT_STACK_SIZE = 1024 * 1024;     
		static constexpr Usize DEFAULT_HEAP_SIZE = 16 * 1024 * 1024; 

		explicit InterpreterMemory(Usize stack_size = DEFAULT_STACK_SIZE,
								   Usize heap_size = DEFAULT_HEAP_SIZE);
		~InterpreterMemory() = default;

		Uint8* StackAlloc(Uint32 size, Uint32 alignment);
		void PushStackFrame();
		void PopStackFrame();

		void Store(Uint8* addr, void const* data, Uint32 size);
		void Load(Uint8* addr, void* data, Uint32 size);

		void StoreInt(Uint8* addr, Int64 val, Uint32 byte_width);
		void StoreFloat(Uint8* addr, Float64 val);
		void StorePointer(Uint8* addr, Uint8* ptr);

		Int64 LoadInt(Uint8* addr, Uint32 byte_width);
		Float64 LoadFloat(Uint8* addr);
		Uint8* LoadPointer(Uint8* addr);

		Uint8* GetGlobalAddress(GlobalVariable* gv);
		Uint8* AllocGlobal(GlobalVariable* gv, Uint32 size, Uint32 alignment);
		Uint8* AllocString(std::string_view str);

		Bool IsValidStackAddress(Uint8* addr) const;
		Bool IsValidHeapAddress(Uint8* addr) const;

	private:
		std::vector<Uint8> stack;
		std::vector<Uint8> heap;

		Uint8* stack_base;
		Uint8* stack_ptr;
		std::vector<Uint8*> frame_pointers;

		Uint8* heap_base;
		Uint8* heap_ptr;

		std::unordered_map<GlobalVariable*, Uint8*> global_addresses;
		std::unordered_map<std::string_view, Uint8*> string_pool;

	private:
		Uint8* AlignPointer(Uint8* ptr, Uint32 alignment);
	};
}
