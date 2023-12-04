#include "AST.h"
#include "ASTVisitor.h"

namespace ola
{
	void TranslationUnit::Accept(ASTVisitor& visitor, uint32 depth) const
	{
		visitor.Visit(*this, depth);
		for (auto&& decl : declarations) decl->Accept(visitor, depth + 1);
	}

	void TranslationUnit::Accept(ASTVisitor& visitor) const
	{
		visitor.Visit(*this, 0);
	}
}

