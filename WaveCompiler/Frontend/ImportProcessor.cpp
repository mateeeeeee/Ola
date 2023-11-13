#include <filesystem>
#include <functional>
#include "ImportProcessor.h"
#include "Diagnostics.h"
#include "SourceBuffer.h"
#include "Lexer.h"
#include "Parser.h"
#include "AST.h"
#include "autogen/WaveConfig.h"


namespace fs = std::filesystem;

namespace wave
{
	char const* ImportProcessor::wave_extension = ".wv";
	char const* ImportProcessor::wave_lib_path = WAVE_COMPILER_PATH;

	ImportProcessor::ImportProcessor(Diagnostics& diagnostics) : diagnostics(diagnostics) {}

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
				std::string import_name(current_token->GetIdentifier());
				import_path /= import_name;
				++current_token;
			} while (Consume(TokenKind::period));
			Expect(TokenKind::semicolon);
			TokenPtr end_token = current_token;
			for (; start_token != end_token; ++start_token) start_token->SetFlag(TokenFlag_PartOfImportDirective);

			import_path += wave_extension;
			if (!fs::exists(import_path))
			{
				import_path = fs::path(wave_lib_path) / import_path;
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
			if (!token.IsOneOf(TokenKind::comment, TokenKind::newline, TokenKind::KW_import) 
			 && !token.HasFlag(TokenFlag_PartOfImportDirective))
				preprocessed_tokens.push_back(token);
		}
		std::swap(preprocessed_tokens, tokens);
	}

	std::vector<Token> ImportProcessor::GetImportTokens(std::string_view import_path)
	{
		//#todo: cache intermediate results of this process
		SourceBuffer import_src_buffer(import_path);
		Lexer lex(diagnostics);
		lex.Lex(import_src_buffer);
		std::vector<Token> imported_tokens = lex.GetTokens();

		ImportProcessor import_processor(diagnostics);
		import_processor.RemoveImports(std::move(imported_tokens));
		imported_tokens = import_processor.GetProcessedTokens();

		Parser parser(diagnostics);
		parser.Parse(imported_tokens);
		AST const* ast = parser.GetAST();

		std::vector<Decl const*> global_public_decls;
		for (auto const& decl : ast->translation_unit->GetDecls())
		{
			if (decl->IsPublic() || decl->IsExtern()) global_public_decls.push_back(decl.get());
		}

		std::vector<Token> import_tokens{};
		std::function<void(QualifiedType const& type, std::vector<Token>& tokens)> TypeToTokens
			= [&TypeToTokens](QualifiedType const& type, std::vector<Token>& tokens)
			{
				if (type.IsConst()) tokens.emplace_back(TokenKind::KW_const);
				switch (type->GetKind())
				{
				case TypeKind::Void:
					tokens.emplace_back(TokenKind::KW_void); break;
				case TypeKind::Bool:
					tokens.emplace_back(TokenKind::KW_bool); break;
				case TypeKind::Char:
					tokens.emplace_back(TokenKind::KW_char); break;
				case TypeKind::Int:
					tokens.emplace_back(TokenKind::KW_int); break;
				case TypeKind::Float:
					tokens.emplace_back(TokenKind::KW_float); break;
				case TypeKind::Array:
				{
					ArrayType const& arr_type = type_cast<ArrayType>(type);
					TypeToTokens(arr_type.GetBaseType(), tokens);
					tokens.emplace_back(TokenKind::left_square);
					tokens.emplace_back(TokenKind::right_square);
				}
				break;
				case TypeKind::Function: 
				case TypeKind::Class:
				case TypeKind::Invalid:
				default:
					WAVE_ASSERT(false);
					break;
				}
			};
		for (Decl const* decl : global_public_decls)
		{
			import_tokens.emplace_back(TokenKind::KW_extern);
			if (FunctionDecl const* func_decl = dynamic_ast_cast<FunctionDecl>(decl))
			{
				FunctionType const& func_type = type_cast<FunctionType>(func_decl->GetType());
				TypeToTokens(func_type.GetReturnType(), import_tokens);
				Token& tok = import_tokens.emplace_back(TokenKind::identifier);
				tok.SetIdentifier(func_decl->GetName());
				import_tokens.emplace_back(TokenKind::left_round);
				std::span<FunctionParameter const> func_params = func_type.GetParameters();
				for (auto const& param : func_params)
				{
					TypeToTokens(param.type, import_tokens);
					import_tokens.emplace_back(TokenKind::comma);
				}
				if(!func_params.empty()) import_tokens.pop_back();
				import_tokens.emplace_back(TokenKind::right_round);
				import_tokens.emplace_back(TokenKind::semicolon);
			}
			else if (VariableDecl const* var_decl = dynamic_ast_cast<VariableDecl>(decl))
			{
				TypeToTokens(var_decl->GetType(), import_tokens);
				Token& tok = import_tokens.emplace_back(TokenKind::identifier);
				tok.SetIdentifier(var_decl->GetName());
				import_tokens.emplace_back(TokenKind::semicolon);
			}
			else WAVE_ASSERT(false);
		}

		return import_tokens;
	}
}

