#include "Parser.hpp"

/* STARTING PARSING IN BRANCH */
/* Need to do a plan of ASDL and AST that i want use for the parsing */

Token *Parser::peek(void) {
	return (_tokens[_current]);
}

Token *Parser::advance(void) {
	Token *tmp = _tokens[_current];
	_current++;
	return (tmp);
}

Token *Parser::previous(void) {
	return (_tokens[_current - 1]);
}

bool Parser::check(enum type type) {
	if (isAtEnd())
		return (false);
	return (peek()->TYPE == type);
}

bool Parser::match(enum type type) {
	if (!check(type))
		return (false);
	advance();
	return (true);
}

void Parser::except(enum type type, const std::string &message) {
	if (!check(type))
		throw UnMatchedTypeException(message);
	advance();
}

bool Parser::isAtEnd(void) {
	return (_current == _tokens.size());
}

// Parse function part
Program *Parser::parseProgram(void) {
	if (isAtEnd())
		return (_program);
}
