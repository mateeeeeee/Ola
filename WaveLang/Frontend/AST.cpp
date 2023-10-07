#include "AST.h"

namespace wave
{
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

	void TranslationUnitAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{

	}

	void DeclAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(false);
	}
	void VariableDeclAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{

	}
	void FunctionDeclAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{

	}

	void StmtAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{
		WAVE_ASSERT(false);
	}

	void CompoundStmtAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{

	}

	void ExprStmtAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{

	}

	void NullStmtAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{

	}

	void DeclStmtAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{

	}

	void ReturnStmtAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{

	}

	void IfStmtAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{

	}

	void ExprAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{

	}

	void UnaryExprAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{

	}

	void BinaryExprAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{

	}

	void TernaryExprAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{

	}

	void IntLiteralAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{

	}

	void StringLiteralAST::Accept(INodeVisitorAST& visitor, uint32 depth) const
	{

	}

}

