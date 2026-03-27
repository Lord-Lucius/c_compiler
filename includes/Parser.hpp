/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:37 by luluzuri          #+#    #+#             */
/*   Updated: 2026/03/27 17:25:29 by luluzuri         ###   ########.fr       */
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
};

class Constant : public Expression {
	private:
		int _value;
};

class Return : public Statement {
	Expression *_value;
};

class Block : public Statement {
	private:
		std::vector<Statement *> _functions;
};

class Function {
	private:
		std::string _name;
		std::string _return_type;
		std::vector<Statement *> _body;
};

class Program {
	private:
		std::vector<Function *> _functions;
};


// Parser
class Parser {
	private:
		std::vector<Token *> _token;
		int _current = 0;

		Token *peak(void);
		Token *advance(void);
		bool match(enum type type);

		bool check(enum type type);
		void except(enum type type, const std::string &message);

	public:
		Program *parse(std::vector<Token *> &tokens);
};
