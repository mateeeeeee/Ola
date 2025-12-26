#pragma once
#include <memory>
#include <vector>
#include "Backend/Custom/IR/Instruction.h"
#include "Backend/Custom/Codegen/MachineOperand.h"

namespace ola
{
	class ISelNodeVisitor;

	enum class ISelNodeKind : Uint32
	{
		Register,
		Immediate,
		Address,
		BinaryOp,
		UnaryOp,
		Load,
		Store,
		Compare,
		Select,
		Call,
		Phi,
		Asm
	};

	class ISelNode
	{
	public:
		explicit ISelNode(ISelNodeKind kind) : kind(kind), original_value(nullptr) {}
		virtual ~ISelNode() = default;

		ISelNodeKind GetKind() const { return kind; }
		virtual void Accept(ISelNodeVisitor* visitor) = 0;

		void SetValue(Value* v) { original_value = v; }
		Value* GetValue() const { return original_value; }

	private:
		ISelNodeKind kind;
		Value* original_value;
	};

	using ISelNodePtr = std::unique_ptr<ISelNode>;

	class ISelRegisterNode final : public ISelNode
	{
	public:
		explicit ISelRegisterNode(MachineOperand reg)
			: ISelNode(ISelNodeKind::Register)
			, reg(reg)
			, source(nullptr)
		{}

		ISelRegisterNode(MachineOperand reg, ISelNodePtr source)
			: ISelNode(ISelNodeKind::Register)
			, reg(reg)
			, source(std::move(source))
		{}

		void Accept(ISelNodeVisitor* visitor) override;

		MachineOperand GetRegister() const { return reg; }
		void SetRegister(MachineOperand r) { reg = r; }

		ISelNode* GetSource() const { return source.get(); }
		ISelNodePtr TakeSource() { return std::move(source); }
		Bool HasSource() const { return source != nullptr; }

		void ConsumeSource(ISelNodePtr src)
		{
			source = std::move(src);
		}

		static Bool ClassOf(ISelNode const* N)
		{
			return N->GetKind() == ISelNodeKind::Register;
		}

	private:
		MachineOperand reg;
		ISelNodePtr source;
	};

	class ISelImmediateNode final : public ISelNode
	{
	public:
		ISelImmediateNode(Int64 value, MachineType type)
			: ISelNode(ISelNodeKind::Immediate)
			, value(value)
			, type(type)
		{}

		void Accept(ISelNodeVisitor* visitor) override;

		Int64 GetImmediate() const { return value; }
		MachineType GetType() const { return type; }

		static Bool ClassOf(ISelNode const* N)
		{
			return N->GetKind() == ISelNodeKind::Immediate;
		}

	private:
		Int64 value;
		MachineType type;
	};

	class ISelAddressNode final : public ISelNode
	{
	public:
		ISelAddressNode()
			: ISelNode(ISelNodeKind::Address)
			, base(nullptr)
			, index(nullptr)
			, scale(1)
			, displacement(0)
		{}

		ISelAddressNode(ISelNodePtr base, ISelNodePtr index = nullptr, Int64 scale = 1, Int64 displacement = 0)
			: ISelNode(ISelNodeKind::Address)
			, base(std::move(base))
			, index(std::move(index))
			, scale(scale)
			, displacement(displacement)
		{}

		void Accept(ISelNodeVisitor* visitor) override;

		ISelNode* GetBase() const { return base.get(); }
		ISelNode* GetIndex() const { return index.get(); }
		Int64 GetScale() const { return scale; }
		Int64 GetDisplacement() const { return displacement; }

		ISelNodePtr TakeBase() { return std::move(base); }
		ISelNodePtr TakeIndex() { return std::move(index); }

		void SetBase(ISelNodePtr b) { base = std::move(b); }
		void SetIndex(ISelNodePtr i) { index = std::move(i); }
		void SetScale(Int64 s) { scale = s; }
		void SetDisplacement(Int64 d) { displacement = d; }

		Bool HasBase() const { return base != nullptr; }
		Bool HasIndex() const { return index != nullptr; }
		Bool HasDisplacement() const { return displacement != 0; }

		static Bool ClassOf(ISelNode const* N)
		{
			return N->GetKind() == ISelNodeKind::Address;
		}

	private:
		ISelNodePtr base;
		ISelNodePtr index;
		Int64 scale;
		Int64 displacement;
	};

