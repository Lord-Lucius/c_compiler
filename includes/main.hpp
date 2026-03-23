/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 09:53:31 by luluzuri          #+#    #+#             */
/*   Updated: 2026/03/23 21:14:24 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>
#include <string>
#include <vector>

#pragma region Exception
class CustomException : public std::exception {
	protected:
		std::string _message;

	public:
		CustomException(const std::string &msg) : _message("Error: " + msg) {}

		const char *what() const noexcept override { return _message.c_str(); }
};

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
#pragma endregion

#pragma region Lexer
struct Token {
		std::string value;
		std::string type;
};

std::vector<Token> tokenizer(const std::string &code);
#pragma endregion

#pragma region Parser
struct AST {};

void Parser(void);
#pragma endregion