#include <vector>
#include <list>
#include <memory>
#include "MachineOperand.h"
#include "MachineRelocable.h"

namespace ola
{
	class MachineBasicBlock;
	class MachineFunction final : public MachineRelocable
	{
	public:
		explicit MachineFunction(std::string_view symbol, Bool is_declaration);
		~MachineFunction();

		Bool IsDeclaration() const { return is_declaration; }

		auto& Blocks() { return blocks; }
		auto const& Blocks() const { return blocks; }

		std::vector<MachineOperand>& Args()
		{
			return args;
		}
		MachineOperand& AllocateLocalStack(MachineType type)
		{
			local_stack_offset += GetOperandSize(type);
			MachineOperand stack_object = MachineOperand::StackObject(-local_stack_offset, type);
			local_stack_objects.push_back(stack_object);
			return local_stack_objects.back();
		}
		MachineOperand& AllocateLocalStack(Uint32 size)
		{
			local_stack_offset += size;
			local_stack_offset = OLA_ALIGN_UP(local_stack_offset, 8);
			MachineOperand stack_object = MachineOperand::StackObject(-local_stack_offset, MachineType::Ptr);
			local_stack_objects.push_back(stack_object);
			return local_stack_objects.back();
		}
		void AllocateArgumentStack(Uint32 size)
		{
			argument_stack_offset += size;
		}
		Int32 GetStackAllocationSize() const
		{
			return GetLocalStackAllocationSize() + argument_stack_offset;
		}
		Int32 GetLocalStackAllocationSize() const
		{
			return local_stack_offset;
		}

		void AddCallInstructionArgCount(Uint32 arg_count)
		{
			has_call_instructions = true;
			max_call_arg_count = std::max(max_call_arg_count, arg_count);
		}
		Uint32 GetMaxCallArgCount() const
		{
			return max_call_arg_count;
		}
		Bool HasCallInstructions() const
		{
			return has_call_instructions;
		}

		virtual RelocableKind GetRelocableKind() const override
		{
			return RelocableKind::Function;
		}

	private:
		Bool is_declaration;
		std::list<std::unique_ptr<MachineBasicBlock>> blocks;
		std::vector<MachineOperand> args;
		Int32 local_stack_offset = 0;
		Int32 argument_stack_offset = 0;
		std::vector<MachineOperand> local_stack_objects;
		Bool has_call_instructions = false;
		Uint32 max_call_arg_count = 0;
	};
}