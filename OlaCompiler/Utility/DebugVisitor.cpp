#include "DebugVisitor.h"
#include "Frontend/AST/AST.h"
#include "Core/Log.h"

namespace ola
{
	namespace
	{
		constexpr std::string GetIndentation(Uint32 indent)
		{
			std::string indentation(indent * 3, ' ');
			if (!indentation.empty())
			{
				indentation[indent * 3 - 3] = '`';
				indentation[indent * 3 - 2] = '-';
				indentation[indent * 3 - 1] = '>';
			}
			return indentation;
		}

		constexpr std::string BinaryExprKindToString(BinaryExprKind kind)
		{
			switch (kind)
			{
			case BinaryExprKind::Add:
				return "+";
			case BinaryExprKind::Subtract:
				return "-";
			case BinaryExprKind::Multiply:
				return "*";
			case BinaryExprKind::Divide:
				return "/";
			case BinaryExprKind::Modulo:
				return "%";
			case BinaryExprKind::ShiftLeft:
				return "<<";
			case BinaryExprKind::ShiftRight:
				return ">>";
			case BinaryExprKind::BitAnd:
				return "&";
			case BinaryExprKind::BitOr:
				return "|";
			case BinaryExprKind::BitXor:
				return "^";
			case BinaryExprKind::Assign:
				return "=";
			case BinaryExprKind::Comma:
				return ",";
			case BinaryExprKind::LogicalAnd:
				return "&&";
			case BinaryExprKind::LogicalOr:
				return "||";
			case BinaryExprKind::Equal:
				return "==";
			case BinaryExprKind::NotEqual:
				return "!=";
			case BinaryExprKind::Less:
				return "<";
			case BinaryExprKind::Greater:
				return ">";
			case BinaryExprKind::LessEqual:
				return "<=";
			case BinaryExprKind::GreaterEqual:
				return ">=";
			case BinaryExprKind::Invalid:
			default:
				return "invalid";
			}
		}

		constexpr std::string UnaryExprKindToString(UnaryExprKind kind)
		{
			switch (kind)
			{
			case UnaryExprKind::PreIncrement:
				return "++";
			case UnaryExprKind::PreDecrement:
				return "--";
			case UnaryExprKind::PostIncrement:
				return "++";
			case UnaryExprKind::PostDecrement:
				return "--";
			case UnaryExprKind::Plus:
				return "+";
			case UnaryExprKind::Minus:
				return "-";
			case UnaryExprKind::BitNot:
				return "~";
			case UnaryExprKind::LogicalNot:
				return "!";
			default:
				return "invalid";
			}
		}
	}

	DebugVisitor::DebugVisitor(AST const* ast)
	{
		OLA_DEBUG("AST Traversal:\n");
		ast->translation_unit->Accept(*this, 0);
	}

