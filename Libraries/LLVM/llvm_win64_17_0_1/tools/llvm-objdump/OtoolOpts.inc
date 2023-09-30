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
OPTION(llvm::ArrayRef<llvm::StringLiteral>(), "kind", grp_obsolete, Group, INVALID, INVALID, nullptr, 0, 0,
       "Obsolete and unsupported flags", nullptr, nullptr)

//////////
// Options

OPTION(prefix_0, llvm::StringLiteral("<input>"), INPUT, Input, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_0, llvm::StringLiteral("<unknown>"), UNKNOWN, Unknown, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("arch"), arch, Separate, INVALID, INVALID, nullptr, 0, 0,
       "select slice of universal Mach-O file", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("B"), anonymous_1, Flag, grp_obsolete, INVALID, nullptr, HelpHidden, 0,
       "force Thum disassembly (ARM 32-bit objects only)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("chained_fixups"), chained_fixups, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print chained fixup information", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("C"), C, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print linker optimization hints", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("dyld_info"), dyld_info, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print bind and rebase information", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("D"), D, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print shared library id", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("d"), d, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print data section", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("f"), f, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print universal headers", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("G"), G, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print data-in-code table", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("help-hidden"), help_hidden, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print help for hidden flags", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("help"), help, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print help", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("H"), anonymous_2, Flag, grp_obsolete, INVALID, nullptr, HelpHidden, 0,
       "print two-level hints table", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("h"), h, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print mach header", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("I"), I, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print indirect symbol table", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("j"), j, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print opcode bytes", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("L"), L, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print used shared libraries", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("l"), l, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print load commnads", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("mcpu="), mcpu_EQ, Joined, INVALID, INVALID, nullptr, 0, 0,
       "select cpu for disassembly", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("M"), anonymous_3, Flag, grp_obsolete, INVALID, nullptr, HelpHidden, 0,
       "print module table of shared library", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("o"), o, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print Objective-C segment", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("P"), P, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print __TEXT,__info_plist section as strings", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("p"), p, Separate, INVALID, INVALID, nullptr, 0, 0,
       "start disassembly at <function name>", "<function name>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("Q"), anonymous_7, Flag, grp_obsolete, INVALID, nullptr, HelpHidden, 0,
       "llvm-otool cannot use otool-classic's disassembler", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("q"), anonymous_0, Flag, INVALID, INVALID, nullptr, HelpHidden, 0,
       "use LLVM's disassembler (default)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("R"), anonymous_4, Flag, grp_obsolete, INVALID, nullptr, HelpHidden, 0,
       "print reference table of shared library", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("r"), r, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print relocation entries", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("S"), anonymous_5, Flag, grp_obsolete, INVALID, nullptr, HelpHidden, 0,
       "print table of contents of library", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("s"), s, MultiArg, INVALID, INVALID, nullptr, 0, 2,
       "print contents of section", "<segname> <sectname>", nullptr)
OPTION(prefix_1, llvm::StringLiteral("T"), anonymous_6, Flag, grp_obsolete, INVALID, nullptr, HelpHidden, 0,
       "print table of contents of shared library", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("t"), t, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print text section", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("version"), version, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print version", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("V"), V, Flag, INVALID, INVALID, nullptr, 0, 0,
       "symbolize disassembled operands (implies -v)", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("v"), v, Flag, INVALID, INVALID, nullptr, 0, 0,
       "verbose output / disassemble when printing text sections", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("X"), X, Flag, INVALID, INVALID, nullptr, 0, 0,
       "omit leading addresses or headers", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("x"), x, Flag, INVALID, INVALID, nullptr, 0, 0,
       "print all text sections", nullptr, nullptr)
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


