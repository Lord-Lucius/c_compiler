# 🔨 C Compiler

**Building a fully functional C compiler from scratch in C++**

> *"In the end, we only regret the chances we didn't take." — Musashi Miyamoto*

---

## 📋 Overview

This project implements a **complete C compiler** following the principles outlined in *Writing a C Compiler*. Starting from raw source code, the compiler produces executable x86-64 machine code through a series of well-defined phases.

**Language:** C++  
**Status:** 🚀 In Progress
**Difficulty:** ⭐⭐⭐⭐⭐ (Expert)

---

## 🎯 Project Goals

- ✅ Lexical analysis (tokenization)
- ✅ Parsing (syntax analysis → AST)
- ✅ Semantic analysis (type checking, validation)
- ✅ Code generation (x86-64 assembly)
- ✅ Optimization techniques
- ✅ Unit testing per phase
- 🔄 Handle edge cases & error reporting

---

## 🏗️ Compiler Phases

### Phase 1️⃣: **Lexical Analysis (Lexer)**
Converts raw source code into _tokens.

```
Input:  int main() { return 42; }
Output: [INT] [IDENT:main] [LPAREN] [RPAREN] [LBRACE] 
        [RETURN] [INT:42] [SEMICOLON] [RBRACE]
```

**Key Tasks:**
- Tokenization with lookahead
- Whitespace & comment handling
- String literal parsing
- Keyword recognition

### Phase 2️⃣: **Syntax Analysis (Parser)**
Builds an Abstract Syntax Tree (AST) from _tokens.

```
_tokens → Parser → AST
         ↓
    Grammar Rules
    Recursive Descent
```

**Key Tasks:**
- Recursive descent parsing
- Precedence handling
- Error recovery
- AST node construction

### Phase 3️⃣: **Semantic Analysis**
Validates the AST and gathers semantic information.

**Key Tasks:**
- Type checking
- Symbol table management
- Scope resolution
- Variable declaration tracking
- Function signature validation

### Phase 4️⃣: **Code Generation (Codegen)**
Transforms AST into x86-64 assembly.

```
AST → Code Generator → Assembly
                    ↓
                x86-64 Instructions
                Stack Management
                Register Allocation
```

**Key Tasks:**
- Instruction selection
- Register allocation
- Stack frame management
- Function prologue/epilogue
- Call convention handling

### Phase 5️⃣: **Assembly & Linking**
Produces final executable.

```
Assembly → Assembler (as) → Object File (.o)
                         ↓
                      Linker (ld) → Executable
```

---

## 🛠️ Architecture

### 📁 Project Structure
```
TODO
```

### 🔄 Data Flow
```
C Source Code
     ↓
  ┌─────────────────────┐
  │   LEXICAL ANALYSIS  │
  │   (Lexer)          │
  └────────┬────────────┘
           ↓
      Token Stream
           ↓
  ┌─────────────────────┐
  │  SYNTAX ANALYSIS    │
  │   (Parser)         │
  └────────┬────────────┘
           ↓
    Abstract Syntax Tree
           ↓
  ┌─────────────────────┐
  │ SEMANTIC ANALYSIS   │
  │  (Type Checking)   │
  └────────┬────────────┘
           ↓
   Validated AST
           ↓
  ┌─────────────────────┐
  │  CODE GENERATION    │
  │  (x86-64 Codegen)  │
  └────────┬────────────┘
           ↓
    Assembly Code (.s)
           ↓
  ┌─────────────────────┐
  │ ASSEMBLY & LINKING  │
  │  (as, ld)          │
  └────────┬────────────┘
           ↓
      Executable Binary
```

---

## 🚀 How to Use

### Compilation
```bash
# Build the compiler
make

# Clean object files
make clean

# Full rebuild
make re
```

### Using the Compiler
```bash
# Compile a C file
./c_compiler input.c -o output

# Run the output
./output

# Verbose mode (see assembly)
./c_compiler input.c -o output -S
```

### Example Program
```c
// simple.c
int main(void) {
    int x = 5;
    int y = 10;
    return x + y;
}
```

