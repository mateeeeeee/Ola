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
	class UnaryExprAST;
	class BinaryExprAST;
	class TernaryExprAST;
	class IntLiteralAST;
	class StringLiteralAST;
	class IdentifierAST;

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
		virtual void Visit(CompoundStmtAST const& node, uint32 depth) {}
		virtual void Visit(ExprStmtAST const& node, uint32 depth) {}
		virtual void Visit(DeclStmtAST const& node, uint32 depth) {}
		virtual void Visit(NullStmtAST const& node, uint32 depth) {}
		virtual void Visit(ReturnStmtAST const& node, uint32 depth) {}
		virtual void Visit(IfStmtAST const& node, uint32 depth) {}

		virtual void Visit(ExprAST const& node, uint32 depth) {}
		virtual void Visit(UnaryExprAST const& node, uint32 depth) {}
		virtual void Visit(BinaryExprAST const& node, uint32 depth) {}
		virtual void Visit(TernaryExprAST const& node, uint32 depth) {}
		virtual void Visit(IntLiteralAST const& node, uint32 depth) {}
		virtual void Visit(StringLiteralAST const& node, uint32 depth) {}
		virtual void Visit(IdentifierAST const& node, uint32 depth) {}
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
	class TranslationUnitAST final : public NodeAST
	{
	public:
		TranslationUnitAST() = default;

		void AddDeclaration(std::unique_ptr<DeclAST>&& declaration)
		{
			declarations.push_back(std::move(declaration));
		}

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const override;

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
		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const;

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
		VariableDeclAST(std::string_view name, SourceLocation const& loc) : DeclAST(DeclKind::Variable, name, loc) {}

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const;

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
		FunctionDeclAST(std::string_view name, SourceLocation const& loc) : DeclAST(DeclKind::Function, name, loc) {}
		
		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const;

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

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const;

	protected:
		StmtKind kind;

	protected:
		explicit StmtAST(StmtKind kind) : kind(kind) {}
	};
	class CompoundStmtAST final : public StmtAST
	{
	public:
		CompoundStmtAST() : StmtAST(StmtKind::Compound) {}

		void AddStatement(std::unique_ptr<StmtAST>&& stmt)
		{
			statements.push_back(std::move(stmt));
		}

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const;

	private:
		std::vector<std::unique_ptr<StmtAST>> statements;
	};
	class ExprStmtAST : public StmtAST
	{
	public:
		ExprStmtAST(std::unique_ptr<ExprAST>&& expr) : StmtAST(expr ? StmtKind::Expr : StmtKind::Null), expr(std::move(expr)) {}

		ExprAST* GetExpr() const { return expr.get(); }

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const;

	private:
		std::unique_ptr<ExprAST> expr;
	};
	class NullStmtAST final : public ExprStmtAST
	{
	public:
		NullStmtAST() : ExprStmtAST(nullptr) {}

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const;
	};
	class DeclStmtAST final : public StmtAST
	{
	public:
		DeclStmtAST(std::unique_ptr<DeclAST>&& decl) : StmtAST(StmtKind::Decl), declaration(std::move(decl)) {}

		DeclAST* GetDeclarations() const { return declaration.get(); }

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const;

	private:
		std::unique_ptr<DeclAST> declaration;
	};
	class ReturnStmtAST final : public StmtAST
	{
	public:
		explicit ReturnStmtAST(std::unique_ptr<ExprStmtAST>&& ret_expr)
			: StmtAST(StmtKind::Return), ret_expr(std::move(ret_expr)) {}

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const;

	private:
		std::unique_ptr <ExprStmtAST> ret_expr;
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

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const;

	private:
		std::unique_ptr<ExprAST> condition;
		std::unique_ptr<StmtAST> then_stmt;
		std::unique_ptr<StmtAST> else_stmt;
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
	enum class ExprValueCategory : bool
	{
		LValue,
		RValue
	};
	class ExprAST : public NodeAST
	{
	public:
		SourceLocation const& GetLocation() const { return loc; }
		ExprKind GetExprKind() const { return kind; }
		bool IsLValue() const { return value_category == ExprValueCategory::LValue; }

		void SetType(QualifiedType const& _type) { type = _type; }
		QualifiedType const& GetType() const { return type; }

		virtual bool IsConstexpr() const { return false; }
		virtual int64 EvaluateConstexpr() const { return 0; }

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const;

	protected:
		ExprKind kind;
		SourceLocation loc;
		QualifiedType type;
		ExprValueCategory value_category = ExprValueCategory::RValue;

	protected:
		ExprAST(ExprKind kind, SourceLocation const& loc) : kind(kind), loc(loc) {}
		void SetValueCategory(ExprValueCategory _value_category) { value_category = _value_category; }
	};
	class UnaryExprAST : public ExprAST
	{
	public:
		UnaryExprAST(UnaryExprKind op, SourceLocation const& loc) : ExprAST(ExprKind::Unary, loc), op(op), operand(nullptr) {}
		void SetOperand(std::unique_ptr<ExprAST>&& _operand)
		{
			operand = std::move(_operand);
		}
		UnaryExprKind GetUnaryKind() const { return op; }
		ExprAST* GetOperand() const { return operand.get(); }

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const override;

	private:
		UnaryExprKind op;
		std::unique_ptr<ExprAST> operand;
	};
	class BinaryExprAST : public ExprAST
	{
	public:
		BinaryExprAST(BinaryExprKind op, SourceLocation const& loc) : ExprAST(ExprKind::Binary, loc), op(op) {}
		void SetLHS(std::unique_ptr<ExprAST>&& _lhs) { lhs = std::move(_lhs); }
		void SetRHS(std::unique_ptr<ExprAST>&& _rhs) { rhs = std::move(_rhs); }

		BinaryExprKind GetBinaryKind() const { return op; }
		ExprAST* GetLHS() const { return lhs.get(); }
		ExprAST* GetRHS() const { return rhs.get(); }

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const override;

	private:
		std::unique_ptr<ExprAST> lhs, rhs;
		BinaryExprKind op;
	};
	class TernaryExprAST : public ExprAST
	{
	public:
		explicit TernaryExprAST(SourceLocation const& loc) : ExprAST(ExprKind::Ternary, loc),
			cond_expr(std::move(cond_expr)),
			true_expr(std::move(true_expr)),
			false_expr(std::move(false_expr))
		{}

		void SetCondition(std::unique_ptr<ExprAST>&& expr) { cond_expr = std::move(expr); }
		void SetTrueExpr(std::unique_ptr<ExprAST>&& expr) { true_expr = std::move(expr); }
		void SetFalseExpr(std::unique_ptr<ExprAST>&& expr) { false_expr = std::move(expr); }

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const override;

	private:
		std::unique_ptr<ExprAST> cond_expr;
		std::unique_ptr<ExprAST> true_expr;
		std::unique_ptr<ExprAST> false_expr;
	};
	class IntLiteralAST final : public ExprAST
	{
	public:
		IntLiteralAST(int64 value, SourceLocation const& loc) : ExprAST(ExprKind::IntLiteral, loc), value(value) 
		{
			SetType(builtin_types::Int);
		}
		int64 GetValue() const { return value; }

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const override;

	private:
		int64 value;
	};
	class StringLiteralAST final : public ExprAST
	{
	public:
		StringLiteralAST(std::string_view str, SourceLocation const& loc) : ExprAST(ExprKind::StringLiteral, loc), str(str) 
		{
			SetType(ArrayType(builtin_types::Char, (uint32)str.size()));
		}
		std::string_view GetString() const { return str; }

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const override;

	private:
		std::string str;
	};
	class IdentifierAST : public ExprAST
	{
	public:
		std::string_view GetName() const { return name; }

	protected:
		explicit IdentifierAST(std::string_view name, SourceLocation const& loc) : ExprAST(ExprKind::DeclRef, loc), name(name)
		{
			SetValueCategory(ExprValueCategory::LValue);
		}

	private:
		std::string name;
	};
	class CastExprAST : public ExprAST
	{
	public:
		CastExprAST(SourceLocation const& loc, QualifiedType const& qtype)
			: ExprAST(ExprKind::Cast, loc), operand(nullptr)
		{
			SetType(qtype);
			SetValueCategory(ExprValueCategory::RValue);
		}
		void SetOperand(std::unique_ptr<ExprAST>&& _operand)
		{
			operand = std::move(_operand);
		}

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const override;

	private:
		std::unique_ptr<ExprAST> operand;
	};
	class FunctionCallExprAST final : public ExprAST
	{
	public:
		FunctionCallExprAST(std::unique_ptr<ExprAST>&& func, SourceLocation const& loc)
			: ExprAST(ExprKind::FunctionCall, loc), func_expr(std::move(func)) {}

		void AddArgument(std::unique_ptr<ExprAST>&& arg)
		{
			func_args.push_back(std::move(arg));
		}

		ExprAST* GetFunction() const { return func_expr.get(); }

		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const override;

	private:
		std::unique_ptr<ExprAST> func_expr;
		std::vector<std::unique_ptr<ExprAST>> func_args;
	};

	struct AST
	{
		AST() { translation_unit = std::make_unique<TranslationUnitAST>(); }
		std::unique_ptr<TranslationUnitAST> translation_unit;
	};
}