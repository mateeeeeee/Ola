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
		for (auto&& decl : translation_unit.GetDeclarations()) decl->Accept(*this);
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

		if (!function_decl.IsExtern())
		{
			function_decl.GetBody()->Accept(*this);
		}
		llvm_value_map[&function_decl] = llvm_function;
	}

	void LLVMVisitor::Visit(VariableDecl const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(Stmt const& node, uint32 depth)
	{
		WAVE_ASSERT(false);
	}

	void LLVMVisitor::Visit(CompoundStmt const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(ExprStmt const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(DeclStmt const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(NullStmt const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(ReturnStmt const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(IfStmt const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(Expr const& node, uint32 depth)
	{
		WAVE_ASSERT(false);
	}

	void LLVMVisitor::Visit(UnaryExpr const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(BinaryExpr const& node, uint32 depth)
	{
		
	}

	void LLVMVisitor::Visit(TernaryExpr const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(IntLiteral const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(StringLiteral const& node, uint32 depth)
	{

	}

	void LLVMVisitor::Visit(IdentifierExpr const& node, uint32 depth)
	{

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


