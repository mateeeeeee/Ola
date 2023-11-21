#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include "Frontend/ASTVisitor.h"
#include "llvm/IR/IRBuilder.h"

namespace llvm
{
	class Context;
	class Module;
	class Value;
	class Type;
	class IntegerType;
	class AllocaInst;
	class SwitchInst;
}

namespace wave
{
	class QualType;

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
		LLVMVisitor(llvm::LLVMContext& context, llvm::Module& module);

		void VisitAST(AST const* ast);
		virtual void Visit(NodeAST const&, uint32) override;
		virtual void Visit(TranslationUnit const&, uint32) override;

		virtual void Visit(Decl const&, uint32) override;
		virtual void Visit(FunctionDecl const&, uint32) override;
		virtual void Visit(MethodDecl const&, uint32) override;
		virtual void Visit(ParamVarDecl const&, uint32) override;
		virtual void Visit(FieldDecl const&, uint32) override;
		virtual void Visit(VarDecl const&, uint32) override;
		virtual void Visit(TagDecl const&, uint32) override;
		virtual void Visit(EnumDecl const&, uint32) override;
		virtual void Visit(EnumMemberDecl const&, uint32) override;
		virtual void Visit(AliasDecl const&, uint32) override;
		virtual void Visit(ClassDecl const&, uint32) override;

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
		virtual void Visit(GotoStmt const&, uint32) override;
		virtual void Visit(LabelStmt const&, uint32) override;

		virtual void Visit(Expr const&, uint32) override;
		virtual void Visit(UnaryExpr const&, uint32) override;
		virtual void Visit(BinaryExpr const&, uint32) override;
		virtual void Visit(TernaryExpr const&, uint32) override;
		virtual void Visit(IdentifierExpr const&, uint32) override;
		virtual void Visit(DeclRefExpr const&, uint32) override;
		virtual void Visit(ConstantInt const&, uint32) override;
		virtual void Visit(ConstantChar const&, uint32) override;
		virtual void Visit(ConstantString const&, uint32) override;
		virtual void Visit(ConstantBool const&, uint32) override;
		virtual void Visit(ConstantFloat const&, uint32) override;
		virtual void Visit(ImplicitCastExpr const&, uint32) override;
		virtual void Visit(CallExpr const&, uint32) override;
		virtual void Visit(InitializerListExpr const&, uint32) override;
		virtual void Visit(ArrayAccessExpr const&, uint32) override;
		virtual void Visit(MemberExpr const&, uint32) override;
		virtual void Visit(MemberCallExpr const&, uint32) override;
		virtual void Visit(ThisExpr const&, uint32) override;

	private:
		llvm::LLVMContext& context;
		llvm::Module& module;
		llvm::IRBuilder<> builder;

		LLVMValueMap llvm_value_map;

		llvm::Type* this_struct_type = nullptr;
		llvm::Value* this_value = nullptr;
		llvm::AllocaInst* return_alloc = nullptr;
		llvm::BasicBlock* exit_block = nullptr;

		std::vector<llvm::SwitchInst*> switch_instructions;
		std::vector<llvm::BasicBlock*> continue_blocks;
		std::vector<llvm::BasicBlock*> break_blocks;
		std::unordered_map<std::string, llvm::BasicBlock*> label_blocks;

		llvm::Type* void_type			= nullptr;
		llvm::Type* float_type			= nullptr;
		llvm::IntegerType* int_type		= nullptr;
		llvm::IntegerType* bool_type	= nullptr;
		llvm::IntegerType* char_type	= nullptr;
	private:

		void ConditionalBranch(llvm::Value*, llvm::BasicBlock*, llvm::BasicBlock*);
		llvm::Type* ConvertToLLVMType(QualType const&);

		[[maybe_unused]] llvm::Value* Load(QualType const&, llvm::Value*);
		[[maybe_unused]] llvm::Value* Load(llvm::Type*, llvm::Value*);
		[[maybe_unused]] llvm::Value* Store(llvm::Value*, llvm::Value*);

		static bool IsBoolean(llvm::Type*);
		static bool IsInteger(llvm::Type*);
		static bool IsFloat(llvm::Type*);
		static bool IsReference(llvm::Type*);
	};
}