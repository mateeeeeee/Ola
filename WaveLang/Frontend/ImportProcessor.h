#pragma once
#include <vector>
#include "Token.h"

namespace wave
{
	class Diagnostics;

	class ImportProcessor
	{
		using TokenPtr = std::vector<Token>::iterator;
		inline static char const* import_extension = ".wvi";
	public:
		explicit ImportProcessor(Diagnostics& diagnostics);

		void Process(std::vector<Token>&& tokens);

		std::vector<Token>&& GetProcessedTokens()  
		{
			return std::move(tokens);
		}

	private:
		Diagnostics& diagnostics;
		std::vector<Token> tokens;
		TokenPtr current_token;

	private:
		bool Consume(TokenKind k);
		bool Expect(TokenKind k);

		void PreFilterTokens();
		void PostFilterTokens();

		bool VerifyImportTokens(std::vector<Token> const&);
	};
}