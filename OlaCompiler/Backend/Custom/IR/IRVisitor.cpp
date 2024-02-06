#include "IRVisitor.h"
#include "IRBuilder.h"
#include "IRModule.h"
#include "IRContext.h"
#include "IRType.h"
#include "IR.h"
#include "Frontend/AST/AST.h"
#include "Frontend/AST/Decl.h"
#include "Frontend/AST/Stmt.h"
#include "Frontend/AST/Expr.h"

namespace ola
{

	IRVisitor::IRVisitor(IRContext& context, IRModule& module) : context(context), module(module)
	{
		builder = std::make_unique<IRBuilder>(context);

		void_type = IRVoidType::Get(context);
		bool_type = IRIntType::Get(context, 1);
		char_type = IRIntType::Get(context, 1);
		int_type = IRIntType::Get(context, 8);
		float_type = IRFloatType::Get(context);
	}

	IRVisitor::~IRVisitor()
	{
	}

	void IRVisitor::VisitAST(AST const* ast)
	{
		ast->translation_unit->Accept(*this);
	}

	void IRVisitor::Visit(ASTNode const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(TranslationUnit const& translation_unit, uint32)
	{
		for (auto&& decl : translation_unit.GetDecls()) decl->Accept(*this);
	}

	void IRVisitor::Visit(Decl const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(FunctionDecl const& function_decl, uint32)
	{
		FuncType const* type = function_decl.GetFuncType();
		IRFuncType* function_type = cast<IRFuncType>(ConvertToIRType(type));
		Linkage linkage = function_decl.IsPublic() || function_decl.IsExtern() ? Linkage::External : Linkage::Internal;
		Function* llvm_function = Create<Function>(function_type, module, linkage, function_decl.GetMangledName());

		Argument* param_arg = llvm_function->GetArg(0);
		if (isa<ClassType>(type->GetReturnType()))
		{
			Value* sret_value = param_arg;
			++param_arg;
			return_value = sret_value;
		}
		for (auto& param : function_decl.GetParamDecls())
		{
			Value* llvm_param = param_arg;
			llvm_param->SetName(param->GetName());
			value_map[param.get()] = llvm_param;
			++param_arg;
		}
		if (!function_decl.HasDefinition()) return;

	}

	void IRVisitor::Visit(MethodDecl const&, uint32)
	{

	}

	void IRVisitor::Visit(ParamVarDecl const&, uint32)
	{

	}

	void IRVisitor::Visit(FieldDecl const&, uint32)
	{

	}

	void IRVisitor::Visit(VarDecl const&, uint32)
	{

	}

	void IRVisitor::Visit(TagDecl const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(EnumDecl const& enum_decl, uint32)
	{
		for (auto const& enum_member : enum_decl.GetEnumMembers()) enum_member->Accept(*this);
	}

	void IRVisitor::Visit(EnumMemberDecl const&, uint32)
	{

	}

	void IRVisitor::Visit(AliasDecl const&, uint32)
	{

	}

	void IRVisitor::Visit(ClassDecl const&, uint32)
	{

	}

	void IRVisitor::Visit(Stmt const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(CompoundStmt const& compound_stmt, uint32)
	{
		for (auto const& stmt : compound_stmt.GetStmts()) stmt->Accept(*this);
	}

	void IRVisitor::Visit(DeclStmt const& decl_stmt, uint32)
	{
		for (auto const& decl : decl_stmt.GetDecls())  decl->Accept(*this);
	}

	void IRVisitor::Visit(ExprStmt const& expr_stmt, uint32)
	{
		if (expr_stmt.GetExpr()) expr_stmt.GetExpr()->Accept(*this);
	}

	void IRVisitor::Visit(NullStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(ReturnStmt const& return_stmt, uint32)
	{
		BasicBlock* current_block = builder->GetInsertBlock();
		Function* current_function = current_block->GetParent();
		if (Expr const* return_expr = return_stmt.GetExprStmt()->GetExpr())
		{
			return_expr->Accept(*this);
			Value* return_expr_value = value_map[return_expr];
			OLA_ASSERT(return_expr_value);
			if (current_function->GetReturnType()->IsPointerType())
			{
				builder->CreateStore(return_expr_value, return_value);
			}
			else
			{
				Value* load = builder->CreateLoad(return_expr_value->GetType(), return_expr_value);
				builder->CreateStore(load, return_value);
			}
		}
		builder->CreateBranch(exit_block);
		BasicBlock* return_block = Create<BasicBlock>(context, "return", current_function, current_block->GetNext());
		builder->SetInsertPoint(return_block);
	}

	void IRVisitor::Visit(IfStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(BreakStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(ContinueStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(ForStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(WhileStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(DoWhileStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(CaseStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(SwitchStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(GotoStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(LabelStmt const&, uint32)
	{

	}

	void IRVisitor::Visit(Expr const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(UnaryExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(BinaryExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(TernaryExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(IdentifierExpr const&, uint32)
	{
		OLA_ASSERT(false);
	}

	void IRVisitor::Visit(DeclRefExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(IntLiteral const& int_constant, uint32)
	{
		ConstantInt* constant = context.GetConstantInt64(int_constant.GetValue()); 
		value_map[&int_constant] = constant;
	}

	void IRVisitor::Visit(CharLiteral const& char_constant, uint32)
	{
		ConstantInt* constant = context.GetConstantInt8(char_constant.GetChar());
		value_map[&char_constant] = constant;
	}

	void IRVisitor::Visit(StringLiteral const&, uint32)
	{

	}

	void IRVisitor::Visit(BoolLiteral const&, uint32)
	{

	}

	void IRVisitor::Visit(FloatLiteral const&, uint32)
	{

	}

	void IRVisitor::Visit(ImplicitCastExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(CallExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(InitializerListExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(ArrayAccessExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(MemberExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(MethodCallExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(ThisExpr const&, uint32)
	{

	}

	void IRVisitor::Visit(SuperExpr const&, uint32)
	{

	}

	void IRVisitor::VisitFunctionDeclCommon(FunctionDecl const& func_decl, Function* func)
	{
		if (func_decl.IsInline()) func->SetFuncAttribute(Function::Attribute_ForceInline);
		else if (func_decl.IsNoInline()) func->SetFuncAttribute(Function::Attribute_NoInline);

		BasicBlock* entry_block = Create<BasicBlock>(context, "entry", func);
		builder->SetInsertPoint(entry_block);

		for (auto& param : func_decl.GetParamDecls())
		{
			Value* arg_value = value_map[param.get()];
			AllocaInst* arg_alloc = builder->CreateAlloca(arg_value->GetType(), nullptr);
			builder->CreateStore(arg_value, arg_alloc);
			if (isa<RefType>(param->GetType()))
			{
				Value* arg_ref = builder->CreateLoad(arg_value->GetType(), arg_alloc);
				value_map[param.get()] = arg_ref;
			}
			else
			{
				value_map[param.get()] = arg_alloc;
			}
		}

		if (!func->GetReturnType()->IsVoidType()) return_value = builder->CreateAlloca(func->GetReturnType(), nullptr);
		exit_block = Create<BasicBlock>(context, "exit", func);

		auto const& labels = func_decl.GetLabels();
		for (LabelStmt const* label : labels)
		{
			std::string block_name = "label."; block_name += label->GetName();
			BasicBlock* label_block = Create<BasicBlock>(context, block_name, func, exit_block);
			label_blocks[block_name] = label_block;
		}

		func_decl.GetBodyStmt()->Accept(*this);

		builder->SetInsertPoint(exit_block);
		if (!func->GetReturnType()->IsVoidType())
		{
			//builder->CreateRet(Load(func->GetReturnType(), return_value));
		}
		else builder->CreateRetVoid();

		std::vector<BasicBlock*> unreachable_blocks{};
		for (auto&& block : *func) if (block.HasNPredecessors(0) && &block != entry_block) unreachable_blocks.push_back(&block);

		std::vector<BasicBlock*> empty_blocks{};
		for (auto&& block : *func) if (block.Empty()) empty_blocks.push_back(&block);

		for (BasicBlock* empty_block : empty_blocks)
		{
			builder->SetInsertPoint(empty_block);
			builder->CreateAlloca(IRIntType::Get(context, 1), nullptr);
			if (empty_block_successors.contains(empty_block))
				builder->CreateBranch(empty_block_successors[empty_block]);
			else builder->CreateBranch(exit_block);
		}

		for (auto&& block : *func)
		{
			if (block.GetTerminator() == nullptr)
			{
				builder->SetInsertPoint(&block);
				builder->CreateBranch(exit_block);
			}
		}

		label_blocks.clear();

		exit_block = nullptr;
		return_value = nullptr;

		value_map[&func_decl] = func;
	}

	IRType* IRVisitor::ConvertToIRType(Type const* type)
	{
		switch (type->GetKind())
		{
		case TypeKind::Void:
			return void_type;
		case TypeKind::Bool:
			return bool_type;
		case TypeKind::Char:
			return char_type;
		case TypeKind::Int:
			return int_type;
		case TypeKind::Float:
			return float_type;
		case TypeKind::Array:
		{
			ArrayType const* array_type = cast<ArrayType>(type);
			if (array_type->GetArraySize() > 0) return IRArrayType::Get(ConvertToIRType(array_type->GetBaseType()), array_type->GetArraySize());
			else return GetPointerType(ConvertToIRType(array_type->GetBaseType()));
		}
		case TypeKind::Function:
		{
			FuncType const* function_type = cast<FuncType>(type);
			std::span<QualType const> function_params = function_type->GetParams();

			IRType* return_type = ConvertToIRType(function_type->GetReturnType());
			bool return_type_struct = return_type->IsStructType();

			std::vector<IRType*> param_types; param_types.reserve(function_params.size());
			if (return_type_struct) param_types.push_back(GetPointerType(return_type));

			for (auto const& func_param_type : function_params)
			{
				IRType* param_type = ConvertToIRType(func_param_type);
				param_types.push_back(param_type);
			}
			return IRFuncType::Get(return_type_struct ? void_type : return_type, param_types);
		}
		case TypeKind::Class:
		{
			ClassType const* class_type = cast<ClassType>(type);
			return ConvertClassDecl(class_type->GetClassDecl());
		}
		case TypeKind::Ref:
		{
			RefType const* ref_type = cast<RefType>(type);
			return GetPointerType(ConvertToIRType(ref_type->GetReferredType()));
		}
		default:
			OLA_UNREACHABLE();
		}
		return nullptr;
	}

	IRType* IRVisitor::ConvertClassDecl(ClassDecl const*)
	{
		return nullptr;
	}

	IRFuncType* IRVisitor::ConvertMethodType(FuncType const*, IRType*)
	{
		return nullptr;
	}

	IRType* IRVisitor::GetStructType(Type const*)
	{
		return nullptr;
	}

	IRPtrType* IRVisitor::GetPointerType(IRType* type)
	{
		return IRPtrType::Get(context, type);
	}

}

