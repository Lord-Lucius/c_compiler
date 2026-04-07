/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 23:04:44 by luluzuri          #+#    #+#             */
/*   Updated: 2026/04/07 23:11:44 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>
#include <string>

class CompilerException : public std::exception {
	protected:
		std::string _message;

	public:
		CompilerException(const std::string &msg) : _message(msg) {}

		virtual const char *what() const noexcept { return _message.c_str(); }
};

class LexerException : public CompilerException {
	public:
		LexerException(const std::string &msg) : CompilerException(msg) {}
};

class UnexpectedCharacterException : public LexerException {
	public:
		UnexpectedCharacterException(const std::string &msg)
			: LexerException(msg) {}
};

class EmptyFileException : public LexerException {
	public:
		EmptyFileException(const std::string &msg) : LexerException(msg) {}
};

class ParserException : public CompilerException {
	public:
		ParserException(const std::string &msg) : CompilerException(msg) {}
};

class UnexpectedTokenException : public ParserException {
	public:
		UnexpectedTokenException(const std::string &msg)
			: ParserException(msg) {}
};

class InvalidTypeException : public ParserException {
	public:
		InvalidTypeException(const std::string &msg) : ParserException(msg) {}
};

class InvalidExpressionException : public ParserException {
	public:
		InvalidExpressionException(const std::string &msg)
			: ParserException(msg) {}
};

class EmptyBodyException : public ParserException {
	public:
		EmptyBodyException()
			: ParserException("Error: Empty body not allowed.") {}
};

class SemanticException : public CompilerException {
	public:
		SemanticException(const std::string &msg) : CompilerException(msg) {}
};

class UndeclaredVariableException : public SemanticException {
	public:
		UndeclaredVariableException(const std::string &msg)
			: SemanticException(msg) {}
};

class TypeMismatchException : public SemanticException {
	public:
		TypeMismatchException(const std::string &msg)
			: SemanticException(msg) {}
};
