#include "Instruction.h"
#include "Use.h"

namespace ola
{
	class Function;
	class BasicBlock;

	class CallInst : public Instruction
	{
		static uint32 ComputeNumOperands(uint32 num_args) 
		{
			return 1 + num_args;
		}
	public:

		CallInst(FunctionType* type, Value* called_func, std::vector<Value*> const& args, BasicBlock* bb = nullptr)
			: Instruction(ValueKind_Call, type->GetReturnType(), ComputeNumOperands(args.size()), bb), func_type(type)
		{
			Initialize(called_func, args);
		}
		CallInst(FunctionType* type, Value* called_func, std::vector<Value*> const& args, Instruction* position)
			: Instruction(ValueKind_Call, type->GetReturnType(), ComputeNumOperands(args.size()), position), func_type(type)
		{
			Initialize(called_func, args);
		}
		CallInst(FunctionType* type, Value* called_func, BasicBlock* bb = nullptr)
			: Instruction(ValueKind_Call, type->GetReturnType(), ComputeNumOperands(0), bb), func_type(type)
		{
			Initialize(called_func, {});
		}
		CallInst(FunctionType* type, Value* called_func, Instruction* position)
			: Instruction(ValueKind_Call, type->GetReturnType(), ComputeNumOperands(0), position), func_type(type)
		{
			Initialize(called_func, {});
		}

		FunctionType* GetFunctionType() const { return func_type; }

 		auto ArgBegin() { return OpBegin(); }
		auto ArgBegin() const { return OpBegin(); }
		auto ArgEnd() { return OpEnd() - 1; }
		auto ArgEnd() const { return OpEnd() - 1; }
		IteratorRange<OpIterator> Args() { return MakeRange(ArgBegin(), ArgEnd()); }
		IteratorRange<ConstOpIterator> Args() const { return MakeRange(ArgBegin(), ArgEnd()); }
		bool ArgEmpty() const { return ArgEnd() == ArgBegin(); }
		uint32 ArgSize() const { return ArgEnd() - ArgBegin(); }

		Value const* GetArgOperand(uint32 i) const 
		{
			OLA_ASSERT_MSG(i < ArgSize(), "Out of bounds!");
			return GetOperand(i);
		}
		void SetArgOperand(uint32 i, Value* v) 
		{
			OLA_ASSERT_MSG(i < ArgSize(), "Out of bounds!");
			SetOperand(i, v);
		}

		Use const& GetArgOperandUse(unsigned i) const
		{
			OLA_ASSERT_MSG(i < ArgSize(), "Out of bounds!");
			return GetOperandUse(i);
		}
		Use& GetArgOperandUse(unsigned i) 
		{
			OLA_ASSERT_MSG(i < ArgSize(), "Out of bounds!");
			return GetOperandUse(i);
		}

		Value* GetCalledOperand() const { return GetOperand(GetNumOperands() - 1); }
		Use const& GetCalledOperandUse() const { return GetOperandUse(GetNumOperands() - 1); }
		Use& GetCalledOperandUse() { return GetOperandUse(GetNumOperands() - 1); }

		Function* GetCalledFunction() const;

		Function* GetCaller();

		static bool ClassOf(Value const* I)
		{
			return I->GetKind() == ValueKind_Call;
		}
	private:
		FunctionType* func_type;

	private:
		void Initialize(Value* called_func, std::vector<Value*> const& args = {})
		{
			OLA_ASSERT_MSG(GetNumOperands() == args.size() + 1, "Wrong number of arguments!");
			OLA_ASSERT_MSG(args.size() == func_type->GetParamCount(), "Calling a function with bad signature!");
			for (uint32 i = 0; i <= args.size(); ++i)
			{
				OLA_ASSERT_MSG(func_type->GetParamType(i) == args[i]->GetType(), "Calling a function with a bad signature!");
				SetOperand(i, args[i]);
			}
			SetOperand(args.size(), called_func);
		}
	};

	class SelectInst : public Instruction 
	{
	public:
		SelectInst(Value* C, Value* S1, Value* S2, Instruction* InsertBefore)
			: Instruction(ValueKind_Select, S1->GetType(), 3, InsertBefore)
		{
			Init(C, S1, S2);
		}

