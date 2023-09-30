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
OPTION(prefix_1, llvm::StringLiteral("all"), all, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Silently ignored. Present for GNU strings compatibility", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("a"), anonymous_2, Flag, INVALID, all, nullptr, 0, 0,
       "Alias for --all", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("bytes="), bytes_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Print sequences of the specified length", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("bytes"), anonymous_0, Separate, INVALID, bytes_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("f"), anonymous_3, Flag, INVALID, print_file_name, nullptr, 0, 0,
       "Alias for --print-file-name", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display this help", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("h"), anonymous_4, Flag, INVALID, help, nullptr, 0, 0,
       "Alias for --help", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("n"), anonymous_5, JoinedOrSeparate, INVALID, bytes_EQ, nullptr, 0, 0,
       "Alias for --bytes", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("print-file-name"), print_file_name, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Print the name of the file before each string", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("radix="), radix_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Print the offset within the file with the specified radix: o (octal), d (decimal), x (hexadecimal)", "<radix>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("radix"), anonymous_1, Separate, INVALID, radix_EQ, nullptr, 0, 0, nullptr, "<radix>", nullptr)
OPTION(prefix_2, llvm::StringLiteral("t"), anonymous_6, JoinedOrSeparate, INVALID, radix_EQ, nullptr, 0, 0,
       "Alias for --radix", "<radix>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("version"), version, Flag, INVALID, INVALID, nullptr, 0, 0,
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


