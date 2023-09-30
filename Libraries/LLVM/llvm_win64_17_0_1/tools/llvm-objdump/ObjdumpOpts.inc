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
       "llvm-objdump MachO Specific Options", nullptr, nullptr)

//////////
// Options

OPTION(prefix_0, llvm::StringLiteral("<input>"), INPUT, Input, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_0, llvm::StringLiteral("<unknown>"), UNKNOWN, Unknown, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("adjust-vma="), adjust_vma_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Increase the displayed address by the specified offset", "offset", nullptr)
OPTION(prefix_1, llvm::StringLiteral("all-headers"), all_headers, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display all available header information, relocation entries and the symbol table", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("arch-name="), arch_name_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Target arch to disassemble for, see --version for available targets", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("arch="), arch_EQ, Joined, grp_mach_o, INVALID, nullptr, 0, 0,
       "architecture(s) from a Mach-O file to dump", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("archive-headers"), archive_headers, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display archive header information", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("archive-member-offsets"), archive_member_offsets, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print the offset to each archive member for Mach-O archives (requires --macho and --archive-headers)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("arch"), anonymous_30, Separate, grp_mach_o, arch_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("a"), anonymous_2, Flag, INVALID, archive_headers, nullptr, 0, 0,
       "Alias for --archive-headers", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("bind"), bind, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Display mach-o binding info", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("build-id="), build_id_eq, Joined, INVALID, build_id, nullptr, 0, 0,
       "Build ID to look up. Once found, added as an input file", "<hex>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("build-id"), build_id, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "<hex>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("chained-fixups"), chained_fixups, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print chained fixup information (requires --macho)", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("C"), anonymous_3, Flag, INVALID, demangle, nullptr, 0, 0,
       "Alias for --demangle", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("data-in-code"), data_in_code, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print the data in code table for Mach-O objects (requires --macho)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("debug-file-directory="), debug_file_directory_eq, Joined, INVALID, debug_file_directory, nullptr, 0, 0,
       "Path to directory where to look for debug files", "<dir>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("debug-file-directory"), debug_file_directory, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "<dir>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("debug-vars-indent="), debug_vars_indent_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Distance to indent the source-level variable display, relative to the start of the disassembly", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("debug-vars="), debug_vars_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Print the locations (in registers or memory) of source-level variables alongside disassembly. Supported formats: ascii, unicode (default)", nullptr, "unicode,ascii")
OPTION(prefix_1, llvm::StringLiteral("debug-vars"), anonymous_27, Flag, INVALID, debug_vars_EQ, "unicode\0", 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("debuginfod"), debuginfod, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Use debuginfod to find debug files", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("demangle"), demangle, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Demangle symbol names", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dis-symname"), dis_symname, Separate, grp_mach_o, INVALID, nullptr, 0, 0,
       "disassemble just this symbol's instructions (requires --macho)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("disassemble-all"), disassemble_all, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Disassemble all sections found in the input files", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("disassemble-symbols="), disassemble_symbols_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "List of symbols to disassemble. Accept demangled names when --demangle is specified, otherwise accept mangled names", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("disassemble-zeroes"), disassemble_zeroes, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Do not skip blocks of zeroes when disassembling", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("disassembler-options="), disassembler_options_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Pass target specific disassembler options", "options", nullptr)
OPTION(prefix_1, llvm::StringLiteral("disassemble"), disassemble, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Disassemble all executable sections found in the input files", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dsym="), dsym_EQ, Joined, grp_mach_o, INVALID, nullptr, 0, 0,
       "Use .dSYM file for debug info", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dsym"), anonymous_28, Separate, grp_mach_o, dsym_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dwarf="), dwarf_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Dump the specified DWARF debug sections. The only supported value is 'frames'", nullptr, "frames")
OPTION(prefix_1, llvm::StringLiteral("dyld-info"), dyld_info, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print bind and rebase information used by dyld to resolve external references in a final linked binary (requires --macho)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dylib-id"), dylib_id, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print the shared library's id for the dylib Mach-O file (requires --macho)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dylibs-used"), dylibs_used, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print the shared libraries used for linked Mach-O files (requires --macho)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dynamic-reloc"), dynamic_reloc, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the dynamic relocation entries in the file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dynamic-syms"), dynamic_syms, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the contents of the dynamic symbol table", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("D"), anonymous_5, Flag, INVALID, disassemble_all, nullptr, 0, 0,
       "Alias for --disassemble-all", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("d"), anonymous_4, Flag, INVALID, disassemble, nullptr, 0, 0,
       "Alias for --disassemble", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("exports-trie"), exports_trie, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Display mach-o exported symbols", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("fault-map-section"), fault_map_section, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the content of the fault map section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("file-headers"), file_headers, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the contents of the overall file header", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("full-contents"), full_contents, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the content of each section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("full-leading-addr"), full_leading_addr, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print full leading address", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("function-starts="), function_starts_EQ, Joined, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print the function starts table for Mach-O objects. Options: addrs (default), names, both (requires --macho)", nullptr, "addrs,names,both")
