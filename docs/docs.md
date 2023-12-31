## Syntax
The translation unit, at the top level, consists of import statements and global declarations. All the import statements must be at the top of the file.
If the global declaration is extern, it means it's defined somewhere else. If not, it can be either private or public. By default, all declarations
are private. Private declarations are not visible outside of the translation unit in which they are defined. 
There are 5 different declarations that can be found in global scope:
- Function
- Variable
- Class
- Enum
- Alias

Other types of declarations that can be be found in non-global scope are:
- Variable
- Alias
- Field
- Method
- Enum member 
- Function parameter

### Keywords
- `while`
- `break`
- `switch`
- `case`
- `default`
- `for`
- `foreach`
- `goto`
- `continue`
- `do`
- `if`
- `else`
- `return`
- `enum`
- `class`
- `this`
- `const`
- `bool`
- `char`
- `int`
- `float`
- `void`
- `true`
- `false`
- `alias`
- `extern`
- `public`
- `private`
- `sizeof`
- `length`
- `auto`
- `import`
- `ref`
- `inline`
- `noinline`
- `extends`
- `super`
- `virtual`
- `implements`

### Import statement
Import statement has a following grammar:
```
<import-declaration> ::= import <import_identifier>;
<import_identifier> ::= <identifier>{.<identifier>}*
```
If the file specified by `<import_identifier>` exists, all the public global declarations will get imported. Depending on the type of declaration,
the imported declaration will be different. For example, imported variables and functions: 

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
Importing enum or alias declaration will, more or less, copy paste the declaration. Importing class declaration will remove method definitions and leave
only method declarations.

### Variables
Variable declarations can omit the type of the variable and let the compiler deduce it from the initializer expression using `auto` keyword.
```
public auto a = 10; // a is of type int
public int main() 
{
	int b = 3;
	auto c = b; //c is of type int
	const auto d = c; //d is of type const int
}
```

### Arrays

```
import std.assert;

auto arr1 = {1,2,3}; 	//arr1 is of type int[3] 
int[] arr2 = {1,2,3,4}; //arr2 is of type int[4] 
int[7] arr3 = {1,2,3,4}; //arr2 is of type int[7] and initialized with {1,2,3,4,0,0,0} 

private void modifyArray(int[] arr)
{
    arr[0] = 10;
}

public int main() 
{
    Assert(length(arr1) == 3);
    Assert(sizeof(arr2) == 32); // 4*sizeof(int) = 32
    Assert(arr3[6] == 0);
    auto arr4 = {1,2,3};

	int b = arr4[2]; 
    Assert(b == 3);

    int d = 10;
    const int c = arr4[10]; //compiler error, index out of bounds
    const int c = arr4[d];  //not a compiler error since d is not constexpr (runtime error)
    modifyArray(arr4);
    return arr4[0]; //returns 10
}
```

Two arrays can alias each other:
```
public int main() 
{
    int[] arr1 = {1,2,3};
    int[] arr2 = arr1; //arr2 and arr1 alias each other
	
    arr2[0] = 100;
    Assert(arr1[0] == 100);

    arr1[1] = 200;
    Assert(arr2[1] == 100);

    int[] arr3 = {1,1,1,1,1,1,1,1,1};
    arr2 = arr3; 
    Assert(arr2[7] == 1);

    int[] arr4 = arr2;
    Assert(arr4[5] == 1);

	int[] arr3; //not assigned, arr3 is of type int[] and can alias an array

	arr3 = arr4;
	++arr4[0];
	Assert(arr3[0] == arr4[0]);
    return 0;
}
```
Note that when declaring an array variable to alias another variable (or not initializing it at all) its type is considered to be `int[]` and not `int[N]`, in other words the variable doesn't
keep the information on how big is the array it is aliasing. That makes it possible to later alias another array. The same happens when function takes an array as 
an argument. Semantically it acts more as a pointer than array despite the array-like declaration. For that reason calling `length` operator on that kind of variable doesn't make sense.

Multidimensional arrays are also possible:
```
public int main() 
{
    int sum2d = 0;
	int[][] int2d = int[2][2]{ {1,2}, {3,4}}; 
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			sum2d += int2d[i][j];
		}
	}
	Assert(sum2d == 10); 

    int[] firstRow = sum2d[0];
    Assert(firstRow[0] == 1);
    Assert(firstRow[1] == 2);

    return 0;
}
```

Arrays also support `foreach` statement for iterating over them.
```
import std.io;

public int main()
{
    auto a = int[6]{1,2,3};
    a[0] = 10;
    foreach(int e : a)
    {
        PrintInt(e);  //prints 10,2,3,0,0,0
    } 
    return 0;
}
```

### ref
You use the `ref` keyword in the following contexts:
- in function/method signature to pass parameter by reference
- in variable/field declaration to declare a reference variable
- in function/method signature to return by reference

