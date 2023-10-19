#include "LLVMVisitor.h"
#include "Frontend/AST.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/Casting.h"

namespace wave
{

	LLVMVisitor::LLVMVisitor(AST const* ast) : builder(context)
	{
		llvm::InitializeAllTargets();
		llvm::InitializeAllTargetMCs();
		llvm::InitializeAllAsmPrinters();
		llvm::InitializeAllAsmParsers();
		module = std::make_unique<llvm::Module>("WaveModule", context);

		ast->translation_unit->Accept(*this);
	}

	void LLVMVisitor::Visit(NodeAST const&, uint32)
	{
		WAVE_ASSERT(false);
	}

	void LLVMVisitor::Visit(TranslationUnit const& translation_unit, uint32)
	{
		for (auto&& decl : translation_unit.GetDecls()) decl->Accept(*this);
	}

	void LLVMVisitor::Visit(Decl const&, uint32)
	{
		WAVE_ASSERT(false);
	}

	void LLVMVisitor::Visit(FunctionDecl const& function_decl, uint32)
	{
		QualifiedType const& type = function_decl.GetType();
		WAVE_ASSERT(IsFunctionType(type));
		llvm::FunctionType* function_type = llvm::cast<llvm::FunctionType>(ConvertToLLVMType(type));
		llvm::Function* llvm_function = llvm::Function::Create(function_type, llvm::Function::ExternalLinkage, function_decl.GetName(), *module);

		llvm::BasicBlock* entry_block = llvm::BasicBlock::Create(context, "entry", llvm_function);
		builder.SetInsertPoint(entry_block);

		llvm::Function::arg_iterator param_it = llvm_function->arg_begin();
		for (auto& param : function_decl.GetParamDeclarations())
		{
			llvm::Value* llvm_param = &*param_it;
			llvm_param->setName(param->GetName());
			llvm_value_map[&param] = llvm_param;
			++param_it;
		}

		if (!function_decl.IsDefinition())
		{
			return_alloc = builder.CreateAlloca(function_type->getReturnType(), nullptr);
			exit_block = llvm::BasicBlock::Create(context, "exit", llvm_function);

			function_decl.GetBodyStmt()->Accept(*this);

			builder.SetInsertPoint(exit_block);
			if (return_alloc) builder.CreateRet(Load(function_type->getReturnType(), return_alloc));
			else builder.CreateRetVoid();

			std::vector<llvm::BasicBlock*> unreachable_blocks{};
			for (auto&& block : *llvm_function)
				if (block.hasNPredecessors(0) && &block != entry_block) unreachable_blocks.push_back(&block);
			for (auto unreachable_block : unreachable_blocks)
				unreachable_block->removeFromParent();

			std::vector<llvm::BasicBlock*> empty_blocks{};
			for (auto&& block : *llvm_function)
				if (block.empty()) empty_blocks.push_back(&block);
			for (auto empty_block : empty_blocks)
			{
				builder.SetInsertPoint(empty_block);
				builder.CreateAlloca(llvm::IntegerType::get(context, 1), nullptr, "nop");
				builder.CreateBr(exit_block);
			}

			exit_block = nullptr;
			return_alloc = nullptr;
		}

		llvm_value_map[&function_decl] = llvm_function;
	}

	void LLVMVisitor::Visit(VariableDecl const& var_decl, uint32)
	{
		llvm::Type* llvm_type = ConvertToLLVMType(var_decl.GetType());
		llvm::AllocaInst* alloca = builder.CreateAlloca(llvm_type, nullptr);

		if (var_decl.GetInitExpr()) 
		{
			var_decl.GetInitExpr()->Accept(*this);
			llvm::Value* init_value = llvm_value_map[var_decl.GetInitExpr()];
			Store(init_value, alloca);
		}
		llvm_value_map[&var_decl] = alloca;
	}

	void LLVMVisitor::Visit(Stmt const& stmt, uint32)
	{
		WAVE_ASSERT(false);
	}

	void LLVMVisitor::Visit(CompoundStmt const& compound_stmt, uint32)
	{
		for (auto const& statement : compound_stmt.GetStmts()) statement->Accept(*this);
	}

	void LLVMVisitor::Visit(DeclStmt const& decl_stmt, uint32)
	{
		if (decl_stmt.GetDecl()) decl_stmt.GetDecl()->Accept(*this);
	}

	void LLVMVisitor::Visit(ExprStmt const& expr_stmt, uint32)
	{
		if (expr_stmt.GetExpr()) expr_stmt.GetExpr()->Accept(*this);
	}

