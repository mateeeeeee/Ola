#pragma once
#include <vector>
#include <memory>
#include <string_view>
#include "SourceLocation.h"
#include "Type.h"

namespace wave
{
	class Context;
	class Value;

	class NodeAST;
	class TranslationUnitAST;

	class DeclAST;
	class FunctionDeclAST;
	class VariableDeclAST;

	class StmtAST;
	class CompoundStmtAST;
	class ExprStmtAST;
	class DeclStmtAST;
	class NullStmtAST;
	class IfStmtAST;
	class ReturnStmtAST;

	class ExprAST;

	class INodeVisitorAST
	{
	public:
		virtual ~INodeVisitorAST() = default;
		virtual void Visit(NodeAST const& node, uint32 depth) {}
		virtual void Visit(TranslationUnitAST const& node, uint32 depth) {}

		virtual void Visit(DeclAST const& node, uint32 depth) {}
		virtual void Visit(FunctionDeclAST const& node, uint32 depth) {}
		virtual void Visit(VariableDeclAST const& node, uint32 depth) {}

		virtual void Visit(StmtAST const& node, uint32 depth) {}
	};

	class NodeAST
	{
	public:
		virtual ~NodeAST() = default;
		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const {};
		virtual Value* Codegen(Context& context) const { return nullptr; }

	protected:
		NodeAST() = default;
	};

	class TranslationUnitAST : public NodeAST
	{
	public:
		TranslationUnitAST() = default;
		
		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const override {}

		void AddDeclaration(std::unique_ptr<DeclAST>&& declaration)
		{
			declarations.push_back(std::move(declaration));
		}

	private:
		std::vector<std::unique_ptr<DeclAST>> declarations;
	};

	enum class DeclKind : bool
	{
		Variable,
		Function
	};
	class DeclAST
	{
	public:
		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const {}
		virtual Value* Codegen(Context& context) const { return nullptr; }

		DeclKind GetDeclKind() const { return decl_kind; }
		SourceLocation GetLocation() const { return source_loc; }
		std::string_view GetName() const { return name; }

		void SetType(QualifiedType const& _type) { type = _type; }
		QualifiedType const& GetType() const { return type; }

	private:
		DeclKind decl_kind;
		std::string name;
		SourceLocation source_loc;
		QualifiedType type;

	protected:
		DeclAST(DeclKind decl_kind, std::string_view name, SourceLocation const& loc)
			: decl_kind(decl_kind), name(name), source_loc(loc) {}
	};
	class VariableDeclAST : public DeclAST
	{
	public:
		VariableDeclAST(std::string_view name, SourceLocation const& loc)
			: DeclAST(DeclKind::Variable, name, loc) {}

		void SetInitExpression(std::unique_ptr<ExprAST>&& expr)
		{
			init_expr = std::move(expr);
		}

	private:
		std::unique_ptr<ExprAST> init_expr;
	};
	class FunctionDeclAST : public DeclAST
	{
	public:
		FunctionDeclAST(std::string_view name, SourceLocation const& loc)
			: DeclAST(DeclKind::Function, name, loc) {}

		void AddParamDeclaration(std::unique_ptr<VariableDeclAST>&& param)
		{
			param_declarations.push_back(std::move(param));
		}
		void SetDefinition(std::unique_ptr<CompoundStmtAST>&& _definition)
		{
			definition = std::move(_definition);
		}

		bool IsExtern() const
		{
			return definition == nullptr;
		}

	private:
		std::vector<std::unique_ptr<VariableDeclAST>> param_declarations;
		std::unique_ptr<CompoundStmtAST> definition;
	};

	enum class StmtKind : uint8
	{
		Compound,
		Expr,
		Decl,
		Null,
		If,
		While,
		DoWhile,
		Switch,
		Case,
		For,
		Return,
		Goto,
		Label,
		Break,
		Continue
	};
	class StmtAST : public NodeAST
	{
	public:
		StmtKind GetStmtKind() const { return kind; }

	protected:
		StmtKind kind;