	class ISelBinaryOpNode final : public ISelNode
	{
	public:
		ISelBinaryOpNode(Opcode op, ISelNodePtr left, ISelNodePtr right)
			: ISelNode(ISelNodeKind::BinaryOp)
			, opcode(op)
			, left(std::move(left))
			, right(std::move(right))
		{}

		void Accept(ISelNodeVisitor* visitor) override;

		Opcode GetOpcode() const { return opcode; }
		ISelNode* GetLeft() const { return left.get(); }
		ISelNode* GetRight() const { return right.get(); }

		ISelNodePtr TakeLeft() { return std::move(left); }
		ISelNodePtr TakeRight() { return std::move(right); }

		static Bool ClassOf(ISelNode const* N)
		{
			return N->GetKind() == ISelNodeKind::BinaryOp;
		}

	private:
		Opcode opcode;
		ISelNodePtr left;
		ISelNodePtr right;
	};

	class ISelUnaryOpNode final : public ISelNode
	{
	public:
		ISelUnaryOpNode(Opcode op, ISelNodePtr operand)
			: ISelNode(ISelNodeKind::UnaryOp)
			, opcode(op)
			, operand(std::move(operand))
		{}

		void Accept(ISelNodeVisitor* visitor) override;

		Opcode GetOpcode() const { return opcode; }
		ISelNode* GetOperand() const { return operand.get(); }

		ISelNodePtr TakeOperand() { return std::move(operand); }

		static Bool ClassOf(ISelNode const* N)
		{
			return N->GetKind() == ISelNodeKind::UnaryOp;
		}

	private:
		Opcode opcode;
		ISelNodePtr operand;
	};

	class ISelLoadNode final : public ISelNode
	{
	public:
		ISelLoadNode(ISelNodePtr address, MachineType type)
			: ISelNode(ISelNodeKind::Load)
			, address(std::move(address))
			, type(type)
		{}

		void Accept(ISelNodeVisitor* visitor) override;

		ISelNode* GetAddress() const { return address.get(); }
		MachineType GetType() const { return type; }

		ISelNodePtr TakeAddress() { return std::move(address); }

		static Bool ClassOf(ISelNode const* N)
		{
			return N->GetKind() == ISelNodeKind::Load;
		}

	private:
		ISelNodePtr address;
		MachineType type;
	};

	class ISelStoreNode final : public ISelNode
	{
	public:
		ISelStoreNode(ISelNodePtr value, ISelNodePtr address)
			: ISelNode(ISelNodeKind::Store)
			, value(std::move(value))
			, address(std::move(address))
		{}

		void Accept(ISelNodeVisitor* visitor) override;

		ISelNode* GetValueNode() const { return value.get(); }
		ISelNode* GetAddress() const { return address.get(); }

		ISelNodePtr TakeValue() { return std::move(value); }
		ISelNodePtr TakeAddress() { return std::move(address); }

		static Bool ClassOf(ISelNode const* N)
		{
			return N->GetKind() == ISelNodeKind::Store;
		}

	private:
		ISelNodePtr value;
		ISelNodePtr address;
	};

	class ISelCompareNode final : public ISelNode
	{
	public:
		ISelCompareNode(CompareOp cmp, ISelNodePtr left, ISelNodePtr right)
			: ISelNode(ISelNodeKind::Compare)
			, cmp(cmp)
			, left(std::move(left))
			, right(std::move(right))
		{}

		void Accept(ISelNodeVisitor* visitor) override;

		CompareOp GetCompareOp() const { return cmp; }
		ISelNode* GetLeft() const { return left.get(); }
		ISelNode* GetRight() const { return right.get(); }

		ISelNodePtr TakeLeft() { return std::move(left); }
		ISelNodePtr TakeRight() { return std::move(right); }

		static Bool ClassOf(ISelNode const* N)
		{
			return N->GetKind() == ISelNodeKind::Compare;
		}

	private:
		CompareOp cmp;
		ISelNodePtr left;
		ISelNodePtr right;
	};

	class ISelSelectNode final : public ISelNode
	{
	public:
		ISelSelectNode(ISelNodePtr predicate, ISelNodePtr true_val, ISelNodePtr false_val)
			: ISelNode(ISelNodeKind::Select)
			, predicate(std::move(predicate))
			, true_val(std::move(true_val))
			, false_val(std::move(false_val))
		{}

		void Accept(ISelNodeVisitor* visitor) override;

