#pragma once


namespace ola
{
	class ASTVisitor;

	class ASTNode
	{
	public:
		virtual ~ASTNode() = default;
		virtual void Accept(ASTVisitor& visitor, uint32 depth) const {};
		virtual void Accept(ASTVisitor& visitor) const {}
	protected:
		ASTNode() = default;
	};
}