Reference variables must be initialized at declaration and cannot be reassigned to reference other variable. 
```	

void IntByRef(const ref int a)
{
	++a; //compiler error, a is const ref
}

void IntByRef(ref int a)
{
	++a;
}

void IntByValue(int a)
{
	++a;
}

int g = 9;
ref int GetRef()
{
	return g;
}

class S 
{
	public void Init(int x){this.x = x;}
	
	public ref int RefX() { return x;}
	public int GetX() {return x;}
	private int x = 1;
};


public int main()
{
	int a = 9;
	IntByRef(a);
	Assert(a == 10);

	ref int b = a;
	++b;
	Assert(a == 11);

	int c = b;
	++c;
	Assert(c == 12);
	Assert(a == 11);

	ref int d = b; 
	++d;
	Assert(a == 12);

	IntByRef(d);
	Assert(a == 13);

	IntByValue(d);
	Assert(a == 13);
	
	S s; s.Init(10);
	ref int sx = s.RefX();
	++sx;
	Assert(s.GetX() == 11);
}
```

### Classes
```
import std.assert;

public class S
{
	public void Init(int x, int y)
	{
		this.x = x;
		this.y = y;
	}

	public void SetX(int x) {this.x = x;} //declaring SetX/Y as const would trigger a compile error since this.x is modified
	public void SetY(int y) {this.y = y;}
	
	public int GetX() const {return x;}
	public int GetY() const {return y;}
	
	//public ref int GetXByRef() const {return x;} compiler error - returning non-const ref in const method
	public ref int GetXByRef() {return x;} //this is fine
	public const ref int GetXByConstRef() const {return x;} //this is fine

	private int x = 0;
	private int y = 0;
};

void StructByValue(S s)
{
	s.SetX(100);
	s.SetY(100);
	Assert(s.x == 100);
	Assert(s.y == 100);
}

void StructByRef(ref S s)
{
	s.SetX(1000);
	s.SetY(1000);
}

public int main()
{
	S s; s.Init(10, 10);
	StructByValue(s);
	Assert(s.GetX() == 10);
	Assert(s.GetY() == 10);
	
	StructByRef(s);
	Assert(s.GetX() == 1000);
	Assert(s.GetY() == 1000);

	S s2 = s; 
	s.SetX(25);
	s.SetY(25);
	Assert(s2.GetX() == 10);
	Assert(s2.GetY() == 10);
	Assert(s.GetX() == 25);
	Assert(s.GetY() == 25);
	
	ref S s3 = s;
	s3.SetX(500);
	Assert(s.GetX() == 500);
	return 0;
}
```
Class declaration consists of a sequence of method definitions and field declarations, Those declarations can be interleaved.
Every method or field declaration has a visibility, either `public` or `private`. By default, if nothing is specified, the visibility
is `private` which means it cannot be used outside of the class. 
`this` keyword can be used to disambiguate between symbols.
Classes currently support single inheritance using `extends` keyword (No polymorphism for now).
```
import std.assert;

class Base
{
	private int x = 10;
	public int GetX() const {return x;}
};

class Derived extends Base
{
	private int y = 100;
	public int GetY() const {return y;}
};

class ExtDerived extends Derived
{
	private int y = 100;
	public int GetY() const {return y;}
	public int GetYSum() const {return this.y + super.y;}
};

public int main()
{
	Derived d;
	int y = d.GetY(); //y = 100
	int x = d.GetX(); //x = 10
	Base b = d;
	return b.GetX();
}
```

Polymorphism is supported using vtables, i.e. using `virtual` functions . 
```
import std.assert;

class Base
{
    int x = 10;
    int y = 20;
    public int GetX() virtual
    {
        return x;
    }
    public int GetY() virtual
    {
        return y;
    }
};

class Derived : Base
{
     int x = 100;
     public int GetX() virtual
     {
        return x;
     }
};

class ExtDerived : Derived
{
    int y = 200;
    public int GetY() virtual
    {
        return y; 
    }
};

public int main() 
{
    ExtDerived d;
    ref Base b = d;
    Assert(b.GetY() == 200);
    Assert(b.GetX() == 100);
}
```

### Strings
Strings are just arrays of chars. `string` is a built-in alias for `char[]`. 

```
import std.io;
import std.string;
public int main()
{
    char[] name = char[16]{};
    ReadString(name, length(name)); //from std.io
    name[0] = 'M';
    PrintString(name);

    string stringNumber = "12345";
    int integer = StringToInt(number);  //from std.string
	PrintInt(integer); //prints 12345

    return 0;
}
```
### Alias
Alias is similar to `typedef` in C or even more to `using` alias in C++. 
The following example shows its usage:
```
import std.assert;
import std.io;

alias IntArray = int[];

public int main()
{
    alias MyInt = int;

    IntArray a = MyInt[6]{1,2,3};
    foreach(MyInt e : a)
    {
        PrintInt(e);
    }
    return 0;
}
```

### Types
There are 5 basic types: `bool`, `char`, `float`, `int` and `void`. `int` is 64-bit signed integer and float is `64-bit` floating point integer. 
`void` can be used when specifying that the return type of a function. 
All other types can form a composite array type. Function type consists of the return type, and list of parameter types. Other composite types except arrays and functions are classes and reference types.

