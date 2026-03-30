/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:37 by luluzuri          #+#    #+#             */
/*   Updated: 2026/03/30 12:14:07 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

#include "Lexer.hpp"

// Base classes
class ASTNode {
	public:
		virtual ~ASTNode(void);
};

class Expression : public ASTNode {
	public:
		~Expression(void);
};

class Statement : public ASTNode {
	public:
		~Statement(void);
};

class Type : public ASTNode {
	public:
		~Type(void);
};


// Inheritance classes
class BinOp : public Expression {
	private:
		Expression *_left;
		std::string _op;
		Expression *_right;
	public:
		BinOp *parseBinOp(std::vector<Token *> tokens);
};

class Constant : public Expression {
	private:
		int _value;
	public:
		Constant *parseConstant(std::vector<Token *> tokens);
};

class Return : public Statement {
	public:
		Expression *_value;
	private:
		Return *parseReturn(std::vector<Token *> tokens);
};

class Block : public Statement {
	private:
		std::vector<Statement *> _functions;
	public:
		Block *parseBlock(std::vector<Token *> tokens);
};

class Function {
	private:
		std::string _name;
		std::string _return_type;
		std::vector<Statement *> _body;
	public:
		Function *parseFunction(std::vector<Token *> tokens);
};

class Program {
	private:
		std::vector<Function *> _functions;
	public:
		Program *parseProgram(std::vector<Token *> tokens);
};


// Parser
class Parser {
	private:
		std::vector<Token *> _tokens;
		int _current = 0;

		Token *peak(void);
		Token *advance(void);
		Token *previous(void);
		bool match(enum type type);

		bool check(enum type type);
		void except(enum type type, const std::string &message);
		bool isAtEnd(void);

	public:
		Program *parse(std::vector<Token *> &tokens);
	
		// Exceptions
		class UnMatchedTypeException : public CustomException {
			public:
				UnMatchedTypeException(const std::string &msg) : CustomException(msg) {}
		};

		class EmptyBodyNotAllowedException : public CustomException {
			public:
				EmptyBodyNotAllowedException() : CustomException("Error: An empty body is not allowed.") { }
		};
};
