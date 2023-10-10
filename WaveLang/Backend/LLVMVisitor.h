#pragma once
#include <memory>
#include <unordered_map>
#include "Frontend/ASTVisitor.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"

namespace llvm
{
	class Module;
	class Value;
	class Type;
}

namespace wave
{
	class QualifiedType;

	class LLVMVisitor : public ASTVisitor
	{
		friend class LLVMIRGenerator;

		struct VoidPointerHash
		{
			size_t operator()(void const* ptr) const
			{
				return reinterpret_cast<size_t>(ptr);
			}
		};
		using LLVMValueMap = std::unordered_map<void const*, llvm::Value*, VoidPointerHash>;

	private:
		explicit LLVMVisitor(AST const* ast);


		virtual void Visit(NodeAST const& node, uint32 depth);
		virtual void Visit(TranslationUnit const& node, uint32 depth);

		virtual void Visit(Decl const& node, uint32 depth);
		virtual void Visit(FunctionDecl const& node, uint32 depth);
		virtual void Visit(VariableDecl const& node, uint32 depth);

		virtual void Visit(Stmt const& node, uint32 depth);
		virtual void Visit(CompoundStmt const& node, uint32 depth);
		virtual void Visit(ExprStmt const& node, uint32 depth);
		virtual void Visit(DeclStmt const& node, uint32 depth);
		virtual void Visit(NullStmt const& node, uint32 depth);
		virtual void Visit(ReturnStmt const& node, uint32 depth);
		virtual void Visit(IfStmt const& node, uint32 depth);

		virtual void Visit(Expr const& node, uint32 depth);
		virtual void Visit(UnaryExpr const& node, uint32 depth);
		virtual void Visit(BinaryExpr const& node, uint32 depth);
		virtual void Visit(TernaryExpr const& node, uint32 depth);
		virtual void Visit(ConstantInt const& node, uint32 depth);
		virtual void Visit(StringLiteral const& node, uint32 depth);
		virtual void Visit(IdentifierExpr const& node, uint32 depth);
		virtual void Visit(DeclRefExpr const& node, uint32 depth);

	private:
		llvm::LLVMContext context;
		llvm::IRBuilder<> builder;
		std::unique_ptr<llvm::Module> module;
		LLVMValueMap llvm_value_map;

	private:
		llvm::Type* ConvertToLLVMType(QualifiedType const& type);
	};
}