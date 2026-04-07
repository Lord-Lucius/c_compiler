/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:49:31 by luluzuri          #+#    #+#             */
/*   Updated: 2026/04/07 23:11:58 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"
#include "Exceptions.hpp"
#include <cctype>
#include <cstddef>
#include <cstring>
#include <sstream>

Lexer::Lexer(std::string &sourceCode) {
	_source = sourceCode;
	_cursor = 0;
	_size = sourceCode.length();
	_current = sourceCode.at(_cursor);
}

Lexer::~Lexer(void) {
	for (Token *t : _tokens)
		delete t;
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

char Lexer::peek(int offset) {
	if (_cursor + offset < _size)
		return (_source[_cursor + offset]);
	else
		return ('\0');
}

void Lexer::checkAndSkip(void) {
	while (std::isspace(_current))
		advance_cursor();
}

bool Lexer::tokenizeKeyword(const std::string &word) {
	if (word.length() <= 1)
		return (false);

	if (word == "return") {
		_tokens.push_back(new Token(TokenType::Keyword, word, Keyword::RETURN));
		return (true);
	} else if (word == "if") {
		_tokens.push_back(new Token(TokenType::Keyword, word, Keyword::IF));
		return (true);
	} else if (word == "else") {
		_tokens.push_back(new Token(TokenType::Keyword, word, Keyword::ELSE));
		return (true);
	} else if (word == "while") {
		_tokens.push_back(new Token(TokenType::Keyword, word, Keyword::WHILE));
		return (true);
	} else if (word == "for") {
		_tokens.push_back(new Token(TokenType::Keyword, word, Keyword::FOR));
		return (true);
	} else if (word == "void") {
		_tokens.push_back(new Token(TokenType::Keyword, word, Keyword::VOID));
		return (true);
	} else if (word == "int") {
		_tokens.push_back(new Token(TokenType::Keyword, word, Keyword::INT));
		return (true);
	} else if (word == "float") {
		_tokens.push_back(new Token(TokenType::Keyword, word, Keyword::FLOAT));
		return (true);
	} else if (word == "char") {
		_tokens.push_back(new Token(TokenType::Keyword, word, Keyword::CHAR));
		return (true);
	} else if (word == "static") {
		_tokens.push_back(new Token(TokenType::Keyword, word, Keyword::STATIC));
		return (true);
	}
	return (false);
}

bool Lexer::tokenizeIdentifier(const std::string &word) {
	if (word.empty())
		return (false);
	
	if (!std::isalpha(word[0]) && word[0] != '_')
		return (false);

	for (char c : word) {
		if (!std::isalnum(c) && c != '_')
			return (false);
	}

	_tokens.push_back(new Token(TokenType::Identifier, word));
	return (true);
}

bool Lexer::singleOperator(char word_char) {
	switch (word_char) {
	case '+':
		_tokens.push_back(new Token(TokenType::Operator,
									std::string(1, word_char), Operator::PLUS));
		return (true);
	case '-':
		_tokens.push_back(new Token(
			TokenType::Operator, std::string(1, word_char), Operator::MINUS));
		return (true);
	case '*':
		_tokens.push_back(new Token(TokenType::Operator,
									std::string(1, word_char), Operator::STAR));
		return (true);
	case '/':
		_tokens.push_back(new Token(
			TokenType::Operator, std::string(1, word_char), Operator::SLASH));
		return (true);
	case '%':
		_tokens.push_back(new Token(
			TokenType::Operator, std::string(1, word_char), Operator::PERCENT));
		return (true);
	case '=':
		_tokens.push_back(new Token(
			TokenType::Operator, std::string(1, word_char), Operator::ASSIGN));
		return (true);
	case '!':
		_tokens.push_back(new Token(TokenType::Operator,
									std::string(1, word_char), Operator::NOT));
		return (true);
	case '<':
		_tokens.push_back(new Token(TokenType::Operator,
									std::string(1, word_char), Operator::LESS));
		return (true);
	case '>':
		_tokens.push_back(new Token(
			TokenType::Operator, std::string(1, word_char), Operator::GREATER));
		return (true);
	default:
		return (false);
	}
}

bool Lexer::doubleOperator(const std::string &word) {
	if (word == "==") {
		_tokens.push_back(
			new Token(TokenType::Operator, word, Operator::EQUAL_EQUAL));
		return (true);
	} else if (word == "!=") {
		_tokens.push_back(
			new Token(TokenType::Operator, word, Operator::NOT_EQUAL));
		return (true);
	} else if (word == "<=") {
		_tokens.push_back(
			new Token(TokenType::Operator, word, Operator::LESS_EQUAL));
		return (true);
	} else if (word == ">=") {
		_tokens.push_back(
			new Token(TokenType::Operator, word, Operator::GREATER_EQUAL));
		return (true);
	} else if (word == "&&") {
		_tokens.push_back(new Token(TokenType::Operator, word, Operator::AND));
		return (true);
	} else if (word == "||") {
		_tokens.push_back(new Token(TokenType::Operator, word, Operator::OR));
		return (true);
	}
	return (false);
}

bool Lexer::tokenizeOperator(const std::string &word) {
	if (word.length() < 1 || word.length() > 2)
		return (false);

	bool succeed;
	if (word.length() == 1)
		succeed = singleOperator(word[0]);
	else
		succeed = doubleOperator(word);
	return (succeed);
}

bool Lexer::tokenizeLiteral(const std::string &word) {
    if (word.empty())
        return (false);

    char first = word[0];
    char last = word[word.length() - 1];

    if (std::isdigit(first)) {
        if (word.find('.') != std::string::npos) {
            _tokens.push_back(new Token(TokenType::Literal, word, Literal::FLOAT));
        } else {
            _tokens.push_back(new Token(TokenType::Literal, word, Literal::INTEGER));
        }
        return (true);
    }

    if (first == '\'' && last == '\'') {
        _tokens.push_back(new Token(TokenType::Literal, word, Literal::CHAR));
        return (true);
    }

    if (first == '"' && last == '"') {
        _tokens.push_back(new Token(TokenType::Literal, word, Literal::STRING));
        return (true);
    }

    return (false);
}

bool Lexer::tokenizePunctuation(const std::string &word) {

	if (word.length() < 1 || word.length() > 2)
		return (false);

	switch (word[0]) {
	case '{':
		_tokens.push_back(new Token(TokenType::Punctuation,
									std::string(1, word[0]),
									Punctuation::LEFT_BRACKET));
		return (true);
	case '}':
		_tokens.push_back(new Token(TokenType::Punctuation,
									std::string(1, word[0]),
									Punctuation::RIGHT_BRACKET));
		return (true);
	case '[':
		_tokens.push_back(new Token(TokenType::Punctuation,
									std::string(1, word[0]),
									Punctuation::LEFT_CROCHET));
		return (true);
	case ']':
		_tokens.push_back(new Token(TokenType::Punctuation,
									std::string(1, word[0]),
									Punctuation::RIGHT_CROCHET));
		return (true);
	case '(':
		_tokens.push_back(new Token(TokenType::Punctuation,
									std::string(1, word[0]),
									Punctuation::LEFT_PAREN));
		return (true);
	case ')':
		_tokens.push_back(new Token(TokenType::Punctuation,
									std::string(1, word[0]),
									Punctuation::RIGHT_PAREN));
		return (true);
	case ';':
		_tokens.push_back(new Token(TokenType::Punctuation,
									std::string(1, word[0]),
									Punctuation::SEMICOLON));
		return (true);
	default:
		return (false);
	}
}

std::string Lexer::createWord(void) {
	std::stringstream buffer;
	std::string punctuation = "{}[]();,";
	std::string operators = "+-*/<>=!%";

	if (_current == '\0') {
		return ("");
	}

	if (std::isalpha(_current) || _current == '_') {
		while ((std::isalpha(_current) || std::isdigit(_current) ||
				_current == '_') &&
			   _current != '\0' && !std::isspace(_current)) {
			buffer << advance_cursor();
		}
		return (buffer.str());
	}

	if (std::isdigit(_current)) {
		while (std::isdigit(_current) && _current != '\0' &&
			   !std::isspace(_current)) {
			buffer << advance_cursor();
		}
		if (_current == '.' && std::isdigit(peek(1))) {
			buffer << advance_cursor();
			while (std::isdigit(_current) && _current != '\0' &&
				   !std::isspace(_current)) {
				buffer << advance_cursor();
			}
		}
		return (buffer.str());
	}

	if (punctuation.find(_current) != std::string::npos) {
		buffer << advance_cursor();
		return (buffer.str());
	}

	if (operators.find(_current) != std::string::npos) {
		buffer << advance_cursor();

		if ((_current == '=' || _current == '&' || _current == '|') &&
			(buffer.str() == "=" || buffer.str() == "!" ||
			 buffer.str() == "<" || buffer.str() == ">" ||
			 buffer.str() == "&" || buffer.str() == "|")) {
			buffer << advance_cursor();
		} else if (_current == '=' &&
				   (buffer.str() == "+" || buffer.str() == "-" ||
					buffer.str() == "*" || buffer.str() == "/" ||
					buffer.str() == "%")) {
			buffer << advance_cursor();
		}

		return (buffer.str());
	}

	if (_current == '\'') {
		buffer << advance_cursor();

		if (_current == '\\') {
			buffer << advance_cursor();
			if (_current != '\0') {
				buffer << advance_cursor();
			}
		} else {
			buffer << advance_cursor();
		}

		if (_current == '\'') {
			buffer << advance_cursor();
		} else {
			throw UnexpectedCharacterException("[ERROR] Unrecognized character: " + buffer.str());
		}

		return (buffer.str());
	}

	if (_current == '"') {
		buffer << advance_cursor();

		while (_current != '"' && _current != '\0') {
			if (_current == '\\') {
				buffer << advance_cursor();
				if (_current != '\0') {
					buffer << advance_cursor();
				}
			} else {
				buffer << advance_cursor();
			}
		}

		if (_current == '"') {
			buffer << advance_cursor();
		} else {
			throw UnexpectedCharacterException("[ERROR] Unrecognized character: " + buffer.str());
		}

		return (buffer.str());
	}

	throw UnexpectedCharacterException("[ERROR] Unrecognized character: " + buffer.str());
}

