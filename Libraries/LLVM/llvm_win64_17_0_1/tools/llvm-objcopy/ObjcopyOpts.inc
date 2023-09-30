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
OPTION(prefix_1, llvm::StringLiteral("add-gnu-debuglink="), add_gnu_debuglink_eq, Joined, INVALID, add_gnu_debuglink, nullptr, 0, 0,
       "Add a .gnu_debuglink for <debug-file>", "debug-file", nullptr)
OPTION(prefix_1, llvm::StringLiteral("add-gnu-debuglink"), add_gnu_debuglink, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "debug-file", nullptr)
OPTION(prefix_1, llvm::StringLiteral("add-section="), add_section_eq, Joined, INVALID, add_section, nullptr, 0, 0,
       "Make a section named <section> with the contents of <file>", "section=file", nullptr)
OPTION(prefix_1, llvm::StringLiteral("add-section"), add_section, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "section=file", nullptr)
OPTION(prefix_1, llvm::StringLiteral("add-symbol="), add_symbol_eq, Joined, INVALID, add_symbol, nullptr, 0, 0,
       "Add new symbol <name> to .symtab. Accepted flags: global, local, weak, default, hidden, protected, file, section, object, function, indirect-function. Accepted but ignored for compatibility: debug, constructor, warning, indirect, synthetic, unique-object, before", "name=[section:]value[,flags]", nullptr)
OPTION(prefix_1, llvm::StringLiteral("add-symbol"), add_symbol, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "name=[section:]value[,flags]", nullptr)
OPTION(prefix_1, llvm::StringLiteral("adjust-start"), adjust_start, JoinedOrSeparate, INVALID, change_start, nullptr, 0, 0,
       "Alias for --change-start", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("allow-broken-links"), allow_broken_links, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Allow the tool to remove sections even if it would leave invalid section references. The appropriate sh_link fields will be set to zero.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("binary-architecture="), binary_architecture_eq, Joined, INVALID, binary_architecture, nullptr, 0, 0,
       "Ignored for compatibility", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("binary-architecture"), binary_architecture, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("B"), B, JoinedOrSeparate, INVALID, binary_architecture, nullptr, 0, 0,
       "Alias for --binary-architecture", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("change-start="), change_start_eq, Joined, INVALID, change_start, nullptr, 0, 0,
       "Add <incr> to the start address. Can be specified multiple times, all values will be applied cumulatively", "incr", nullptr)
OPTION(prefix_1, llvm::StringLiteral("change-start"), change_start, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "incr", nullptr)
OPTION(prefix_1, llvm::StringLiteral("compress-debug-sections="), compress_debug_sections, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Compress DWARF debug sections using specified format. Supported formats: zlib, zstd. Select zlib if <format> is omitted", "format", nullptr)
OPTION(prefix_1, llvm::StringLiteral("compress-debug-sections"), anonymous_0, Flag, INVALID, compress_debug_sections, "zlib\0", 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("decompress-debug-sections"), decompress_debug_sections, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Decompress DWARF debug sections", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("disable-deterministic-archives"), disable_deterministic_archives, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Disable deterministic mode when operating on archives (use real values for UIDs, GIDs, and timestamps).", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("discard-all"), discard_all, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove all local symbols except file and section symbols. Also remove all debug sections", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("discard-locals"), discard_locals, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove compiler-generated local symbols, (e.g. symbols starting with .L)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dump-section="), dump_section_eq, Joined, INVALID, dump_section, nullptr, 0, 0,
       "Dump contents of section named <section> into file <file>", "section=file", nullptr)
OPTION(prefix_1, llvm::StringLiteral("dump-section"), dump_section, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "section=file", nullptr)
OPTION(prefix_2, llvm::StringLiteral("D"), D, Flag, INVALID, enable_deterministic_archives, nullptr, 0, 0,
       "Alias for --enable-deterministic-archives", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("enable-deterministic-archives"), enable_deterministic_archives, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Enable deterministic mode when operating on archives (use zero for UIDs, GIDs, and timestamps).", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("extract-dwo"), extract_dwo, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove all sections that are not DWARF .dwo sections from file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("extract-main-partition"), extract_main_partition, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Extract main partition from the input file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("extract-partition="), extract_partition_eq, Joined, INVALID, extract_partition, nullptr, 0, 0,
       "Extract named partition from input file", "name", nullptr)
