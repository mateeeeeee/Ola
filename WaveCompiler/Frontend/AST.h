#pragma once
#include "ASTTypeAliases.h"
#include "ASTVisitor.h"
#include "SourceLocation.h"
#include "Type.h"

namespace wave
{
	class NodeAST
	{
	public:
		virtual ~NodeAST() = default;
		virtual void Accept(ASTVisitor& visitor, uint32 depth) const {};
		virtual void Accept(ASTVisitor& visitor) const {}
	protected:
		NodeAST() = default;
	};


	class TranslationUnit final : public NodeAST
	{
	public:
		TranslationUnit() = default;

		void AddDecl(UniqueDeclPtr&& declaration)
		{
			declarations.push_back(std::move(declaration));
		}
		UniqueDeclPtrList const& GetDecls() const { return declarations; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueDeclPtrList declarations;
	};

	enum class DeclKind : uint8
	{
		Variable,
		Function,
		Enum,
		EnumMember,
		Alias,
		Class
	};

	enum class DeclVisibility : uint8
	{
		None,
		Private,
		Public,
		Extern
	};

	class Decl : public NodeAST
	{
	public:
		DeclKind GetDeclKind() const { return decl_kind; }
		SourceLocation GetLocation() const { return source_loc; }
		std::string_view GetName() const { return name; }

		void SetType(QualType const& _type) { type = _type; }
		QualType const& GetType() const { return type; }

		void SetVisibility(DeclVisibility _visibility)
		{
			visibility = _visibility;
		}
		bool IsPublic() const { return visibility == DeclVisibility::Public; }
		bool IsPrivate() const { return visibility == DeclVisibility::Private; }
		bool IsExtern() const { return visibility == DeclVisibility::Extern; }

		virtual bool IsTag() const { return false; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		DeclKind const decl_kind;
		std::string name;
		SourceLocation source_loc;
		QualType type;
		DeclVisibility visibility = DeclVisibility::None;

	protected:
		Decl(DeclKind decl_kind, std::string_view name, SourceLocation const& loc)
			: decl_kind(decl_kind), name(name), source_loc(loc) {}
	};

	class VariableDecl : public Decl
	{
	public:
		VariableDecl(std::string_view name, SourceLocation const& loc) : Decl(DeclKind::Variable, name, loc) {}

		void SetGlobal(bool _is_global)
		{
			is_global = _is_global;
		}
		bool IsGlobal() const { return is_global; }

		void SetInitExpr(UniqueExprPtr&& expr)
		{
			init_expr = std::move(expr);
		}
		Expr const* GetInitExpr() const { return init_expr.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueExprPtr init_expr;
		bool is_global = false;
	};

	class FunctionDecl : public Decl
	{
		friend class LabelVisitor;
	public:
		FunctionDecl(std::string_view name, SourceLocation const& loc) : Decl(DeclKind::Function, name, loc) {}

		void SetParamDecls(UniqueVariableDeclPtrList&& param_decls)
		{
			param_declarations = std::move(param_decls);
		}
		void SetBodyStmt(UniqueCompoundStmtPtr&& _body_stmt)
		{
			body_stmt = std::move(_body_stmt);
		}

		UniqueVariableDeclPtrList const& GetParamDeclarations() const { return param_declarations; }
		CompoundStmt const* GetBodyStmt() const { return body_stmt.get(); }

		bool HasDefinition() const
		{
			return body_stmt != nullptr;
		}

		ConstLabelStmtPtrList GetLabels() const;

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueVariableDeclPtrList param_declarations;
		UniqueCompoundStmtPtr body_stmt;
		mutable ConstLabelStmtPtrList labels;
	};

	class TagDecl : public Decl
	{
	public:
		virtual bool IsTag() const override { return true; }

	protected:
		TagDecl(DeclKind decl_kind, std::string_view name, SourceLocation const& loc) : Decl(decl_kind, name, loc) {}
	};

	class EnumDecl : public TagDecl
	{
	public:
		EnumDecl(std::string_view name, SourceLocation const& loc)  : TagDecl(DeclKind::Enum, name, loc) {}

		void SetEnumMembers(UniqueEnumMemberDeclPtrList&& _enum_members)
		{
			enum_members = std::move(_enum_members);
		}
		UniqueEnumMemberDeclPtrList const& GetEnumMembers() const { return enum_members; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueEnumMemberDeclPtrList enum_members;
	};

