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
OPTION(llvm::ArrayRef<llvm::StringLiteral>(), "kind", grp_mach_o, Group, INVALID, INVALID, nullptr, 0, 0,
       "llvm-symbolizer Mach-O Specific Options", nullptr, nullptr)

//////////
// Options

OPTION(prefix_0, llvm::StringLiteral("<input>"), INPUT, Input, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_0, llvm::StringLiteral("<unknown>"), UNKNOWN, Unknown, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("addresses"), addresses, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Show address before line information", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("adjust-vma="), adjust_vma_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Add specified offset to object file addresses", "<offset>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("adjust-vma"), anonymous_0, Separate, INVALID, adjust_vma_EQ, nullptr, 0, 0, nullptr, "<offset>", nullptr)
OPTION(prefix_2, llvm::StringLiteral("a"), anonymous_11, Flag, INVALID, addresses, nullptr, 0, 0,
       "Alias for --addresses", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("basenames"), basenames, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Strip directory names from paths", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("build-id="), build_id_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Build ID used to look up the object file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("build-id"), anonymous_1, Separate, INVALID, build_id_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("cache-size="), cache_size_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Max size in bytes of the in-memory binary cache.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("cache-size"), anonymous_2, Separate, INVALID, cache_size_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("color="), color_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Whether to use color when symbolizing log markup: always, auto, never", nullptr, "always,auto,never")
OPTION(prefix_1, llvm::StringLiteral("color"), color, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Use color when symbolizing log markup.", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("C"), anonymous_13, Flag, INVALID, demangle, nullptr, 0, 0,
       "Alias for --demangle", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("debug-file-directory="), debug_file_directory_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Path to directory where to look for debug files", "<dir>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("debug-file-directory"), anonymous_3, Separate, INVALID, debug_file_directory_EQ, nullptr, 0, 0, nullptr, "<dir>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("debuginfod"), debuginfod, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Use debuginfod to find debug binaries", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("default-arch="), default_arch_EQ, Joined, grp_mach_o, INVALID, nullptr, 0, 0,
       "Default architecture (for multi-arch objects)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("default-arch"), anonymous_4, Separate, grp_mach_o, default_arch_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("demangle=false"), anonymous_29, Flag, INVALID, no_demangle, nullptr, 0, 0,
       "Alias for --no-demangle", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("demangle=true"), anonymous_28, Flag, INVALID, demangle, nullptr, 0, 0,
       "Alias for --demangle", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("demangle"), demangle, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Demangle function names", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dia"), use_dia, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Use the DIA library to access symbols (Windows only)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dsym-hint="), dsym_hint_EQ, Joined, grp_mach_o, INVALID, nullptr, 0, 0,
       "Path to .dSYM bundles to search for debug info for the object files", "<dir>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("dsym-hint"), anonymous_6, Separate, grp_mach_o, dsym_hint_EQ, nullptr, 0, 0, nullptr, "<dir>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("dwp="), dwp_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Path to DWP file to be use for any split CUs", "<file>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("dwp"), anonymous_5, Separate, INVALID, dwp_EQ, nullptr, 0, 0, nullptr, "<file>", nullptr)
OPTION(prefix_2, llvm::StringLiteral("e="), anonymous_17, Joined, INVALID, obj_EQ, nullptr, 0, 0,
       "Alias for --obj", "<file>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("exe="), anonymous_14, Joined, INVALID, obj_EQ, nullptr, 0, 0,
       "Alias for --obj", "<file>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("exe"), anonymous_15, Separate, INVALID, obj_EQ, nullptr, 0, 0,
       "Alias for --obj", "<file>", nullptr)
OPTION(prefix_2, llvm::StringLiteral("e"), anonymous_16, JoinedOrSeparate, INVALID, obj_EQ, nullptr, 0, 0,
       "Alias for --obj", "<file>", nullptr)
OPTION(prefix_2, llvm::StringLiteral("f="), anonymous_19, Joined, INVALID, functions_EQ, nullptr, 0, 0,
       "Alias for --functions=", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("fallback-debug-path="), fallback_debug_path_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Fallback path for debug binaries", "<dir>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("fallback-debug-path"), anonymous_7, Separate, INVALID, fallback_debug_path_EQ, nullptr, 0, 0, nullptr, "<dir>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("filter-markup"), filter_markup, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Filter symbolizer markup from stdin.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("functions="), functions_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Print function name for a given address", nullptr, "none,short,linkage")
OPTION(prefix_1, llvm::StringLiteral("functions"), functions, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Print function name for a given address", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("f"), anonymous_18, Flag, INVALID, functions, nullptr, 0, 0,
       "Alias for --functions", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display this help", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("h"), anonymous_20, Flag, INVALID, help, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("inlines"), inlines, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Print all inlined frames for a given address", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("inlining=false"), anonymous_27, Flag, INVALID, no_inlines, nullptr, 0, 0,
       "Alias for --no-inlines", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("inlining=true"), anonymous_26, Flag, INVALID, inlines, nullptr, 0, 0,
       "Alias for --inlines", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("inlining"), anonymous_22, Flag, INVALID, inlines, nullptr, 0, 0,
       "Alias for --inlines", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("i"), anonymous_21, Flag, INVALID, inlines, nullptr, 0, 0,
       "Alias for --inlines", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-debuginfod"), no_debuginfod, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Don't use debuginfod to find debug binaries", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-demangle"), no_demangle, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Don't demangle function names", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-inlines"), no_inlines, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Do not print inlined frames", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-untag-addresses"), no_untag_addresses, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove memory tags from addresses before symbolization", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("obj="), obj_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Path to object file to be symbolized (if not provided, object file should be specified for each input line)", "<file>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("obj"), anonymous_8, Separate, INVALID, obj_EQ, nullptr, 0, 0, nullptr, "<file>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("output-style="), output_style_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify print style. Supported styles: LLVM, GNU, JSON", "style", "LLVM,GNU,JSON")
OPTION(prefix_1, llvm::StringLiteral("output-style"), anonymous_9, Separate, INVALID, output_style_EQ, nullptr, 0, 0, nullptr, "style", "LLVM,GNU,JSON")
OPTION(prefix_1, llvm::StringLiteral("pretty-print"), pretty_print, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Make the output more human friendly", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("print-address"), anonymous_12, Flag, INVALID, addresses, nullptr, 0, 0,
       "Alias for --addresses", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("print-source-context-lines="), print_source_context_lines_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Print N lines of source file context", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("print-source-context-lines"), anonymous_10, Separate, INVALID, print_source_context_lines_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("p"), anonymous_23, Flag, INVALID, pretty_print, nullptr, 0, 0,
       "Alias for --pretty-print", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("relative-address"), relative_address, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Interpret addresses as addresses relative to the image base", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("relativenames"), relativenames, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Strip the compilation directory from paths", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("s"), anonymous_24, Flag, INVALID, basenames, nullptr, 0, 0,
       "Alias for --basenames", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("untag-addresses"), untag_addresses, Flag, INVALID, INVALID, nullptr, 0, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("use-symbol-table=true"), anonymous_30, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("verbose"), verbose, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Print verbose line info", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("version"), version, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the version", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("v"), anonymous_25, Flag, INVALID, version, nullptr, 0, 0,
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


