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
PREFIX(prefix_3, {llvm::StringLiteral("-") COMMA llvm::StringLiteral("--") COMMA llvm::StringLiteral("")})
PREFIX(prefix_4, {llvm::StringLiteral("--") COMMA llvm::StringLiteral("")})
PREFIX(prefix_2, {llvm::StringLiteral("--") COMMA llvm::StringLiteral("-") COMMA llvm::StringLiteral("")})
PREFIX(prefix_5, {llvm::StringLiteral("/") COMMA llvm::StringLiteral("")})
PREFIX(prefix_6, {llvm::StringLiteral("/") COMMA llvm::StringLiteral("-") COMMA llvm::StringLiteral("")})
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
OPTION(llvm::ArrayRef<llvm::StringLiteral>(), "my group", my_group, Group, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)

//////////
// Options

OPTION(prefix_0, llvm::StringLiteral("<input>"), INPUT, Input, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_0, llvm::StringLiteral("<unknown>"), UNKNOWN, Unknown, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("AB"), AB, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("A"), A, Flag, INVALID, INVALID, nullptr, OptFlag1, 0,
       "The A option", nullptr, nullptr)
OPTION(prefix_2, llvm::StringLiteral("blarn"), Blarn, Flag, INVALID, INVALID, nullptr, OptFlag1, 0,
       "The blarn option", nullptr, nullptr)
OPTION(prefix_3, llvm::StringLiteral("blorp"), Blorp, Flag, INVALID, INVALID, nullptr, OptFlag1, 0,
       "The blorp option", nullptr, nullptr)
OPTION(prefix_4, llvm::StringLiteral("blurmp="), Blurmpq_eq, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_4, llvm::StringLiteral("blurmp"), Blurmpq, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("B"), B, Joined, INVALID, INVALID, nullptr, OptFlag2, 0,
       "The B option", "B", nullptr)
OPTION(prefix_3, llvm::StringLiteral("C="), Ceq, Joined, INVALID, C, nullptr, OptFlag1, 0, nullptr, nullptr, nullptr)
OPTION(prefix_5, llvm::StringLiteral("cramb:"), Cramb, Joined, INVALID, INVALID, nullptr, OptFlag1, 0,
       "The cramb option", "CRAMB", nullptr)
OPTION(prefix_1, llvm::StringLiteral("C"), C, Separate, INVALID, INVALID, nullptr, OptFlag1, 0,
       "The C option", "C", nullptr)
OPTION(prefix_6, llvm::StringLiteral("C"), SLASH_C, Separate, INVALID, INVALID, nullptr, OptFlag3, 0,
       "The C option", "C", nullptr)
OPTION(prefix_1, llvm::StringLiteral("doopf1"), Doopf1, Flag, INVALID, INVALID, nullptr, OptFlag1, 0,
       "The doopf1 option", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("doopf2"), Doopf2, Flag, INVALID, INVALID, nullptr, OptFlag2, 0,
       "The doopf2 option", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("D"), D, CommaJoined, INVALID, INVALID, nullptr, 0, 0,
       "The D option", "D", nullptr)
OPTION(prefix_4, llvm::StringLiteral("ermgh"), Ermgh, Joined, INVALID, INVALID, nullptr, OptFlag1, 0,
       "The ermgh option", "ERMGH", nullptr)
OPTION(prefix_1, llvm::StringLiteral("E"), E, MultiArg, INVALID, INVALID, nullptr, OptFlag1 | OptFlag2, 2, nullptr, nullptr, nullptr)
OPTION(prefix_4, llvm::StringLiteral("fjormp"), Fjormp, Flag, INVALID, INVALID, nullptr, OptFlag1, 0,
       "The fjormp option", nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("F"), F, JoinedOrSeparate, INVALID, INVALID, nullptr, 0, 0,
       "The F option", "F", nullptr)
OPTION(prefix_4, llvm::StringLiteral("glorrmp="), Glorrmp_eq, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("G"), G, JoinedAndSeparate, INVALID, INVALID, nullptr, 0, 0,
       "The G option", "G", nullptr)
OPTION(prefix_1, llvm::StringLiteral("H"), H, Flag, INVALID, INVALID, nullptr, HelpHidden, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("I"), I, Flag, my_group, H, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("Joo"), Joo, Flag, INVALID, B, "bar\0", 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("J"), J, Flag, INVALID, B, "foo\0", 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("K"), K, Flag, INVALID, B, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("marshalled-flag-a"), marshalled_flag_a, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("marshalled-flag-b"), marshalled_flag_b, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("marshalled-flag-c"), marshalled_flag_c, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("marshalled-flag-d"), marshalled_flag_d, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("slurpjoined"), SlurpJoined, RemainingArgsJoined, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
OPTION(prefix_1, llvm::StringLiteral("slurp"), Slurp, RemainingArgs, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr)
#endif // OPTION
#ifdef OPTION_WITH_MARSHALLING
OPTION_WITH_MARSHALLING(prefix_1, llvm::StringLiteral("marshalled-flag-d"), marshalled_flag_d, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr, "-marshalled-flag-d", true, 0, X->MarshalledFlagD, false, false, false, normalizeSimpleFlag, denormalizeSimpleFlag, mergeForwardValue, extractForwardValue, -1)
#endif // OPTION_WITH_MARSHALLING
#ifdef OPTION_WITH_MARSHALLING
OPTION_WITH_MARSHALLING(prefix_1, llvm::StringLiteral("marshalled-flag-c"), marshalled_flag_c, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr, "-marshalled-flag-c", true, 0, X->MarshalledFlagC, false, false || X->MarshalledFlagD, true, normalizeSimpleFlag, denormalizeSimpleFlag, mergeForwardValue, extractForwardValue, -1)
#endif // OPTION_WITH_MARSHALLING
#ifdef OPTION_WITH_MARSHALLING
OPTION_WITH_MARSHALLING(prefix_1, llvm::StringLiteral("marshalled-flag-b"), marshalled_flag_b, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr, "-marshalled-flag-b", true, 0, X->MarshalledFlagB, false, false || X->MarshalledFlagD, true, normalizeSimpleFlag, denormalizeSimpleFlag, mergeForwardValue, extractForwardValue, -1)
#endif // OPTION_WITH_MARSHALLING
#ifdef OPTION_WITH_MARSHALLING
OPTION_WITH_MARSHALLING(prefix_1, llvm::StringLiteral("marshalled-flag-a"), marshalled_flag_a, Flag, INVALID, INVALID, nullptr, 0, 0, nullptr, nullptr, nullptr, "-marshalled-flag-a", true, 0, X->MarshalledFlagA, false, false || X->MarshalledFlagC || X->MarshalledFlagB, true, normalizeSimpleFlag, denormalizeSimpleFlag, mergeForwardValue, extractForwardValue, -1)
#endif // OPTION_WITH_MARSHALLING

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


