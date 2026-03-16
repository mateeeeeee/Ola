<img align="center" padding="2" src="OlaDocs/olalogo_wide_new2.png"/>
Optimizing C-like compiler with both LLVM backend and fully custom backend targeting x86-64 and ARM64. 

## Features
  * classes
	- constructors
  	- templates: `class Box<T>`
	- single inheritance: `class D : B`
	- polymorphism using vtables: `virtual`, `pure`, `final`
	- access modifiers: `public`, `private`
	- static fields and methods: `static int count;`, `static int Get()`
	- `interface`, `this` and `super` keywords
  * functions
    - overloading
    - default parameter values: `int foo(int a, int b = 10)`
    - templates: `T Foo<T>(T x)`
    - attributes: `inline`, `noinline`, `nomangle` (equivalent to C++'s `extern "C"`), `noopt`, `deprecated`
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
import std.assert;

enum Weekday { Mon, Tue, Wed, Thu, Fri, Sat, Sun };

bool IsWeekend(Weekday d)
{
    return d == Sat || d == Sun;
}

interface Printable
{
    public int Length() const;
};

class Animal : Printable
{
    Animal(int legs) { this.legs = legs; }
    public int Length() const virtual { return this.legs; }
    public int Sound() const virtual { return 0; }
    private int legs;
};

class Dog : Animal
{
    Dog() { super(4); count = count + 1; }
    public int Sound() const virtual { return 1; }
    public static int GetCount() { return count; }
    private static int count = 0;
};

class Bird : Animal
{
    Bird() { super(2); this.can_fly = true; }
    public int Sound() const virtual { return 2; }
    public bool CanFly() const { return this.can_fly; }
    private bool can_fly;
};

class Cage<T>
{
    Cage(T pet) { this.pet = pet; }
    public T GetPet() const { return this.pet; }
    private T pet;
};

int CountLegs(ref Animal a1, ref Animal a2)
{
    return a1.Length() + a2.Length();
}

int SumArray(int[5] arr)
{
    int total = 0;
    foreach (int x : arr)
    {
        total += x;
    }
    return total;
}

int Fibonacci(int n)
{
    if (n <= 1) return n;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

public int main()
{
    // enums
    Weekday today = Fri;
    Assert(!IsWeekend(today));
    Assert(IsWeekend(Sat));

    // inheritance, polymorphism, virtual dispatch
    Dog dog;
    Bird bird;
    Assert(dog.Sound() == 1);
    Assert(bird.Sound() == 2);
    Assert(bird.CanFly());

    // ref parameters with polymorphic dispatch
    int legs = CountLegs(dog, bird);
    Assert(legs == 6);

    // auto type deduction
    auto area = 5 * 10;
    Assert(area == 50);

    // templates
    Cage<int> cage(42);
    Assert(cage.GetPet() == 42);

    // arrays, foreach, for loop
    int[5] squares;
    for (int i = 0; i < 5; ++i)
    {
        squares[i] = (i + 1) * (i + 1);
    }
    Assert(squares[0] == 1);
    Assert(squares[4] == 25);
    int sum = SumArray(squares);
    Assert(sum == 55);

    // switch
    int result = 0;
    switch (today)
    {
        case 0: result = 10; break;
        case 4: result = 50; break;
        default: result = -1; break;
    }
    Assert(result == 50);

    // ternary
    int sign = area > 0 ? 1 : -1;
    Assert(sign == 1);

    // recursion
    Assert(Fibonacci(10) == 55);

    // alias
    alias Score = int;
    Score s = 100;
    Assert(s == 100);

    // pointers and heap allocation
    Dog* ptr = new Dog;
    Assert(ptr->Sound() == 1);
    delete ptr;
    
    // static fields and methods
    Dog d1;
    Dog d2;
    Assert(Dog.GetCount() == 3);

    return 0;
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
     - **OlaTests**: Unit tests for the Lexer, Parser, Sema, IR, IR Passes, Machine IR, Register Allocation and Interpreter. ~700 tests, no system calls.
     - **OlaTestsE2E**, **OlaTestsInterpreter**, **OlaTestsLLVM**: End-to-end tests that invoke **OlaDriver** via system calls, each targeting a different backend (custom, interpreter, and LLVM respectively). All three share the same test suite (~50 tests), differing only in the backend used. **OlaTestsLLVM** is only built when LLVM is detected. E2E tests rely on the `Assert` function from the `std.assert` import.

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
