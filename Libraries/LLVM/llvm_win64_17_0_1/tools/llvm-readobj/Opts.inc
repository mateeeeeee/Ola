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
OPTION(llvm::ArrayRef<llvm::StringLiteral>(), "kind", grp_coff, Group, INVALID, INVALID, nullptr, 0, 0,
       "OPTIONS (PE/COFF specific)", nullptr, nullptr)
OPTION(llvm::ArrayRef<llvm::StringLiteral>(), "kind", grp_elf, Group, INVALID, INVALID, nullptr, 0, 0,
       "OPTIONS (ELF specific)", nullptr, nullptr)
OPTION(llvm::ArrayRef<llvm::StringLiteral>(), "kind", grp_mach_o, Group, INVALID, INVALID, nullptr, 0, 0,
       "OPTIONS (Mach-O specific)", nullptr, nullptr)
OPTION(llvm::ArrayRef<llvm::StringLiteral>(), "kind", grp_xcoff, Group, INVALID, INVALID, nullptr, 0, 0,
       "OPTIONS (XCOFF specific)", nullptr, nullptr)

//////////
// Options

OPTION(prefix_0, llvm::StringLiteral("<input>"), INPUT, Input, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_0, llvm::StringLiteral("<unknown>"), UNKNOWN, Unknown, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("addrsig"), addrsig, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display address-significance table", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("all"), all, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Equivalent to setting: --file-header, --program-headers, --section-headers, --symbols, --relocations, --dynamic-table, --notes, --version-info, --unwind, --section-groups and --histogram", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("arch-specific"), arch_specific, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display architecture-specific information", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("auxiliary-header"), auxiliary_header, Flag, grp_xcoff, INVALID, nullptr, 0, 0,
       "Display the auxiliary header", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("A"), anonymous_19, Flag, INVALID, arch_specific, nullptr, 0, 0,
       "Alias for --arch-specific", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("a"), anonymous_20, Flag, INVALID, all, nullptr, 0, 0,
       "Alias for --all", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("bb-addr-map"), bb_addr_map, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the BB address map section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("cg-profile"), cg_profile, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display call graph profile section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("codeview-ghash"), codeview_ghash, Flag, grp_coff, INVALID, nullptr, 0, 0,
       "Enable global hashing for CodeView type stream de-duplication", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("codeview-merged-types"), codeview_merged_types, Flag, grp_coff, INVALID, nullptr, 0, 0,
       "Display the merged CodeView type stream", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("codeview-subsection-bytes"), codeview_subsection_bytes, Flag, grp_coff, INVALID, nullptr, 0, 0,
       "Dump raw contents of codeview debug sections and records", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("codeview"), codeview, Flag, grp_coff, INVALID, nullptr, 0, 0,
       "Display CodeView debug information", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("coff-basereloc"), coff_basereloc, Flag, grp_coff, INVALID, nullptr, 0, 0,
       "Display .reloc section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("coff-debug-directory"), coff_debug_directory, Flag, grp_coff, INVALID, nullptr, 0, 0,
       "Display debug directory", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("coff-directives"), coff_directives, Flag, grp_coff, INVALID, nullptr, 0, 0,
       "Display .drectve section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("coff-exports"), coff_exports, Flag, grp_coff, INVALID, nullptr, 0, 0,
       "Display export table", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("coff-imports"), coff_imports, Flag, grp_coff, INVALID, nullptr, 0, 0,
       "Display import table", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("coff-load-config"), coff_load_config, Flag, grp_coff, INVALID, nullptr, 0, 0,
       "Display load config", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("coff-resources"), coff_resources, Flag, grp_coff, INVALID, nullptr, 0, 0,
       "Display .rsrc section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("coff-tls-directory"), coff_tls_directory, Flag, grp_coff, INVALID, nullptr, 0, 0,
       "Display TLS directory", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("C"), anonymous_21, Flag, INVALID, demangle, nullptr, 0, 0,
       "Alias for --demangle", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("demangle"), demangle, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Demangle symbol names", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dependent-libraries"), dependent_libraries, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the dependent libraries section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dt"), anonymous_5, Flag, INVALID, dyn_syms, nullptr, 0, 0,
       "Alias for --dyn-syms", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dyn-relocations"), dyn_relocations, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the dynamic relocation entries in the file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dyn-symbols"), anonymous_9, Flag, INVALID, dyn_syms, nullptr, 0, 0,
       "Alias for --dyn-syms", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dyn-syms"), dyn_syms, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the dynamic symbol table", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dynamic-table"), dynamic_table, Flag, grp_elf, INVALID, nullptr, 0, 0,
       "Display the dynamic section table", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dynamic"), anonymous_10, Flag, INVALID, dynamic_table, nullptr, 0, 0,
       "Alias for --dynamic-table", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("d"), anonymous_22, Flag, grp_elf, dynamic_table, nullptr, 0, 0,
       "Alias for --dynamic-table", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("elf-cg-profile"), anonymous_11, Flag, INVALID, cg_profile, nullptr, HelpHidden, 0,
       "Alias for --cg-profile", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("elf-hash-histogram"), anonymous_12, Flag, INVALID, histogram, nullptr, HelpHidden, 0,
       "Alias for --histogram", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("elf-linker-options"), elf_linker_options, Flag, grp_elf, INVALID, nullptr, 0, 0,
       "Display the .linker-options section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("elf-output-style="), elf_output_style_EQ, Joined, grp_elf, INVALID, nullptr, 0, 0,
       "Specify ELF dump style: LLVM, GNU, JSON", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("elf-output-style"), anonymous_3, Separate, grp_elf, elf_output_style_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("elf-section-groups"), anonymous_13, Flag, INVALID, section_groups, nullptr, HelpHidden, 0,
       "Alias for --section-groups", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("exception-section"), exception_section, Flag, grp_xcoff, INVALID, nullptr, 0, 0,
       "Display the exception section entries", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("expand-relocs"), expand_relocs, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Expand each shown relocation to multiple lines", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("e"), anonymous_23, Flag, INVALID, headers, nullptr, 0, 0,
       "Alias for --headers", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("file-headers"), anonymous_14, Flag, INVALID, file_header, nullptr, HelpHidden, 0,
       "Alias for --file-header", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("file-header"), file_header, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display file header", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("gnu-hash-table"), gnu_hash_table, Flag, grp_elf, INVALID, nullptr, 0, 0,
       "Display the GNU hash table for dynamic symbols", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("g"), anonymous_24, Flag, grp_elf, section_groups, nullptr, 0, 0,
       "Alias for --section-groups", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("hash-symbols"), hash_symbols, Flag, grp_elf, INVALID, nullptr, 0, 0,
       "Display the dynamic symbols derived from the hash section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("hash-table"), hash_table, Flag, grp_elf, INVALID, nullptr, 0, 0,
       "Display .hash section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("headers"), headers, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Equivalent to setting: --file-header, --program-headers, --section-headers", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display this help", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("hex-dump="), hex_dump_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Display the specified section(s) as hexadecimal bytes", "<name or index>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("hex-dump"), anonymous_0, Separate, INVALID, hex_dump_EQ, nullptr, 0, 0, nullptr, "<name or index>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("histogram"), histogram, Flag, grp_elf, INVALID, nullptr, 0, 0,
       "Display bucket list histogram for hash sections", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("h"), anonymous_25, Flag, INVALID, file_header, nullptr, 0, 0,
       "Alias for --file-header", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("I"), anonymous_26, Flag, grp_elf, histogram, nullptr, 0, 0,
       "Alias for --histogram", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("loader-section-header"), loader_section_header, Flag, grp_xcoff, INVALID, nullptr, 0, 0,
       "Display the loader section header", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("loader-section-relocations"), loader_section_relocations, Flag, grp_xcoff, INVALID, nullptr, 0, 0,
       "Display the loader section relocation entries", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("loader-section-symbols"), loader_section_symbols, Flag, grp_xcoff, INVALID, nullptr, 0, 0,
       "Display the loader section symbol table", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("l"), anonymous_27, Flag, INVALID, program_headers, nullptr, 0, 0,
       "Alias for --program-headers", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("macho-data-in-code"), macho_data_in_code, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Display Data in Code command", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("macho-dysymtab"), macho_dysymtab, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Display Dysymtab command", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("macho-indirect-symbols"), macho_indirect_symbols, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Display indirect symbols", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("macho-linker-options"), macho_linker_options, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Display linker options", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("macho-segment"), macho_segment, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Display Segment command", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("macho-version-min"), macho_version_min, Flag, grp_mach_o, INVALID, nullptr, 0, 0,
       "Display version min command", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("memtag"), memtag, Flag, grp_elf, INVALID, nullptr, 0, 0,
       "Display memory tagging metadata (modes, Android notes, global descriptors)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("needed-libs"), needed_libs, Flag, grp_elf, INVALID, nullptr, 0, 0,
       "Display the needed libraries", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("no-demangle"), no_demangle, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Do not demangle symbol names (default)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("notes"), notes, Flag, grp_elf, INVALID, nullptr, 0, 0,
       "Display notes", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("n"), anonymous_28, Flag, INVALID, notes, nullptr, 0, 0,
       "Alias for --notes", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("pretty-print"), pretty_print, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Pretty print JSON output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("program-headers"), program_headers, Flag, grp_elf, INVALID, nullptr, 0, 0,
       "Display program headers", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("p"), anonymous_29, JoinedOrSeparate, INVALID, string_dump_EQ, nullptr, 0, 0,
       "Alias for --string-dump", "<name or index>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("raw-relr"), raw_relr, Flag, grp_elf, INVALID, nullptr, 0, 0,
       "Do not decode relocations in SHT_RELR section, display raw contents", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("relocations"), anonymous_15, Flag, INVALID, relocs, nullptr, 0, 0,
       "Alias for --relocs", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("relocs"), relocs, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the relocation entries in the file", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("r"), anonymous_30, Flag, INVALID, relocs, nullptr, 0, 0,
       "Alias for --relocs", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("sd"), anonymous_6, Flag, INVALID, section_data, nullptr, 0, 0,
       "Alias for --section-data", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("section-data"), section_data, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display section data for each section shown. This option has no effect for GNU style output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("section-details"), section_details, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the section details", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("section-groups"), section_groups, Flag, grp_elf, INVALID, nullptr, 0, 0,
       "Display section groups", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("section-headers"), section_headers, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display section headers", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("section-mapping=false"), section_mapping_EQ_false, Flag, INVALID, INVALID, nullptr, HelpHidden, 0,
       "Don't display the section to segment mapping", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("section-mapping"), section_mapping, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the section to segment mapping", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("section-relocations"), section_relocations, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display relocations for each section shown. This option has no effect for GNU style output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("section-symbols"), section_symbols, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display symbols for each section shown. This option has no effect for GNU style output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("sections"), anonymous_16, Flag, INVALID, section_headers, nullptr, 0, 0,
       "Alias for --section-headers", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("segments"), anonymous_17, Flag, grp_elf, program_headers, nullptr, 0, 0,
       "Alias for --program-headers", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("sort-symbols="), sort_symbols_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify the keys to sort the symbols before displaying symtab", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("sort-symbols"), anonymous_1, Separate, INVALID, sort_symbols_EQ, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("sr"), anonymous_8, Flag, INVALID, section_relocations, nullptr, 0, 0,
       "Alias for --section-relocations", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("stack-sizes"), stack_sizes, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display contents of all stack sizes sections. This option has no effect for GNU style output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("stackmap"), stackmap, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display contents of stackmap section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("string-dump="), string_dump_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Display the specified section(s) as a list of strings", "<name or index>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("string-dump"), anonymous_2, Separate, INVALID, string_dump_EQ, nullptr, 0, 0, nullptr, "<name or index>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("string-table"), string_table, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the string table (only for XCOFF now)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("st"), anonymous_7, Flag, INVALID, section_symbols, nullptr, 0, 0,
       "Alias for --section-symbols", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("symbols"), symbols, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the symbol table. Also display the dynamic symbol table when using GNU output style for ELF", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("syms"), anonymous_18, Flag, INVALID, symbols, nullptr, 0, 0,
       "Alias for --symbols", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("S"), anonymous_31, Flag, INVALID, section_headers, nullptr, 0, 0,
       "Alias for --section-headers", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("s"), anonymous_32, Flag, INVALID, symbols, nullptr, 0, 0,
       "Alias for --symbols", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("t"), anonymous_33, Flag, INVALID, section_details, nullptr, 0, 0,
       "Alias for --section-details", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("unwind"), unwind, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display unwind information", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("u"), anonymous_34, Flag, INVALID, unwind, nullptr, 0, 0,
       "Alias for --unwind", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("version-info"), version_info, Flag, grp_elf, INVALID, nullptr, 0, 0,
       "Display version sections", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("version"), version, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Display the version", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("V"), anonymous_35, Flag, grp_elf, version_info, nullptr, 0, 0,
       "Alias for --version-info", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("wide"), wide, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Ignored for GNU readelf compatibility", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("W"), anonymous_4, Flag, INVALID, wide, nullptr, 0, 0,
       "Ignored for GNU readelf compatibility", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("x"), anonymous_36, JoinedOrSeparate, INVALID, hex_dump_EQ, nullptr, 0, 0,
       "Alias for --hex-dump", "<name or index>", nullptr)
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


