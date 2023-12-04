#pragma once
#include <vector>
#include "Token.h"


namespace ola
{
	class Diagnostics;

	class ImportProcessor
	{
		using TokenPtr = std::vector<Token>::iterator;
		static char const* ola_extension; 
		static char const* ola_lib_path; 

	public:
		explicit ImportProcessor(Diagnostics& diagnostics);
		void ProcessImports(std::vector<Token>&& tokens);
		void RemoveImports(std::vector<Token>&& tokens);
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

		std::vector<Token> GetImportTokens(std::string_view import_path);

	};
}