std::vector<Token *> &Lexer::tokenize() {
	bool notEof = true;
	std::string word = "";

	if (_source.empty())
		throw EmptyFileException("[ERROR] Empty file detected");

	while (_cursor < _size && notEof) {
		checkAndSkip();
		
		if (_current == '\0')
			break;

		word.clear();
		word = createWord();
		
		if (word.empty())
			break;

		if (tokenizeKeyword(word)) {
			continue;
		} else if (tokenizeIdentifier(word)) {
			continue;
		} else if (tokenizeLiteral(word)) {
			continue;
		} else if (tokenizePunctuation(word)) {
			continue;
		} else {
			throw UnexpectedCharacterException("[ERROR] Unrecognized character: " + word);
		}
	}
	return (_tokens);
}

std::vector<Token *> Lexer::getTokens(void) { return (_tokens); }

// DEBUG
std::string tokenTypeToString(TokenType type) {
	switch (type) {
	case TokenType::Keyword:
		return "KEYWORD";
	case TokenType::Operator:
		return "OPERATOR";
	case TokenType::Punctuation:
		return "PUNCTUATION";
	case TokenType::Identifier:
		return "IDENTIFIER";
	case TokenType::Literal:
		return "LITERAL";
	default:
		return "UNKNOWN";
	}
}