	protected:
		explicit StmtAST(StmtKind kind) : kind(kind) {}
	};
	class CompoundStmtAST : public StmtAST
	{
	public:
		CompoundStmtAST() : StmtAST(StmtKind::Compound) {}

		void AddStatement(std::unique_ptr<StmtAST>&& stmt)
		{
			statements.push_back(std::move(stmt));
		}

	private:
		std::vector<std::unique_ptr<StmtAST>> statements;
	};
	class ExprStmtAST : public StmtAST
	{
	public:
		ExprStmtAST(std::unique_ptr<ExprAST>&& expr) : StmtAST(expr ? StmtKind::Expr : StmtKind::Null), expr(std::move(expr)) {}
		ExprAST* GetExpr() const { return expr.get(); }

	private:
		std::unique_ptr<ExprAST> expr;
	};
	class DeclStmtAST : public StmtAST
	{
	public:
		DeclStmtAST(std::unique_ptr<DeclAST>&& decl) : StmtAST(StmtKind::Decl), declaration(std::move(decl)) {}
		DeclAST* GetDeclarations() const { return declaration.get(); }

	private:
		std::unique_ptr<DeclAST> declaration;
	};
	class NullStmtAST final : public ExprStmtAST
	{
	public:
		NullStmtAST() : ExprStmtAST(nullptr) {}
	};
	class IfStmtAST final : public StmtAST
	{
	public:
		IfStmtAST() : StmtAST(StmtKind::If) {}

		void SetCondition(std::unique_ptr<ExprAST>&& _condition)
		{
			condition = std::move(_condition);
		}
		void SetThenStatement(std::unique_ptr<StmtAST>&& _then_stmt)
		{
			then_stmt = std::move(_then_stmt);
		}
		void SetElseStatement(std::unique_ptr<StmtAST>&& _else_stmt)
		{
			else_stmt = std::move(_else_stmt);
		}

	private:
		std::unique_ptr<ExprAST> condition;
		std::unique_ptr<StmtAST> then_stmt;
		std::unique_ptr<StmtAST> else_stmt;
	};
	class ReturnStmtAST final : public StmtAST
	{
	public:
		explicit ReturnStmtAST(std::unique_ptr<ExprStmtAST>&& ret_expr)
			: StmtAST(StmtKind::Return), ret_expr(std::move(ret_expr)) {}

	private:
		std::unique_ptr <ExprStmtAST> ret_expr;
	};

	enum class ExprKind : uint8
	{
		Unary,
		Binary,
		Ternary,
		FunctionCall,
		IntLiteral,
		FloatLiteral,
		StringLiteral,
		DeclRef,
		Cast
	};
	enum class UnaryExprKind : uint8
	{
		PreIncrement, PreDecrement,
		PostIncrement, PostDecrement,
		Plus, Minus, BitNot,
		LogicalNot,
		Dereference, AddressOf
	};
	enum class BinaryExprKind : uint8
	{
		Add, Subtract, Multiply, Divide, Modulo,
		ShiftLeft, ShiftRight, BitAnd, BitOr, BitXor,
		Assign,
		Comma,
		LogicalAnd, LogicalOr,
		Equal, NotEqual,
		Less, Greater,
		LessEqual, GreaterEqual,
		Invalid
	};
	class ExprAST : public NodeAST
	{
	public:
		virtual bool IsConstexpr() const { return false; }
		virtual int64 EvaluateConstexpr() const { return 0; }

		SourceLocation const& GetLocation() const { return loc; }
		Type const& GetType() const { return *type; }
		ExprKind GetExprKind() const { return kind; }

	protected:
		ExprKind kind;
		SourceLocation loc;
		std::unique_ptr<Type> type;

	protected:
		ExprAST(ExprKind kind, SourceLocation const& loc, std::unique_ptr<Type>&& type) : kind(kind), loc(loc), type(std::move(type)) {}
	};

	struct AST
	{
		AST() { translation_unit = std::make_unique<TranslationUnitAST>(); }
		std::unique_ptr<TranslationUnitAST> translation_unit;
	};
}