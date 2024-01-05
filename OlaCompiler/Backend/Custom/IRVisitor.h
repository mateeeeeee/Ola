#pragma once
#include "Frontend/AST/ASTVisitor.h"

namespace ola::ir
{
	struct AST;
	class IRContext;
	class IRModule;

	class IRVisitor : public ASTVisitor
	{
		friend class IRGen;

	public:

		IRVisitor(IRContext& context, IRModule& module);
		void VisitAST(AST const* ast);


	private:
		IRContext& context;
		IRModule& module;
	};
}