	void LLVMVisitor::Visit(NullStmt const& null_stmt, uint32) {}

	void LLVMVisitor::Visit(ReturnStmt const& return_stmt, uint32)
	{
		if (ExprStmt const* expr_stmt = return_stmt.GetExprStmt()) 
		{
			expr_stmt->GetExpr()->Accept(*this);
			llvm::Value* return_expr_value = llvm_value_map[expr_stmt->GetExpr()];
			WAVE_ASSERT(return_expr_value);
			llvm_value_map[&return_stmt] = Store(return_expr_value, return_alloc);
		}
		else 
		{
			llvm_value_map[&return_stmt] = nullptr;
		}
		builder.CreateBr(exit_block);

		llvm::BasicBlock* currentBlock = builder.GetInsertBlock();
		llvm::Function* currentFunction = currentBlock->getParent();
		llvm::BasicBlock* returnBlock = llvm::BasicBlock::Create(context, "return", currentFunction, currentBlock->getNextNode());
		builder.SetInsertPoint(returnBlock);
	}

	void LLVMVisitor::Visit(IfStmt const& if_stmt, uint32)
	{
		Expr const* cond_expr = if_stmt.GetConditionExpr();
		Stmt const* then_stmt = if_stmt.GetThenStmt();
		Stmt const* else_stmt = if_stmt.GetElseStmt();

		llvm::Function* function = builder.GetInsertBlock()->getParent();
		llvm::BasicBlock* then_block = llvm::BasicBlock::Create(context, "if.then", function, exit_block);
		llvm::BasicBlock* else_block = nullptr;
		if(else_stmt) else_block = llvm::BasicBlock::Create(context, "if.else", function, exit_block);
		llvm::BasicBlock* merge_block = llvm::BasicBlock::Create(context, "if.end", function, exit_block);

		cond_expr->Accept(*this);
		llvm::Value* condition_value = llvm_value_map[cond_expr];
		WAVE_ASSERT(condition_value);

		if (IsBoolean(condition_value->getType()))
		{
			builder.CreateCondBr(condition_value, then_block, else_block ? else_block : merge_block);
		}
		else
		{
			llvm::Value* condition = Load(cond_expr->GetType(), condition_value);
			llvm::Value* boolean_cond = builder.CreateICmpNE(condition, llvm::ConstantInt::get(context, llvm::APInt(64, 0)), "ifcond");
			builder.CreateCondBr(boolean_cond, then_block, else_block ? else_block : merge_block);
		}

		builder.SetInsertPoint(then_block);
		then_stmt->Accept(*this);
		builder.CreateBr(merge_block);

		if (else_stmt)
		{
			builder.SetInsertPoint(else_block);
			else_stmt->Accept(*this);
			builder.CreateBr(merge_block);
		}
		builder.SetInsertPoint(merge_block);
	}

	void LLVMVisitor::Visit(Expr const& node, uint32)
	{
		WAVE_ASSERT(false);
	}

	void LLVMVisitor::Visit(UnaryExpr const& unary_expr, uint32)
	{
		Expr const* operand_expr = unary_expr.GetOperand();
		operand_expr->Accept(*this);
		llvm::Value* operand_value = llvm_value_map[operand_expr];
		WAVE_ASSERT(operand_value);
		llvm::Value* operand = Load(operand_expr->GetType(), operand_value);

		llvm::Value* result = nullptr;
		switch (unary_expr.GetUnaryKind())
		{
		case UnaryExprKind::PreIncrement:
		{
			llvm::Value* incremented_value = builder.CreateAdd(operand, llvm::ConstantInt::get(operand->getType(), 1));
			Store(incremented_value, operand_value);
			result = incremented_value;
		}
		break;
		case UnaryExprKind::PreDecrement:
		{
			llvm::Value* decremented_value = builder.CreateSub(operand, llvm::ConstantInt::get(operand->getType(), 1));
			Store(decremented_value, operand_value);
			result = decremented_value;
		}
		break;
		case UnaryExprKind::PostIncrement:
		{
			result = builder.CreateAlloca(operand_value->getType());
			Store(operand_value, result);
			llvm::Value* incremented_value = builder.CreateAdd(operand, llvm::ConstantInt::get(operand->getType(), 1));
			Store(incremented_value, operand_value);
		}
		break;
		case UnaryExprKind::PostDecrement:
		{
			result = builder.CreateAlloca(operand_value->getType());
			Store(operand_value, result);
			llvm::Value* decremented_value = builder.CreateSub(operand, llvm::ConstantInt::get(operand->getType(), 1));
			Store(decremented_value, operand_value);
		}
		break;
		case UnaryExprKind::Plus:
		{
			result = operand_value;
		}
		break;
		case UnaryExprKind::Minus:
		{
			result = builder.CreateNeg(operand);
		}
		break;
		case UnaryExprKind::BitNot:
		{
			result = builder.CreateNot(operand);
		}
		break;
		case UnaryExprKind::LogicalNot:
		{
			result = builder.CreateICmpEQ(operand, llvm::ConstantInt::get(operand_value->getType(), 0));
		}
		break;
		default:
			WAVE_ASSERT(false);
		}
		WAVE_ASSERT(result);
		llvm_value_map[&unary_expr] = result;
	}

