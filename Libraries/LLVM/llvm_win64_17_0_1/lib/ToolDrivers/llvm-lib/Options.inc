/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Option Parsing Definitions                                                 *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

/////////
// Prefixes

#ifdef PREFIX
#define COMMA ,
PREFIX(prefix_0, {llvm::StringLiteral("")})
PREFIX(prefix_1, {llvm::StringLiteral("/") COMMA llvm::StringLiteral("-") COMMA llvm::StringLiteral("/?") COMMA llvm::StringLiteral("-?") COMMA llvm::StringLiteral("")})
PREFIX(prefix_2, {llvm::StringLiteral("/??") COMMA llvm::StringLiteral("-??") COMMA llvm::StringLiteral("/?") COMMA llvm::StringLiteral("-?") COMMA llvm::StringLiteral("")})
#undef COMMA
#endif // PREFIX

/////////
// Prefix Union

#ifdef PREFIX_UNION
#define COMMA ,
PREFIX_UNION({
llvm::StringLiteral("-") COMMA llvm::StringLiteral("-?") COMMA llvm::StringLiteral("-??") COMMA llvm::StringLiteral("/") COMMA llvm::StringLiteral("/?") COMMA llvm::StringLiteral("/??") COMMA llvm::StringLiteral("")})
#undef COMMA
#endif // PREFIX_UNION

/////////
// ValuesCode

#ifdef OPTTABLE_VALUES_CODE
#endif
/////////
// Groups

#ifdef OPTION

//////////
// Options

OPTION(prefix_0, llvm::StringLiteral("<input>"), INPUT, Input, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_0, llvm::StringLiteral("<unknown>"), UNKNOWN, Unknown, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("def:"), deffile, Joined, INVALID, INVALID, nullptr, 0, 0,
       "def file to use to generate import library", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("ignore:"), ignore, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify warning codes to ignore", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("libpath:"), libpath, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Object file search path", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("list"), lst, Flag, INVALID, INVALID, nullptr, 0, 0,
       "List contents of .lib file on stdout", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("llvmlibempty"), llvmlibempty, Flag, INVALID, INVALID, nullptr, 0, 0,
       "When given no contents, produce an empty .lib file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("llvmlibthin"), llvmlibthin, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Make .lib point to .obj files instead of copying their contents", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("ltcg"), ltcg, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("machine:"), machine, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify target platform", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("nodefaultlib:"), nodefaultlib, Joined, INVALID, INVALID, nullptr, 0, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("nodefaultlib"), nodefaultlib_all, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("nologo"), nologo, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("out:"), out, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Path to file to write output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("subsystem:"), subsystem, Joined, INVALID, INVALID, nullptr, 0, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("verbose"), verbose, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("WX:no"), WX_no, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Don't treat warnings as errors (default)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("WX"), WX, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Treat warnings as errors", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral(""), help_q, Flag, INVALID, help, nullptr, 0, 0, nullptr, nullptr, nullptr)
#endif // OPTION

#ifdef SIMPLE_ENUM_VALUE_TABLE

struct SimpleEnumValue {
  const char *Name;
  unsigned Value;
};

struct SimpleEnumValueTable {
  const SimpleEnumValue *Table;
  unsigned Size;
};
static const SimpleEnumValueTable SimpleEnumValueTables[] = {};
static const unsigned SimpleEnumValueTablesSize = std::size(SimpleEnumValueTables);
#endif // SIMPLE_ENUM_VALUE_TABLE