```bash
$ ./c_compiler simple.c -o simple
$ ./simple
$ echo $?  # Output: 15
```

---

## 💡 Features Implemented

### ✅ Supported C Features
- [x] Integer types (int, char, long)
- [x] Arithmetic operators (+, -, *, /, %)
- [x] Comparison operators (<, >, ==, !=, <=, >=)
- [x] Logical operators (&&, ||, !)
- [x] Variable declarations & assignments
- [x] Function declarations & definitions
- [x] Function calls & return statements
- [x] if/else conditionals
- [x] while loops
- [x] for loops
- [x] break/continue statements
- [x] Block scoping
- [x] Comments (// and /* */)

### 🔄 In Progress
- [ ] Arrays
- [ ] Pointers
- [ ] Structs
- [ ] Bitwise operators
- [ ] Switch statements
- [ ] Ternary operator

### 📋 Not Yet Implemented
- [ ] Floating point types
- [ ] String literals (proper support)
- [ ] Preprocessor directives
- [ ] Macros
- [ ] Unions
- [ ] Enums

---

### Common Issues & Solutions

| Issue | Solution |
|-------|----------|
| Segfault in parser | Check token lookahead bounds |
| Type mismatch error | Verify symbol table scope |
| Wrong assembly output | Debug codegen with `--print-asm` |
| Linker errors | Ensure function declarations |

---

## 📚 Resources & References

### The Bible
- **Writing a C Compiler** — Jack Crenshaw
- **Crafting Interpreters** — Robert Nystrom
- **Dragon Book** — Aho, Lam, Sethi, Ullman

### Standards
- **C11 Standard** — ISO/IEC 9899:2011
- **x86-64 ABI** — System V AMD64 calling convention
- **GCC Assembly Syntax** — AT&T format

### Tools
```bash
# Disassemble generated code
objdump -d output

# Check assembly syntax
as -o test.o test.s

# Link object files
ld -o executable test.o
```

---

## 🛠️ Tech Stack

![C++](https://img.shields.io/badge/-C%2B%2B-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)
![GCC](https://img.shields.io/badge/-GCC-A42E2B?style=flat-square&logo=gcc&logoColor=white)
![GDB](https://img.shields.io/badge/-GDB-FF6B6B?style=flat-square&logoColor=white)
![Make](https://img.shields.io/badge/-Make-427819?style=flat-square&logoColor=white)
![x86-64](https://img.shields.io/badge/-x86--64-FF6B00?style=flat-square&logoColor=white)

---

## 💻 Sample Output

### Input Program
```c
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main(void) {
    return factorial(5);
}
```

### Generated Assembly (excerpt)
```asm
.globl factorial
factorial:
    push %rbp
    mov %rsp, %rbp
    sub $16, %rsp
    mov %rdi, -8(%rbp)      # n = rdi
    
    mov -8(%rbp), %rax
    cmp $1, %rax
    jg .L1
    
    mov $1, %rax
    jmp .L2
    
.L1:
    mov -8(%rbp), %rax
    sub $1, %rax
    mov %rax, %rdi
    call factorial
    mov -8(%rbp), %rbx
    imul %rbx, %rax
    
.L2:
    leave
    ret
```

### Execution
```bash
$ ./c_compiler factorial.c -o factorial
$ ./factorial
$ echo $?  # Output: 120 (5! = 120)
```

---

## 🎓 Progress Tracker

```
Lexer:        ████████████████████ 100% ✅
Parser:       ████████████████████ 100% ✅
Semantic:     ██████████░░░░░░░░░░  50% 🔄
Codegen:      ████████░░░░░░░░░░░░  40% 🔄
Optimization: ░░░░░░░░░░░░░░░░░░░░   0% 📋
```

---

## 📞 References

- Lexer inspiration: [Crafting Interpreters](https://craftinginterpreters.com/)
- Parser design: [Recursive Descent Parsing](https://en.wikibooks.org/wiki/Compiler_Construction)
- x86-64: [System V AMD64 ABI](https://www.uclibc.org/docs/psABI-x86_64.pdf)
- GCC internals: [GCC Development](https://gcc.gnu.org/develop.html)

---

**Made in my personnal cave**
