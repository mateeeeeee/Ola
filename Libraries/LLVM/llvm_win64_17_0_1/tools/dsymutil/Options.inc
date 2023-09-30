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
PREFIX(prefix_3, {llvm::StringLiteral("-") COMMA llvm::StringLiteral("--") COMMA llvm::StringLiteral("")})
PREFIX(prefix_1, {llvm::StringLiteral("--") COMMA llvm::StringLiteral("-") COMMA llvm::StringLiteral("")})
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
OPTION(llvm::ArrayRef<llvm::StringLiteral>(), "Dsymutil", grp_general, Group, INVALID, INVALID, nullptr, 0, 0,
       "Dsymutil Options", nullptr, nullptr)

//////////
// Options

OPTION(prefix_0, llvm::StringLiteral("<input>"), INPUT, Input, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_0, llvm::StringLiteral("<unknown>"), UNKNOWN, Unknown, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("accelerator="), anonymous_13, Joined, INVALID, accelerator, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("accelerator"), accelerator, Separate, grp_general, INVALID, nullptr, 0, 0,
       "Specify the desired type of accelerator table. Valid options are 'Apple' (.apple_names, .apple_namespaces, .apple_types, .apple_objc), 'Dwarf' (.debug_names), 'Pub' (.debug_pubnames, .debug_pubtypes), 'Default' and 'None'", "<accelerator type>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("arch="), anonymous_12, Joined, INVALID, arch, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("arch"), arch, Separate, grp_general, INVALID, nullptr, 0, 0,
       "Link DWARF debug information only for specified CPU architecturetypes. This option can be specified multiple times, once for eachdesired architecture. All CPU architectures will be linked bydefault.", "<arch>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("dump-debug-map"), dump_debug_map, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Parse and dump the debug map to standard output. No DWARF link will take place.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("fat64"), fat64, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Use a 64-bit header when emitting universal binaries.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("flat"), flat, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Produce a flat dSYM file (not a bundle).", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("f"), anonymous_4, Flag, grp_general, flat, nullptr, 0, 0,
       "Alias for --flat", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("gen-reproducer"), gen_reproducer, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Generate a reproducer consisting of the input object files. Alias for --reproducer=GenerateOnExit.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Prints this help output.", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("h"), anonymous_0, Flag, grp_general, help, nullptr, 0, 0,
       "Alias for --help", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("j"), anonymous_14, Separate, grp_general, INVALID, nullptr, 0, 0,
       "Alias for --num-threads", "<threads>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-function-for-static"), keep_func_for_static, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Make a static variable keep the enclosing function even if it would have been omitted otherwise.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("linker="), anonymous_19, Joined, INVALID, linker, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("linker"), linker, Separate, grp_general, INVALID, nullptr, 0, 0,
       "Specify the desired type of DWARF linker. Defaults to 'apple'", "<DWARF linker type>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-odr"), no_odr, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Do not use ODR (One Definition Rule) for type uniquing.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-output"), no_output, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Do the link in memory, but do not emit the result file.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-swiftmodule-timestamp"), no_swiftmodule_timestamp, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Don't check timestamp for swiftmodule files.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("num-threads"), threads, Separate, grp_general, INVALID, nullptr, 0, 0,
       "Specifies the maximum number of simultaneous threads to use when linking multiple architectures.", "<threads>", nullptr)
OPTION(prefix_3, llvm::StringLiteral("o="), anonymous_8, Joined, INVALID, output, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("object-prefix-map="), anonymous_10, Joined, INVALID, object_prefix_map, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("object-prefix-map"), object_prefix_map, Separate, grp_general, INVALID, nullptr, 0, 0,
       "Remap object file paths (but no source paths) before processing.Use this for Clang objects where the module cache location wasremapped using -fdebug-prefix-map; to help dsymutilfind the Clang module cache.", "<prefix=remapped>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("oso-prepend-path="), anonymous_9, Joined, INVALID, oso_prepend_path, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("oso-prepend-path"), oso_prepend_path, Separate, grp_general, INVALID, nullptr, 0, 0,
       "Specify a directory to prepend to the paths of object files.", "<path>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("out="), anonymous_7, Joined, INVALID, output, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("out"), anonymous_6, Separate, grp_general, output, nullptr, 0, 0,
       "Alias for -o", "<filename>", nullptr)
