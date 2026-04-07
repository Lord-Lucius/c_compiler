/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:51:48 by luluzuri          #+#    #+#             */
/*   Updated: 2026/04/07 23:05:55 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <optional>
#include <string>
#include <vector>

enum class Keyword { RETURN, IF, ELSE, WHILE, FOR, VOID, INT, FLOAT, CHAR, STATIC };

/* NEED ADDING BITWISE LATER AND SHIFTING */
enum class Operator { PLUS, MINUS, STAR, SLASH, PERCENT, ASSIGN, EQUAL_EQUAL, NOT_EQUAL, LESS, LESS_EQUAL, GREATER, GREATER_EQUAL, AND, OR, NOT, PLUS_EQUAL, MINUS_EQUAL, STAR_EQUAL, SLASH_EQUAL, PERCENT_EQUAL };

enum class Punctuation { LEFT_BRACKET, RIGHT_BRACKET, LEFT_PAREN, RIGHT_PAREN, LEFT_CROCHET, RIGHT_CROCHET, SEMICOLON };

enum class Literal { FLOAT, INTEGER, CHAR, STRING };

enum class TokenType { Keyword, Operator, Identifier, Literal, Punctuation };

struct Token {
		TokenType TYPE;
		std::string value;

		std::optional<Keyword> keyword = std::nullopt;
		std::optional<Operator> oper = std::nullopt;
		std::optional<Literal> lit = std::nullopt;
		std::optional<Punctuation> punc = std::nullopt;

		Token() {}
		Token(TokenType type, const std::string &val): TYPE(type), value(val) { }
		Token(TokenType type, const std::string &val, Keyword k): TYPE(type), value(val), keyword(k) { }
		Token(TokenType type, const std::string &val, Operator o): TYPE(type), value(val), oper(o) { }
		Token(TokenType type, const std::string &val, Literal l): TYPE(type), value(val), lit(l) { }
		Token(TokenType type, const std::string &val, Punctuation p): TYPE(type), value(val), punc(p) { }
};

class Lexer {
	private:
		std::string _source;
		int _cursor;
		int _size;
		char _current;
		std::vector<Token *> _tokens;

		std::string createWord(void);
		bool singleOperator(char word_char);
		bool doubleOperator(const std::string &word);

	public:
		Lexer(std::string &sourceCode);
		~Lexer(void);
		void checkAndSkip(void);
		char advance_cursor(void);
		char peek(int offset = 0);
		bool tokenizeKeyword(const std::string &word);
		bool tokenizeIdentifier(const std::string &word);
		bool tokenizeOperator(const std::string &word);
		bool tokenizeLiteral(const std::string &word);
		bool tokenizePunctuation(const std::string &word);
		std::vector<Token *> &tokenize(void);
		void freeTokens(void);

		// GETTER / SETTER
		std::vector<Token *> getTokens(void);

		// Exception
/*		class NoneAlphaCharacterException : public CustomException {
			public:
				NoneAlphaCharacterException()
					: CustomException("First character is not alpha") {}
		};

		class UnrecognizedCharacterException : public CustomException {
			public:
				UnrecognizedCharacterException()
					: CustomException("Unrecognized character") {}
		};

		class EmptyFileException : public CustomException {
			public:
				EmptyFileException() : CustomException("Empty file detected") {}
		};*/
};

// DEBUG
std::string tokenTypeToString(TokenType type);
