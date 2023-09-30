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
PREFIX(prefix_1, {llvm::StringLiteral("-") COMMA llvm::StringLiteral("")})
PREFIX(prefix_2, {llvm::StringLiteral("--") COMMA llvm::StringLiteral("")})
#undef COMMA
#endif // PREFIX

/////////
// Prefix Union

#ifdef PREFIX_UNION
#define COMMA ,
PREFIX_UNION({
llvm::StringLiteral("-") COMMA llvm::StringLiteral("--") COMMA llvm::StringLiteral("")})
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
OPTION(prefix_1, llvm::StringLiteral("_"), anonymous_3, Flag, INVALID, strip_underscore, nullptr, 0, 0,
       "Alias for --strip-underscore", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("format="), anonymous_1_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify mangling format. Currently ignored because only 'gnu' is supported", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("format"), anonymous_0, Separate, INVALID, anonymous_1_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display this help", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("h"), anonymous_4, Flag, INVALID, help, nullptr, 0, 0,
       "Alias for --help", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("no-strip-underscore"), no_strip_underscore, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Don't strip the leading underscore", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("n"), anonymous_5, Flag, INVALID, no_strip_underscore, nullptr, 0, 0,
       "Alias for --no-strip-underscore", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("strip-underscore"), strip_underscore, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Strip the leading underscore", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("s"), anonymous_2, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Alias for --format", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("types"), types, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Attempt to demangle types as well as function names", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("t"), anonymous_6, Flag, INVALID, types, nullptr, 0, 0,
       "Alias for --types", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("version"), version, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the version", nullptr, nullptr)
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


