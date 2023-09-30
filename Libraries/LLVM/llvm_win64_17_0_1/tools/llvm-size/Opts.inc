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
PREFIX(prefix_1, {llvm::StringLiteral("--") COMMA llvm::StringLiteral("")})
PREFIX(prefix_2, {llvm::StringLiteral("--") COMMA llvm::StringLiteral("-") COMMA llvm::StringLiteral("")})
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
OPTION(llvm::ArrayRef<llvm::StringLiteral>(), "kind", grp_mach_o, Group, INVALID, INVALID, nullptr, 0, 0,
       "OPTIONS (Mach-O specific)", nullptr, nullptr)

//////////
// Options

OPTION(prefix_0, llvm::StringLiteral("<input>"), INPUT, Input, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_0, llvm::StringLiteral("<unknown>"), UNKNOWN, Unknown, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("arch="), arch_EQ, Joined, grp_mach_o, INVALID, nullptr, 0, 0,
       "architecture(s) from a Mach-O file to dump", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("arch"), anonymous_2, Separate, INVALID, arch_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("A"), anonymous_3, Flag, INVALID, format_EQ, "sysv\0", 0, 0,
       "Alias for --format", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("B"), anonymous_4, Flag, INVALID, format_EQ, "berkeley\0", 0, 0,
       "Alias for --format", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("common"), common, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Print common symbols in the ELF file. When using Berkeley format, this is added to bss", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("d"), anonymous_5, Flag, INVALID, radix_EQ, "10\0", 0, 0,
       "Alias for --radix=10", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("format="), format_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify output format", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("format"), anonymous_0, Separate, INVALID, format_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display this help", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("h"), anonymous_6, Flag, INVALID, help, nullptr, 0, 0,
       "Alias for --help", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("l"), l, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "When format is darwin, use long format to include addresses and offsets", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("m"), anonymous_7, Flag, INVALID, format_EQ, "darwin\0", 0, 0,
       "Alias for --format", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("o"), anonymous_8, Flag, INVALID, radix_EQ, "8\0", 0, 0,
       "Alias for --radix=8", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("radix="), radix_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Print size in radix", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("radix"), anonymous_1, Separate, INVALID, radix_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("totals"), totals, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Print totals of all objects - Berkeley format only", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("t"), anonymous_9, Flag, INVALID, totals, nullptr, 0, 0,
       "Alias for --totals", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("version"), version, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the version", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("x"), anonymous_10, Flag, INVALID, radix_EQ, "16\0", 0, 0,
       "Alias for --radix=16", nullptr, nullptr)
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


