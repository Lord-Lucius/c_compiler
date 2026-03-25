/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:51:48 by luluzuri          #+#    #+#             */
/*   Updated: 2026/03/25 17:00:05 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

enum type {
	TOKEN_ID,
	TOKEN_KEYWORD,
	TOKEN_IDENTIFIER,
	TOKEN_INT,
	TOKEN_SEMICOLON,
	TOKEN_LEFT_BRACKET,
	TOKEN_RIGHT_BRACKET,
	TOKEN_LEFT_PARENTHESE,
	TOKEN_RIGHT_PARENTHESE,
	TOKEN_LEFT_CROCHET,
	TOKEN_RIGHT_CROCHET
};

struct Token {
		enum type TYPE;
		std::string value;
};

class CustomException : public std::exception {
	protected:
		std::string _message;

	public:
		CustomException(const std::string &msg) : _message("Error: " + msg) {}

		const char *what() const noexcept override { return _message.c_str(); }
};

class Lexer {
	private:
		std::string _source;
		int _cursor;
		int _size;
		char _current;
		std::vector<Token *> _tokens;

	public:
		Lexer(std::string &sourceCode);
		void checkAndSkip(void);
		char advance_cursor(void);
		char peak(int offset = 0);
		Token *tokenizeID(void);
		Token *tokenizeINT(void);
		Token *tokenizeSPECIAL(enum type);
		bool handleSpecials(void);
		std::vector<Token *> tokenize(void);

		// GETTER / SETTER
		std::vector<Token *> getTokens(void);

		// Exception
		class NoneAlphaCharacterException : public CustomException {
			public:
				NoneAlphaCharacterException()
					: CustomException("First character is not alpha") {}
		};

		class UnrecognizedCharacterException : public CustomException {
			public:
				UnrecognizedCharacterException()
					: CustomException("Unrecognized character") {}
		};
};
