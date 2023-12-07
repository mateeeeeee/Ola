<img align="left" src="OlaCompiler/olalogo.jpg" width="120px"/>

# Ola
Ola is a toy programming language with LLVM backend. 

## Dependencies
  * [LLVM 17.0.1](https://github.com/llvm/llvm-project) for compiler backend.
  * [spdlog](https://github.com/gabime/spdlog) for logging.
  * [CLI11](https://github.com/CLIUtils/CLI11) for command line parsing.

## Features
  * classes
	- access modifiers: `public`, `private`
	- single inheritance: `extends`
	- `this` and `super` keywords
  * reference type: `ref`
  * automatic type deduction: `auto`
  * operators:
    - additive: `+`, `-`, `+=`, `-=`, `++`, `--`
    - multiplicative: `*`, `/`, `%`, `*=`, `/=`, `%=`
    - relation: `==`, `!=`, `>`, `>=`, `<`, `<=`
    - shift: `>>`, `<<`, `>>=`, `<<=`
    - bitwise: `&`, `|`, `^`, `~`, `&=`, `|=`, `^=`
    - logic: `&&`, `||`, `!`
  * control statements: `if` `else`, `switch`, `goto`, `?:`
  * loop statements: `for`,`foreach`, `while`, `do` `while`, `break`, `continue`
  * enums
  * functions 
	- attributes: `inline` and `noinline`
  * arrays
  * `sizeof`, `length` operators
  * `alias`
  * strings
  * floats 
  * implicit casts
  * scopes
  * import statement
  * standard library

## Todo
  * object oriented constructs (wip)
      - virtual methods: `virtual`
      - interfaces: `implements`

## Structure
Ola consists of three parts: 
1. __Ola library__ - standard library for Ola language implemented in C and built as static library to be used by the compiler.  Currently it contains 4 files: olaio.h, olamath.h, olaassert.h, olastring.h.
2. __Ola compiler__ - consists of the following parts:
   * __Lexer__ - turns source file into a sequence of tokens
   * __Import Processor__ - receives tokens from previous phase and processes import statements. 
   * __Parser__ - recursive descent parser that receives processed tokens and constructs Abstract Syntax Tree (AST) of a translation unit. 
   * __Sema__ - does semantic analysis of a translation unit. 
   * __LLVM Visitor__ - traverses AST and emits LLVM IR.
   * __LLVM Optimizer__ - applies optimizations to the generated LLVM IR produced by LLVM Visitor based on the optimization level used.
4. __Ola tests__
   * UnitTest framework for testing existing Ola features. Uses GoogleTest.


## Usage
### Command line options
  * -h,--help: Print this help message and exit
  * --astdump: Dump AST to output/log
  * --testdebug: Print debug information during tests
  * --test : used for running g-tests
  * --Od : No optimizations
  * --O0 : Same as --Od
  * --O1 : Optimize
  * --O2 : Optimize more
  * --O3 : Optimize even more
  * -i ... : Input files
  * -o     : Output file
  * --directory : Directory of project files
  * --simple : input code in the form of a string
