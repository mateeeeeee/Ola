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
OPTION(prefix_1, llvm::StringLiteral("arch="), arch_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify the architecture, e.g. x86_64", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("arch"), anonymous_0, Separate, INVALID, arch_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("bitwidth="), bitwidth_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify the bit width", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("bitwidth"), anonymous_1, Separate, INVALID, bitwidth_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("endianness="), endianness_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify the endianness", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("endianness"), anonymous_2, Separate, INVALID, endianness_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("exclude="), exclude_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Remove symbols which match the pattern. Can be specified multiple times", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("exclude"), anonymous_3, Separate, INVALID, exclude_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display this help", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("hint-ifs-target="), hint_ifs_target_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "When --output-format is 'IFS', this flag will hint the expected target triple for IFS output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("hint-ifs-target"), anonymous_5, Separate, INVALID, hint_ifs_target_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("h"), anonymous_4, Flag, INVALID, help, nullptr, 0, 0,
       "Alias for --help", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("input-format="), input_format_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify the input file format", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("input-format"), anonymous_7, Separate, INVALID, input_format_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("input="), input_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "input", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("input"), anonymous_6, Separate, INVALID, input_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("output-elf="), output_elf_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Output path for ELF file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("output-elf"), anonymous_10, Separate, INVALID, output_elf_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("output-format="), output_format_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify the output file format **DEPRECATED**", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("output-format"), anonymous_11, Separate, INVALID, output_format_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("output-ifs="), output_ifs_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Output path for IFS file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("output-ifs"), anonymous_12, Separate, INVALID, output_ifs_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("output-tbd="), output_tbd_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Output path for TBD file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("output-tbd"), anonymous_13, Separate, INVALID, output_tbd_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("output="), output_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Output file **DEPRECATED**", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("output"), anonymous_8, Separate, INVALID, output_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("o"), anonymous_9, Separate, INVALID, output_EQ, nullptr, 0, 0,
       "Alias for --output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("soname="), soname_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "name", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("soname"), anonymous_14, Separate, INVALID, soname_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-ifs-arch"), strip_ifs_arch, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Strip target architecture information away from IFS output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-ifs-bitwidth"), strip_ifs_bitwidth, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Strip target bit width information away from IFS output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-ifs-endianness"), strip_ifs_endianness, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Strip target endianness information away from IFS output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-ifs-target"), strip_ifs_target, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Strip all target information away from IFS output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-needed"), strip_needed, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Strip needed libs from output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-size"), strip_size, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove object size from the output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-undefined"), strip_undefined, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Strip undefined symbols from IFS output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("target="), target_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify the target triple, e.g. x86_64-linux-gnu", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("target"), anonymous_15, Separate, INVALID, target_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("version"), version, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the version", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("V"), anonymous_16, Flag, INVALID, version, nullptr, 0, 0,
       "Alias for --version", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("write-if-changed"), write_if_changed, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Write the output file only if it is new or has changed", nullptr, nullptr)
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


