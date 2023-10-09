#pragma once

namespace wave
{
	struct AST;

	class ICodegen
	{
	public:
		virtual ~ICodegen() = default;
		virtual void Generate(AST* ast) = 0;
	};
}