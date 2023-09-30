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
PREFIX(prefix_1, {llvm::StringLiteral("/") COMMA llvm::StringLiteral("-") COMMA llvm::StringLiteral("")})
#undef COMMA
#endif // PREFIX

/////////
// Prefix Union

#ifdef PREFIX_UNION
#define COMMA ,
PREFIX_UNION({
llvm::StringLiteral("-") COMMA llvm::StringLiteral("/") COMMA llvm::StringLiteral("")})
#undef COMMA
#endif // PREFIX_UNION

/////////
// ValuesCode

#ifdef OPTTABLE_VALUES_CODE
#endif
/////////
// Groups

#ifdef OPTION
OPTION(llvm::ArrayRef<llvm::StringLiteral>(), "unsupported", unsupported, Group, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)

//////////
// Options

OPTION(prefix_0, llvm::StringLiteral("<input>"), INPUT, Input, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_0, llvm::StringLiteral("<unknown>"), UNKNOWN, Unknown, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("?"), help, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("canonicalize:"), canonicalize, Flag, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("category"), category, Flag, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("check_for_duplicates:"), check_for_duplicates, Flag, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dll:"), dll, Joined, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", "dll", nullptr)
OPTION(prefix_1, llvm::StringLiteral("hashupdate:"), hash_update, Joined, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", "file", nullptr)
OPTION(prefix_1, llvm::StringLiteral("hashupdate"), hash_update_flag, Flag, unsupported, hash_update, nullptr, 0, 0,
       "Not supported", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("help"), help_long, Flag, INVALID, help, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("h"), h, Flag, INVALID, help, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("identity:"), identity, Joined, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", "identity", nullptr)
OPTION(prefix_1, llvm::StringLiteral("inputresource:"), input_resource, Joined, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", "file", nullptr)
OPTION(prefix_1, llvm::StringLiteral("makecdfs:"), make_cdfs, Flag, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("managedassemblyname:"), managed_assembly_name, Joined, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", "assembly", nullptr)
OPTION(prefix_1, llvm::StringLiteral("manifest"), manifest, Separate, INVALID, INVALID, nullptr, 0, 0,
       "Used to specify each manifest that need to be processed", "manifest", nullptr)
OPTION(prefix_1, llvm::StringLiteral("nodependency"), no_dependency, Flag, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("nologo"), no_logo, Flag, INVALID, INVALID, nullptr, 0, 0,
       "No effect as this tool never writes copyright data.  Included for parity", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("notify_update"), notify_update, Flag, INVALID, INVALID, nullptr, 0, 0,
       "Exit with a special exit code if the output file has changed", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("out:"), out, Joined, INVALID, INVALID, nullptr, 0, 0,
       "Name of the output manifest.  If this is skipped and only one manifest is being operated upon by the tool, that manifest is modified in place", "manifest", nullptr)
OPTION(prefix_1, llvm::StringLiteral("outputresource:"), output_resource, Joined, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", "file", nullptr)
OPTION(prefix_1, llvm::StringLiteral("outputresource"), output_resource_flag, Flag, unsupported, output_resource, nullptr, 0, 0,
       "Not supported", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("replacements:"), replacements, Joined, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", "file", nullptr)
OPTION(prefix_1, llvm::StringLiteral("rgs:"), rgs, Joined, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", "script", nullptr)
OPTION(prefix_1, llvm::StringLiteral("tlb:"), tlb, Joined, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", "file", nullptr)
OPTION(prefix_1, llvm::StringLiteral("updateresource:"), update_resource, Joined, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", "file", nullptr)
OPTION(prefix_1, llvm::StringLiteral("validate_file_hashes:"), validate_file_hashes, Joined, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", "", nullptr)
OPTION(prefix_1, llvm::StringLiteral("validate_manifest"), validate_manifest, Flag, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("verbose"), verbose, Flag, unsupported, INVALID, nullptr, 0, 0,
       "Not supported", nullptr, nullptr)
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