	void LLVMVisitor::Visit(BinaryExpr const& binary_expr, uint32)
	{
		Expr const* lhs_expr = binary_expr.GetLHS();
		lhs_expr->Accept(*this);
		llvm::Value* lhs_value = llvm_value_map[lhs_expr];
		Expr const* rhs_expr = binary_expr.GetRHS();
		rhs_expr->Accept(*this);
		llvm::Value* rhs_value = llvm_value_map[rhs_expr];
		WAVE_ASSERT(lhs_value && rhs_value);

		llvm::Value* lhs = Load(lhs_expr->GetType(), lhs_value);
		llvm::Value* rhs = Load(rhs_expr->GetType(), rhs_value);

		llvm::Value* result = nullptr;
		switch (binary_expr.GetBinaryKind())
		{
		case BinaryExprKind::Assign:
		{
			result = Store(rhs_value, lhs_value);
		}
		break;
		case BinaryExprKind::Add:
		{
			result = builder.CreateAdd(lhs, rhs);
		}
		break;
		case BinaryExprKind::Subtract:
		{
			result = builder.CreateSub(lhs, rhs);
		}
		break;
		case BinaryExprKind::Multiply:
		{
			result = builder.CreateMul(lhs, rhs);
		}
		break;
		case BinaryExprKind::Divide:
		{
			result = builder.CreateSDiv(lhs, rhs);
		}
		break;
		case BinaryExprKind::Modulo:
		{
			result = builder.CreateSRem(lhs, rhs);
		}
		break;
		case BinaryExprKind::ShiftLeft:
			break;
		case BinaryExprKind::ShiftRight:
			break;
		case BinaryExprKind::BitAnd:
			break;
		case BinaryExprKind::BitOr:
			break;
		case BinaryExprKind::BitXor:
			break;
		case BinaryExprKind::Comma:
			break;
		case BinaryExprKind::LogicalAnd:
			break;
		case BinaryExprKind::LogicalOr:
			break;
		case BinaryExprKind::Equal:
		{
			result = builder.CreateICmpEQ(lhs, rhs);
		}
		break;
		case BinaryExprKind::NotEqual:
		{
			result = builder.CreateICmpNE(lhs, rhs);
		}
		break;
		case BinaryExprKind::Less:
		{
			result = builder.CreateICmpSLT(lhs, rhs);
		}
		break;
		case BinaryExprKind::Greater:
		{
			result = builder.CreateICmpSGT(lhs, rhs);
		}
		break;
		case BinaryExprKind::LessEqual:
		{
			result = builder.CreateICmpSLE(lhs, rhs);
		}
		break;
		case BinaryExprKind::GreaterEqual:
		{
			result = builder.CreateICmpSGE(lhs, rhs);
		}
		break;
		case BinaryExprKind::Invalid:
		default:
			WAVE_ASSERT(false);
		}
		WAVE_ASSERT(result);
		llvm_value_map[&binary_expr] = result;
	}

	void LLVMVisitor::Visit(TernaryExpr const&, uint32)
	{

	}

	void LLVMVisitor::Visit(IdentifierExpr const&, uint32)
	{
		WAVE_ASSERT(false);
	}

	void LLVMVisitor::Visit(DeclRefExpr const& decl_ref, uint32)
	{
		llvm::Value* value = llvm_value_map[decl_ref.GetDecl()];
		WAVE_ASSERT(value);
		llvm_value_map[&decl_ref] = value;
	}

