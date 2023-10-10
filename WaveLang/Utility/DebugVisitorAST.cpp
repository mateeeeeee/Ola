#include "DebugVisitorAST.h"
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
			case UnaryExprKind::Dereference:
				return "*";
			case UnaryExprKind::AddressOf:
				return "&";
			default:
				return "invalid";
			}
		}
	}

	DebugVisitorAST::DebugVisitorAST(AST const* ast)
	{
		WAVE_DEBUG("AST Traversal:\n");
		ast->translation_unit->Accept(*this, 0);
	}

	void DebugVisitorAST::Visit(NodeAST const& node, uint32 depth)
	{
		WAVE_DEBUG("{}NodeAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(Identifier const& node, uint32 depth)
	{
		WAVE_DEBUG("{}IdentifierAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(StringLiteral const& node, uint32 depth)
	{
		WAVE_DEBUG("{}StringLiteralAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(IntLiteral const& node, uint32 depth)
	{
		WAVE_DEBUG("{}IntLiteralAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(TernaryExpr const& node, uint32 depth)
	{
		WAVE_DEBUG("{}TernaryExprAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(BinaryExpr const& node, uint32 depth)
	{
		WAVE_DEBUG("{}BinaryExprAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(UnaryExpr const& node, uint32 depth)
	{
		WAVE_DEBUG("{}UnaryExprAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(Expr const& node, uint32 depth)
	{
		WAVE_DEBUG("{}ExprAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(IfStmt const& node, uint32 depth)
	{
		WAVE_DEBUG("{}IfStmtAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(ReturnStmt const& node, uint32 depth)
	{
		WAVE_DEBUG("{}ReturnStmtAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(NullStmt const& node, uint32 depth)
	{
		WAVE_DEBUG("{}NullStmtAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(DeclStmt const& node, uint32 depth)
	{
		WAVE_DEBUG("{}DeclStmtAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(ExprStmt const& node, uint32 depth)
	{
		WAVE_DEBUG("{}ExprStmtAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(CompoundStmt const& node, uint32 depth)
	{
		WAVE_DEBUG("{}CompoundStmtAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(Stmt const& node, uint32 depth)
	{
		WAVE_DEBUG("{}StmtAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(VariableDecl const& node, uint32 depth)
	{
		WAVE_DEBUG("{}VariableDeclAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(FunctionDecl const& node, uint32 depth)
	{
		WAVE_DEBUG("{}FunctionDeclAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(Decl const& node, uint32 depth)
	{
		WAVE_DEBUG("{}DeclAST \n", GetIndentation(depth));
	}

	void DebugVisitorAST::Visit(TranslationUnit const& node, uint32 depth)
	{
		WAVE_DEBUG("{}TranslationUnitAST \n", GetIndentation(depth));
	}

}