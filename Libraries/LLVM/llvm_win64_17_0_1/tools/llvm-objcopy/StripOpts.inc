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
OPTION(prefix_1, llvm::StringLiteral("allow-broken-links"), allow_broken_links, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Allow the tool to remove sections even if it would leave invalid section references. The appropriate sh_link fields will be set to zero.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("disable-deterministic-archives"), disable_deterministic_archives, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Disable deterministic mode when operating on archives (use real values for UIDs, GIDs, and timestamps).", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("discard-all"), discard_all, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove all local symbols except file and section symbols. Also remove all debug sections", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("discard-locals"), discard_locals, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove compiler-generated local symbols, (e.g. symbols starting with .L)", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("D"), D, Flag, INVALID, enable_deterministic_archives, nullptr, 0, 0,
       "Alias for --enable-deterministic-archives", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("d"), d, Flag, INVALID, strip_debug, nullptr, 0, 0,
       "Alias for --strip-debug", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("enable-deterministic-archives"), enable_deterministic_archives, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Enable deterministic mode when operating on archives (use zero for UIDs, GIDs, and timestamps).", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("g"), g, Flag, INVALID, strip_debug, nullptr, 0, 0,
       "Alias for --strip-debug", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("h"), h, Flag, INVALID, help, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-file-symbols"), keep_file_symbols, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Do not remove file symbols", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-section="), keep_section_eq, Joined, INVALID, keep_section, nullptr, 0, 0,
       "Keep <section>", "section", nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-section"), keep_section, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "section", nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-symbol="), keep_symbol_eq, Joined, INVALID, keep_symbol, nullptr, 0, 0,
       "Do not remove symbol <symbol>", "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-symbol"), keep_symbol, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-undefined"), keep_undefined, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Do not remove undefined symbols", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("K"), K, JoinedOrSeparate, INVALID, keep_symbol, nullptr, 0, 0,
       "Alias for --keep-symbol", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-strip-all"), no_strip_all, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Disable --strip-all", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("N"), N, JoinedOrSeparate, INVALID, strip_symbol, nullptr, 0, 0,
       "Alias for --strip-symbol", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("only-keep-debug"), only_keep_debug, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Produce a debug file as the output that only preserves contents of sections useful for debugging purposes", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("o"), output, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "Write output to <file>", "<file>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("preserve-dates"), preserve_dates, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Preserve access and modification timestamps", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("p"), p, Flag, INVALID, preserve_dates, nullptr, 0, 0,
       "Alias for --preserve-dates", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("regex"), regex, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Permit regular expressions in name comparison", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("remove-section="), remove_section_eq, Joined, INVALID, remove_section, nullptr, 0, 0,
       "Remove <section>", "section", nullptr)
OPTION(prefix_1, llvm::StringLiteral("remove-section"), remove_section, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "section", nullptr)
OPTION(prefix_2, llvm::StringLiteral("R"), R, JoinedOrSeparate, INVALID, remove_section, nullptr, 0, 0,
       "Alias for --remove-section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-all-gnu"), strip_all_gnu, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Compatible with GNU's --strip-all", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-all"), strip_all, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove non-allocated sections outside segments. .gnu.warning* and .ARM.attribute sections are not removed", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-debug"), strip_debug, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove all debug sections", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-sections"), strip_sections, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove all section headers and all sections not in segments", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-symbol="), strip_symbol_eq, Joined, INVALID, strip_symbol, nullptr, 0, 0,
       "Strip <symbol>", "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-symbol"), strip_symbol, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-unneeded"), strip_unneeded, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove all symbols not needed by relocations", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("S"), S, Flag, INVALID, strip_debug, nullptr, 0, 0,
       "Alias for --strip-debug", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("s"), s, Flag, INVALID, strip_all, nullptr, 0, 0,
       "Alias for --strip-all", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("T"), strip_swift_symbols, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove Swift symbols", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("U"), U, Flag, INVALID, disable_deterministic_archives, nullptr, 0, 0,
       "Alias for --disable-deterministic-archives", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("version"), version, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Print the version and exit.", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("V"), V, Flag, INVALID, version, nullptr, 0, 0,
       "Alias for --version", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("wildcard"), wildcard, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Allow wildcard syntax for symbol-related flags. Incompatible with --regex. Allows using '*' to match any number of characters, '?' to match any single character, '' to escape special characters, and '[]' to define character classes. Wildcards beginning with '!' will prevent a match, for example \"-N '*' -N '!x'\" will strip all symbols except for \"x\".", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("w"), w, Flag, INVALID, wildcard, nullptr, 0, 0,
       "Alias for --wildcard", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("X"), X, Flag, INVALID, discard_locals, nullptr, 0, 0,
       "Alias for --discard-locals", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("x"), x, Flag, INVALID, discard_all, nullptr, 0, 0,
       "Alias for --discard-all", nullptr, nullptr)
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


