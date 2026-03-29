#include "Parser.hpp"

/* STARTING PARSING IN BRANCH */
/* Need to do a plan of ASDL and AST that i want use for the parsing */

Token *Parser::peak(void) {
	return (_tokens[_current]);
}

Token *Parser::advance(void) {
	_current++;
	return (_tokens[_current]);
}

Token *Parser::previous(void) {
	_current--;
	return (_tokens[_current]);
}

bool Parser::match(enum type type) {
	return ((type == _tokens[_current]->TYPE) ? true : false);
}

bool Parser::check(enum type type) {
	int tmp = _current;
	_current++;
	return (match(type));
}

void Parser::except(enum type type, const std::string &message) {
	if (check(type))
		throw UnMatchedTypeException(message);
}

bool Parser::isAtEnd(void) {
	return (_current == _tokens.size());
}
