#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "IR/IRFwd.h"
#include "Frontend/AST/ASTVisitor.h"

namespace ola
{
	struct AST;
	class IRContext;
	class IRBuilder;
	class IRType;

	class IRVisitor : public ASTVisitor
	{
		friend class IRGen;

		struct VoidPointerHash
		{
			uint64 operator()(void const* ptr) const
			{
				return reinterpret_cast<uint64>(ptr);
			}
		};
		using ValueMap = std::unordered_map<void const*, Value*, VoidPointerHash>;
		using VTableMap = std::unordered_map<void const*, GlobalVariable*, VoidPointerHash>;
		using EmptyBlockSuccessorMap = std::unordered_map<BasicBlock*, BasicBlock*, VoidPointerHash>;

	public:

		IRVisitor(IRContext& context, IRModule& module);
		~IRVisitor();
		void VisitAST(AST const* ast);

		virtual void Visit(ASTNode const&, uint32) override;
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
		virtual void Visit(IntLiteral const&, uint32) override;
		virtual void Visit(CharLiteral const&, uint32) override;
		virtual void Visit(StringLiteral const&, uint32) override;
		virtual void Visit(BoolLiteral const&, uint32) override;
		virtual void Visit(FloatLiteral const&, uint32) override;
		virtual void Visit(ImplicitCastExpr const&, uint32) override;
		virtual void Visit(CallExpr const&, uint32) override;
		virtual void Visit(InitializerListExpr const&, uint32) override;
		virtual void Visit(ArrayAccessExpr const&, uint32) override;
		virtual void Visit(MemberExpr const&, uint32) override;
		virtual void Visit(MethodCallExpr const&, uint32) override;
		virtual void Visit(ThisExpr const&, uint32) override;
		virtual void Visit(SuperExpr const&, uint32) override;

	private:
		IRContext& context;
		IRModule& module;
		std::unique_ptr<IRBuilder> builder;

		ValueMap value_map;
		VTableMap vtable_map;

		IRType* this_struct_type = nullptr;
		Value* this_value = nullptr;
		Value* return_value = nullptr;
		BasicBlock* exit_block = nullptr;

		std::vector<SwitchInst*> switch_instructions;
		std::vector<BasicBlock*> continue_blocks;
		std::vector<BasicBlock*> break_blocks;
		std::vector<BasicBlock*> end_blocks;
		std::unordered_map<std::string, BasicBlock*> label_blocks;
		EmptyBlockSuccessorMap empty_block_successors;

		IRType* void_type = nullptr;
		IRType* float_type = nullptr;
		IRIntType* int_type = nullptr;
		IRIntType* bool_type = nullptr;
		IRIntType* char_type = nullptr;
	};
}