OPTION(prefix_1, llvm::StringLiteral("function-starts"), anonymous_29, Flag, grp_mach_o, function_starts_EQ, "addrs\0", 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("f"), anonymous_9, Flag, INVALID, file_headers, nullptr, 0, 0,
       "Alias for --file-headers", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("g"), g, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print line information from debug info if available", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("headers"), anonymous_19, Flag, INVALID, section_headers, nullptr, 0, 0,
       "Alias for --section-headers", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help-hidden"), help_hidden, Flag, INVALID, INVALID, nullptr, HelpHidden, 0,
       "Display all available options", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display available options (--help-hidden for more)", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("h"), anonymous_20, Flag, INVALID, section_headers, nullptr, 0, 0,
       "Alias for --section-headers", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("indirect-symbols"), indirect_symbols, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print indirect symbol table for Mach-O objects (requires --macho)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("info-plist"), info_plist, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print the info plist section as strings for Mach-O objects (requires --macho)", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("j"), anonymous_18, JoinedOrSeparate, INVALID, section_EQ, nullptr, 0, 0,
       "Alias for --section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("lazy-bind"), lazy_bind, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Display mach-o lazy binding info", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("line-numbers"), line_numbers, Flag, INVALID, INVALID, nullptr, 0, 0,
       "When disassembling, display source line numbers. Implies --disassemble", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("link-opt-hints"), link_opt_hints, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print the linker optimization hints for Mach-O objects (requires --macho)", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("l"), anonymous_11, Flag, INVALID, line_numbers, nullptr, 0, 0,
       "Alias for --line-numbers", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("macho"), macho, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Use MachO specific object file parser", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("mattr="), mattr_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Target specific attributes (--mattr=help for details)", "a1,+a2,-a3,...", nullptr)
OPTION(prefix_1, llvm::StringLiteral("mcpu="), mcpu_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Target a specific cpu type (--mcpu=help for details)", "cpu-name", nullptr)
OPTION(prefix_2, llvm::StringLiteral("M"), anonymous_7, JoinedOrSeparate, INVALID, disassembler_options_EQ, nullptr, 0, 0,
       "Alias for --disassembler-options=", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("m"), anonymous_12, Flag, INVALID, macho, nullptr, 0, 0,
       "Alias for --macho", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-addresses"), anonymous_13, Flag, INVALID, no_leading_addr, nullptr, 0, 0,
       "Alias for --no-leading-addr", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-debuginfod"), no_debuginfod, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Don't use debuginfod to find debug files", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-leading-addr"), no_leading_addr, Flag, INVALID, INVALID, nullptr, 0, 0,
       "When disassembling, do not print leading addresses for instructions or inline relocations", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-leading-headers"), no_leading_headers, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print no leading headers", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-print-imm-hex"), no_print_imm_hex, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Do not use hex format for immediate values", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-show-raw-insn"), no_show_raw_insn, Flag, INVALID, INVALID, nullptr, 0, 0,
       "When disassembling instructions, do not print the instruction bytes.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-symbolic-operands"), no_symbolic_operands, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "do not symbolic operands when disassembling (requires --macho)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("non-verbose"), non_verbose, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print the info for Mach-O objects in non-verbose or numeric form (requires --macho)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("objc-meta-data"), objc_meta_data, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print the Objective-C runtime meta data for Mach-O files (requires --macho)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("offloading"), offloading, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the content of the offloading section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("prefix-strip="), prefix_strip_eq, Joined, INVALID, prefix_strip, nullptr, 0, 0,
       "Strip out initial directories from absolute paths. No effect without --prefix", "prefix", nullptr)
