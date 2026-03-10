<img align="center" padding="2" src="OlaDocs/olalogo_wide_new2.png"/>
Optimizing C-like compiler with both LLVM backend and fully custom backend targeting x86-64 and ARM64. 

## Features
  * classes
	- constructors
  	- templates: `class Box<T>`
	- single inheritance: `:`
	- polymorphism using vtables: `virtual`, `pure`, `final`
	- access modifiers: `public`, `private`
	- `interface`, `this` and `super` keywords
  * operators:
    - additive: `+`, `-`, `+=`, `-=`, `++`, `--`
    - multiplicative: `*`, `/`, `%`, `*=`, `/=`, `%=`
    - relation: `==`, `!=`, `>`, `>=`, `<`, `<=`
    - shift: `>>`, `<<`, `>>=`, `<<=`
    - bitwise: `&`, `|`, `^`, `~`, `&=`, `|=`, `^=`
    - logic: `&&`, `||`, `!`
  * control statements: `if` `else`, `switch`, `goto`, `?:`
  * loop statements: `for`,`foreach`, `while`, `do` `while`, `break`, `continue`
  * pointers, dereference and heap allocation: `T*`, `new T[]`, `delete`, `->`, `*ptr`
  * reference type: `ref`
  * automatic type deduction: `auto`
  * enums
  * functions 
    - overloading
    - attributes: `inline`, `noinline`, `nomangle` (equivalent to C++'s `extern "C"`), `noopt`, `deprecated`
  * arrays
  * misc: `alias`, `sizeof`, `length` operators, strings, floats, implicit casts, scopes, import
  * std library: `io`, `math`, `assert`, `string`, `file`, `pair`, `optional`, `vector`, `list`, `stack`, `queue`, `map`, `set`
  * LLVM backend
  * Custom backend
    - Custom IR
    	- Optimization passes: Function Inlining, Simplify CFG, Mem2Reg, CSE, GVN, Arithmetic Reduction, CP and IPCP, LICM, Loop Unroll, DCE, Global DCE, SROA, Devirtualization, Tail Recursion Elimination
      - Analysis passes: CFG, Loop, Alias, Dominator Tree, Dominator Frontier, Call Graph
    - Custom MIR
	  - Instruction Selection: Tree pattern matching ISel (with legacy fallback)
      - Legalization: Automated instruction lowering and legalization
      - Register Allocation: linear scan, graph coloring with optional copy coalescing
    - x86-64 code generation
      - Microsoft ABI
      - SysV ABI (wip)
    - ARM64 code generation
    - Class support
    - Interpreter

## Example
```cpp
class Pair<A, B>
{
    Pair(A a, B b)
    {
        this.first = a;
        this.second = b;
    }
    public A First() const { return this.first; }
    public B Second() const { return this.second; }
    private A first;
    private B second;
};

class Shape
{
    Shape(int x, int y) { this.x = x; this.y = y; }
    public int GetX() const { return this.x; }
    public int GetY() const { return this.y; }
    public int Area() const virtual { return 0; }
    private int x;
    private int y;
};

class Rectangle : Shape
{
    Rectangle(int x, int y, int w, int h)
    {
        super(x, y);
        this.w = w;
        this.h = h;
    }
    public int Area() const virtual { return this.w * this.h; }
    private int w;
    private int h;
};

int AreaAt(ref Pair<int,int> origin, int w, int h)
{
    return w * h;
}

public int main()
{
    Pair<int, float> p(10, 3.14);

    Rectangle r(0, 0, p.First(), 5);
    ref Shape s = r;
    int area = s.Area();

    Pair<int, int> origin(0, 0);
    int area2 = AreaAt(origin, 3, 4);

    return area + area2; // 62
}
```

## Architecture
<img src="OlaDocs/olaarch.svg" alt="Ola compiler architecture">

## Structure
The project consists of the following parts:
1. **Ola Library**:
   - A standard library for the Ola language, implemented in C and built as a static library to be used by the compiler. It includes essential components like:
     - C headers: `olaio.h`, `olamath.h`, `olaassert.h`, `olastring.h`, `olafile.h`
     - Ola std imports: `std.io`, `std.math`, `std.assert`, `std.string`, `std.file`, `std.pair`, `std.optional`, `std.vector`, `std.list`, `std.stack`, `std.queue`, `std.map`, `std.set`
   
2. **Ola Compiler**:
   - The core of the Ola project, implemented as a **static library** (`OlaCompiler`) with the following components:
     - **Lexer**: Tokenizes the source code.
     - **Import Processor**: Processes `import` statements from the tokenized input.
     - **Parser**: A recursive descent parser that constructs an Abstract Syntax Tree (AST) from processed tokens.
     - **Sema**: Performs semantic analysis on the AST. Runs together with Parser, not as a separate step.
     - **Backend**: After frontend processing, the compilation process diverges into two backend paths:
       - **LLVM**:
         - **LLVMIR Visitor**: Transforms the AST into LLVM IR.
         - **LLVMIR Pass Manager**: Applies LLVM optimization passes to the IR.
         - Compilation to assembly is done using the `clang -S` command.
       - **Custom Backend**:
         - **Interpreter**: Executes IR directly without generating machine code
         - **IR Visitor**: Transforms the AST into Ola's custom IR.
         - **IR Pass Manager**: Applies custom optimization passes at the IR level.
         - **MachineModule**: Responsible for lowering IR to MIR and finally to assembly.

3. **Ola Driver**:
   - An **executable** (`OlaDriver`) that serves as the main entry point for compiling Ola code. It links to the `OlaCompiler` library and calls compiler's API.

4. **Ola Playground**:
   - A separate **executable** that links to the `OlaCompiler` static library. It provides a development environment for experimenting with the compiler and Ola code, without directly invoking the `OlaDriver`.

5. **Ola Tests**:
   - A set of tests built with GoogleTest, organized into four targets:
     - **OlaTests**: Unit tests for the Lexer, Parser, Sema, IR, IR Passes, Machine IR, Register Allocation and Interpreter — no system calls.
     - **OlaTestsE2E**: End-to-end tests using the custom backend. Invokes **OlaDriver** via system calls.
     - **OlaTestsInterpreter**: End-to-end tests using the interpreter backend. Invokes **OlaDriver** via system calls.
     - **OlaTestsLLVM**: End-to-end tests using the LLVM backend. Only built when LLVM is detected. Invokes **OlaDriver** via system calls.
     - E2E tests rely on the `Assert` function from the `std.assert` import.

## Dependencies
* [LLVM 17.0](https://github.com/llvm/llvm-project) for LLVM backend (optional)
  * _Note: You can disable the LLVM backend by generating project with `ENABLE_LLVM=OFF`:_
    ```bash
    cmake -DENABLE_LLVM=OFF -B build
    ```
* CMake 3.20 or higher
* C++20 compatible compiler (MSVC 2019+, GCC 10+, Clang 12+)

## Building

### Windows (MSVC)
```bash
cmake -B build [-G "Visual Studio 17 2022"]
cmake --build build --config Release
```

### Linux
```bash
cmake -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### macOS
```bash
# Xcode
cmake -B build -G Xcode
cmake --build build --config Release

# Unix Makefiles
cmake -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Build Options
```bash
cmake -B build -DENABLE_LLVM=OFF          # Disable LLVM backend
cmake -B build -DBUILD_TESTS=OFF          # Disable tests
cmake -B build -DBUILD_PLAYGROUND=OFF     # Disable playground
```

## Usage
### Command line options
  * `--ast`: Dump AST to output/log
  * `--cfg`: Dump CFGs to .dot files and visualize them
  * `--callgraph`: Dump Call Graphs to .dot files and visualize them
  * `--domtree`: Dump Dominator Trees to .dot files and visualize them
  * `--emit-ir`: Emit IR file
  * `--emit-mir`: Emit IR file
  * `--emit-asm`: Emit ASM file
  * `--domfrontier`: Print dominance frontiers to standard output
  * `--llvm`: Use LLVM backend instead of the default custom backend (ignored if LLVM is not available)
  * `--test`: Used for running g-tests
  * `--timeout`: Used for detecting infinite loops during tests
  * `--Od`: No optimizations
  * `--O0`: Same as `--Od`
  * `--O1`: Optimize
  * `--O2`: Optimize more
  * `--O3`: Optimize even more
  * `-i` ... : Input files
  * `-o`: Output file
  * `--directory`: Directory of input files
  

## Examples
You can find example programs for Ola in the `OlaTests/Tests/` folder.