OPTION(prefix_1, llvm::StringLiteral("extract-partition"), extract_partition, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "name", nullptr)
OPTION(prefix_2, llvm::StringLiteral("F"), F, JoinedOrSeparate, INVALID, target, nullptr, 0, 0,
       "Alias for --target", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("globalize-symbol="), globalize_symbol_eq, Joined, INVALID, globalize_symbol, nullptr, 0, 0,
       "Mark <symbol> as global", "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("globalize-symbols="), globalize_symbols_eq, Joined, INVALID, globalize_symbols, nullptr, 0, 0,
       "Reads a list of symbols from <filename> and marks them global", "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("globalize-symbols"), globalize_symbols, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("globalize-symbol"), globalize_symbol, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "symbol", nullptr)
OPTION(prefix_2, llvm::StringLiteral("G"), G, JoinedOrSeparate, INVALID, keep_global_symbol, nullptr, 0, 0,
       "Alias for --keep-global-symbol", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("g"), g, Flag, INVALID, strip_debug, nullptr, 0, 0,
       "Alias for --strip-debug", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("h"), h, Flag, INVALID, help, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("input-target="), input_target_eq, Joined, INVALID, input_target, nullptr, 0, 0,
       "Format of the input file", nullptr, "binary")
OPTION(prefix_1, llvm::StringLiteral("input-target"), input_target, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, "binary")
OPTION(prefix_2, llvm::StringLiteral("I"), I, JoinedOrSeparate, INVALID, input_target, nullptr, 0, 0,
       "Alias for --input-target", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("j"), j, JoinedOrSeparate, INVALID, only_section, nullptr, 0, 0,
       "Alias for --only-section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-file-symbols"), keep_file_symbols, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Do not remove file symbols", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-global-symbol="), keep_global_symbol_eq, Joined, INVALID, keep_global_symbol, nullptr, 0, 0,
       "Convert all symbols except <symbol> to local. May be repeated to convert all except a set of symbols to local", "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-global-symbols="), keep_global_symbols_eq, Joined, INVALID, keep_global_symbols, nullptr, 0, 0,
       "Reads a list of symbols from <filename> and runs as if --keep-global-symbol=<symbol> is set for each one. <filename> contains one symbol per line and may contain comments beginning with '#'. Leading and trailing whitespace is stripped from each line. May be repeated to read symbols from many files", "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-global-symbols"), keep_global_symbols, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-global-symbol"), keep_global_symbol, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-section="), keep_section_eq, Joined, INVALID, keep_section, nullptr, 0, 0,
       "Keep <section>", "section", nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-section"), keep_section, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "section", nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-symbol="), keep_symbol_eq, Joined, INVALID, keep_symbol, nullptr, 0, 0,
       "Do not remove symbol <symbol>", "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-symbols="), keep_symbols_eq, Joined, INVALID, keep_symbols, nullptr, 0, 0,
       "Reads a list of symbols from <filename> and runs as if --keep-symbol=<symbol> is set for each one. <filename> contains one symbol per line and may contain comments beginning with '#'. Leading and trailing whitespace is stripped from each line. May be repeated to read symbols from many files", "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-symbols"), keep_symbols, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-symbol"), keep_symbol, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("keep-undefined"), keep_undefined, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Do not remove undefined symbols", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("K"), K, JoinedOrSeparate, INVALID, keep_symbol, nullptr, 0, 0,
       "Alias for --keep-symbol", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("localize-hidden"), localize_hidden, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Mark all symbols that have hidden or internal visibility as local", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("localize-symbol="), localize_symbol_eq, Joined, INVALID, localize_symbol, nullptr, 0, 0,
       "Mark <symbol> as local", "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("localize-symbols="), localize_symbols_eq, Joined, INVALID, localize_symbols, nullptr, 0, 0,
       "Reads a list of symbols from <filename> and marks them local", "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("localize-symbols"), localize_symbols, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("localize-symbol"), localize_symbol, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "symbol", nullptr)
OPTION(prefix_2, llvm::StringLiteral("L"), L, JoinedOrSeparate, INVALID, localize_symbol, nullptr, 0, 0,
       "Alias for --localize-symbol", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("new-symbol-visibility="), new_symbol_visibility_eq, Joined, INVALID, new_symbol_visibility, nullptr, 0, 0,
       "Visibility of symbols generated for binary input or added with --add-symbol unless otherwise specified. The default value is 'default'", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("new-symbol-visibility"), new_symbol_visibility, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("N"), N, JoinedOrSeparate, INVALID, strip_symbol, nullptr, 0, 0,
       "Alias for --strip-symbol", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("only-keep-debug"), only_keep_debug, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Produce a debug file as the output that only preserves contents of sections useful for debugging purposes", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("only-section="), only_section_eq, Joined, INVALID, only_section, nullptr, 0, 0,
       "Remove all but <section>", "section", nullptr)
