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
OPTION(prefix_1, llvm::StringLiteral("as-flags"), f_alias, JoinedOrSeparate, INVALID, f, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("as"), S_alias, JoinedOrSeparate, INVALID, S, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dllname"), D_long, JoinedOrSeparate, INVALID, D, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("D"), D, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "Specify the input DLL Name", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("d"), d, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "Input .def File", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("f"), f, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "Assembler Flags", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("input-def"), d_long, JoinedOrSeparate, INVALID, d, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("kill-at"), k_alias, Flag, INVALID, k, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("k"), k, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Kill @n Symbol from export", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("l"), l, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "Generate an import lib", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("machine"), m_long, JoinedOrSeparate, INVALID, m, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("m"), m, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "Set target machine", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-leading-underscore"), no_leading_underscore, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Don't add leading underscores on symbols", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("output-lib"), l_long, JoinedOrSeparate, INVALID, l, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("S"), S, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "Assembler", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("temp-prefix"), t_alias, JoinedOrSeparate, INVALID, t, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("t"), t, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "Prefix for temporary files (ignored)", nullptr, nullptr)
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


