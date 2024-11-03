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
		MachineOperand& AllocateStack(MachineType type)
		{
			stack_offset += GetOperandSize(type);
			MachineOperand stack_object = MachineOperand::StackObject(-stack_offset, type);
			stack_objects.push_back(stack_object);
			return stack_objects.back();
		}
		MachineOperand& AllocateStack(Uint32 size)
		{
			stack_offset += size;
			MachineOperand stack_object = MachineOperand::StackObject(-stack_offset, MachineType::Ptr);
			stack_objects.push_back(stack_object);
			return stack_objects.back();
		}
		Sint32 GetStackAllocationSize() const
		{
			return stack_offset;
		}

		virtual RelocableKind GetRelocableKind() const override
		{
			return RelocableKind::Function;
		}

	private:
		Bool is_declaration;
		std::list<std::unique_ptr<MachineBasicBlock>> blocks;
		std::vector<MachineOperand> args;
		Sint32 stack_offset = 0;
		std::vector<MachineOperand> stack_objects;
	};
}