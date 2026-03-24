/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NewLexer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:49:31 by luluzuri          #+#    #+#             */
/*   Updated: 2026/03/24 22:32:20 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"
#include <iostream>
#include <cctype>
#include <sstream>

Lexer::Lexer(std::string &sourceCode) {
	_source = sourceCode;
	_cursor = 0;
	_size = sourceCode.length();
	_current = sourceCode.at(_cursor);
}

char Lexer::advance_cursor(void) {
	if (_cursor < _size) {
		char tmp = _current;
		_cursor++;
		_current = (_cursor < _size) ? _source[_cursor] : '\0';
		return (tmp);
	}
	return ('\0');
}

char Lexer::peak(int offset) {
	if (_cursor + offset < _size)
		return (_source[_cursor + offset]);
	else
		return ('\0');
}

void Lexer::checkAndSkip(void) {
	while (std::isspace(_current))
		advance_cursor();
}

Token *Lexer::tokenizeID(void) {
	std::stringstream buffer;

	buffer << advance_cursor();

	while (std::isalnum(_current) || _current == '_') {
		buffer << advance_cursor();
	}

	Token *new_token = new Token();

	new_token->TYPE = TOKEN_ID;
	new_token->value = buffer.str();
	return (new_token);
}

Token *Lexer::tokenizeINT(void) {
	std::stringstream buffer;

	while (std::isdigit(_current)) {
		buffer << advance_cursor();
	}
	Token *newToken = new Token();
	newToken->TYPE = TOKEN_INT;
	newToken->value = buffer.str();

	return (newToken);
}

Token *Lexer::tokenizeSPECIAL(enum type TYPE) {
	Token *newToken = new Token();
	newToken->TYPE = TYPE;
	newToken->value = advance_cursor();

	return (newToken);
}

void Lexer::handleSpecials(void) {
	switch (_current) {
		case ';': {
			_tokens.push_back(tokenizeSPECIAL(TOKEN_SEMICOLON));
			break;
		}
		case '(': {
			_tokens.push_back(tokenizeSPECIAL(TOKEN_LEFT_PARENTHESE));
			break;
		}
		case ')': {
			_tokens.push_back(tokenizeSPECIAL(TOKEN_RIGHT_PARENTHESE));
			break;
		}
		case '{': {
			_tokens.push_back(tokenizeSPECIAL(TOKEN_LEFT_BRACKET));
			break;
		}
		case '}': {
			_tokens.push_back(tokenizeSPECIAL(TOKEN_RIGHT_BRACKET));
			break;
		}
		case '[': {
			_tokens.push_back(tokenizeSPECIAL(TOKEN_LEFT_CROCHET));
			break;
		}
		case ']': {
			_tokens.push_back(tokenizeSPECIAL(TOKEN_RIGHT_CROCHET));
			break;
		}
		default:
			throw UnrecognizedCharacterException();
	}
}

std::vector<Token *> Lexer::tokenize() {
	bool notEof = true;
	while (_cursor < _size && notEof) {
		checkAndSkip();
		if (std::isalpha(_current) || _current == '_') {
			_tokens.push_back(tokenizeID());
			continue;
		}

		if (std::isdigit(_current)) {
			_tokens.push_back(tokenizeINT());
			continue;
		}

		handleSpecials();
	}
	return (_tokens);
}