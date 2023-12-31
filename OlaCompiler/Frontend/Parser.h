#pragma once
#include <vector>
#include <memory>
#include "Token.h"
#include "AST/ASTAliases.h"

namespace ola
{
	class QualType;
	class Sema;
	class Context;
	class Parser;
	class Diagnostics;
	
	enum DiagCode : uint32;
	enum class BinaryExprKind : uint8;
	enum class DeclVisibility : uint8;
	using ExprParseFn = UniqueExprPtr(Parser::*)();

	class Parser
	{
		using TokenPtr = std::vector<Token>::iterator;
	public:

		Parser(Context* context, Diagnostics& diagnostics);
		~Parser();

		void Parse(std::vector<Token>&& tokens);
		void ParseImported(std::vector<Token> const& tokens);
		AST const* GetAST() const { return ast.get(); }

	private:
		Context* context;
		Diagnostics& diagnostics;
		std::vector<Token> tokens;
		TokenPtr current_token;

		std::unique_ptr<Sema> sema;
		std::unique_ptr<AST> ast;

	private:
		bool Consume(TokenKind k);
		template<typename... Ts>
		bool Consume(TokenKind k, Ts... ts);
		bool Expect(TokenKind k);
		template<typename... Ts>
		bool Expect(TokenKind k, Ts... ts);
		void Diag(DiagCode);
		template<typename... Ts>
		void Diag(DiagCode code, Ts&&... args);

		void ParseTranslationUnit();
		void AddBuiltinDecls(UniqueTranslationUnitPtr& TU);

		OLA_NODISCARD UniqueDeclPtrList ParseGlobalDeclaration();
		OLA_NODISCARD UniqueFunctionDeclPtr ParseFunctionDeclaration();
		OLA_NODISCARD UniqueFunctionDeclPtr ParseFunctionDefinition(DeclVisibility visibility);
		OLA_NODISCARD UniqueMethodDeclPtr ParseMethodDefinition(bool first_pass);
		OLA_NODISCARD UniqueConstructorDeclPtr ParseConstructorDefinition(bool first_pass);
		OLA_NODISCARD UniqueParamVarDeclPtr ParseParamVariableDeclaration();
		OLA_NODISCARD UniqueVarDeclPtrList ParseVariableDeclaration(DeclVisibility visibility);
		OLA_NODISCARD UniqueFieldDeclPtrList ParseFieldDeclaration(bool first_pass);
		OLA_NODISCARD UniqueDeclPtrList ParseExternVariableDeclaration();
		OLA_NODISCARD UniqueEnumDeclPtr ParseEnumDeclaration();
		OLA_NODISCARD UniqueAliasDeclPtr ParseAliasDeclaration();
		OLA_NODISCARD UniqueClassDeclPtr ParseClassDeclaration();

		OLA_NODISCARD UniqueStmtPtr ParseStatement();
		OLA_NODISCARD UniqueCompoundStmtPtr ParseCompoundStatement();
		OLA_NODISCARD UniqueExprStmtPtr ParseExpressionStatement();
		OLA_NODISCARD UniqueReturnStmtPtr ParseReturnStatement();
		OLA_NODISCARD UniqueIfStmtPtr ParseIfStatement();
		OLA_NODISCARD UniqueBreakStmtPtr ParseBreakStatement();
		OLA_NODISCARD UniqueContinueStmtPtr ParseContinueStatement();
		OLA_NODISCARD UniqueForStmtPtr ParseForStatement();
		OLA_NODISCARD UniqueForStmtPtr ParseForeachStatement();
		OLA_NODISCARD UniqueWhileStmtPtr ParseWhileStatement();
		OLA_NODISCARD UniqueDoWhileStmtPtr ParseDoWhileStatement();
		OLA_NODISCARD UniqueCaseStmtPtr ParseCaseStatement();
		OLA_NODISCARD UniqueSwitchStmtPtr ParseSwitchStatement();
		OLA_NODISCARD UniqueGotoStmtPtr ParseGotoStatement();
		OLA_NODISCARD UniqueLabelStmtPtr ParseLabelStatement();

		template<ExprParseFn ParseFn, TokenKind token_kind, BinaryExprKind op_kind>
		OLA_NODISCARD UniqueExprPtr ParseBinaryExpression();
		OLA_NODISCARD UniqueExprPtr ParseExpression();
		OLA_NODISCARD UniqueExprPtr ParseParenthesizedExpression();
		OLA_NODISCARD UniqueExprPtr ParseAssignmentExpression();
		OLA_NODISCARD UniqueExprPtr ParseConditionalExpression();
		OLA_NODISCARD UniqueExprPtr ParseLogicalOrExpression();
		OLA_NODISCARD UniqueExprPtr ParseLogicalAndExpression();
		OLA_NODISCARD UniqueExprPtr ParseInclusiveOrExpression();
		OLA_NODISCARD UniqueExprPtr ParseExclusiveOrExpression();
		OLA_NODISCARD UniqueExprPtr ParseAndExpression();
		OLA_NODISCARD UniqueExprPtr ParseEqualityExpression();
		OLA_NODISCARD UniqueExprPtr ParseRelationalExpression();
		OLA_NODISCARD UniqueExprPtr ParseShiftExpression();
		OLA_NODISCARD UniqueExprPtr ParseAdditiveExpression();
		OLA_NODISCARD UniqueExprPtr ParseMultiplicativeExpression();
		OLA_NODISCARD UniqueExprPtr ParseUnaryExpression();
		OLA_NODISCARD UniqueExprPtr ParsePostFixExpression();
		OLA_NODISCARD UniqueExprPtr ParsePrimaryExpression();
		OLA_NODISCARD UniqueIntLiteralPtr ParseSizeofExpression();
		OLA_NODISCARD UniqueIntLiteralPtr ParseLengthExpression();
		OLA_NODISCARD UniqueIntLiteralPtr ParseConstantInt();
		OLA_NODISCARD UniqueCharLiteralPtr ParseConstantChar();
		OLA_NODISCARD UniqueStringLiteralPtr ParseConstantString();
		OLA_NODISCARD UniqueBoolLiteralPtr ParseConstantBool();
		OLA_NODISCARD UniqueFloatLiteralPtr ParseConstantFloat();
		OLA_NODISCARD UniqueExprPtr ParseIdentifier();
		OLA_NODISCARD UniqueThisExprPtr ParseThisExpression();
		OLA_NODISCARD UniqueSuperExprPtr ParseSuperExpression();
		OLA_NODISCARD UniqueIdentifierExprPtr ParseMemberIdentifier();
		OLA_NODISCARD UniqueInitializerListExprPtr ParseInitializerListExpression();

		void ParseFunctionAttributes(uint8& attrs);
		void ParseMethodAttributes(uint8& attrs);
		void ParseTypeQualifier(QualType& type);
		void ParseTypeSpecifier(QualType& type, bool array_size_forbidden = false, bool allow_ref = true);

		bool IsFunctionDeclaration();
		bool IsCurrentTokenTypename();
	};

}