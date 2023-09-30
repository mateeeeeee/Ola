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
PREFIX(prefix_2, {llvm::StringLiteral("--") COMMA llvm::StringLiteral("-") COMMA llvm::StringLiteral("")})
PREFIX(prefix_1, {llvm::StringLiteral("/") COMMA llvm::StringLiteral("-") COMMA llvm::StringLiteral("")})
#undef COMMA
#endif // PREFIX

/////////
// Prefix Union

#ifdef PREFIX_UNION
#define COMMA ,
PREFIX_UNION({
llvm::StringLiteral("-") COMMA llvm::StringLiteral("--") COMMA llvm::StringLiteral("/") COMMA llvm::StringLiteral("")})
#undef COMMA
#endif // PREFIX_UNION

/////////
// ValuesCode

#ifdef OPTTABLE_VALUES_CODE
#endif
/////////
// Groups

#ifdef OPTION
OPTION(llvm::ArrayRef<llvm::StringLiteral>(), "<ml options>", ml_Group, Group, INVALID, INVALID, nullptr, 0, 0,
       "ML.EXE COMPATIBILITY OPTIONS", nullptr, nullptr)
OPTION(llvm::ArrayRef<llvm::StringLiteral>(), "unsupported", unsupported_Group, Group, INVALID, INVALID, nullptr, 0, 0,
       "UNSUPPORTED ML.EXE COMPATIBILITY OPTIONS", nullptr, nullptr)

//////////
// Options

OPTION(prefix_0, llvm::StringLiteral("<input>"), INPUT, Input, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_0, llvm::StringLiteral("<unknown>"), UNKNOWN, Unknown, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("?"), help, Flag, ml_Group, INVALID, nullptr, 0, 0,
       "Display available options", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("as-lex"), as_lex, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Lex tokens from a file without assembling", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("AT"), tiny_model_support, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Bl"), alternate_linker, Joined, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("coff"), coff_object_file, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Cp"), preserve_identifier_case, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Cu"), uppercase_identifiers, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Cx"), preserve_extern_case, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("c"), assemble_only, Flag, ml_Group, INVALID, nullptr, 0, 0,
       "Assemble only; do not link", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("debug-only="), debug_only, CommaJoined, INVALID, INVALID, nullptr, HelpHidden, 0,
       "Enable a specific type of debug output (comma separated list of types)", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("debug"), debug, Flag, INVALID, INVALID, nullptr, HelpHidden, 0,
       "Enable debug output", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("D"), define, JoinedOrSeparate, ml_Group, INVALID, nullptr, 0, 0,
       "Define <macro> to <value> (or blank if <value> omitted)", "<macro>=<value>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("EP"), output_preprocessed, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("ERRORREPORT"), errorreport, Joined, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("fatal-warnings"), fatal_warnings, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Treat warnings as errors", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Fe"), executable_file, Separate, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("filetype="), filetype, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Emit a file with the given type", nullptr, "obj,s,null")
OPTION(prefix_1, llvm::StringLiteral("FI"), code_listing_file, Joined, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Fm"), linker_map_file, Joined, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Fo"), output_file, JoinedOrSeparate, ml_Group, INVALID, nullptr, 0, 0,
       "Names the output file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("FPi"), fp_emulator_fixups, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("FR"), extended_source_browser_file, Joined, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Fr"), source_browser_file, Joined, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("F"), stacksize, Separate, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Gc"), pascal_conventions, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Gd"), c_conventions, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("gmtime"), gmtime, Flag, INVALID, utc, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("GZ"), stdcall_conventions, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help_long, Flag, ml_Group, help, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("H"), extern_name_limit, Separate, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("I"), include_path, JoinedOrSeparate, ml_Group, INVALID, nullptr, 0, 0,
       "Sets path for include files", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("m"), bitness, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Target platform (x86 or x86-64)", nullptr, "32,64")
OPTION(prefix_1, llvm::StringLiteral("nologo"), no_logo, Flag, ml_Group, INVALID, nullptr, 0, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("omf"), omf_object_file, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("output-att-asm"), output_att_asm, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Use ATT syntax for output assembly", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("preserve-comments"), preserve_comments, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Preserve comments in output assembly", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("print-imm-hex"), print_imm_hex, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Prefer hex format for immediate values in output assembly", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("safeseh"), safeseh, Flag, ml_Group, INVALID, nullptr, 0, 0,
       "Mark resulting object files as either containing no exception handlers or containing exception handlers that are all declared with .SAFESEH. Only available in 32-bit.", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("save-temp-labels"), save_temp_labels, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Don't discard temporary labels", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Sa"), full_listing, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Sf"), first_pass_listing, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("show-encoding"), show_encoding, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Show instruction encodings in output assembly", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("show-inst-operands"), show_inst_operands, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Show instructions operands as parsed", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("show-inst"), show_inst, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Show internal instruction representation in output assembly", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("SI"), listing_width, Separate, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Sn"), listing_without_symbols, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Sp"), listing_page_length, Separate, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Ss"), listing_subtitle, Separate, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("St"), listing_title, Separate, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Sx"), listing_false_conditionals, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Ta"), assembly_file, JoinedOrSeparate, ml_Group, INVALID, nullptr, 0, 0,
       "Assemble source file with the given name. Used if the filename begins with a forward slash.", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("timestamp="), timestamp, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Specify the assembly timestamp (used for @Date and @Time built-ins)", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("utc"), utc, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Render @Date and @Time built-ins in GMT/UTC", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("WX"), error_on_warning, Flag, ml_Group, fatal_warnings, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("W"), warning_level, Joined, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("w"), extra_warnings, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("X"), ignore_include_envvar, Flag, ml_Group, INVALID, nullptr, 0, 0,
       "Ignore the INCLUDE environment variable", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Zd"), line_number_info, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Zf"), export_all_symbols, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Zi"), codeview_info, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Zm"), enable_m510_option, Flag, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Zp"), structure_packing, Joined, unsupported_Group, INVALID, nullptr, HelpHidden, 0,
       "", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Zs"), parse_only, Flag, ml_Group, filetype, "null\0", 0, 0,
       "Run a syntax-check only", nullptr, nullptr)
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


