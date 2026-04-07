/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 01:35:55 by luluzuri          #+#    #+#             */
/*   Updated: 2026/04/07 23:16:17 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "Lexer.hpp"
#include "Exceptions.hpp"
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

bool Parser::check(enum TokenType type) {
	if (isAtEnd())
		return (false);
	return (peek()->TYPE == type);
}

bool Parser::match(enum TokenType type) {
	if (check(type)) {
		advance();
		return (true);
	}
	return (false);
}

Token *Parser::expect(TokenType type, const std::string &message) {
	if (check(type))
		return advance();
	throw UnexpectedTokenException(message);
}

bool Parser::isAtEnd(void) { return (_current == _tokens.size()); }

// Parse function part
Program *Parser::parseProgram(void) {
	Program *p = new Program();
	while (!isAtEnd()) {
		p->addFunction(parseFunction());
	}
	return (p);
}
