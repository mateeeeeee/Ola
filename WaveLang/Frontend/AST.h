#pragma once
#include <vector>
#include <memory>

namespace wave
{
	class Context;
	class Value;

	class NodeAST;
	class TranslationUnitAST;
	class DeclAST;

	class INodeVisitorAST
	{
	public:
		virtual ~INodeVisitorAST() = default;
		virtual void Visit(NodeAST const& node, uint32 depth) {}
		virtual void Visit(TranslationUnitAST const& node, uint32 depth) {}
		virtual void Visit(DeclAST const& node, uint32 depth) {}
	};

	class NodeAST
	{
	public:
		virtual ~NodeAST() = default;
		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const = 0;
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
		virtual void Accept(INodeVisitorAST& visitor, uint32 depth) const = 0;
		virtual Value* Codegen(Context& context) const {}

		DeclKind GetDeclKind() const { return decl_kind; }
	private:
		DeclKind decl_kind;

	protected:
		explicit DeclAST(DeclKind decl_kind) : decl_kind(decl_kind) {}
	};

	struct AST
	{
		AST() { translation_unit = std::make_unique<TranslationUnitAST>(); }
		std::unique_ptr<TranslationUnitAST> translation_unit;
	};

	template<typename To, typename From> requires std::is_base_of_v<NodeAST, To>&& std::is_base_of_v<NodeAST, From>
	inline To* DynamicAstCast(From* from)
	{
		return dynamic_cast<To*>(from);
	}
	template<typename To, typename From> requires std::is_base_of_v<NodeAST, To>&& std::is_base_of_v<NodeAST, From>
	inline To const* DynamicAstCast(From const* from)
	{
		return dynamic_cast<To const*>(from);
	}
	template<typename To, typename From> requires std::is_base_of_v<NodeAST, To>&& std::is_base_of_v<NodeAST, From>
	inline To* AstCast(From* from)
	{
		return static_cast<To*>(from);
	}
	template<typename To, typename From> requires std::is_base_of_v<NodeAST, To>&& std::is_base_of_v<NodeAST, From>
	inline To const* AstCast(From const* from)
	{
		return static_cast<To const*>(from);
	}
}