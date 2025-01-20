#include <filesystem>
#include <functional>
#include "ImportProcessor.h"
#include "Diagnostics.h"
#include "SourceBuffer.h"
#include "Lexer.h"
#include "Parser.h"
#include "AST/AST.h"
#include "autogen/OlaConfig.h"


namespace fs = std::filesystem;

namespace ola
{
	static constexpr Char const* ola_extension = ".ola";
	static constexpr Char const* ola_lib_path = OLA_LIB_PATH;

	ImportProcessor::ImportProcessor(FrontendContext* context, Diagnostics& diagnostics) : context(context), diagnostics(diagnostics) {}

	void ImportProcessor::ProcessImports(std::vector<Token>&& _tokens)
	{
		tokens = std::move(_tokens);
		PreFilterTokens();
		current_token = tokens.begin();
		while (Consume(TokenKind::KW_import))
		{
			TokenPtr start_token = current_token;
			fs::path import_path = "";
			do 
			{
				if (current_token->IsNot(TokenKind::identifier)) diagnostics.Report(current_token->GetLocation(), unexpected_token);
				std::string import_name(current_token->GetData());
				import_path /= import_name;
				++current_token;
			} while (Consume(TokenKind::period));
			Expect(TokenKind::semicolon);
			TokenPtr end_token = current_token;
			for (; start_token != end_token; ++start_token) start_token->SetFlag(TokenFlag_PartOfImportDirective);

			import_path += ola_extension;
			if (!fs::exists(import_path))
			{
				import_path = fs::path(ola_lib_path) / import_path;
				if (!fs::exists(import_path)) diagnostics.Report(current_token->GetLocation(), invalid_import_path);
			}
			
			std::vector<Token> import_tokens = GetImportTokens(import_path.string());

			TokenPtr first_inserted = tokens.insert(current_token, import_tokens.begin(), import_tokens.end());
			current_token = first_inserted + import_tokens.size();
		}
		PostFilterTokens();
	}

	void ImportProcessor::RemoveImports(std::vector<Token>&& _tokens)
	{
		tokens = std::move(_tokens);
		PreFilterTokens();
		current_token = tokens.begin();
		while (Consume(TokenKind::KW_import))
		{
			TokenPtr start_token = current_token;
			do
			{
				if (current_token->IsNot(TokenKind::identifier)) diagnostics.Report(current_token->GetLocation(), unexpected_token);
				++current_token;
			} while (Consume(TokenKind::period));
			Expect(TokenKind::semicolon);
			TokenPtr end_token = current_token;
			for (; start_token != end_token; ++start_token) start_token->SetFlag(TokenFlag_PartOfImportDirective);
		}
		PostFilterTokens();
	}

	Bool ImportProcessor::Consume(TokenKind k)
	{
		if (current_token->Is(k))
		{
			++current_token; return true;
		}
		else return false;
	}

	Bool ImportProcessor::Expect(TokenKind k)
	{
		if (!Consume(k))
		{
			diagnostics.Report(current_token->GetLocation(), unexpected_token);
			return false;
		}
		return true;
	}

	void ImportProcessor::PreFilterTokens()
	{
		std::vector<Token> preprocessed_tokens{};
		for (auto const& token : tokens)
		{
			if (!token.IsOneOf(TokenKind::comment, TokenKind::newline))
				preprocessed_tokens.push_back(token);
		}
		std::swap(preprocessed_tokens, tokens);
	}

	void ImportProcessor::PostFilterTokens()
	{
		std::vector<Token> preprocessed_tokens{};
		for (auto const& token : tokens)
		{
			if (!token.IsOneOf(TokenKind::comment, TokenKind::newline, TokenKind::KW_import) 
			 && !token.HasFlag(TokenFlag_PartOfImportDirective))
				preprocessed_tokens.push_back(token);
		}
		std::swap(preprocessed_tokens, tokens);
	}

	std::vector<Token> ImportProcessor::GetImportTokens(std::string_view import_path)
	{
		SourceBuffer import_src_buffer(import_path);
		Lexer lex(diagnostics);
		lex.Lex(import_src_buffer);
		std::vector<Token> imported_tokens = lex.GetTokens();

		ImportProcessor import_processor(context, diagnostics);
		import_processor.RemoveImports(std::move(imported_tokens));
		imported_tokens = import_processor.GetProcessedTokens();
		if (imported_tokens.back().GetKind() == TokenKind::eof)
		{
			imported_tokens.pop_back();
		}
		return imported_tokens;
	}
}