OPTION(prefix_1, llvm::StringLiteral("only-section"), only_section, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "section", nullptr)
OPTION(prefix_1, llvm::StringLiteral("output-target="), output_target_eq, Joined, INVALID, output_target, nullptr, 0, 0,
       "Format of the output file", nullptr, "binary")
OPTION(prefix_1, llvm::StringLiteral("output-target"), output_target, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, "binary")
OPTION(prefix_2, llvm::StringLiteral("O"), O, JoinedOrSeparate, INVALID, output_target, nullptr, 0, 0,
       "Alias for --output-target", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("prefix-alloc-sections="), prefix_alloc_sections_eq, Joined, INVALID, prefix_alloc_sections, nullptr, 0, 0,
       "Add <prefix> to the start of every allocated section name", "prefix", nullptr)
OPTION(prefix_1, llvm::StringLiteral("prefix-alloc-sections"), prefix_alloc_sections, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "prefix", nullptr)
OPTION(prefix_1, llvm::StringLiteral("prefix-symbols="), prefix_symbols_eq, Joined, INVALID, prefix_symbols, nullptr, 0, 0,
       "Add <prefix> to the start of every symbol name", "prefix", nullptr)
OPTION(prefix_1, llvm::StringLiteral("prefix-symbols"), prefix_symbols, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "prefix", nullptr)
OPTION(prefix_1, llvm::StringLiteral("preserve-dates"), preserve_dates, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Preserve access and modification timestamps", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("p"), p, Flag, INVALID, preserve_dates, nullptr, 0, 0,
       "Alias for --preserve-dates", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("redefine-sym="), redefine_symbol_eq, Joined, INVALID, redefine_symbol, nullptr, 0, 0,
       "Change the name of a symbol old to new", "old=new", nullptr)
OPTION(prefix_1, llvm::StringLiteral("redefine-syms="), redefine_symbols_eq, Joined, INVALID, redefine_symbols, nullptr, 0, 0,
       "Reads a list of symbol pairs from <filename> and runs as if --redefine-sym=<old>=<new> is set for each one. <filename> contains two symbols per line separated with whitespace and may contain comments beginning with '#'. Leading and trailing whitespace is stripped from each line. May be repeated to read symbols from many files", "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("redefine-syms"), redefine_symbols, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("redefine-sym"), redefine_symbol, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "old=new", nullptr)
OPTION(prefix_1, llvm::StringLiteral("regex"), regex, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Permit regular expressions in name comparison", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("remove-section="), remove_section_eq, Joined, INVALID, remove_section, nullptr, 0, 0,
       "Remove <section>", "section", nullptr)
OPTION(prefix_1, llvm::StringLiteral("remove-section"), remove_section, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "section", nullptr)
OPTION(prefix_1, llvm::StringLiteral("rename-section="), rename_section_eq, Joined, INVALID, rename_section, nullptr, 0, 0,
       "Renames a section from old to new, optionally with specified flags. Flags supported for GNU compatibility: alloc, load, noload, readonly, exclude, debug, code, data, rom, share, contents, merge, strings", "old=new[,flag1,...]", nullptr)
OPTION(prefix_1, llvm::StringLiteral("rename-section"), rename_section, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "old=new[,flag1,...]", nullptr)
OPTION(prefix_2, llvm::StringLiteral("R"), R, JoinedOrSeparate, INVALID, remove_section, nullptr, 0, 0,
       "Alias for --remove-section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("set-section-alignment="), set_section_alignment_eq, Joined, INVALID, set_section_alignment, nullptr, 0, 0,
       "Set alignment for a given section", "section=align", nullptr)
OPTION(prefix_1, llvm::StringLiteral("set-section-alignment"), set_section_alignment, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "section=align", nullptr)
OPTION(prefix_1, llvm::StringLiteral("set-section-flags="), set_section_flags_eq, Joined, INVALID, set_section_flags, nullptr, 0, 0,
       "Set section flags for a given section. Flags supported for GNU compatibility: alloc, load, noload, readonly, exclude, debug, code, data, rom, share, contents, merge, strings", "section=flag1[,flag2,...]", nullptr)
OPTION(prefix_1, llvm::StringLiteral("set-section-flags"), set_section_flags, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "section=flag1[,flag2,...]", nullptr)
OPTION(prefix_1, llvm::StringLiteral("set-section-type="), set_section_type_eq, Joined, INVALID, set_section_type, nullptr, 0, 0,
       "Set the type of section <section> to the integer <type>", "section=type", nullptr)
OPTION(prefix_1, llvm::StringLiteral("set-section-type"), set_section_type, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "section=type", nullptr)
OPTION(prefix_1, llvm::StringLiteral("set-start="), set_start_eq, Joined, INVALID, set_start, nullptr, 0, 0,
       "Set the start address to <addr>. Overrides any previous --change-start or --adjust-start values", "addr", nullptr)
OPTION(prefix_1, llvm::StringLiteral("set-start"), set_start, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "addr", nullptr)
OPTION(prefix_1, llvm::StringLiteral("split-dwo="), split_dwo_eq, Joined, INVALID, split_dwo, nullptr, 0, 0,
       "Equivalent to extract-dwo on the input file to <dwo-file>, then strip-dwo on the input file", "dwo-file", nullptr)
OPTION(prefix_1, llvm::StringLiteral("split-dwo"), split_dwo, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "dwo-file", nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-all-gnu"), strip_all_gnu, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Compatible with GNU's --strip-all", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-all"), strip_all, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove non-allocated sections outside segments. .gnu.warning* and .ARM.attribute sections are not removed", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-debug"), strip_debug, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove all debug sections", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-dwo"), strip_dwo, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove all DWARF .dwo sections from file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-non-alloc"), strip_non_alloc, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove all non-allocated sections outside segments", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-sections"), strip_sections, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove all section headers and all sections not in segments", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-symbol="), strip_symbol_eq, Joined, INVALID, strip_symbol, nullptr, 0, 0,
       "Strip <symbol>", "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-symbols="), strip_symbols_eq, Joined, INVALID, strip_symbols, nullptr, 0, 0,
       "Reads a list of symbols from <filename> and removes them", "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-symbols"), strip_symbols, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-symbol"), strip_symbol, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-unneeded-symbol="), strip_unneeded_symbol_eq, Joined, INVALID, strip_unneeded_symbol, nullptr, 0, 0,
       "Remove symbol <symbol> if it is not needed by relocations", "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-unneeded-symbols="), strip_unneeded_symbols_eq, Joined, INVALID, strip_unneeded_symbols, nullptr, 0, 0,
       "Reads a list of symbols from <filename> and removes them if they are not needed by relocations", "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-unneeded-symbols"), strip_unneeded_symbols, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-unneeded-symbol"), strip_unneeded_symbol, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("strip-unneeded"), strip_unneeded, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Remove all symbols not needed by relocations", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("subsystem="), subsystem_eq, Joined, INVALID, subsystem, nullptr, 0, 0,
       "Set PE subsystem and version", "name[:version]", nullptr)
