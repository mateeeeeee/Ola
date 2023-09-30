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
       "llvm-nm Mach-O Specific Options", nullptr, nullptr)
OPTION(llvm::ArrayRef<llvm::StringLiteral>(), "kind", grp_xcoff_o, Group, INVALID, INVALID, nullptr, 0, 0,
       "llvm-nm XCOFF Specific Options", nullptr, nullptr)

//////////
// Options

OPTION(prefix_0, llvm::StringLiteral("<input>"), INPUT, Input, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_0, llvm::StringLiteral("<unknown>"), UNKNOWN, Unknown, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("add-dyldinfo"), add_dyldinfo, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Add symbols from the dyldinfo not already in the symbol table", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("add-inlinedinfo"), add_inlinedinfo, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Add symbols from the inlined libraries, TBD only", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("arch="), arch_EQ, Joined, grp_mach_o, INVALID, nullptr, 0, 0,
       "architecture(s) from a Mach-O file to dump", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("arch"), anonymous_2, Separate, INVALID, arch_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("A"), anonymous_6, Flag, INVALID, print_file_name, nullptr, 0, 0,
       "Alias for --print-file-name", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("a"), anonymous_5, Flag, INVALID, debug_syms, nullptr, 0, 0,
       "Alias for --debug-syms", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("B"), anonymous_7, Flag, INVALID, format_EQ, "bsd\0", 0, 0,
       "Alias for --format=bsd", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("C"), anonymous_8, Flag, INVALID, demangle, nullptr, 0, 0,
       "Alias for --demangle", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("debug-syms"), debug_syms, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Show all symbols, even debugger only", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("defined-only"), defined_only, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Show only defined symbols", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("demangle"), demangle, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Demangle C++ symbol names", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dyldinfo-only"), dyldinfo_only, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Show only symbols from the dyldinfo", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dynamic"), dynamic, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display dynamic symbols instead of normal symbols", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("D"), anonymous_9, Flag, INVALID, dynamic, nullptr, 0, 0,
       "Alias for --dynamic", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("export-symbols"), export_symbols, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Export symbol list for all inputs", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("extern-only"), extern_only, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Show only external symbols", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("format="), format_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify output format: bsd (default), posix, sysv, darwin, just-symbols", "<format>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("format"), anonymous_0, Separate, INVALID, format_EQ, nullptr, 0, 0, nullptr, "<format>", nullptr)
OPTION(prefix_3, llvm::StringLiteral("f"), anonymous_10, JoinedOrSeparate, INVALID, format_EQ, nullptr, 0, 0,
       "Alias for --format", "<format>", nullptr)
OPTION(prefix_3, llvm::StringLiteral("g"), anonymous_12, Flag, INVALID, extern_only, nullptr, 0, 0,
       "Alias for --extern-only", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display this help", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("h"), anonymous_11, Flag, INVALID, help, nullptr, 0, 0,
       "Alias for --help", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("just-symbol-name"), anonymous_3, Flag, INVALID, format_EQ, "just-symbols\0", HelpHidden, 0,
       "Alias for --format=just-symbols", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("j"), anonymous_13, Flag, INVALID, format_EQ, "just-symbols\0", 0, 0,
       "Alias for --format=just-symbols", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("M"), anonymous_15, Flag, INVALID, print_armap, nullptr, HelpHidden, 0,
       "Deprecated alias for --print-armap", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("m"), anonymous_14, Flag, INVALID, format_EQ, "darwin\0", 0, 0,
       "Alias for --format=darwin", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-demangle"), no_demangle, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Don't demangle symbol names", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-dyldinfo"), no_dyldinfo, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Don't add any symbols from the dyldinfo", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-llvm-bc"), no_llvm_bc, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Disable LLVM bitcode reader", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-rsrc"), no_rsrc, Flag, grp_xcoff_o, INVALID, nullptr, 0, 0,
       "Exclude resource file symbols (__rsrc) from the export symbol list.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-sort"), no_sort, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Show symbols in order encountered", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-weak"), no_weak, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Show only non-weak symbols", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("numeric-sort"), numeric_sort, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Sort symbols by address", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("n"), anonymous_16, Flag, INVALID, numeric_sort, nullptr, 0, 0,
       "Alias for --numeric-sort", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("o"), anonymous_17, Flag, INVALID, print_file_name, nullptr, 0, 0,
       "Alias for --print-file-name", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("portability"), anonymous_4, Flag, INVALID, format_EQ, "posix\0", 0, 0,
       "Alias for --format=posix", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("print-armap"), print_armap, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Print the archive map", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("print-file-name"), print_file_name, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Precede each symbol with the object file it came from", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("print-size"), print_size, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Show symbol size as well as address", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("P"), anonymous_19, Flag, INVALID, format_EQ, "posix\0", 0, 0,
       "Alias for --format=posix", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("p"), anonymous_18, Flag, INVALID, no_sort, nullptr, 0, 0,
       "Alias for --no-sort", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("quiet"), quiet, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Suppress 'no symbols' diagnostic", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("radix="), radix_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Radix (o/d/x) for printing symbol Values", "<radix>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("radix"), anonymous_1, Separate, INVALID, radix_EQ, nullptr, 0, 0, nullptr, "<radix>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("reverse-sort"), reverse_sort, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Sort in reverse order", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("r"), anonymous_20, Flag, INVALID, reverse_sort, nullptr, 0, 0,
       "Alias for --reverse-sort", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("size-sort"), size_sort, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Sort symbols by size", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("special-syms"), special_syms, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Do not filter special symbols from the output", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("S"), anonymous_21, Flag, INVALID, print_size, nullptr, 0, 0,
       "Alias for --print-size", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("s"), s, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Dump only symbols from this segment and section name", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("t"), anonymous_22, JoinedOrSeparate, INVALID, radix_EQ, nullptr, 0, 0,
       "Alias for --radix", "<radix>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("undefined-only"), undefined_only, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Show only undefined symbols", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("U"), anonymous_24, Flag, INVALID, defined_only, nullptr, 0, 0,
       "Alias for --defined-only", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("u"), anonymous_23, Flag, INVALID, undefined_only, nullptr, 0, 0,
       "Alias for --undefined-only", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("version"), version, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the version", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("V"), anonymous_26, Flag, INVALID, version, nullptr, 0, 0,
       "Alias for --version", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("v"), anonymous_25, Flag, INVALID, numeric_sort, nullptr, 0, 0,
       "Alias for --numeric-sort", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("without-aliases"), without_aliases, Flag, INVALID, INVALID, nullptr, HelpHidden, 0,
       "Exclude aliases from output", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("W"), anonymous_27, Flag, INVALID, no_weak, nullptr, 0, 0,
       "Alias for --no-weak", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("X"), X, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "Specifies the type of ELF, XCOFF, or IR object file to examine. The value must be one of: 32, 64, 32_64, any (default)", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("x"), x, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print symbol entry in hex", nullptr, nullptr)
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


