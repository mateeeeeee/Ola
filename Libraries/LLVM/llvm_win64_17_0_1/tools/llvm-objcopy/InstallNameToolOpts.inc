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
PREFIX(prefix_3, {llvm::StringLiteral("-") COMMA llvm::StringLiteral("")})
PREFIX(prefix_1, {llvm::StringLiteral("-") COMMA llvm::StringLiteral("--") COMMA llvm::StringLiteral("")})
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
OPTION(prefix_1, llvm::StringLiteral("add_rpath"), add_rpath, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Add new rpath", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("change"), change, MultiArg, INVALID, INVALID, nullptr, 0, 2,
       "Change dependent shared library install name", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("delete_all_rpaths"), delete_all_rpaths, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Delete all rpath directives", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("delete_rpath"), delete_rpath, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Delete specified rpath", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("h"), h, Flag, INVALID, help, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("id"), id, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Change dynamic shared library id", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("prepend_rpath"), prepend_rpath, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Add new rpath before other rpaths", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("rpath"), rpath, MultiArg, INVALID, INVALID, nullptr, 0, 2,
       "Change rpath path name", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("version"), version, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Print the version and exit.", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("V"), V, Flag, INVALID, version, nullptr, 0, 0,
       "Alias for --version", nullptr, nullptr)
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