		SelectInst(Value* C, Value* S1, Value* S2, BasicBlock* InsertAtEnd = nullptr)
			: Instruction(ValueKind_Select, S1->GetType(), 3, InsertAtEnd)
		{
			Init(C, S1, S2);
		}

		void Init(Value* C, Value* S1, Value* S2) 
		{
			OLA_ASSERT_MSG(S1->GetType() == S2->GetType(), "Invalid operands for select");
			OLA_ASSERT_MSG(C->GetType() == IntegerType::Get(GetContext(), 1), "Invalid operands for select");
			Op<0>() = C;
			Op<1>() = S1;
			Op<2>() = S2;
		}

		const Value* GetCondition() const { return Op<0>(); }
		const Value* GetTrueValue() const { return Op<1>(); }
		const Value* GetFalseValue() const { return Op<2>(); }
		Value* GetCondition() { return Op<0>(); }
		Value* GetTrueValue() { return Op<1>(); }
		Value* GetFalseValue() { return Op<2>(); }

		void SetCondition(Value* V) { Op<0>() = V; }
		void SetTrueValue(Value* V) { Op<1>() = V; }
		void SetFalseValue(Value* V) { Op<2>() = V; }

		static bool ClassOf(Value const* V) 
		{
			return V->GetKind() == ValueKind_Select;
		}
	};

	class ReturnInst : public Instruction 
	{
	public:

		ReturnInst(IRContext& C, Value* ret_value, Instruction* position)
			: Instruction(ValueKind_Return, VoidType::Get(C), !!ret_value, position)
		{
			if (ret_value) Op<0>() = ret_value;
		}
		ReturnInst(IRContext& C, Value* ret_value = nullptr, BasicBlock* bb = nullptr)
			: Instruction(ValueKind_Return, VoidType::Get(C), !!ret_value, bb)
		{
			if (ret_value) Op<0>() = ret_value;
		}

		Value* GetReturnValue() const 
		{
			return GetNumOperands() > 0 ? GetOperand(0) : nullptr;
		}
		uint32 GetNumSuccessors() const { return 0; }

		static bool ClassOf(Value const* V) 
		{
			return V->GetKind() == ValueKind_Return;
		}
	};

	class BranchInst : public Instruction 
	{
	public:
		explicit BranchInst(BasicBlock* if_true, BasicBlock* bb = nullptr);
		BranchInst(BasicBlock* if_true, Instruction* position);
		BranchInst(BasicBlock* if_true, BasicBlock* if_false, Value* cond, BasicBlock* bb = nullptr);
		BranchInst(BasicBlock* if_true, BasicBlock* if_false, Value* cond, Instruction* position);

		bool IsUnconditional() const { return GetNumOperands() == 1; }
		bool IsConditional()   const { return GetNumOperands() == 3; }

		Value* GetCondition() const 
		{
			OLA_ASSERT(IsConditional());
			return Op<2>();
		}
		void SetCondition(Value* C) 
		{
			OLA_ASSERT(IsConditional());
			Op<2>() = C;
		}

		uint32 GetNumSuccessors() const { return 1 + IsConditional(); }
		BasicBlock* GetSuccessor(uint32 i) const;
		void SetSuccessor(uint32 idx, BasicBlock* successor);

		static bool ClassOf(Value const* V) 
		{
			return V->GetKind() == ValueKind_Branch;
		}

	private:

		void Assert()
		{
			if (IsConditional()) OLA_ASSERT_MSG(GetCondition()->GetType() == IntegerType::Get(GetContext(), 1), "May only branch on boolean predicates!");
		}
	};

	class PHIInst : public Instruction
	{
	public:
		explicit PHIInst(IRType* type, unsigned num_reserved_values,
			Instruction* position)
			: Instruction(ValueKind_Phi, type, 0, position),
			reserved_space(num_reserved_values)
		{
		}

