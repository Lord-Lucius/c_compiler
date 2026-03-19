# C Compiler in C++

A from-scratch C compiler implementation written in C++ following the **"Writing a C Compiler"** book. This project focuses on understanding compiler architecture through practical implementation of each compilation phase.

## 🎯 Project Overview

This compiler translates C source code into machine-executable code by implementing the fundamental phases of compilation:

1. **Lexical Analysis (Lexer)** — Tokenize source code
2. **Syntax Analysis (Parser)** — Build Abstract Syntax Tree (AST)
3. **Semantic Analysis** — Type checking & validation
4. **Code Generation (Codegen)** — Emit assembly or executable

## 🛠️ Building

### Prerequisites
- C++17 or higher
- `clang++` or `g++`
- GNU Make

### Compile
```bash
make          # Build the compiler
make re       # Clean and rebuild
make clean    # Remove build artifacts
```

The Makefile automatically detects all `.cpp` and `.hpp` files and compiles them with a progress bar.

## 📁 Project Structure (Not Final Version)

```
c_compiler/
├── includes/
│   ├── lexer/
│   │   └── lexer.hpp          # Tokenizer interface
│   └── parser/
│       └── parser.hpp          # Parser interface
├── srcs/
│   ├── lexer/
│   │   └── lexer.cpp           # Tokenization implementation
│   └── parser/
│       └── parser.cpp          # Parsing implementation
├── tests/
│   └── return_2.c              # Test C programs
├── main.cpp                    # Entry point
├── Makefile                    # Build configuration
├── .clangd                     # Clangd LSP configuration
└── README.md                   # This file
```

## 🚀 Usage

```bash
./c_compiler <input.c>
```

### Example (To Modify)
```bash
./c_compiler tests/return_2.c
# Output:
# In if condition: int
# In if condition: return
```

## 📖 Learning Resources

This project follows **"Writing a C Compiler"** by Nora Sandler:
- Official book: https://nostarch.com/writing-c-compiler
- Companion code: https://github.com/nlsandler/writing-a-c-compiler

Additional references:
- [Crafting Interpreters](https://craftinginterpreters.com/) — Parser design patterns
- [cppreference](https://en.cppreference.com/) — C++ standard library
- [Regex patterns for tokenization](https://regex101.com/) — Pattern testing (locally)

## 🔧 Technical Decisions

### Language: C++
Chosen for:
- Existing familiarity with the language
- Rich Standard Template Library (`std::vector`, `std::map`, `std::regex`)
- Zero-cost abstractions for performance
- Strong type system for AST representation

### Architecture
- **Modular design**: Each phase (lexer, parser, codegen) is independent
- **Single responsibility**: Each component has one job
- **Testable**: Each phase can be unit tested in isolation

## 📄 License

This project is for educational purposes. It follows the structure and exercises from "Writing a C Compiler" by Nora Sandler.

## 👤 Author

**Luluzuri (Lord-Lucius)** — 42 student, learning compiler design from first principles.

---

**Last Updated**: March 2026  
**Status**: Early development — Lexer phase active