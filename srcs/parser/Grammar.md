# Definition of the accepted C grammar

### Basic grammar for PART 1 of `Writing a C compiler`
```bnf
<program> ::= <function>*
<function> ::= <type> <identifier> LPAREN <parameter> RPAREN LBRACE <statement>* RBRACE
<type> ::= INT | VOID
<statement> ::= RETURN <expression> SEMICOLON
<expression> ::= <term> ((PLUS | MINUS) <term>)*
<term> ::= <factor> ((STAR | SLASH) <factor>)*
<factor> ::= NUMBER | IDENTIFIER | LPAREN <expression> RPAREN
```