OPTION(prefix_1, llvm::StringLiteral("prefix-strip"), prefix_strip, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "prefix", nullptr)
OPTION(prefix_1, llvm::StringLiteral("prefix="), prefix_eq, Joined, INVALID, prefix, nullptr, 0, 0,
       "Add prefix to absolute paths", "prefix", nullptr)
OPTION(prefix_1, llvm::StringLiteral("prefix"), prefix, Separate, INVALID, INVALID, nullptr, 0, 0, nullptr, "prefix", nullptr)
OPTION(prefix_1, llvm::StringLiteral("print-imm-hex=false"), anonymous_15, Flag, INVALID, no_print_imm_hex, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("print-imm-hex"), print_imm_hex, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Use hex format for immediate values (default)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("private-headers"), private_headers, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display format specific file headers", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("private-header"), private_header, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Display only the first format specific file header", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("p"), anonymous_16, Flag, INVALID, private_headers, nullptr, 0, 0,
       "Alias for --private-headers", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("raw-clang-ast"), raw_clang_ast, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Dump the raw binary contents of the clang AST section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("rebase"), rebase, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Display mach-o rebasing info", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("reloc"), reloc, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the relocation entries in the file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("rpaths"), rpaths, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print the runtime search paths for the Mach-O file (requires --macho)", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("R"), anonymous_8, Flag, INVALID, dynamic_reloc, nullptr, 0, 0,
       "Alias for --dynamic-reloc", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("r"), anonymous_14, Flag, INVALID, reloc, nullptr, 0, 0,
       "Alias for --reloc", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("section-headers"), section_headers, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display summaries of the headers for each section.", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("section="), section_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Operate on the specified sections only. With --macho dump segment,section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("section"), anonymous_17, Separate, INVALID, section_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("show-all-symbols"), show_all_symbols, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Show all symbols during disassembly, even if multiple symbols are defined at the same location", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("show-lma"), show_lma, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display LMA column when dumping ELF section headers", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("source"), source, Flag, INVALID, INVALID, nullptr, 0, 0,
       "When disassembling, display source interleaved with the disassembly. Implies --disassemble", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("start-address="), start_address_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Set the start address for disassembling, printing relocations and printing symbols", "address", nullptr)
OPTION(prefix_1, llvm::StringLiteral("stop-address="), stop_address_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Set the stop address for disassembling, printing relocations and printing symbols", "address", nullptr)
OPTION(prefix_1, llvm::StringLiteral("symbol-description"), symbol_description, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Add symbol description for disassembly. This option is for XCOFF files only", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("symbolize-operands"), symbolize_operands, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Symbolize instruction operands when disassembling", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("syms"), syms, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the symbol table", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("S"), anonymous_21, Flag, INVALID, source, nullptr, 0, 0,
       "Alias for --source", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("s"), anonymous_10, Flag, INVALID, full_contents, nullptr, 0, 0,
       "Alias for --full-contents", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("traceback-table"), traceback_table, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Decode traceback table in disassembly. Implies --disassemble. This option is for XCOFF files only", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("triple="), triple_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Target triple to disassemble for, see --version for available targets", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("triple"), anonymous_24, Separate, INVALID, triple_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("T"), anonymous_23, Flag, INVALID, dynamic_syms, nullptr, 0, 0,
       "Alias for --dynamic-syms", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("t"), anonymous_22, Flag, INVALID, syms, nullptr, 0, 0,
       "Alias for --syms", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("universal-headers"), universal_headers, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Print Mach-O universal headers (requires --macho)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("unwind-info"), unwind_info, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display unwind information", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("u"), anonymous_25, Flag, INVALID, unwind_info, nullptr, 0, 0,
       "Alias for --unwind-info", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("version"), version, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the version of this program", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("v"), anonymous_0, Flag, INVALID, version, nullptr, 0, 0,
       "Alias for --version", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("weak-bind"), weak_bind, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Display mach-o weak binding info", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("wide"), wide, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Ignored for compatibility with GNU objdump", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("w"), anonymous_26, Flag, INVALID, wide, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("x86-asm-syntax=att"), x86_asm_syntax_att, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Emit AT&T-style disassembly", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("x86-asm-syntax=intel"), x86_asm_syntax_intel, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Emit Intel-style disassembly", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("x"), anonymous_1, Flag, INVALID, all_headers, nullptr, 0, 0,
       "Alias for --all-headers", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("z"), anonymous_6, Flag, INVALID, disassemble_zeroes, nullptr, 0, 0,
       "Alias for --disassemble-zeroes", nullptr, nullptr)
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