		PHIInst(IRType* type, unsigned num_reserved_values, BasicBlock* bb = nullptr)
			: Instruction(ValueKind_Phi, type, 0, bb), reserved_space(num_reserved_values)
		{
		}

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind_Phi;
		}
	private:
		uint32 reserved_space;
	};

	class SwitchInst : public Instruction
	{
	public:

		SwitchInst(Value* Value, BasicBlock* Default, unsigned NumCases, Instruction* InsertBefore);
		SwitchInst(Value* Value, BasicBlock* Default, unsigned NumCases, BasicBlock* InsertAtEnd);

		Value* GetCondition() const { return GetOperand(0); }
		void SetCondition(Value* V) { SetOperand(0, V); }

		BasicBlock* GetDefaultDest() const;
		void SetDefaultDest(BasicBlock* DefaultCase);

		uint32 GetNumCases() const 
		{
			return GetNumOperands() / 2 - 1;
		}
		uint32 GetNumSuccessors() const { return GetNumOperands() / 2; }
		BasicBlock* GetSuccessor(uint32 idx) const;
		void SetSuccessor(uint32 idx, BasicBlock* successor);

		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind_Switch;
		}

	private:
		void Initialize(Value* Value, BasicBlock* Default, unsigned NumReserved)
		{

		}

	};

	class GetElementPtrInst : public Instruction
	{
	public:
		GetElementPtrInst(IRType* PointeeType, Value* Ptr, std::vector<Value*> const& IdxList, Instruction* InsertBefore)
			: Instruction(ValueKind_GEP, PointeeType, IdxList.size() + 1, InsertBefore)
		{
			Initialize(Ptr, IdxList);
		}
		GetElementPtrInst(IRType* PointeeType, Value* Ptr, std::vector<Value*> const& IdxList, BasicBlock* InsertAtEnd = nullptr)
			: Instruction(ValueKind_GEP, PointeeType, IdxList.size() + 1, InsertAtEnd)
		{
			Initialize(Ptr, IdxList);
		}

		GetElementPtrInst(IRType* PointeeType, Value* Ptr, std::vector<Value*> const& IdxList, bool in_bounds, Instruction* InsertBefore)
			: GetElementPtrInst(PointeeType, Ptr, IdxList, InsertBefore)
		{
			SetInBounds(in_bounds);
		}
		GetElementPtrInst(IRType* PointeeType, Value* Ptr, std::vector<Value*> const& IdxList, bool in_bounds, BasicBlock* InsertAtEnd = nullptr)
			: GetElementPtrInst(PointeeType, Ptr, IdxList, InsertAtEnd)
		{
			SetInBounds(in_bounds);
		}

		void SetSourceElementType(IRType* ty) { src_element_type = ty; }
		void SetResultElementType(IRType* ty) { result_element_type = ty; }
		IRType* GetSourceElementType() const { return src_element_type; }
		IRType* GetResultElementType() const { return result_element_type; }

		Value* GetPointerOperand() 
		{
			return GetOperand(0);
		}
		Value const* GetPointerOperand() const
		{
			return GetOperand(0);
		}
		IRType* GetPointerOperandType() const 
		{
			return GetPointerOperand()->GetType();
		}

		uint32 GetNumIndices() const {  return GetNumOperands() - 1; }
		bool HasIndices() const { return GetNumIndices() > 0; }

		void SetInBounds(bool _in_bounds = true) { in_bounds = _in_bounds; }
		bool IsInBounds() const { return in_bounds; }

		OpIterator       IdxBegin() { return OpBegin() + 1; }
		ConstOpIterator  IdxBegin() const { return OpBegin() + 1; }
		OpIterator       IdxEnd() { return OpEnd(); }
		ConstOpIterator  IdxEnd()   const { return OpEnd(); }
		IteratorRange<OpIterator> Indices()
		{
			return MakeRange(IdxBegin(), IdxEnd());
		}
		IteratorRange<ConstOpIterator> Indices()  const 
		{
			return MakeRange(IdxBegin(), IdxEnd());
		}

		static IRType* getTypeAtIndex(IRType* ty, Value* idx)
		{
			return nullptr;
		}
		static IRType* getTypeAtIndex(IRType* ty, uint64 idx)
		{
			return nullptr;
		}
		static bool ClassOf(Value const* V)
		{
			return V->GetKind() == ValueKind_GEP;
		}

	private:
		IRType* src_element_type = nullptr;
		IRType* result_element_type = nullptr;
		bool    in_bounds = false;
	private:
		void Initialize(Value* Ptr, std::vector<Value*> const& IdxList)
		{
			Op<0>() = Ptr;
			for (uint32 i = 0; i <= IdxList.size(); ++i)
			{
				SetOperand(i + 1, IdxList[i]);
			}
		}
	};
}