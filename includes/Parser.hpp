#pragma once

#include <string>
#include <vector>

#include "Lexer.hpp"

class ASTNode {
public:
    virtual ~ASTNode(void) {}
};

class Expression : public ASTNode {
public:
    ~Expression(void) override {}
};

class Statement : public ASTNode {
public:
    ~Statement(void) override {}
};

class Type : public ASTNode {
private:
    std::string _name;

public:
    Type(const std::string &name) : _name(name) {}
    ~Type(void) override {}

    std::string getName(void) const { return _name; }
};

class Identifier : public Expression {
private:
    std::string _name;

public:
    Identifier(const std::string &n) : _name(n) {}
    std::string getName(void) const { return _name; }
};

class Constant : public Expression {
private:
    int _value;

public:
    Constant(int val) : _value(val) {}
    int getValue(void) const { return _value; }
};

class BinOp : public Expression {
private:
    Expression *_left;
    std::string _op;
    Expression *_right;

public:
    BinOp(Expression *l, const std::string &op, Expression *r)
        : _left(l), _op(op), _right(r) {}

    Expression *getLeft(void) const { return _left; }
    std::string getOp(void) const { return _op; }
    Expression *getRight(void) const { return _right; }
};

class UnaryOp : public Expression {
private:
    std::string _op;
    Expression *_expr;

public:
    UnaryOp(const std::string &op, Expression *expr)
        : _op(op), _expr(expr) {}

    std::string getOp(void) const { return _op; }
    Expression *getExpr(void) const { return _expr; }
};

class Assignment : public Expression {
private:
    std::string _name;
    Expression *_value;

public:
    Assignment(const std::string &name, Expression *val)
        : _name(name), _value(val) {}

    std::string getName(void) const { return _name; }
    Expression *getValue(void) const { return _value; }
};

class Return : public Statement {
private:
    Expression *_value;

public:
    Return(Expression *val) : _value(val) {}
    Expression *getValue(void) const { return _value; }
};

class Block : public Statement {
private:
    std::vector<Statement *> _statements;

public:
    Block(const std::vector<Statement *> &stmts) : _statements(stmts) {}

    std::vector<Statement *> getStatements(void) const { return _statements; }
};

class If : public Statement {
private:
    Expression *_condition;
    Statement *_thenBranch;
    Statement *_elseBranch;

public:
    If(Expression *cond, Statement *thenB, Statement *elseB)
        : _condition(cond), _thenBranch(thenB), _elseBranch(elseB) {}

    Expression *getCondition(void) const { return _condition; }
    Statement *getThen(void) const { return _thenBranch; }
    Statement *getElse(void) const { return _elseBranch; }
};

class While : public Statement {
private:
    Expression *_condition;
    Statement *_body;

public:
    While(Expression *cond, Statement *body)
        : _condition(cond), _body(body) {}

    Expression *getCondition(void) const { return _condition; }
    Statement *getBody(void) const { return _body; }
};

class VarDecl : public Statement {
private:
    Type *_type;
    std::string _name;
    Expression *_init;

public:
    VarDecl(Type *t, const std::string &n, Expression *init = nullptr)
        : _type(t), _name(n), _init(init) {}

    Type *getType(void) const { return _type; }
    std::string getName(void) const { return _name; }
    Expression *getInit(void) const { return _init; }
};

class ExprStmt : public Statement {
private:
    Expression *_expr;

public:
    ExprStmt(Expression *expr) : _expr(expr) {}
    Expression *getExpr(void) const { return _expr; }
};

class Parameter {
private:
    Type *_type;
    std::string _name;

public:
    Parameter(Type *type, const std::string &name)
        : _type(type), _name(name) {}

    Type *getType(void) const { return _type; }
    std::string getName(void) const { return _name; }
};

class Function {
private:
    Type *_return_type;
    std::string _name;
    std::vector<Parameter *> _parameters;
    Block *_body;

public:
    Function(Type *rt, const std::string &n,
             const std::vector<Parameter *> &params,
             Block *body)
        : _return_type(rt), _name(n), _parameters(params), _body(body) {}

    Type *getReturnType(void) const { return _return_type; }
    std::string getName(void) const { return _name; }
    std::vector<Parameter *> getParameters(void) const { return _parameters; }
    Block *getBody(void) const { return _body; }
};

class Program {
private:
    std::vector<Function *> _functions;

public:
    void addFunction(Function *f) { _functions.push_back(f); }
    std::vector<Function *> getFunctions(void) const { return _functions; }
};

class Parser {
private:
    std::vector<Token *> _tokens;
    int _current = 0;

    Token *peek(void);
    Token *advance(void);
    Token *previous(void);
    bool isAtEnd(void);

    bool check(TokenType type);
    bool check(Keyword kw);
    bool check(Operator op);
    bool check(Literal lit);
    bool check(Punctuation p);

    bool match(TokenType type);
    bool match(Keyword kw);
    bool match(Operator op);
    bool match(Literal lit);
    bool match(Punctuation p);

    Token *expect(TokenType type, const std::string &msg);
    Token *expect(Keyword kw, const std::string &msg);
    Token *expect(Literal lit, const std::string &msg);
    Token *expect(Punctuation p, const std::string &msg);

    Program *parseProgram(void);
    Function *parseFunction(void);
    Parameter *parseParameter(void);
    Type *parseType(void);

    Block *parseBlock(void);
    Statement *parseStatement(void);
    Statement *parseReturn(void);
    Statement *parseIf(void);
    Statement *parseWhile(void);
    Statement *parseVarDecl(void);
    Statement *parseExprStmt(void);

    Expression *parseExpression(void);
    Expression *parseAssignment(void);
    Expression *parseEquality(void);
    Expression *parseComparison(void);
    Expression *parseTerm(void);
    Expression *parseFactor(void);
    Expression *parseUnary(void);
    Expression *parsePrimary(void);

public:
    Parser(const std::vector<Token *> &tokens) : _tokens(tokens) {}

    Program *parse(void) {
        return parseProgram();
    }
};