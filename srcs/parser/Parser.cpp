/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 01:35:55 by luluzuri          #+#    #+#             */
/*   Updated: 2026/04/11 20:25:27 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "Lexer.hpp"
#include "Exceptions.hpp"
#include <cstddef>
#include <vector>

/* STARTING PARSING IN BRANCH */
Token *Parser::peek(void) {
	if (isAtEnd())
		return nullptr;
	return _tokens[_current];
}

Token *Parser::advance(void) {
	if (!isAtEnd())
		_current++;
	return (previous());
}

Token *Parser::previous(void) {
	return _tokens[_current - 1];
}

bool Parser::isAtEnd(void) {
	return (_current >= _tokens.size());
}

bool Parser::check(TokenType type) {
	return (_tokens[_current]->TYPE == type);
}

bool Parser::check(Keyword kw) {
	if (!check(TokenType::Keyword))
		return (false);
	return (peek()->keyword.value() == kw);
}

bool Parser::check(Operator op) {
	if (!check(TokenType::Operator))
		return (false);
	return (peek()->oper.value() == op);
}

bool Parser::check(Literal lit) {
	if (!check(TokenType::Literal))
		return (false);
	return (peek()->lit.value() == lit);
}

bool Parser::check(Punctuation punc) {
	if (!check(TokenType::Punctuation))
		return (false);
	return (peek()->punc.value() == punc);
}

bool Parser::match(TokenType type) {
	if (check(type)) {
		advance();
		return (true);
	}
	return (false);
}

bool Parser::match(Keyword kw) {
	if (check(kw)) {
		advance();
		return (true);
	}
	return (false);
}

bool Parser::match(Operator op) {
	if (check(op)) {
		advance();
		return (true);
	}
	return (false);
}

bool Parser::match(Literal lit) {
	if (check(lit)) {
		advance();
		return (true);
	}
	return (false);
}

bool Parser::match(Punctuation punc) {
	if (check(punc)) {
		advance();
		return (true);
	}
	return (false);
}

Token *Parser::expect(TokenType type, const std::string &msg) {
	if (check(type)) {
		return (advance());
	}
	throw UnexpectedTokenException(msg);
}

Token *Parser::expect(Keyword kw, const std::string &msg) {
	if (check(kw)) {
		return (advance());
	}
	throw UnexpectedTokenException(msg);
}

Token *Parser::expect(Literal lit, const std::string &msg) {
	if (check(lit)) {
		return (advance());
	}
	throw UnexpectedTokenException(msg);
}

Token *Parser::expect(Punctuation punc, const std::string &msg) {
	if (check(punc)) {
		return (advance());
	}
	throw UnexpectedTokenException(msg);
}

Program *Parser::parseProgram(void) {
	Program *p = new Program();

	while (!isAtEnd()) {
		Function *func = parseFunction();
		p->addFunction(func);
	}
	return (p);
}

Function *Parser::parseFunction(void) {
	Type *return_type = parseType();
	std::string name = expect(TokenType::Identifier, "Expected function name")->value;
	expect(Punctuation::LEFT_PAREN, "Expected '(' and didn't found it");
	std::vector<Parameter *> parameters;
	if (!check(Punctuation::RIGHT_PAREN)) {
		do {
			Parameter *param = parseParameter();
			parameters.push_back(param);
		} while (match(Punctuation::RIGHT_PAREN));
	}
	expect(Punctuation::RIGHT_PAREN, "Expected ')'");
	Block *body = parseBlock();

	return (new Function(return_type, name, parameters, body));
}

Parameter *Parser::parseParameter(void) {
	Type *type = parseType();
	Token *token_name = expect(TokenType::Identifier, "Expected parameter name");
	std::string name = token_name->value;
	return (new Parameter(type, name));
}

Type *Parser::parseType(void) {
	if (check(Keyword::INT)) {
		advance();
		return (new Type("int"));
	} else if (check(Keyword::VOID)) {
		advance();
		return (new Type("void"));
	} else if (check(Keyword::FLOAT)) {
		advance();
		return (new Type("float"));
	} else if (check(Keyword::CHAR)) {
		advance();
		return (new Type("char"));
	}
	throw InvalidTypeException("Expected type");
}

Block *Parser::parseBlock(void) {
	std::vector<Statement *> statements;
	expect(Punctuation::LEFT_BRACKET, "Expected '{'");
	while (!check(Punctuation::RIGHT_BRACKET) && !isAtEnd()) {
		Statement *s = parseStatement();
		statements.push_back(s);
	}
	expect(Punctuation::RIGHT_BRACKET, "Expected '}'");
	return (new Block(statements));
}

Statement *Parser::parseStatement(void) {
	if (check(Keyword::RETURN))
		return (parseReturn());
	else if (check(Keyword::IF))
		return (parseIf());
	else if (check(Keyword::WHILE))
		return (parseWhile());
	else if (check(Punctuation::LEFT_BRACKET))
		return (parseBlock());
	else if (check(Keyword::INT) || check(Keyword::FLOAT) || check(Keyword::CHAR))
		return (parseVarDecl());
	else if (check(TokenType::Identifier))
		return (parseExprStmt());
	throw ParserException("Expected statement");
}

Statement *Parser::parseReturn(void) {
	expect(Keyword::RETURN, "Expected 'retur'");
	Expression *expr = parseExpression();
	expect(Punctuation::SEMICOLON, "Expected ';' after return");
	return (new Return(expr));
}

