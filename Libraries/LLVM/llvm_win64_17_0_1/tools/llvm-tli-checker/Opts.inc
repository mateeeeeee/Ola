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
PREFIX(prefix_2, {llvm::StringLiteral("-") COMMA llvm::StringLiteral("")})
PREFIX(prefix_1, {llvm::StringLiteral("--") COMMA llvm::StringLiteral("")})
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
OPTION(prefix_1, llvm::StringLiteral("dump-tli"), dump_tli, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Dump TLI's list of functions and whether they are available", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display available options", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("h"), anonymous_1, Flag, INVALID, help, nullptr, 0, 0,
       "Alias for --help", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("libdir="), libdir_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Root directory for finding library files", "<directory>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("libdir"), anonymous_2, Separate, INVALID, libdir_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("report="), report_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Level of detail to report", nullptr, "summary,discrepancy,full")
OPTION(prefix_1, llvm::StringLiteral("separate"), separate, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Report on each library file separately", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("triple="), triple_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Target triple", "<triple>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("triple"), anonymous_0, Separate, INVALID, triple_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
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


