#include "DebugVisitor.h"
#include "Frontend/AST.h"
#include "Core/Logger.h"

namespace wave
{
	namespace
	{
		constexpr std::string GetIndentation(uint32 indent)
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
		WAVE_DEBUG("AST Traversal:\n");
		ast->translation_unit->Accept(*this, 0);
	}

	void DebugVisitor::Visit(NodeAST const&, uint32 depth)
	{
		WAVE_DEBUG("{}Node\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(TranslationUnit const&, uint32 depth)
	{
		WAVE_DEBUG("{}TranslationUnit\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(Decl const&, uint32 depth)
	{
		WAVE_DEBUG("{}Decl\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(VariableDecl const&, uint32 depth)
	{
		WAVE_DEBUG("{}VariableDecl\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(FunctionDecl const&, uint32 depth)
	{
		WAVE_DEBUG("{}FunctionDecl\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(Stmt const&, uint32 depth)
	{
		WAVE_DEBUG("{}Stmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(CompoundStmt const&, uint32 depth)
	{
		WAVE_DEBUG("{}CompoundStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(DeclStmt const&, uint32 depth)
	{
		WAVE_DEBUG("{}DeclStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(ExprStmt const&, uint32 depth)
	{
		WAVE_DEBUG("{}ExprStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(NullStmt const&, uint32 depth)
	{
		WAVE_DEBUG("{}NullStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(ReturnStmt const&, uint32 depth)
	{
		WAVE_DEBUG("{}ReturnStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(IfStmt const&, uint32 depth)
	{
		WAVE_DEBUG("{}IfStmt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(Expr const&, uint32 depth)
	{
		WAVE_DEBUG("{}Expr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(UnaryExpr const&, uint32 depth)
	{
		WAVE_DEBUG("{}UnaryExpr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(BinaryExpr const&, uint32 depth)
	{
		WAVE_DEBUG("{}BinaryExpr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(TernaryExpr const&, uint32 depth)
	{
		WAVE_DEBUG("{}TernaryExpr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(IdentifierExpr const&, uint32 depth)
	{
		WAVE_DEBUG("{}Identifier\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(DeclRefExpr const&, uint32 depth)
	{
		WAVE_DEBUG("{}DeclRefExpr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(ConstantInt const&, uint32 depth)
	{
		WAVE_DEBUG("{}ConstantInt\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(ConstantString const&, uint32 depth)
	{
		WAVE_DEBUG("{}ConstantString\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(ConstantBool const&, uint32 depth)
	{
		WAVE_DEBUG("{}ConstantBool\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(ConstantFloat const&, uint32 depth)
	{
		WAVE_DEBUG("{}ConstantFloat\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(CastExpr const&, uint32 depth)
	{
		WAVE_DEBUG("{}CastExpr\n", GetIndentation(depth));
	}

	void DebugVisitor::Visit(FunctionCallExpr const&, uint32 depth)
	{
		WAVE_DEBUG("{}FunctionCallExpr\n", GetIndentation(depth));
	}

}