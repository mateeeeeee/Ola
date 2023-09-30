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
#undef COMMA
#endif // PREFIX

/////////
// Prefix Union

#ifdef PREFIX_UNION
#define COMMA ,
PREFIX_UNION({
llvm::StringLiteral("-") COMMA llvm::StringLiteral("/") COMMA llvm::StringLiteral("")})
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
OPTION(prefix_1, llvm::StringLiteral("###"), _HASH_HASH_HASH, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("?"), help, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display this help and exit.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("C"), codepage, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "Set the codepage used for input strings.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dry-run"), dry_run, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Don't compile the input; only try to parse it.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("D"), define, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "Define a symbol for the C preprocessor.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("FM"), fm, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("FO"), fileout, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "Change the output file location.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("G1"), g1, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("G2"), g2, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("GN"), gn, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("G"), g, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("H"), h, Flag, INVALID, help, nullptr, 0, 0,
       "Display this help and exit.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("I"), includepath, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "Add an include path.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("LN"), lang_name, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Set the default language name.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("L"), lang_id, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "Set the default language identifier.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-preprocess"), no_preprocess, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Don't try to preprocess the input file.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("NOLOGO"), nologo, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("N"), add_null, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Null-terminate all strings in the string table.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Q"), q, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("R"), r, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("SL"), sl, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("U"), undef, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "Undefine a symbol for the C preprocessor.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("V"), verbose, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Be verbose.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("W"), w, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("X"), noinclude, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Ignore 'include' variable.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Y"), dupid_nowarn, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Suppress warnings on duplicate resource IDs.", nullptr, nullptr)
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


