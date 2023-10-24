#include <filesystem>
#include "ImportProcessor.h"
#include "Diagnostics.h"
#include "SourceBuffer.h"
#include "Lexer.h"
#include "Parser.h"
#include "AST.h"

namespace fs = std::filesystem;

namespace wave
{
	namespace std_imports
	{
		static const std::string std_io = R"(
			extern void PrintInteger(int);
			extern void PrintFloat(float);
		)";
		static const std::string std_util = R"(
			extern void Assert(bool);
		)";
		static const std::string std_math = R"(
			extern int Sin(float);
			extern int Cos(float);
			extern int Tan(float);
		)";
	}

	ImportProcessor::ImportProcessor(Diagnostics& diagnostics) : diagnostics(diagnostics) {}

	void ImportProcessor::Process(std::vector<Token>&& _tokens)
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
				std::string import_name(current_token->GetIdentifier());
				import_path /= import_name;
				++current_token;
			} while (Consume(TokenKind::period));
			Expect(TokenKind::semicolon);
			TokenPtr end_token = current_token;
			for (; start_token != end_token; ++start_token) start_token->SetFlag(TokenFlag_PartOfImportDirective);

			import_path += import_extension;
			if (!fs::exists(import_path)) diagnostics.Report(current_token->GetLocation(), invalid_import_path);
			
			SourceBuffer import_src_buffer(import_path.string());
			Lexer lex(diagnostics);
			lex.Lex(import_src_buffer);

			std::vector<Token> imported_tokens = lex.GetTokens();
			TokenPtr first_inserted = tokens.insert(current_token, imported_tokens.begin(), imported_tokens.end() - 1);
			current_token = first_inserted + imported_tokens.size() - 1;
		}

		PostFilterTokens();
	}

	bool ImportProcessor::Consume(TokenKind k)
	{
		if (current_token->Is(k))
		{
			++current_token; return true;
		}
		else return false;
	}

	bool ImportProcessor::Expect(TokenKind k)
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
			if (!token.Is(TokenKind::KW_import) && !token.HasFlag(TokenFlag_PartOfImportDirective))
				preprocessed_tokens.push_back(token);
		}
		std::swap(preprocessed_tokens, tokens);
	}

	bool ImportProcessor::VerifyImportTokens(std::vector<Token> const& import_tokens)
	{
		Parser parser(diagnostics);
		parser.Parse(import_tokens);
		UniqueDeclPtrList const& decls = parser.GetAST()->translation_unit->GetDecls();

		for (auto const& decl : decls) 
		{
			if (decl->GetDeclKind() != DeclKind::Function) return false;
			FunctionDecl const* func_decl = ast_cast<FunctionDecl>(decl.get());
			if (func_decl->HasDefinition()) return false;
		}

		return true;
	}

}

