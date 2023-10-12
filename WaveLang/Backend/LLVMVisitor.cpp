#include "LLVMVisitor.h"
#include "Frontend/AST.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"

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

	void LLVMVisitor::Visit(NodeAST const& node, uint32 depth)
	{
		WAVE_ASSERT(false);
	}

	void LLVMVisitor::Visit(TranslationUnit const& translation_unit, uint32 depth)
	{
		for (auto&& decl : translation_unit.GetDecls()) decl->Accept(*this);
	}

	void LLVMVisitor::Visit(Decl const& decl, uint32 depth)
	{
		WAVE_ASSERT(false);
	}

	void LLVMVisitor::Visit(FunctionDecl const& function_decl, uint32 depth)
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
			function_decl.GetBodyStmt()->Accept(*this);
		}
		llvm_value_map[&function_decl] = llvm_function;
	}

	void LLVMVisitor::Visit(VariableDecl const& var_decl, uint32 depth)
	{
		llvm::Type* llvm_type = ConvertToLLVMType(var_decl.GetType());
		llvm::AllocaInst* alloca_inst = builder.CreateAlloca(llvm_type, nullptr, var_decl.GetName());

		if (var_decl.GetInitExpr()) 
		{
			var_decl.GetInitExpr()->Accept(*this);
			llvm::Value* init_value = llvm_value_map[var_decl.GetInitExpr()];
			builder.CreateStore(init_value, alloca_inst);
		}
		llvm_value_map[&var_decl] = alloca_inst;
	}

	void LLVMVisitor::Visit(Stmt const& stmt, uint32 depth)
	{
		WAVE_ASSERT(false);
	}

	void LLVMVisitor::Visit(CompoundStmt const& compound_stmt, uint32 depth)
	{
		for (auto const& statement : compound_stmt.GetStmts()) statement->Accept(*this);
	}

	void LLVMVisitor::Visit(ExprStmt const& expr_stmt, uint32 depth)
	{
		if (expr_stmt.GetExpr()) expr_stmt.GetExpr()->Accept(*this);
	}

	void LLVMVisitor::Visit(DeclStmt const& decl_stmt, uint32 depth)
	{
		if (decl_stmt.GetDecl()) decl_stmt.GetDecl()->Accept(*this);
	}

	void LLVMVisitor::Visit(NullStmt const& null_stmt, uint32 depth) {}

	void LLVMVisitor::Visit(ReturnStmt const& return_stmt, uint32 depth)
	{
		if (return_stmt.GetExprStmt()) 
		{
			return_stmt.GetExprStmt()->Accept(*this);
			llvm::Value* return_value = llvm_value_map[return_stmt.GetExprStmt()->GetExpr()];
			builder.CreateRet(return_value);
		}
		else 
		{
			builder.CreateRetVoid();
		}
	}

	void LLVMVisitor::Visit(IfStmt const& if_stmt, uint32 depth)
	{
		if_stmt.GetConditionExpr()->Accept(*this);
		llvm::Value* condition_value = llvm_value_map[if_stmt.GetConditionExpr()];
		WAVE_ASSERT(condition_value);

		llvm::Function* function = builder.GetInsertBlock()->getParent();
		llvm::BasicBlock* if_block = llvm::BasicBlock::Create(context, "if", function);
		llvm::BasicBlock* else_block = llvm::BasicBlock::Create(context, "else");
		llvm::BasicBlock* merge_block = llvm::BasicBlock::Create(context, "merge");

		builder.CreateCondBr(condition_value, if_block, else_block);
	}

	void LLVMVisitor::Visit(Expr const& node, uint32 depth)
	{
		WAVE_ASSERT(false);
	}

	void LLVMVisitor::Visit(UnaryExpr const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(BinaryExpr const& binary_expr, uint32 depth)
	{
		Expr const* lhs = binary_expr.GetLHS();
		lhs->Accept(*this);
		llvm::Value* lhs_value = llvm_value_map[lhs];
		Expr const* rhs = binary_expr.GetRHS();
		rhs->Accept(*this);
		llvm::Value* rhs_value = llvm_value_map[rhs];
		WAVE_ASSERT(lhs_value && rhs_value);

		llvm::Value* result = nullptr;
		switch (binary_expr.GetBinaryKind())
		{
		case BinaryExprKind::Assign:
		{
			if (DeclRefExpr const* decl_ref = ast_cast<DeclRefExpr>(lhs))
			{
				Decl const* decl = decl_ref->GetDecl();
				llvm::Value* decl_value = llvm_value_map[decl];
				result = builder.CreateStore(rhs_value, decl_value);
			}
			else
			{
				WAVE_ASSERT(false);
			}
		}
		break;
		case BinaryExprKind::Add:
			result = builder.CreateAdd(lhs_value, rhs_value, "addtmp");
			break;
		case BinaryExprKind::Subtract:
			result = builder.CreateSub(lhs_value, rhs_value, "subtmp");
			break;
		case BinaryExprKind::Multiply:
			result = builder.CreateMul(lhs_value, rhs_value, "multmp");
			break;
		case BinaryExprKind::Divide:
			result = builder.CreateSDiv(lhs_value, rhs_value, "sdivtmp");
			break;
		}
		WAVE_ASSERT(result);
		llvm_value_map[&binary_expr] = result;
	}

	void LLVMVisitor::Visit(TernaryExpr const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(ConstantInt const& constant_int, uint32 depth)
	{
		llvm::ConstantInt* constant = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), constant_int.GetValue());
		llvm_value_map[&constant_int] = constant;
	}

	void LLVMVisitor::Visit(ConstantString const& string_constant, uint32 depth)
	{
		llvm::Constant* constant = llvm::ConstantDataArray::getString(context, string_constant.GetString());
		llvm_value_map[&string_constant] = constant;
	}

	void LLVMVisitor::Visit(IdentifierExpr const& node, uint32 depth)
	{
		WAVE_ASSERT(false);
	}

	void LLVMVisitor::Visit(DeclRefExpr const& decl_ref, uint32 depth)
	{
		llvm::Value* value = llvm_value_map[decl_ref.GetDecl()];
		WAVE_ASSERT(value);
		llvm::LoadInst* load = builder.CreateLoad(ConvertToLLVMType(decl_ref.GetType()), value, decl_ref.GetDecl()->GetName());
		llvm_value_map[&decl_ref] = load;
	}

	void LLVMVisitor::Visit(ConstantBool const& bool_constant, uint32 depth)
	{
		llvm::ConstantInt* constant = llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), bool_constant.GetValue());
		llvm_value_map[&bool_constant] = constant;
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
			ArrayType const& array_type = type->As<ArrayType>();
			return llvm::ArrayType::get(ConvertToLLVMType(array_type.GetBaseType()), array_type.GetArraySize());
		}
		case TypeKind::Function:
		{
			FunctionType const& function_type = type->As<FunctionType>();
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
		default:
			WAVE_UNREACHABLE();
		}
		return nullptr;
	}

}


