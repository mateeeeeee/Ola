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
PREFIX(prefix_1, {llvm::StringLiteral("-") COMMA llvm::StringLiteral("--") COMMA llvm::StringLiteral("")})
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
OPTION(prefix_1, llvm::StringLiteral("continue-on-cu-index-overflow"), continueOnCuIndexOverflow, Flag, INVALID, INVALID, nullptr, 0, 0,
       "This turns an error when offset for .debug_*.dwo sections overfolws into a warning.", "<filename>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("e"), execFileNames, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Specify the executable/library files to get the list of *.dwo from.", "<filename>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display this help", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("h"), anonymous_0, Flag, INVALID, help, nullptr, 0, 0,
       "Alias for --help", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("o"), outputFileName, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Specify the output file.", "<filename>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("version"), version, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the version of this program", nullptr, nullptr)
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


