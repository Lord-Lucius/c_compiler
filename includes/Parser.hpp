/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:37 by luluzuri          #+#    #+#             */
/*   Updated: 2026/03/31 23:58:09 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

#include "Lexer.hpp"

#pragma region DefaultClasses
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
#pragma endregion

#pragma region ASTClasses

// Expression
class Identifier : public Expression {
	private:
		std::string _name;
	public:
		Identifier(std::string &n) : _name(n) {}
		// GETTER
		std::string getName(void) { return (_name); }
};

class BinOp : public Expression {
	private:
		Expression *_left;
		std::string _op;
		Expression *_right;
	public:
		BinOp(Expression *left, std::string &op, Expression *right) : _left(left), _op(op), _right(right) { }

		// GETTER
		Expression *getLeft(void) { return (_left); }
		std::string getOp(void) { return (_op); }
		Expression *getRight(void) { return (_right); }
};

class Constant : public Expression {
	private:
		int _value;
	public:
		Constant(int &val) : _value(val) { }
		//GETTER
		int getValue(void) { return (_value); }
};

// Statements
class Return : public Statement {
	private:
		Expression *_value;
	public:
		Return(Expression *val) : _value(val) { }

		// GETTER
		Expression *getValue(void) { return (_value); }
};

class Block : public Statement {
	private:
		std::vector<Statement *> _functions;
	public:
		std::vector<Statement *> getFunctions(void) { return (_functions); }
};

// TOP Level
class Function {
	private:
		std::string _return_type;
		std::string _name;
		std::vector<Statement *> _body;
	public:
		Function(std::string &rt, const std::string &n, const std::vector<Statement *> &b) : _return_type(rt), _name(n), _body(b) { }

		// GETTER
		std::string getReturnType(void) { return (_return_type); }
		std::string getName(void) { return (_name); }
		std::vector<Statement *> getBody(void) { return (_body); }
};

class Program {
	private:
		std::vector<Function *> _functions;
	public:
		std::vector<Function *> getFunctions(void) { return (_functions); }
};

#pragma endregion


#pragma region ParserClass
class Parser {
	private:
		Program *_program;
		std::vector<Token *> _tokens;
		int _current = 0;

		Token *peek(void);
		Token *advance(void);
		Token *previous(void);
		bool match(enum type type);

		bool check(enum type type);
		void except(enum type type, const std::string &message);
		bool isAtEnd(void);

		// Parse fonctions
		Program* parseProgram(void);
		Function* parseFunction(void);
		std::string parseType(void);
		Statement* parseStatement(void);
		Expression* parseExpression(void);
		Expression* parseTerm(void);
		Expression* parseFactor(void);

	public:
		Parser(std::vector<Token *> tokens) : _tokens(tokens) { }
		Program *parse(void) { return (_program); };
	
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
#pragma endregion
