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
PREFIX(prefix_1, {llvm::StringLiteral("/") COMMA llvm::StringLiteral("-") COMMA llvm::StringLiteral("")})
PREFIX(prefix_2, {llvm::StringLiteral("/?") COMMA llvm::StringLiteral("-?") COMMA llvm::StringLiteral("")})
#undef COMMA
#endif // PREFIX

/////////
// Prefix Union

#ifdef PREFIX_UNION
#define COMMA ,
PREFIX_UNION({
llvm::StringLiteral("-") COMMA llvm::StringLiteral("-?") COMMA llvm::StringLiteral("/") COMMA llvm::StringLiteral("/?") COMMA llvm::StringLiteral("")})
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
OPTION(prefix_1, llvm::StringLiteral("DEFINE:"), DEFINE, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Not implemented", "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("FOLDDUPS:"), FOLDDUPS, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Not implemented", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("HELP"), HELP, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display available options", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("H"), H, Flag, INVALID, HELP, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("MACHINE:"), MACHINE, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Machine architecture", "{ARM|ARM64|EBC|IA64|X64|X86}", nullptr)
OPTION(prefix_1, llvm::StringLiteral("NOLOGO"), NOLOGO, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Not implemented", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("OUT:"), OUT, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Output file", "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("READONLY"), READONLY, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Not implemented", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("TIMESTAMP:"), TIMESTAMP, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Timestamp for coff header, defaults to current time", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("VERBOSE"), VERBOSE, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Use verbose output", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral(""), HELP_Q, Flag, INVALID, HELP, nullptr, 0, 0, nullptr, nullptr, nullptr)
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


