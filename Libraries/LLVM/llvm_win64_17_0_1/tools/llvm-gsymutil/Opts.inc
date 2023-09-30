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
OPTION(prefix_1, llvm::StringLiteral("address="), address_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Lookup an address in a GSYM file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("addresses-from-stdin"), addresses_from_stdin, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Lookup addresses in a GSYM file that are read from stdin\nEach input line is expected to be of the following format: <addr> <gsym-path>", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("address"), anonymous_8, Separate, INVALID, address_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("arch="), arch_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Process debug information for the specified CPU architecture only.\nArchitectures may be specified by name or by number.\nThis option can be specified multiple times, once for each desired architecture", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("arch"), anonymous_3, Separate, INVALID, arch_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("convert="), convert_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Convert the specified file to the GSYM format.\nSupported files include ELF and mach-o files that will have their debug info (DWARF) and symbol table converted", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("convert"), anonymous_0, Separate, INVALID, convert_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display this help", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("h"), anonymous_1, Flag, INVALID, help, nullptr, 0, 0,
       "Alias for --help", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("num-threads="), num_threads_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify the maximum number (n) of simultaneous threads to use when converting files to GSYM.\nDefaults to the number of cores on the current machine", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("num-threads"), anonymous_6, Separate, INVALID, num_threads_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("out-file="), out_file_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify the path where the converted GSYM file will be saved.\nWhen not specified, a '.gsym' extension will be appended to the file name specified in the --convert option", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("out-file"), anonymous_4, Separate, INVALID, out_file_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("o"), anonymous_5, Separate, INVALID, out_file_EQ, nullptr, 0, 0,
       "Alias for --out-file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("quiet"), quiet, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Do not output warnings about the debug information", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("segment-size="), segment_size_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify the size in bytes of the size the final GSYM file should be segmented into. This allows GSYM files to be split across multiple files", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("segment-size"), anonymous_7, Separate, INVALID, segment_size_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("verbose"), verbose, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Enable verbose logging and encoding details", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("verify"), verify, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Verify the generated GSYM file against the information in the file that was converted", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("version"), version, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the version", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("v"), anonymous_2, Flag, INVALID, version, nullptr, 0, 0,
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


