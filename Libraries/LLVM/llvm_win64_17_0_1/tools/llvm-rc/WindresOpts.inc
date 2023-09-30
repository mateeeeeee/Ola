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
PREFIX(prefix_1, {llvm::StringLiteral("-") COMMA llvm::StringLiteral("")})
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
OPTION(prefix_1, llvm::StringLiteral("###"), _HASH_HASH_HASH, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("codepage="), codepage_eq, Joined, INVALID, codepage, nullptr, 0, 0,
       "Default codepage to use", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("codepage"), codepage, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("c"), codepage_short, JoinedOrSeparate, INVALID, codepage, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("define="), define_eq, Joined, INVALID, define, nullptr, 0, 0,
       "Define to pass to the preprocessor", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("define"), define, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("D"), define_short, JoinedOrSeparate, INVALID, define, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("F"), target_short, JoinedOrSeparate, INVALID, target, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("help"), help_long, Flag, INVALID, help, nullptr, 0, 0,
       "Display this message and exit", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("h"), help, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("include-dir="), include_dir_eq, Joined, INVALID, include_dir, nullptr, 0, 0,
       "Include directory", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("include-dir"), include_dir, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("include="), include_alias_eq, Joined, INVALID, include_dir, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("include"), include_alias, Separate, INVALID, include_dir, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("input-format="), input_format_eq, Joined, INVALID, input_format, nullptr, 0, 0,
       "Input format", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("input-format"), input_format, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("input="), input_eq, Joined, INVALID, input, nullptr, 0, 0,
       "Input file", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("input"), input, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("I"), include_dir_short, JoinedOrSeparate, INVALID, include_dir, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("i"), input_short, JoinedOrSeparate, INVALID, input, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("J"), input_format_short, JoinedOrSeparate, INVALID, input_format, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("language="), language_eq, Joined, INVALID, language, nullptr, 0, 0,
       "Default language to use (0x0-0xffff)", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("language"), language, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("l"), language_short, JoinedOrSeparate, INVALID, language, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("no-preprocess"), no_preprocess, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("output-format="), output_format_eq, Joined, INVALID, output_format, nullptr, 0, 0,
       "Output format", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("output-format"), output_format, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("output="), output_eq, Joined, INVALID, output, nullptr, 0, 0,
       "Output file", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("output"), output, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("O"), output_format_short, JoinedOrSeparate, INVALID, output_format, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("o"), output_short, JoinedOrSeparate, INVALID, output, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("preprocessor-arg="), preprocessor_arg_eq, Joined, INVALID, preprocessor_arg, nullptr, 0, 0,
       "Preprocessor command argument", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("preprocessor-arg"), preprocessor_arg, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("preprocessor="), preprocessor_eq, Joined, INVALID, preprocessor, nullptr, 0, 0,
       "Custom preprocessor command", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("preprocessor"), preprocessor, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("target="), target_eq, Joined, INVALID, target, nullptr, 0, 0,
       "Target BFD format name", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("target"), target, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("undefine="), undef_eq, Joined, INVALID, undef, nullptr, 0, 0,
       "Undefine to pass to the preprocessor", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("undefine"), undef, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("use-temp-file"), use_temp_file, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Mimic GNU windres preprocessor option handling (don't unescape preprocessor options)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("U"), undef_short, JoinedOrSeparate, INVALID, undef, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("verbose"), verbose_long, Flag, INVALID, verbose, nullptr, 0, 0,
       "Enable verbose output", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("version"), version_long, Flag, INVALID, version, nullptr, 0, 0,
       "Display version", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("V"), version, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("v"), verbose, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
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


