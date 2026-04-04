/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 01:35:55 by luluzuri          #+#    #+#             */
/*   Updated: 2026/04/02 00:24:44 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "Lexer.hpp"
#include <cstddef>

/* STARTING PARSING IN BRANCH */
/* Need to do a plan of ASDL and AST that i want use for the parsing */

Token *Parser::peek(void) { return (_tokens[_current]); }

Token *Parser::advance(void) {
	Token *tmp = _tokens[_current];
	_current++;
	return (tmp);
}

Token *Parser::previous(void) { return (_tokens[_current - 1]); }

bool Parser::check(enum keyword type) {
	if (isAtEnd())
		return (false);
	return (peek()->TYPE == type);
}

bool Parser::match(enum keyword type) {
	if (!check(type))
		return (false);
	advance();
	return (true);
}

void Parser::except(enum keyword type, const std::string &message) {
	if (!check(type))
		throw UnMatchedTypeException(message);
	advance();
}

bool Parser::isAtEnd(void) { return (_current == _tokens.size()); }

// Parse function part
Program *Parser::parseProgram(void) {
	_program = new Program();
	while (!isAtEnd()) {
		_program->addFunction(parseFunction());
	}
	return (_program);
}

Function *Parser::parseFunction(void) {
	if (check(TOKEN_KEYWORD)) {
		except(TOKEN_KEYWORD, "Wrong keyword");
	}
	return nullptr;
}

// Program
void Program::addFunction(Function *func) { _functions.push_back(func); }
