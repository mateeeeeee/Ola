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
OPTION(llvm::ArrayRef<llvm::StringLiteral>(), "action group", action_group, Group, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)

//////////
// Options

OPTION(prefix_0, llvm::StringLiteral("<input>"), INPUT, Input, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_0, llvm::StringLiteral("<unknown>"), UNKNOWN, Unknown, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("archs"), archs, Flag, action_group, INVALID, nullptr, 0, 0,
       "Display the arch_types present in the input file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("arch"), arch, MultiArg, INVALID, INVALID, nullptr, 0, 2,
       "Specifies the architecture and the corresponding input file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("create"), create, Flag, action_group, INVALID, nullptr, 0, 0,
       "Create a universal binary output file from the input files. Requires -output option", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("extract"), extract, Separate, action_group, INVALID, nullptr, 0, 0,
       "Create a universal output file containing only the specified arch_type from the fat input file. Requires -output option", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("h"), h, Flag, INVALID, help, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("info"), info, Flag, action_group, INVALID, nullptr, 0, 0,
       "Display descriptions of each input file including filename and arch_types. Groups universal binaries together followed by thin files", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("output"), output, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Create output file with specified name", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("o"), o, JoinedOrSeparate, INVALID, output, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("replace"), replace, MultiArg, action_group, INVALID, nullptr, 0, 2,
       "Replace the specified arch type with the contents of the input_file in a universal binary. Requires -output option", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("segalign"), segalign, MultiArg, INVALID, INVALID, nullptr, 0, 2,
       "Specifies the segment alignment for the specified architecture when creating a universal binary file. The alignment is a hexadecimal number that is a power of 2.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("thin"), thin, Separate, action_group, INVALID, nullptr, 0, 0,
       "Create a thin output file of specified arch_type from the fat input file. Requires -output option", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("verify_arch"), verify_arch, RemainingArgs, action_group, INVALID, nullptr, 0, 0,
       "Verify that the specified arch_types are present in the input file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("version"), version, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Print the version and exit.", nullptr, nullptr)
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


