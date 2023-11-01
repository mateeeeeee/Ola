<img align="left" src="WaveCompiler/wavelogo.jpg" width="120px"/>

# Wave
Wave is a toy programming language using LLVM for its backend. Frontend, including lexer and parser, is handwritten (i.e. without using generators). 
It's done as a learning project and its purpose is solely educational.

## Dependencies
  * [LLVM 17.0.1](https://github.com/llvm/llvm-project) for compiler backend.
  * [spdlog](https://github.com/gabime/spdlog) for logging.
  * [CLI11](https://github.com/CLIUtils/CLI11) for command line parsing.

## Features
  * operators:
    - additive: `+`, `-`, `+=`, `-=`, `++`, `--`
    - multiplicative: `*`, `/`, `%`, `*=`, `/=`, `%=`
    - relation: `==`, `!=`, `>`, `>=`, `<`, `<=`
    - shift: `>>`, `<<`, `>>=`, `<<=`
    - bitwise: `&`, `|`, `^`, `~`, `&=`, `|=`, `^=`
    - logic: `&&`, `||`, `!`
  * control statements: `if` `else`, `switch`, `goto`, `?:`
  * loop statements: `for`, `while`, `do` `while`, `break`, `continue`
  * arrays
  * enums
  * functions
  * `sizeof`, `length` operators
  * implicit casts
  * scopes
  * import statement
  * one-line comments
  * standard library
    
## Todo
  * floats
  * classes

## Structure
Wave consists of three parts: 
1. __Wave library__ - standard library for Wave language implemented in C and built as static library to be used by the compiler.  Currently it contains 4 files: io.h, math.h, assert.h, string.h.
2. __Wave compiler__ - consists of the following parts:
   * __Lexer__ - turns source file into a sequence of tokens
   * __Import Processor__ - receives tokens from previous phase and processes import statements. 
   * __Parser__ - recursive descent parser that receives processed tokens and constructs Abstract Syntax Tree (AST) of a translation unit. 
   * __Sema__ - does semantic analysis of a translation unit. 
   * __LLVM Visitor__ - traverses AST and emits LLVM IR.
   * __LLVM Optimizer__ - applies optimizations to the generated LLVM IR produced by LLVM Visitor based on the optimization level used.
4. __Wave tests__
   * UnitTest framework for testing existing Wave features. Uses GoogleTest.

## Syntax
The translation unit, at the top level, consists of import statements and global declarations. All the import statements must be at the top of the file.
If the global declaration is extern, it means it's defined somewhere else. If not, it can be either private or public. By default, both function and variable declarations
are private. Private declarations are not visible outside of the translation unit in which they are defined. 
### Import statement
Import statement has a following grammar:
```
<import-declaration> ::= import <import_identifier>;
<import_identifier> ::= <identifier>{.<identifier>}*
```
If the file specified by `<import_identifier>` exists, it will check all the global declarations of that file translation unit, and for every public declaration, add the extern declaration to a file that's importing it. 

File `util/math.wv`

```
public float PI = 3.14;

private int AddImpl(int a, int b)
{
	return a + b;
}
public int Add(int a, int b) 
{
	return AddImpl(a,b);
}
```

File `main.wv`

```
import util.math;

public int main() 
{
	int a = 3;
	return Add(a, 2);
}
```

File `main.wv` is equivalent to:
```
extern float PI;
extern int Add(int a, int b);

public int main() 
{
	int a = 3;
	return Add(a, 2);
}
```

### Variables
Variable declaration has a slightly different grammar rule for global and local variables:

```
<global-variable-declaration> ::= extern <type-qualifier> <type-specifier> <identifier>:
                                | {<declaration-visibility>}? <type-qualifier> <type-specifier> <identifier> { = <constant-expression>}?;
								| {<declaration-visibility>}? <type-qualifier> var <identifier> = <constant-expression>;

<local-variable-declaration> ::= <type-qualifier> <type-specifier> <identifier> { = <initializer>}?;
                               | <type-qualifier> var <identifier> = <initializer>;
<type-qualifier> ::= {const}?
<type-specifier> ::= void | bool | char | int | float | ...

```
One of the things they have in common is omitting the type of the variable and deducing it from the initializer expression using `var` keyword.

```
public var a = 10; // a is of type int
public int main() 
{
	int b = 3;
	var c = b; //c is of type int
}
```

### Arrays

```
import std.assert;

var arr1 = {1,2,3}; //arr1 is of type int[3] 
int[] arr2 = {1,2,3,4}; //arr2 is of type int[4] 
int[] arr3 = int[7]{1,2,3,4}; //arr2 is of type int[7] and initialized with {1,2,3,4,0,0,0} 

public int main() 
{
    Assert(length(arr1) == 3);
    Assert(sizeof(arr2) == 32); // 4*sizeof(int) = 32
    Assert(arr3[6] == 0);
    var arr4 = int[3]{1,2,3};

	int b = arr4[2]; 
    Assert(b == 3);

    int d = 10;
    const int c = arr4[10]; //compiler error, index out of bounds
    const int c = arr4[d];  //not a compiler error since d is not constexpr (runtime error)
}
```

### Keywords
- `while`
- `break`
- `switch`
- `case`
- `default`
- `for`
- `goto`
- `continue`
- `do`
- `if`
- `else`
- `return`
- `enum`
- `class`
- `const`
- `bool`
- `char`
- `int`
- `float`
- `void`
- `true`
- `false`
- `extern`
- `public`
- `private`
- `sizeof`
- `length`
- `var`
- `import`

### Types
There are 5 basic types: `bool`, `char`, `float`, `int` and `void`. `int` is 64-bit signed integer and float is `64-bit` floating point integer. `void` can be used when specifying that the return type of a function. All other types can form composite array type. Function type consists of the return type, and list of parameter types. Every cast in Wave is implicit, which means that explicit casts don't exist.

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

## Grammar 
```
<translation-unit> ::= { import-declaration }* { <function-definition> | <function-declaration> | <global-variable-declaration> }*

<import-declaration> ::= import <import_identifier>;
<import_identifier> ::= <identifier>{.<identifier>}*

<declaration-visibility>  ::= public | private

<function-declaration>    ::= extern <type-specifier> <identifier>( <parameter-list> );
<function-definition>     ::= {<declaration-visibility>}? <type-specifier> <identifier>( <parameter-list> ) <compound-statement>

<global-variable-declaration> ::= extern <type-qualifier> <type-specifier> <identifier>:
                                | {<declaration-visibility>}? <type-qualifier> <type-specifier> <identifier> { = <constant-expression>}?;
								| {<declaration-visibility>}? <type-qualifier> var <identifier> = <constant-expression>;


<parameter-list> ::= <parameter-declaration>
                   | <parameter-list>, <parameter-declaration>
<parameter-declaration> ::= {<type-qualifier>}? <type-specifier> {<identifier>}?

<type-qualifier> ::= {const}?
<type-specifier> ::= void
                   | bool {[]}*
                   | char {[]}*
                   | int  {[]}*
                   | float {[]}*
                   | <enum-identifier> {[]}*
                   | <class-identifier> {[]}*
				   
<enum-specifier> ::= enum <enum-identifier> { <enumerator-list> }
                   | enum { <enumerator-list> }

<enumerator-list> ::= <enumerator>
                    | <enumerator-list> , <enumerator>

<enumerator> ::= <identifier>
               | <identifier> = <constant-expression>

<enum-identifier> ::= <identifier>
			   
<class-specifier> ::= ... (TODO)

<class-identifier> ::= <identifier>

<constant-expression> ::= <conditional-expression>

<conditional-expression> ::= <logical-or-expression>
                           | <logical-or-expression> ? <expression> : <conditional-expression>

<logical-or-expression> ::= <logical-and-expression>
                          | <logical-or-expression> || <logical-and-expression>

<logical-and-expression> ::= <inclusive-or-expression>
                           | <logical-and-expression> && <inclusive-or-expression>

<inclusive-or-expression> ::= <exclusive-or-expression>
                            | <inclusive-or-expression> | <exclusive-or-expression>

<exclusive-or-expression> ::= <and-expression>
                            | <exclusive-or-expression> ^ <and-expression>

<and-expression> ::= <equality-expression>
                   | <and-expression> & <equality-expression>

<equality-expression> ::= <relational-expression>
                        | <equality-expression> == <relational-expression>
                        | <equality-expression> != <relational-expression>

<relational-expression> ::= <shift-expression>
                          | <relational-expression> < <shift-expression>
                          | <relational-expression> > <shift-expression>
                          | <relational-expression> <= <shift-expression>
                          | <relational-expression> >= <shift-expression>

<shift-expression> ::= <additive-expression>
                     | <shift-expression> << <additive-expression>
                     | <shift-expression> >> <additive-expression>

<additive-expression> ::= <multiplicative-expression>
                        | <additive-expression> + <multiplicative-expression>
                        | <additive-expression> - <multiplicative-expression>

<multiplicative-expression> ::= <unary-expression>
                              | <multiplicative-expression> * <unary-expression>
                              | <multiplicative-expression> / <unary-expression>
                              | <multiplicative-expression> % <unary-expression>
							 

<unary-expression> ::= <postfix-expression>
                     | ++ <unary-expression>
                     | -- <unary-expression>
                     | sizeof (<unary-expression>)
                     | sizeof (<type-specifier>)
                     | length (<unary-expression>)

<postfix-expression> ::= <primary-expression>
                       | <postfix-expression> [ <expression> ]
                       | <postfix-expression> ( {<assignment-expression>}* )
                       | <postfix-expression> ++
                       | <postfix-expression> --

<primary-expression> ::= <identifier>
                       | <constant>
                       | <string>
                       | ( <expression> )

letter	::= {[a-z|A-Z]}
digit	::= [0-9]
identifier ::= letter { letter | digit | _ }*
<string> ::= "{ch}", where ch denotes any printable ASCII character 

<constant> ::= <integer-constant>
             | <character-constant>
             | <floating-constant>
             | <enumeration-constant>
			 
<expression> ::= <assignment-expression>
               | <expression> , <assignment-expression>

<assignment-expression> ::= <conditional-expression>
                          | <unary-expression> <assignment-operator> <assignment-expression>

<assignment-operator> ::= =
                        | *=
                        | /=
                        | %=
                        | +=
                        | -=
                        | <<=
                        | >>=
                        | &=
                        | ^=
                        | |=

<unary-operator> ::= &
                   | *
                   | +
                   | -
                   | ~
                   | !

<local-variable-declaration> ::= <type-qualifier> <type-specifier> <identifier> { = {<initializer> | <init-list-expr> }}?;
                               | <type-qualifier> var <identifier> = {<initializer> | <init-list-expr> };
	
<initializer> ::= <assignment-expression>
<init-list-expr> ::= {<type-specifier>{[<constant-expression>]}+}?{ <initializer>{,<initializer>}* }

<compound-statement> ::= { { <local-variable-declaration> | <statement> }* }

<statement> ::= <labeled-statement>
              | <expression-statement>
              | <compound-statement>
              | <selection-statement>
              | <iteration-statement>
              | <jump-statement>

<labeled-statement> ::= <identifier> : <statement>
                      | case <constant-expression> : <statement>
                      | default : <statement>

<expression-statement> ::= {<expression>}? ;

<selection-statement> ::= if ( <expression> ) <statement>
                        | if ( <expression> ) <statement> else <statement>
                        | switch ( <expression> ) <statement>

<iteration-statement> ::= while ( <expression> ) <statement>
                        | do <statement> while ( <expression> ) ;
                        | for ( {<expression>}? ; {<expression>}? ; {<expression>}? ) <statement>

<jump-statement> ::= goto <identifier> ;
                   | continue ;
                   | break ;
                   | return {<expression>}? ;
```