	class EnumMemberDecl : public Decl
	{
	public:
		EnumMemberDecl(std::string_view name, SourceLocation const& loc) : Decl(DeclKind::EnumMember, name, loc) 
		{
			SetType(builtin_types::Enum);
		}

		void SetValue(int64 _value)
		{
			value = _value;
		}
		int64 GetValue() const { return value; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		int64 value = 0;
	};

	class AliasDecl : public TagDecl
	{
	public:
		AliasDecl(std::string_view name, SourceLocation const& loc, QualType const& aliased_type) : TagDecl(DeclKind::Alias, name, loc)
		{
			SetType(aliased_type);
			SetVisibility(DeclVisibility::Public);
		}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;
	};

	class ClassDecl : public TagDecl
	{
	public:
		ClassDecl(std::string_view name, SourceLocation const& loc) : TagDecl(DeclKind::Class, name, loc) {}

		void SetMemberVariables(UniqueVariableDeclPtrList&& _member_variables)
		{
			member_variables = std::move(_member_variables);
		}
		UniqueVariableDeclPtrList const& GetMemberVariables() const { return member_variables; }
		void SetMemberFunctions(UniqueFunctionDeclPtrList&& _member_functions)
		{
			member_functions = std::move(_member_functions);
		}
		UniqueFunctionDeclPtrList const& GetMemberFunctions() const { return member_functions; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueVariableDeclPtrList member_variables;
		UniqueFunctionDeclPtrList member_functions;
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

	class Stmt : public NodeAST
	{
	public:
		StmtKind GetStmtKind() const { return kind; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	protected:
		StmtKind const kind;

	protected:
		explicit Stmt(StmtKind kind) : kind(kind) {}
	};

	class CompoundStmt final : public Stmt
	{
	public:
		CompoundStmt(UniqueStmtPtrList&& stmts) : Stmt(StmtKind::Compound), statements(std::move(stmts)) {}
		UniqueStmtPtrList const& GetStmts() const { return statements; }

		void AddBeginStmt(UniqueStmtPtr&& stmt)
		{
			statements.insert(std::begin(statements), std::move(stmt));
		}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueStmtPtrList statements;
	};
	
	class DeclStmt final : public Stmt
	{
	public:
		DeclStmt(UniqueDeclPtr&& decl) : Stmt(StmtKind::Decl), declarations{} 
		{
			declarations.push_back(std::move(decl));
		}
		DeclStmt(UniqueDeclPtrList&& decls) : Stmt(StmtKind::Decl), declarations(std::move(decls)) {}

		UniqueDeclPtrList const& GetDecls() const { return declarations; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueDeclPtrList declarations;
	};

	class ExprStmt : public Stmt
	{
	public:
		ExprStmt(UniqueExprPtr&& expr) : Stmt(expr ? StmtKind::Expr : StmtKind::Null), expr(std::move(expr)) {}

		Expr const* GetExpr() const 
		{
			return expr.get(); 
		}

		Expr* ReleaseExpr()
		{
			return expr.release();
		}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueExprPtr expr;
	};

	class NullStmt final : public ExprStmt
	{
	public:
		NullStmt() : ExprStmt(nullptr) {}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	};

	class ReturnStmt final : public Stmt
	{
	public:
		explicit ReturnStmt(std::unique_ptr<ExprStmt>&& ret_expr)
			: Stmt(StmtKind::Return), ret_expr(std::move(ret_expr)) {}

		ExprStmt const* GetExprStmt() const { return ret_expr.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueExprStmtPtr ret_expr;
	};

	class IfStmt final : public Stmt
	{
	public:
		IfStmt() : Stmt(StmtKind::If) {}

		void SetConditionExpr(UniqueExprPtr&& _condition)
		{
			cond_expr = std::move(_condition);
		}
		void SetThenStmt(UniqueStmtPtr&& _then_stmt)
		{
			then_stmt = std::move(_then_stmt);
		}
		void SetElseStmt(UniqueStmtPtr&& _else_stmt)
		{
			else_stmt = std::move(_else_stmt);
		}

		Expr const* GetCondExpr() const { return cond_expr.get(); }
		Stmt const* GetThenStmt() const { return then_stmt.get(); }
		Stmt const* GetElseStmt() const { return else_stmt.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueExprPtr cond_expr;
		UniqueStmtPtr then_stmt;
		UniqueStmtPtr else_stmt;
	};

	class BreakStmt final : public Stmt
	{
	public:
		BreakStmt() : Stmt(StmtKind::Break) {}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;
	};

	class ContinueStmt final : public Stmt
	{
	public:
		ContinueStmt() : Stmt(StmtKind::Continue) {}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;
	};

	class ForStmt final : public Stmt
	{
	public:
		ForStmt() : Stmt(StmtKind::For) {}

		void SetInitStmt(UniqueStmtPtr&& _init_stmt)
		{
			init_stmt = std::move(_init_stmt);
		}
		void SetCondExpr(UniqueExprPtr&& _cond_expr)
		{
			cond_expr = std::move(_cond_expr);
		}
		void SetIterExpr(UniqueExprPtr&& _iter_expr)
		{
			iter_expr = std::move(_iter_expr);
		}
		void SetBodyStmt(UniqueStmtPtr&& _body_stmt)
		{
			body_stmt = std::move(_body_stmt);
		}

		Stmt const* GetInitStmt() const { return init_stmt.get(); }
		Expr const* GetCondExpr() const { return cond_expr.get(); }
		Expr const* GetIterExpr() const { return iter_expr.get(); }
		Stmt const* GetBodyStmt() const { return body_stmt.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueStmtPtr init_stmt;
		UniqueExprPtr cond_expr;
		UniqueExprPtr iter_expr;
		UniqueStmtPtr body_stmt;
	};

	class WhileStmt final : public Stmt
	{
	public:
		WhileStmt() : Stmt(StmtKind::While) {}

		void SetCondExpr(UniqueExprPtr&& _cond_expr)
		{
			cond_expr = std::move(_cond_expr);
		}
		void SetBodyStmt(UniqueStmtPtr&& _body_stmt)
		{
			body_stmt = std::move(_body_stmt);
		}

		Expr const* GetCondExpr() const { return cond_expr.get(); }
		Stmt const* GetBodyStmt() const { return body_stmt.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueExprPtr cond_expr;
		UniqueStmtPtr body_stmt;
	};

	class DoWhileStmt final : public Stmt
	{
	public:
		DoWhileStmt() : Stmt(StmtKind::DoWhile) {}

		void SetCondExpr(UniqueExprPtr&& _cond_expr)
		{
			cond_expr = std::move(_cond_expr);
		}
		void SetBodyStmt(UniqueStmtPtr&& _body_stmt)
		{
			body_stmt = std::move(_body_stmt);
		}

		Expr const* GetCondExpr() const { return cond_expr.get(); }
		Stmt const* GetBodyStmt() const { return body_stmt.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueExprPtr cond_expr;
		UniqueStmtPtr body_stmt;
	};

	class CaseStmt final : public Stmt
	{
	public:
		CaseStmt() : Stmt(StmtKind::Case), is_default(true), value(0) {}
		explicit CaseStmt(int64 value) : Stmt(StmtKind::Case), is_default(false), value(value) {}

		bool IsDefault() const { return is_default; }
		int64 GetValue() const { return value; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		int64 value;
		bool is_default;
	};

	class SwitchStmt final : public Stmt
	{
	public:
		SwitchStmt() : Stmt(StmtKind::Switch) {}

		void SetCondExpr(UniqueExprPtr&& _cond_expr)
		{
			cond_expr = std::move(_cond_expr);
		}
		void SetBodyStmt(UniqueStmtPtr&& _body_stmt)
		{
			body_stmt = std::move(_body_stmt);
		}

		Expr const* GetCondExpr() const { return cond_expr.get(); }
		Stmt const* GetBodyStmt() const { return body_stmt.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueExprPtr cond_expr;
		UniqueStmtPtr body_stmt;
	};

	class LabelStmt final : public Stmt
	{
	public:
		LabelStmt(std::string_view label) : Stmt(StmtKind::Label), label_name(label) {}
		std::string_view GetName() const { return label_name; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		std::string label_name;
	};

	class GotoStmt final : public Stmt
	{
	public:
		explicit GotoStmt(std::string_view label) : Stmt(StmtKind::Label), label_name(label) {}
		std::string_view GetLabelName() const { return label_name; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		std::string label_name;
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
		BoolLiteral,
		CharLiteral,
		DeclRef,
		ImplicitCast,
		InitializerList,
		ArrayAccess
	};
	enum class UnaryExprKind : uint8
	{
		PreIncrement, PreDecrement,
		PostIncrement, PostDecrement,
		Plus, Minus, BitNot,
		LogicalNot
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

	class Expr : public NodeAST
	{
	public:
		SourceLocation const& GetLocation() const { return loc; }
		ExprKind GetExprKind() const { return kind; }
		bool IsLValue() const { return value_category == ExprValueCategory::LValue; }

		void SetType(QualType const& _type) { type = _type; }
		QualType const& GetType() const { return type; }

		virtual bool IsConstexpr() const { return false; }
		virtual int64 EvaluateConstexpr() const { return 0; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	protected:
		ExprKind const kind;
		SourceLocation loc;
		QualType type;
		ExprValueCategory value_category = ExprValueCategory::RValue;

	protected:
		Expr(ExprKind kind, SourceLocation const& loc) : kind(kind), loc(loc) {}
		void SetValueCategory(ExprValueCategory _value_category) { value_category = _value_category; }
	};

	class UnaryExpr : public Expr
	{
	public:
		UnaryExpr(UnaryExprKind op, SourceLocation const& loc) : Expr(ExprKind::Unary, loc), op(op), operand(nullptr) {}
		void SetOperand(UniqueExprPtr&& _operand)
		{
			operand = std::move(_operand);
		}
		UnaryExprKind GetUnaryKind() const { return op; }
		Expr const* GetOperand() const { return operand.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UnaryExprKind op;
		UniqueExprPtr operand;
	};

	class BinaryExpr : public Expr
	{
	public:
		BinaryExpr(BinaryExprKind op, SourceLocation const& loc) : Expr(ExprKind::Binary, loc), op(op) {}
		void SetLHS(UniqueExprPtr&& _lhs) { lhs = std::move(_lhs); }
		void SetRHS(UniqueExprPtr&& _rhs) { rhs = std::move(_rhs); }

		BinaryExprKind GetBinaryKind() const { return op; }
		Expr const* GetLHS() const { return lhs.get(); }
		Expr const* GetRHS() const { return rhs.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueExprPtr lhs, rhs;
		BinaryExprKind op;
	};

	class TernaryExpr : public Expr
	{
	public:
		explicit TernaryExpr(SourceLocation const& loc) : Expr(ExprKind::Ternary, loc)
		{}

		void SetCondExpr(UniqueExprPtr&& expr) { cond_expr = std::move(expr); }
		void SetTrueExpr(UniqueExprPtr&& expr) { true_expr = std::move(expr); }
		void SetFalseExpr(UniqueExprPtr&& expr) { false_expr = std::move(expr); }

		Expr const* GetCondExpr() const { return cond_expr.get(); }
		Expr const* GetTrueExpr() const { return true_expr.get(); }
		Expr const* GetFalseExpr() const { return false_expr.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueExprPtr cond_expr;
		UniqueExprPtr true_expr;
		UniqueExprPtr false_expr;
	};

	class IdentifierExpr : public Expr
	{
	public:
		std::string_view GetName() const { return name; }

	protected:
		explicit IdentifierExpr(ExprKind kind, std::string_view name, SourceLocation const& loc) : Expr(kind, loc), name(name)
		{
			SetValueCategory(ExprValueCategory::LValue);
		}

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		std::string name;
	};

	class DeclRefExpr : public IdentifierExpr
	{
	public:
		DeclRefExpr(Decl* decl, SourceLocation const& loc) : IdentifierExpr(ExprKind::DeclRef, decl->GetName(), loc), decl(decl)
		{
			SetType(decl->GetType());
		}

		Decl const* GetDecl() const { return decl; }
		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		Decl* decl;
	};

	class ConstantInt final : public Expr
	{
	public:
		ConstantInt(int64 value, SourceLocation const& loc) : Expr(ExprKind::IntLiteral, loc), value(value) 
		{
			SetType(builtin_types::Int);
		}
		int64 GetValue() const { return value; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		virtual bool IsConstexpr() const { return true; }
		virtual int64 EvaluateConstexpr() const { return value; }

	private:
		int64 value;
	};

	class ConstantChar final : public Expr
	{
	public:
		ConstantChar(char c, SourceLocation const& loc) : Expr(ExprKind::CharLiteral, loc), c(c)
		{
			SetValueCategory(ExprValueCategory::RValue);
			SetType(builtin_types::Char);
		}
		char GetChar() const { return c; }

		virtual bool IsConstexpr() const { return true; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		char c;
	};

	class ConstantString final : public Expr
	{
	public:
		ConstantString(std::string_view str, SourceLocation const& loc) : Expr(ExprKind::StringLiteral, loc), str(str) 
		{
			SetValueCategory(ExprValueCategory::RValue);
			SetType(QualType(ArrayType(builtin_types::Char, (uint32)str.size() + 1), Qualifier_Const));
		}
		std::string_view GetString() const { return str; }

		virtual bool IsConstexpr() const { return true; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		std::string str;
	};

	class ConstantBool final : public Expr
	{
	public:
		ConstantBool(bool value, SourceLocation const& loc) : Expr(ExprKind::BoolLiteral, loc), value(value)
		{
			SetType(builtin_types::Bool);
		}
		bool GetValue() const { return value; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		virtual bool IsConstexpr() const { return true; }

	private:
		bool value;
	};

	class ConstantFloat final : public Expr 
	{
	public:
		ConstantFloat(double value, SourceLocation const& loc) : Expr(ExprKind::FloatLiteral, loc), value(value)
		{
			SetType(builtin_types::Float);
		}
		double GetValue() const { return value; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		virtual bool IsConstexpr() const { return true; }

	private:
		double value;
	};

	class ImplicitCastExpr : public Expr
	{
	public:
		ImplicitCastExpr(SourceLocation const& loc, QualType const& qtype) : Expr(ExprKind::ImplicitCast, loc), operand(nullptr)
		{
			SetType(qtype);
			SetValueCategory(ExprValueCategory::RValue);
		}

		void SetOperand(UniqueExprPtr&& _operand)
		{
			operand = std::move(_operand);
		}
		Expr const* GetOperand() const { return operand.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueExprPtr operand;
	};

	class FunctionCallExpr final : public Expr
	{
	public:
		FunctionCallExpr(SourceLocation const& loc, std::string_view function_name)
			: Expr(ExprKind::FunctionCall, loc), function_name(function_name) {}

		void SetArgs(UniqueExprPtrList&& args)
		{
			func_args = std::move(args);
		}
		std::string_view GetFunctionName() const { return function_name; }
		UniqueExprPtrList const& GetArgs() const { return func_args; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		std::string function_name;
		UniqueExprPtrList func_args;
	};

	class InitializerListExpr final : public Expr
	{
	public:
		explicit InitializerListExpr(SourceLocation const& loc) : Expr(ExprKind::InitializerList, loc) {}

		void SetInitList(UniqueExprPtrList&& _init_list)
		{
			init_list = std::move(_init_list);
		}
		UniqueExprPtrList const& GetInitList() const { return init_list; }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

		virtual bool IsConstexpr() const 
		{ 
			bool is_constexpr = true;
			for (auto const& init_elem : init_list) if (!init_elem->IsConstexpr()) return false;
			return true;
		}

	private:
		UniqueExprPtrList init_list;
	};

	class ArrayAccessExpr final : public Expr
	{
	public:
		explicit ArrayAccessExpr(SourceLocation const& loc) : Expr(ExprKind::ArrayAccess, loc) 
		{
			SetValueCategory(ExprValueCategory::LValue);
		}

		void SetArrayExpr(UniqueExprPtr&& _array_expr)
		{
			array_expr = std::move(_array_expr);
		}
		void SetIndexExpr(UniqueExprPtr&& _bracket_expr)
		{
			bracket_expr = std::move(_bracket_expr);
		}

		Expr const* GetArrayExpr() const { return array_expr.get(); }
		Expr const* GetIndexExpr() const { return bracket_expr.get(); }

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueExprPtr array_expr;
		UniqueExprPtr bracket_expr;
	};

	struct AST
	{
		AST() { translation_unit = std::make_unique<TranslationUnit>(); }
		std::unique_ptr<TranslationUnit> translation_unit;
	};

	template<typename To, typename From> requires std::is_base_of_v<NodeAST, To> && std::is_base_of_v<NodeAST, From>
	inline To* dynamic_ast_cast(From* from)
	{
		return dynamic_cast<To*>(from);
	}							 
	template<typename To, typename From> requires std::is_base_of_v<NodeAST, To> && std::is_base_of_v<NodeAST, From>
	inline To const* dynamic_ast_cast(From const* from)
	{
		return dynamic_cast<To const*>(from);
	}				 
																				 
	template<typename To, typename From> requires std::is_base_of_v<NodeAST, To> && std::is_base_of_v<NodeAST, From>
	inline To* ast_cast(From* from)
	{
		return static_cast<To*>(from);
	}									 
	template<typename To, typename From> requires std::is_base_of_v<NodeAST, To> && std::is_base_of_v<NodeAST, From>
	inline To const* ast_cast(From const* from)
	{
		return static_cast<To const*>(from);
	}
}