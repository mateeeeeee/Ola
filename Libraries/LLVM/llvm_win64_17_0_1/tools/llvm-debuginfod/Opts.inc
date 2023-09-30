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
OPTION(prefix_1, llvm::StringLiteral("c"), max_concurrency, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Maximum number of files to scan concurrently. If 0, use the hardware concurrency.", "<ulong>", nullptr)
OPTION(prefix_2, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display available options", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("h"), anonymous_0, Flag, INVALID, help, nullptr, 0, 0,
       "Alias for --help", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("i"), host_interface, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Host interface to bind to.", "<string>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("m"), min_interval, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Minimum number of seconds to wait before an on-demand update can betriggered by a request for a buildid which is not in the collection.", "<number>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("p"), port, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Port to listen on. Set to 0 to bind to any available port.", "<uint>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("t"), scan_interval, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Number of seconds to wait between subsequent automated scans of the filesystem.", "<int>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("v"), verbose_logging, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Enable verbose logging.", nullptr, nullptr)
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


