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
		virtual Value* Codegen(Context& context) const {}

	protected:
		NodeAST() = default;
	};

	class TranslationUnitAST : public NodeAST
	{
	public:
		TranslationUnitAST() = default;
		
		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const override {}
		virtual Value* Codegen(Context& context) const {}

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
		virtual Value* Codegen(Context& context) const {}

		DeclKind GetDeclKind() const { return decl_kind; }
		SourceLocation GetLocation() const { return source_loc; }
		std::string_view GetName() const { return name; }

	private:
		DeclKind decl_kind;
		std::string name;
		SourceLocation source_loc;

	protected:
		DeclAST(DeclKind decl_kind, std::string_view name, SourceLocation const& loc)
			: decl_kind(decl_kind), name(name), source_loc(loc) {}
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
	class VariableDeclAST : public DeclAST
	{
	public:

	private:
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