#pragma once
#include "ASTNode.h"
#include "Decl.h"

namespace wave
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

		virtual void Accept(ASTVisitor&, uint32) const override;
		virtual void Accept(ASTVisitor&) const override;

	private:
		UniqueDeclPtrList declarations;
	};

	struct AST
	{
		AST() { translation_unit = std::make_unique<TranslationUnit>(); }
		std::unique_ptr<TranslationUnit> translation_unit;
	};

	template<typename To, typename From> requires std::is_base_of_v<ASTNode, To> && std::is_base_of_v<ASTNode, From>
	WAVE_DEPRECATED inline To* dynamic_ast_cast(From* from)
	{
		return dynamic_cast<To*>(from);
	}							 
	template<typename To, typename From> requires std::is_base_of_v<ASTNode, To> && std::is_base_of_v<ASTNode, From>
	WAVE_DEPRECATED inline To const* dynamic_ast_cast(From const* from)
	{
		return dynamic_cast<To const*>(from);
	}				 
																				 
	template<typename To, typename From> requires std::is_base_of_v<ASTNode, To> && std::is_base_of_v<ASTNode, From>
	WAVE_DEPRECATED inline To* ast_cast(From* from)
	{
		return static_cast<To*>(from);
	}									 
	template<typename To, typename From> requires std::is_base_of_v<ASTNode, To> && std::is_base_of_v<ASTNode, From>
	WAVE_DEPRECATED inline To const* ast_cast(From const* from)
	{
		return static_cast<To const*>(from);
	}
}