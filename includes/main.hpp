/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 09:53:31 by luluzuri          #+#    #+#             */
/*   Updated: 2026/03/24 22:17:46 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>
#include <string>

#pragma region Exception
class CustomException : public std::exception {
	protected:
		std::string _message;

	public:
		CustomException(const std::string &msg) : _message("Error: " + msg) {}

		const char *what() const noexcept override { return _message.c_str(); }
};
#pragma endregion

//#pragma region Lexer
//struct Token {
//		std::string value;
//		std::string type;
//};

//class Lexer {
//	private:
//		std::vector<Token> __tokens;
//		std::vector<std::string> _wordsOutOfCode;
//		std::vector<std::string> split_string(const std::string &code);

//	public:
//		Lexer(const std::string &code);
//		~Lexer(void);

//		// Utils
//		std::vector<Token> getTokenVector();

//		// Exception
//		class NoneAlphaCharacterException : public CustomException {
//			public:
//				NoneAlphaCharacterException()
//					: CustomException("First character is not alpha") {}
//		};

//		class UnrecognizedCharacterException : public CustomException {
//			public:
//				UnrecognizedCharacterException()
//					: CustomException("Unrecognized character") {}
//		};
//};
//#pragma endregion

//#pragma region Parser
//class Expression {
//	public:
//		virtual ~Expression() = default;
//};

//class NumberExpression : public Expression {
//	private:
//		int _value;

//	public:
//		NumberExpression(int &val) : _value(val) {}
//};

//class Function {
//	private:
//		std::unique_ptr<Expression> _body;

//	public:
//		Function(std::unique_ptr<Expression> &body) : _body(std::move(body)) {};
//};

//class Program {
//	private:
//		std::vector<Function> _body;

//	public:
//		Program(std::vector<Token> &_tokens);
//};

//class Parser {
//	private:
//	protected:
//	public:
//		Parser(std::vector<Token> &_tokens);
//		~Parser(void);
//};

//void Parser(void);
//#pragma endregion