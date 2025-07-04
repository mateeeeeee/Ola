#pragma once
#include <vector>
#include "Token.h"


namespace ola
{
	class FrontendContext;
	class Diagnostics;

	class ImportProcessor
	{
		using TokenPtr = std::vector<Token>::iterator;
	public:
		ImportProcessor(FrontendContext* context, Diagnostics& diagnostics);
		void ProcessImports(std::vector<Token>&& tokens);
		void RemoveImports(std::vector<Token>&& tokens);
		std::vector<Token> GetProcessedTokens() const
		{
			return tokens;
		}

	private:
		FrontendContext* context;
		Diagnostics& diagnostics;
		std::vector<Token> tokens;
		TokenPtr current_token;

	private:
		Bool Consume(TokenKind k);
		Bool Expect(TokenKind k);

		void PreFilterTokens();
		void PostFilterTokens();

		std::vector<Token> GetImportTokens(std::string_view import_path);

	};
}