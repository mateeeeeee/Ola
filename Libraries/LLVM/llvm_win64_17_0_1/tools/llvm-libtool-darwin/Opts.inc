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

//////////
// Options

OPTION(prefix_0, llvm::StringLiteral("<input>"), INPUT, Input, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_0, llvm::StringLiteral("<unknown>"), UNKNOWN, Unknown, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("arch_only"), archType, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Specify architecture type for output library", "<arch_type>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("dependency_info"), dependencyInfoPath, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Write an Xcode dependency info file describing the dependencies of the created library", "<string>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("D"), deterministicOption, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Use zero for timestamps and UIDs/GIDs (Default)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("filelist"), fileList, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Pass in file containing a list of filenames", "<listfile[,dirname]>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display this help", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("h"), anonymous_0, Flag, INVALID, help, nullptr, 0, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("L"), librarySearchDirs, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "L<dir> adds <dir> to the list of directories in which to search for libraries", "<dir>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("l"), libraries, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "l<x> searches for the library libx.a in the library search path. If the string 'x' ends with '.o', then the library 'x' is searched for without prepending 'lib' or appending '.a'", "<x>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("no_warning_for_no_symbols"), noWarningForNoSymbols, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Do not warn about files that have no symbols", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("o"), outputFile, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Specify output filename", "<filename>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("static"), static, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Produce a statically linked library from the input files", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("syslibroot"), ignoredSyslibRoot, Separate, INVALID, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("U"), nonDeterministicOption, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Use actual timestamps and UIDs/GIDs", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("version"), version, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the version of this program", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("V"), anonymous_1, Flag, INVALID, version, nullptr, 0, 0,
       "Print the version number and exit", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("warnings_as_errors"), warningsAsErrors, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Treat warnings as errors", nullptr, nullptr)
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


