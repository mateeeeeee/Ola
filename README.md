<img align="left" src="OlaCompiler/olalogo.png" width="120px"/>
<br/><br/>

# Ola
Ola is a toy programming language designed with a focus on modularity and learning, offering both an LLVM-based backend and a work-in-progress custom backend. 

## Dependencies
  * [LLVM 17.0.1](https://github.com/llvm/llvm-project) for compiler backend.
  * [spdlog](https://github.com/gabime/spdlog) for logging.
  * [CLI11](https://github.com/CLIUtils/CLI11) for command line parsing.

## Features
  * classes
	- access modifiers: `public`, `private`
	- constructors
	- single inheritance: `:`
	- polymorphism using vtables: `virtual`, `pure`, `final`
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
    - overloading
	- attributes: `inline`, `noinline`, `nomangling` (equivalent to C++'s `extern "C"`)
  * arrays
  * `sizeof`, `length` operators
  * `alias`
  * strings
  * floats 
  * implicit casts
  * scopes
  * import statement
  * standard library
  * Backend architecture
	- LLVM Backend: Emits LLVM IR and supports LLVM optimization passes.
	- Custom Backend (Work in Progress):
		- Custom Intermediate Representation (IR) and Machine Intermediate Representation (MIR).
		- IR optimization passes
		- Early support for x86-64 code generation.
		- Missing features: proper stack layout and class support.

## Structure
Ola consists of three main parts:

1. **Ola Library**: 
   - A standard library for the Ola language, implemented in C and built as a static library to be used by the compiler. Currently, it includes the following files: 
     - `olaio.h`
     - `olamath.h`
     - `olaassert.h`
     - `olastring.h`
     - `olamemory.h`

2. **Ola Compiler**:
- The core of the Ola project, divided into various stages for flexibility and modularity:
- **Lexer**: Tokenizes the source code.
- **Import Processor**: Processes `import` statements from the tokenized input.
- **Parser**: A recursive descent parser that constructs an Abstract Syntax Tree (AST) from processed tokens.
- **Sema**: Performs semantic analysis on the AST to ensure code correctness.
- **Backend**: After the frontend processing completes, the compilation process diverges into two backend paths:
	- **LLVM Path**:
		- **LLVM Visitor**: Transforms the AST into LLVM IR.
		- **LLVM Optimizer**: Applies LLVM optimization passes to the IR, based on the specified optimization level.
		- Compilation to assembly is done using `clang -S` command 
	- **Custom Backend Path**:
		- **IRVisitor**: Transforms the AST into Ola's custom IR.
		- **IROptimizer**: Applies custom optimizations at the IR level.
		- **MachineModule**: responsible for lowering IR to MIR and finally to assembly.
     
3. **Ola Tests**:
   - A set of unit tests built with GoogleTest, covering Ola language features. They rely on `Assert` funtion from the `std.assert` import. Currently, two folder are maintained: LLVM tests and Custom backend tests with a goal of unifying them once the custom backend reaches the same capabilities as LLVM backend.

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

### Samples
Currently to see the samples you can check the test folder: OlaTests/Tests/.