OPTION(prefix_3, llvm::StringLiteral("o"), output, Separate, grp_general, INVALID, nullptr, 0, 0,
       "Specify the output file. Defaults to <input file>.dwarf", "<filename>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("papertrail"), papertrail, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Embed warnings in the linked DWARF debug info.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("remarks-drop-without-debug"), remarks_drop_without_debug, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Drop remarks without valid debug locations. Without this flags, all remarks are kept.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("remarks-output-format="), anonymous_18, Joined, INVALID, remarks_output_format, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("remarks-output-format"), remarks_output_format, Separate, grp_general, INVALID, nullptr, 0, 0,
       "Specify the format to be used when serializing the linked remarks.", "<format>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("remarks-prepend-path="), anonymous_17, Joined, INVALID, remarks_prepend_path, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("remarks-prepend-path"), remarks_prepend_path, Separate, grp_general, INVALID, nullptr, 0, 0,
       "Specify a directory to prepend to the paths of the external remark files.", "<path>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("reproducer="), anonymous_15, Joined, INVALID, reproducer, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("reproducer"), reproducer, Separate, grp_general, INVALID, nullptr, 0, 0,
       "Specify the reproducer generation mode. Valid options are 'GenerateOnExit', 'GenerateOnCrash', 'Off'.", "<mode>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("statistics"), statistics, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Print statistics about the contribution of each object file to the linked debug info. This prints a table after linking with the object file name, the size of the debug info in the object file (in bytes) and the size contributed (in bytes) to the linked dSYM. The table is sorted by the output size listing the object files with the largest contribution first.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("symbol-map="), anonymous_11, Joined, INVALID, symbolmap, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("symbol-map"), symbolmap, Separate, grp_general, INVALID, nullptr, 0, 0,
       "Updates the existing dSYMs inplace using symbol map specified.", "<bcsymbolmap>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("symtab"), symtab, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Dumps the symbol table found in executable or object file(s) and exits.", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("S"), assembly, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Output textual assembly instead of a binary dSYM companion file.", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("s"), anonymous_3, Flag, grp_general, symtab, nullptr, 0, 0,
       "Alias for --symtab", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("toolchain"), toolchain, Separate, grp_general, INVALID, nullptr, 0, 0,
       "Embed toolchain information in dSYM bundle.", "<toolchain>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("update"), update, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Updates existing dSYM files to contain the latest accelerator tables and other DWARF optimizations.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("use-reproducer="), anonymous_16, Joined, INVALID, use_reproducer, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("use-reproducer"), use_reproducer, Separate, grp_general, INVALID, nullptr, 0, 0,
       "Use the object files from the given reproducer path.", "<path>", nullptr)
OPTION(prefix_2, llvm::StringLiteral("u"), anonymous_5, Flag, grp_general, update, nullptr, 0, 0,
       "Alias for --update", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("verbose"), verbose, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Enable verbose mode.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("verify-dwarf="), anonymous_2, Joined, INVALID, verify_dwarf, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("verify-dwarf"), verify_dwarf, Separate, grp_general, INVALID, nullptr, 0, 0,
       "Run the DWARF verifier on the input and/or output. Valid options are 'none, 'input', 'output', 'all' or 'auto' which runs the output verifier only if input verification passed.", "<verification mode>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("verify"), verify, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Alias for --verify-dwarf=output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("version"), version, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Prints the dsymutil version.", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("v"), anonymous_1, Flag, grp_general, version, nullptr, 0, 0,
       "Alias for --version", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("y"), yaml_input, Flag, grp_general, INVALID, nullptr, 0, 0,
       "Treat the input file is a YAML debug map rather than a binary.", nullptr, nullptr)
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