OPTION(prefix_1, llvm::StringLiteral("subsystem"), subsystem, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "name[:version]", nullptr)
OPTION(prefix_2, llvm::StringLiteral("S"), S, Flag, INVALID, strip_all, nullptr, 0, 0,
       "Alias for --strip-all", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("target="), target_eq, Joined, INVALID, target, nullptr, 0, 0,
       "Format of the input and output file", nullptr, "binary")
OPTION(prefix_1, llvm::StringLiteral("target"), target, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, "binary")
OPTION(prefix_1, llvm::StringLiteral("update-section="), update_section_eq, Joined, INVALID, update_section, nullptr, 0, 0,
       "Replace the contents of section <name> with contents from a file <file>", "name=file", nullptr)
OPTION(prefix_1, llvm::StringLiteral("update-section"), update_section, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "name=file", nullptr)
OPTION(prefix_2, llvm::StringLiteral("U"), U, Flag, INVALID, disable_deterministic_archives, nullptr, 0, 0,
       "Alias for --disable-deterministic-archives", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("version"), version, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Print the version and exit.", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("V"), V, Flag, INVALID, version, nullptr, 0, 0,
       "Alias for --version", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("weaken-symbol="), weaken_symbol_eq, Joined, INVALID, weaken_symbol, nullptr, 0, 0,
       "Mark <symbol> as weak", "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("weaken-symbols="), weaken_symbols_eq, Joined, INVALID, weaken_symbols, nullptr, 0, 0,
       "Reads a list of symbols from <filename> and marks them weak", "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("weaken-symbols"), weaken_symbols, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "filename", nullptr)
OPTION(prefix_1, llvm::StringLiteral("weaken-symbol"), weaken_symbol, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "symbol", nullptr)
OPTION(prefix_1, llvm::StringLiteral("weaken"), weaken, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Mark all global symbols as weak", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("wildcard"), wildcard, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Allow wildcard syntax for symbol-related flags. Incompatible with --regex. Allows using '*' to match any number of characters, '?' to match any single character, '' to escape special characters, and '[]' to define character classes. Wildcards beginning with '!' will prevent a match, for example \"-N '*' -N '!x'\" will strip all symbols except for \"x\".", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("W"), W, JoinedOrSeparate, INVALID, weaken_symbol, nullptr, 0, 0,
       "Alias for --weaken-symbol", nullptr, nullptr)
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