		ISelNode* GetPredicate() const { return predicate.get(); }
		ISelNode* GetTrueValue() const { return true_val.get(); }
		ISelNode* GetFalseValue() const { return false_val.get(); }

		ISelNodePtr TakePredicate() { return std::move(predicate); }
		ISelNodePtr TakeTrueValue() { return std::move(true_val); }
		ISelNodePtr TakeFalseValue() { return std::move(false_val); }

		static Bool ClassOf(ISelNode const* N)
		{
			return N->GetKind() == ISelNodeKind::Select;
		}

	private:
		ISelNodePtr predicate;
		ISelNodePtr true_val;
		ISelNodePtr false_val;
	};

	class ISelCallNode final : public ISelNode
	{
	public:
		ISelCallNode(ISelNodePtr callee, std::vector<ISelNodePtr> args, MachineType return_type)
			: ISelNode(ISelNodeKind::Call)
			, callee(std::move(callee))
			, args(std::move(args))
			, return_type(return_type)
		{}

		void Accept(ISelNodeVisitor* visitor) override;

		ISelNode* GetCallee() const { return callee.get(); }
		MachineType GetReturnType() const { return return_type; }

		Uint32 GetNumArgs() const { return static_cast<Uint32>(args.size()); }
		ISelNode* GetArg(Uint32 i) const { return args[i].get(); }

		std::vector<ISelNodePtr>& Args() { return args; }
		std::vector<ISelNodePtr> const& Args() const { return args; }

		static Bool ClassOf(ISelNode const* N)
		{
			return N->GetKind() == ISelNodeKind::Call;
		}

	private:
		ISelNodePtr callee;
		std::vector<ISelNodePtr> args;
		MachineType return_type;
	};

	class ISelPhiNode final : public ISelNode
	{
	public:
		struct PhiIncoming
		{
			ISelNodePtr value;
			BasicBlock* block;
		};

		explicit ISelPhiNode(MachineType type)
			: ISelNode(ISelNodeKind::Phi)
			, type(type)
		{}

		void Accept(ISelNodeVisitor* visitor) override;

		void AddIncoming(ISelNodePtr value, BasicBlock* block)
		{
			incoming.push_back({ std::move(value), block });
		}

		MachineType GetType() const { return type; }
		Uint32 GetNumIncoming() const { return static_cast<Uint32>(incoming.size()); }

		ISelNode* GetIncomingValue(Uint32 i) const { return incoming[i].value.get(); }
		BasicBlock* GetIncomingBlock(Uint32 i) const { return incoming[i].block; }

		std::vector<PhiIncoming>& Incomings() { return incoming; }
		std::vector<PhiIncoming> const& Incomings() const { return incoming; }

		static Bool ClassOf(ISelNode const* N)
		{
			return N->GetKind() == ISelNodeKind::Phi;
		}

	private:
		std::vector<PhiIncoming> incoming;
		MachineType type;
	};

	class MachineInstruction;

	class ISelAsmNode final : public ISelNode
	{
	public:
		explicit ISelAsmNode(std::vector<MachineInstruction*> instructions)
			: ISelNode(ISelNodeKind::Asm)
			, instructions(std::move(instructions))
		{}

		void Accept(ISelNodeVisitor* visitor) override;

		std::vector<MachineInstruction*>& Instructions() { return instructions; }
		std::vector<MachineInstruction*> const& Instructions() const { return instructions; }

		static Bool ClassOf(ISelNode const* N)
		{
			return N->GetKind() == ISelNodeKind::Asm;
		}

	private:
		std::vector<MachineInstruction*> instructions;
	};

	class ISelNodeVisitor
	{
	public:
		virtual ~ISelNodeVisitor() = default;

		virtual void Visit(ISelRegisterNode* node) = 0;
		virtual void Visit(ISelImmediateNode* node) = 0;
		virtual void Visit(ISelAddressNode* node) = 0;
		virtual void Visit(ISelBinaryOpNode* node) = 0;
		virtual void Visit(ISelUnaryOpNode* node) = 0;
		virtual void Visit(ISelLoadNode* node) = 0;
		virtual void Visit(ISelStoreNode* node) = 0;
		virtual void Visit(ISelCompareNode* node) = 0;
		virtual void Visit(ISelSelectNode* node) = 0;
		virtual void Visit(ISelCallNode* node) = 0;
		virtual void Visit(ISelPhiNode* node) = 0;
		virtual void Visit(ISelAsmNode* node) = 0;
	};
}
