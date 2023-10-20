#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include "Frontend/ASTVisitor.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"

namespace llvm
{
	class Module;
	class Value;
	class Type;
	class AllocaInst;
	class SwitchInst;
}

namespace wave
{
	class QualifiedType;

	class LLVMVisitor : public ASTVisitor
	{
		friend class LLVMIRGenerator;

		struct VoidPointerHash
		{
			uint64 operator()(void const* ptr) const
			{
				return reinterpret_cast<uint64>(ptr);
			}
		};
		using LLVMValueMap = std::unordered_map<void const*, llvm::Value*, VoidPointerHash>;

	private:
		explicit LLVMVisitor(AST const* ast);
		virtual void Visit(NodeAST const&, uint32) override;
		virtual void Visit(TranslationUnit const&, uint32) override;

		virtual void Visit(Decl const&, uint32) override;
		virtual void Visit(FunctionDecl const&, uint32) override;
		virtual void Visit(VariableDecl const&, uint32) override;

		virtual void Visit(Stmt const&, uint32) override;
		virtual void Visit(CompoundStmt const&, uint32) override;
		virtual void Visit(DeclStmt const&, uint32) override;
		virtual void Visit(ExprStmt const&, uint32) override;
		virtual void Visit(NullStmt const&, uint32) override;
		virtual void Visit(ReturnStmt const&, uint32) override;
		virtual void Visit(IfStmt const&, uint32) override;
		virtual void Visit(BreakStmt const&, uint32) override;
		virtual void Visit(ContinueStmt const&, uint32) override;
		virtual void Visit(ForStmt const&, uint32) override;
		virtual void Visit(WhileStmt const&, uint32) override;
		virtual void Visit(DoWhileStmt const&, uint32) override;
		virtual void Visit(CaseStmt const&, uint32) override;
		virtual void Visit(SwitchStmt const&, uint32) override;

		virtual void Visit(Expr const&, uint32) override;
		virtual void Visit(UnaryExpr const&, uint32) override;
		virtual void Visit(BinaryExpr const&, uint32) override;
		virtual void Visit(TernaryExpr const&, uint32) override;
		virtual void Visit(IdentifierExpr const&, uint32) override;
		virtual void Visit(DeclRefExpr const&, uint32) override;
		virtual void Visit(ConstantInt const&, uint32) override;
		virtual void Visit(ConstantString const&, uint32) override;
		virtual void Visit(ConstantBool const&, uint32) override;
		virtual void Visit(ImplicitCastExpr const&, uint32) override;
		virtual void Visit(FunctionCallExpr const&, uint32) override {}

	private:
		llvm::LLVMContext context;
		llvm::IRBuilder<> builder;

		std::unique_ptr<llvm::Module> module;
		LLVMValueMap llvm_value_map;

		llvm::AllocaInst* return_alloc;
		llvm::BasicBlock* exit_block;

		std::vector<llvm::BasicBlock*> continue_blocks;
		std::vector<llvm::BasicBlock*> break_blocks;
		std::vector<llvm::SwitchInst*> switch_instructions;
	private:

		void ConditionalBranch(llvm::Value*, llvm::BasicBlock*, llvm::BasicBlock*);
		llvm::Type* ConvertToLLVMType(QualifiedType const&);

		[[maybe_unused]] llvm::Value* Load(QualifiedType const&, llvm::Value*);
		[[maybe_unused]] llvm::Value* Load(llvm::Type*, llvm::Value*);
		[[maybe_unused]] llvm::Value* Store(llvm::Value*, llvm::Value*);

		static bool IsBoolean(llvm::Type*);
		static bool IsInteger(llvm::Type*);
		static bool IsFloat(llvm::Type*);
	};
}