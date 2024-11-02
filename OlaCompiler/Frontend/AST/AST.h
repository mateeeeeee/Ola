#pragma once
#include "ASTNode.h"
#include "Decl.h"

namespace ola
{
	class TranslationUnit final : public ASTNode
	{
	public:
		TranslationUnit() = default;

		void AddDecl(UniqueDeclPtr&& declaration)
		{
			declarations.push_back(std::move(declaration));
		}
		UniqueDeclPtrList const& GetDecls() const { return declarations; }

		virtual void Accept(ASTVisitor&, Uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueDeclPtrList declarations;
	};
	struct AST
	{
		AST() { translation_unit = std::make_unique<TranslationUnit>(); }
		std::unique_ptr<TranslationUnit> translation_unit;
	};
}