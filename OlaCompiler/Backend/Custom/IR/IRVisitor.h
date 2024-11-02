#pragma once
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "Frontend/AST/ASTVisitor.h"

namespace ola
{
	struct AST;
	class IRContext;
	class IRModule;
	class IRBuilder;
	class IRType;
	class IRIntType;
	class IRFloatType;
	class IRPtrType;
	class IRFuncType;
	class Function;
	class Type;
	class FuncType;

	class Value;
	class BasicBlock;
	class SwitchInst;
	class GlobalVariable;

	class IRVisitor : public ASTVisitor
	{
		friend class IRGenContext;

		template<typename V>
		using VoidPointerMap = std::unordered_map<void const*, V>;

		using ValueMap = VoidPointerMap<Value*>;
		using VTableMap = VoidPointerMap<GlobalVariable*>;
		using EmptyBlockSuccessorMap = std::unordered_map<BasicBlock*, BasicBlock*>;

	public:

		IRVisitor(IRContext& context, IRModule& module);
		~IRVisitor();
		void VisitAST(AST const* ast);

		virtual void Visit(ASTNode const&, Uint32) override;
		virtual void Visit(TranslationUnit const&, Uint32) override;

		virtual void Visit(Decl const&, Uint32) override;
		virtual void Visit(FunctionDecl const&, Uint32) override;
		virtual void Visit(MethodDecl const&, Uint32) override;
		virtual void Visit(ParamVarDecl const&, Uint32) override;
		virtual void Visit(FieldDecl const&, Uint32) override;
		virtual void Visit(VarDecl const&, Uint32) override;
		virtual void Visit(TagDecl const&, Uint32) override;
		virtual void Visit(EnumDecl const&, Uint32) override;
		virtual void Visit(EnumMemberDecl const&, Uint32) override;
		virtual void Visit(AliasDecl const&, Uint32) override;
		virtual void Visit(ClassDecl const&, Uint32) override;

		virtual void Visit(Stmt const&, Uint32) override;
		virtual void Visit(CompoundStmt const&, Uint32) override;
		virtual void Visit(DeclStmt const&, Uint32) override;
		virtual void Visit(ExprStmt const&, Uint32) override;
		virtual void Visit(NullStmt const&, Uint32) override;
		virtual void Visit(ReturnStmt const&, Uint32) override;
		virtual void Visit(IfStmt const&, Uint32) override;
		virtual void Visit(BreakStmt const&, Uint32) override;
		virtual void Visit(ContinueStmt const&, Uint32) override;
		virtual void Visit(ForStmt const&, Uint32) override;
		virtual void Visit(WhileStmt const&, Uint32) override;
		virtual void Visit(DoWhileStmt const&, Uint32) override;
		virtual void Visit(CaseStmt const&, Uint32) override;
		virtual void Visit(SwitchStmt const&, Uint32) override;
		virtual void Visit(GotoStmt const&, Uint32) override;
		virtual void Visit(LabelStmt const&, Uint32) override;

		virtual void Visit(Expr const&, Uint32) override;
		virtual void Visit(UnaryExpr const&, Uint32) override;
		virtual void Visit(BinaryExpr const&, Uint32) override;
		virtual void Visit(TernaryExpr const&, Uint32) override;
		virtual void Visit(IdentifierExpr const&, Uint32) override;
		virtual void Visit(DeclRefExpr const&, Uint32) override;
		virtual void Visit(IntLiteral const&, Uint32) override;
		virtual void Visit(CharLiteral const&, Uint32) override;
		virtual void Visit(StringLiteral const&, Uint32) override;
		virtual void Visit(BoolLiteral const&, Uint32) override;
		virtual void Visit(FloatLiteral const&, Uint32) override;
		virtual void Visit(ImplicitCastExpr const&, Uint32) override;
		virtual void Visit(CallExpr const&, Uint32) override;
		virtual void Visit(InitializerListExpr const&, Uint32) override;
		virtual void Visit(ArrayAccessExpr const&, Uint32) override;
		virtual void Visit(MemberExpr const&, Uint32) override;
		virtual void Visit(MethodCallExpr const&, Uint32) override;
		virtual void Visit(ThisExpr const&, Uint32) override;
		virtual void Visit(SuperExpr const&, Uint32) override;

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
		IRFloatType* float_type = nullptr;
		IRIntType* int_type = nullptr;
		IRIntType* bool_type = nullptr;
		IRIntType* char_type = nullptr;

	private:
		void VisitFunctionDeclCommon(FunctionDecl const& decl, Function* func);
		void ConditionalBranch(Value*, BasicBlock*, BasicBlock*);

		IRType* ConvertToIRType(Type const*);
		IRType* ConvertClassDecl(ClassDecl const*);
		IRFuncType* ConvertMethodType(FuncType const*, IRType*);
		IRType* GetStructType(Type const*);
		IRPtrType* GetPointerType(IRType*);

		OLA_MAYBE_UNUSED Value* Load(Type const*, Value*);
		OLA_MAYBE_UNUSED Value* Load(IRType*, Value*);
		OLA_MAYBE_UNUSED Value* Store(Value*, Value*);
	};
}