	void DebugVisitor::Visit(ASTNode const&, Uint32 depth)
	{
		OLA_DEBUG("{}Node\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(TranslationUnit const&, Uint32 depth)
	{
		OLA_DEBUG("{}TranslationUnit\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(Decl const&, Uint32 depth)
	{
		OLA_DEBUG("{}Decl\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(VarDecl const&, Uint32 depth)
	{
		OLA_DEBUG("{}VariableDecl\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(ParamVarDecl const&, Uint32 depth)
	{
		OLA_DEBUG("{}ParamVariableDecl\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(FieldDecl const&, Uint32 depth)
	{
		OLA_DEBUG("{}MemberVariableDecl\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(FunctionDecl const&, Uint32 depth)
	{
		OLA_DEBUG("{}FunctionDecl\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(ConstructorDecl const&, Uint32 depth)
	{
		OLA_DEBUG("{}ConstructorDecl\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(MethodDecl const&, Uint32 depth)
	{
		OLA_DEBUG("{}MemberFunctionDecl\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(TagDecl const&, Uint32 depth)
	{
		OLA_DEBUG("{}TagDecl\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(EnumDecl const&, Uint32 depth)
	{
		OLA_DEBUG("{}EnumDecl\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(EnumMemberDecl const&, Uint32 depth)
	{
		OLA_DEBUG("{}EnumMemberDecl\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(AliasDecl const&, Uint32 depth)
	{
		OLA_DEBUG("{}AliasDecl\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(ClassDecl const&, Uint32 depth)
	{
		OLA_DEBUG("{}ClassDecl\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(Stmt const&, Uint32 depth)
	{
		OLA_DEBUG("{}Stmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(CompoundStmt const&, Uint32 depth)
	{
		OLA_DEBUG("{}CompoundStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(DeclStmt const&, Uint32 depth)
	{
		OLA_DEBUG("{}DeclStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(ExprStmt const&, Uint32 depth)
	{
		OLA_DEBUG("{}ExprStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(NullStmt const&, Uint32 depth)
	{
		OLA_DEBUG("{}NullStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(ReturnStmt const&, Uint32 depth)
	{
		OLA_DEBUG("{}ReturnStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(IfStmt const&, Uint32 depth)
	{
		OLA_DEBUG("{}IfStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(BreakStmt const&, Uint32 depth)
	{
		OLA_DEBUG("{}BreakStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(ContinueStmt const&, Uint32 depth)
	{
		OLA_DEBUG("{}ContinueStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(ForStmt const&, Uint32 depth)
	{
		OLA_DEBUG("{}ForStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(WhileStmt const&, Uint32 depth)
	{
		OLA_DEBUG("{}WhileStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(DoWhileStmt const&, Uint32 depth)
	{
		OLA_DEBUG("{}DoWhileStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(CaseStmt const&, Uint32 depth)
	{
		OLA_DEBUG("{}CaseStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(SwitchStmt const&, Uint32 depth)
	{
		OLA_DEBUG("{}SwitchStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(GotoStmt const&, Uint32 depth)
	{
		OLA_DEBUG("{}GotoStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(LabelStmt const&, Uint32 depth)
	{
		OLA_DEBUG("{}LabelStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(Expr const&, Uint32 depth)
	{
		OLA_DEBUG("{}Expr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(UnaryExpr const&, Uint32 depth)
	{
		OLA_DEBUG("{}UnaryExpr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(BinaryExpr const&, Uint32 depth)
	{
		OLA_DEBUG("{}BinaryExpr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(TernaryExpr const&, Uint32 depth)
	{
		OLA_DEBUG("{}TernaryExpr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(IdentifierExpr const&, Uint32 depth)
	{
		OLA_DEBUG("{}Identifier\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(DeclRefExpr const&, Uint32 depth)
	{
		OLA_DEBUG("{}DeclRefExpr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(IntLiteral const&, Uint32 depth)
	{
		OLA_DEBUG("{}ConstantInt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(CharLiteral const&, Uint32 depth)
	{
		OLA_DEBUG("{}ConstantChar\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(StringLiteral const&, Uint32 depth)
	{
		OLA_DEBUG("{}ConstantString\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(BoolLiteral const&, Uint32 depth)
	{
		OLA_DEBUG("{}ConstantBool\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(FloatLiteral const&, Uint32 depth)
	{
		OLA_DEBUG("{}ConstantFloat\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(ImplicitCastExpr const&, Uint32 depth)
	{
		OLA_DEBUG("{}ImplicitCastExpr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(CallExpr const&, Uint32 depth)
	{
		OLA_DEBUG("{}FunctionCallExpr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(InitializerListExpr const&, Uint32 depth)
	{
		OLA_DEBUG("{}InitializerListExpr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(ArrayAccessExpr const&, Uint32 depth)
	{
		OLA_DEBUG("{}ArrayAccessExpr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(MemberExpr const&, Uint32 depth)
	{
		OLA_DEBUG("{}MemberAccessExpr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(MethodCallExpr const&, Uint32 depth)
	{
		OLA_DEBUG("{}MemberCallExpr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(ThisExpr const& this_expr, Uint32 depth)
	{
		OLA_DEBUG("{}ThisExpr {}\n", GetIndentation(depth), this_expr.IsImplicit() ? "(implicit)" : "");
	}

	void DebugVisitor::Visit(SuperExpr const& super_expr, Uint32 depth)
	{
		OLA_DEBUG("{}SuperExpr {}\n", GetIndentation(depth), super_expr.IsImplicit() ? "(implicit)" : "");
	}

	void DebugVisitor::Visit(ConstructorExpr const&, Uint32 depth)
	{
		OLA_DEBUG("{}ConstructorExpr\n", GetIndentation(depth));
	}

}