	void LLVMVisitor::Visit(ConstantInt const& constant_int, uint32)
	{
		llvm::ConstantInt* constant = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), constant_int.GetValue());
		llvm_value_map[&constant_int] = constant;
	}

	void LLVMVisitor::Visit(ConstantString const& string_constant, uint32)
	{
		llvm::Constant* constant = llvm::ConstantDataArray::getString(context, string_constant.GetString());
		llvm_value_map[&string_constant] = constant;
	}

	void LLVMVisitor::Visit(ConstantBool const& bool_constant, uint32)
	{
		llvm::ConstantInt* constant = llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), bool_constant.GetValue());
		llvm_value_map[&bool_constant] = constant;
	}

	void LLVMVisitor::Visit(ImplicitCastExpr const& cast_expr, uint32 depth)
	{
		Expr const* cast_operand_expr = cast_expr.GetOperand();
		cast_operand_expr->Accept(*this);
		llvm::Value* cast_operand_value = llvm_value_map[cast_operand_expr];
		WAVE_ASSERT(cast_operand_value);

		llvm::Type* cast_type = ConvertToLLVMType(cast_expr.GetType());
		llvm::Type* cast_operand_type = ConvertToLLVMType(cast_operand_expr->GetType());
		if (IsInteger(cast_type))
		{
			if (IsBoolean(cast_operand_type))
			{
				llvm::Value* cast_operand = Load(cast_operand_type, cast_operand_value);
				llvm_value_map[&cast_expr] = builder.CreateZExt(cast_operand, llvm::Type::getInt64Ty(context));
			}
		}
		else if (IsBoolean(cast_type))
		{
			if (IsInteger(cast_operand_type))
			{
				llvm::Value* cast_operand = Load(cast_operand_type, cast_operand_value);
				llvm_value_map[&cast_expr] = builder.CreateICmpNE(cast_operand, llvm::ConstantInt::get(context, llvm::APInt(64, 0)));
			}
		}
		WAVE_ASSERT(llvm_value_map[&cast_expr] != nullptr);
	}

	llvm::Type* LLVMVisitor::ConvertToLLVMType(QualifiedType const& type)
	{
		switch (type->GetKind())
		{
		case TypeKind::Void:
			return llvm::Type::getVoidTy(context);
		case TypeKind::Bool:
			return llvm::Type::getInt1Ty(context);
		case TypeKind::Char:
			return llvm::Type::getInt8Ty(context);
		case TypeKind::Int:
			return llvm::Type::getInt64Ty(context);
		case TypeKind::Float:
			return llvm::Type::getDoubleTy(context);
		case TypeKind::Array:
		{
			ArrayType const& array_type = type_cast<ArrayType>(type);
			return llvm::ArrayType::get(ConvertToLLVMType(array_type.GetBaseType()), array_type.GetArraySize());
		}
		case TypeKind::Function:
		{
			FunctionType const& function_type = type_cast<FunctionType>(type);
			std::span<FunctionParameter const> function_params = function_type.GetParameters();

			llvm::Type* return_type = ConvertToLLVMType(function_type.GetReturnType());
			std::vector<llvm::Type*> param_types; param_types.reserve(function_params.size());
			for (auto const& func_param : function_params)
			{
				param_types.push_back(ConvertToLLVMType(func_param.type));
			}
			return llvm::FunctionType::get(return_type, param_types, false);
		}
		case TypeKind::Class:
			WAVE_ASSERT_MSG(false, "Not supported yet");
			break;
		default:
			WAVE_UNREACHABLE();
		}
		return nullptr;
	}

	llvm::Value* LLVMVisitor::Load(QualifiedType const& type, llvm::Value* ptr)
	{
		llvm::Type* llvm_type = ConvertToLLVMType(type);
		return Load(llvm_type, ptr);
	}

	llvm::Value* LLVMVisitor::Load(llvm::Type* llvm_type, llvm::Value* ptr)
	{
		if (!isa<llvm::AllocaInst>(ptr)) return ptr;

		llvm::LoadInst* load_inst = builder.CreateLoad(llvm_type, ptr);
		return load_inst;
	}

	llvm::Value* LLVMVisitor::Store(llvm::Value* value, llvm::Value* ptr)
	{
		if (!isa<llvm::AllocaInst>(value)) return builder.CreateStore(value, ptr);
		llvm::LoadInst* load = builder.CreateLoad(value->getType(), value);
		return builder.CreateStore(load, ptr);
	}

	bool LLVMVisitor::IsBoolean(llvm::Type* type)
	{
		return type->isIntegerTy() && type->getIntegerBitWidth() == 1;
	}

	bool LLVMVisitor::IsInteger(llvm::Type* type)
	{
		return type->isIntegerTy() && type->getIntegerBitWidth() == 64;
	}

	bool LLVMVisitor::IsFloat(llvm::Type* type)
	{
		return type->isDoubleTy();
	}

}


