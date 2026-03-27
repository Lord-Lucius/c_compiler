# Definition of the AST for c_compiler for PART 1 of `Writing a C compiler`

### Basic AST
```AST
program = Program(function* functions)

function = Function(type return_type, identifier name, statement* Body)

statement	=	Return(expr value)
			|	Block(statement* statement)

expr	=	Constant(int value)
		|	BinOp(expr left, binop op, expr right)
		|	Identifier(identifier name)


type = INT | VOID


binop = Plus | Minus | Star | Slash
unop = Minus | Not
```

### Classes Needed

```C++

// Base classes
class ASTNode {};
class Expression : public ASTNode {};
class Statement : public ASTNode {};
class Type : public ASTNode {};

// Inheritance classes
class BinOp : public Expression {
	Expression* left;
	std::string op;
	Expression *right;
};

class Constant : public Expression {
	int value;
};

// variantes
class Return : public Statement {
	Expression* value;
};

class Block : public Statement {
	std::vector<Statement*> statements;
};

// Root
class Program {
	std::vector<Functions *> functions;
};

```

### Parser class
```C++

class Parser {
	private:
		std::vector<Token *> tokens;
		int current = 0;

		Token *peek();
		Token *advance();
		bool match(enum type t);

		bool check(enum type t);
		void expect(enum type t, const std::string &msg);

	public:
		Program *parse(std::vector<Token *> &tokens);
};

```