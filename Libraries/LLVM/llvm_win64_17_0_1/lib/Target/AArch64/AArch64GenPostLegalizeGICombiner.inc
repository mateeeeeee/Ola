/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AArch64PostLegalizerCombinerImpl Combiner Match Table                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_GICOMBINER_DEPS
#include "llvm/ADT/SparseBitVector.h"
namespace llvm {
extern cl::OptionCategory GICombinerOptionCategory;
} // end namespace llvm
#endif // ifdef GET_GICOMBINER_DEPS

#ifdef GET_GICOMBINER_TYPES
struct AArch64PostLegalizerCombinerImplRuleConfig {
  SparseBitVector<> DisabledRules;

  bool isRuleEnabled(unsigned RuleID) const;
  bool parseCommandLineOption();
  bool setRuleEnabled(StringRef RuleIdentifier);
  bool setRuleDisabled(StringRef RuleIdentifier);
};

static std::optional<uint64_t> getRuleIdxForIdentifier(StringRef RuleIdentifier) {
  uint64_t I;
  // getAtInteger(...) returns false on success
  bool Parsed = !RuleIdentifier.getAsInteger(0, I);
  if (Parsed)
    return I;

#ifndef NDEBUG
  switch (RuleIdentifier.size()) {
  default: break;
  case 9:	 // 2 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'c':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "opy_prop", 8) != 0)
        break;
      return 0;	 // "copy_prop"
    case 'm':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ul_const", 8) != 0)
        break;
      return 10;	 // "mul_const"
    }
    break;
  case 10:	 // 2 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'i':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "2p_to_p2i", 9) != 0)
        break;
      return 30;	 // "i2p_to_p2i"
    case 'p':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "2i_to_i2p", 9) != 0)
        break;
      return 29;	 // "p2i_to_i2p"
    }
    break;
  case 11:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "add_sub_reg", 11) != 0)
      break;
    return 34;	 // "add_sub_reg"
  case 12:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "redundant_or", 12) != 0)
      break;
    return 9;	 // "redundant_or"
  case 13:	 // 5 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'c':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "onstant_fold", 12) != 0)
        break;
      return 23;	 // "constant_fold"
    case 'l':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "oad_and_mask", 12) != 0)
        break;
      return 2;	 // "load_and_mask"
    case 'm':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "erge_unmerge", 12) != 0)
        break;
      return 18;	 // "merge_unmerge"
    case 'r':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "edundant_and", 12) != 0)
        break;
      return 6;	 // "redundant_and"
    case 'u':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "nmerge_undef", 12) != 0)
        break;
      return 53;	 // "unmerge_undef"
    }
    break;
  case 14:	 // 2 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'b':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "inop_same_val", 13) != 0)
        break;
      return 26;	 // "binop_same_val"
    case 'f':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "neg_fneg_fold", 13) != 0)
        break;
      return 32;	 // "fneg_fneg_fold"
    }
    break;
  case 15:	 // 3 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'e':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "xtending_loads", 14) != 0)
        break;
      return 1;	 // "extending_loads"
    case 'o':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "verlapping_and", 14) != 0)
        break;
      return 41;	 // "overlapping_and"
    case 's':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "elect_same_val", 14) != 0)
        break;
      return 24;	 // "select_same_val"
    }
    break;
  case 16:	 // 3 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 's':	 // 2 strings to match.
      if (memcmp(RuleIdentifier.data()+1, "elect_", 6) != 0)
        break;
      switch (RuleIdentifier[7]) {
      default: break;
      case 't':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+8, "o_minmax", 8) != 0)
          break;
        return 55;	 // "select_to_minmax"
      case 'u':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+8, "ndef_cmp", 8) != 0)
          break;
        return 19;	 // "select_undef_cmp"
      }
      break;
    case 'u':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ndef_to_fp_zero", 15) != 0)
        break;
      return 43;	 // "undef_to_fp_zero"
    }
    break;
  case 17:	 // 4 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'a':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "nyext_trunc_fold", 16) != 0)
        break;
      return 31;	 // "anyext_trunc_fold"
    case 'e':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "rase_undef_store", 16) != 0)
        break;
      return 52;	 // "erase_undef_store"
    case 's':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "elect_to_logical", 16) != 0)
        break;
      return 21;	 // "select_to_logical"
    case 'u':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ndef_to_int_zero", 16) != 0)
        break;
      return 44;	 // "undef_to_int_zero"
    }
    break;
  case 18:	 // 4 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'b':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "inop_left_to_zero", 17) != 0)
        break;
      return 27;	 // "binop_left_to_zero"
    case 'f':	 // 2 strings to match.
      switch (RuleIdentifier[1]) {
      default: break;
      case 'o':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "ld_merge_to_zext", 16) != 0)
          break;
        return 22;	 // "fold_merge_to_zext"
      case 'p':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "trunc_fpext_fold", 16) != 0)
          break;
        return 39;	 // "fptrunc_fpext_fold"
      }
      break;
    case 'r':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ight_identity_one", 17) != 0)
        break;
      return 33;	 // "right_identity_one"
    }
    break;
  case 19:	 // 7 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'b':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "inop_right_to_zero", 18) != 0)
        break;
      return 28;	 // "binop_right_to_zero"
    case 'p':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "tr_add_immed_chain", 18) != 0)
        break;
      return 40;	 // "ptr_add_immed_chain"
    case 'r':	 // 2 strings to match.
      switch (RuleIdentifier[1]) {
      default: break;
      case 'i':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "ght_identity_zero", 17) != 0)
          break;
        return 25;	 // "right_identity_zero"
      case 'o':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "tate_out_of_range", 17) != 0)
          break;
        return 16;	 // "rotate_out_of_range"
      }
      break;
    case 's':	 // 2 strings to match.
      if (RuleIdentifier[1] != 'e')
        break;
      switch (RuleIdentifier[2]) {
      default: break;
      case 'l':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+3, "ect_constant_cmp", 16) != 0)
          break;
        return 20;	 // "select_constant_cmp"
      case 'x':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+3, "t_trunc_sextload", 16) != 0)
          break;
        return 3;	 // "sext_trunc_sextload"
      }
      break;
    case 'u':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "nary_undef_to_zero", 18) != 0)
        break;
      return 48;	 // "unary_undef_to_zero"
    }
    break;
  case 20:	 // 3 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'b':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "itcast_bitcast_fold", 19) != 0)
        break;
      return 38;	 // "bitcast_bitcast_fold"
    case 'r':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "edundant_sext_inreg", 19) != 0)
        break;
      return 11;	 // "redundant_sext_inreg"
    case 's':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "plit_store_zero_128", 19) != 0)
        break;
      return 42;	 // "split_store_zero_128"
    }
    break;
  case 21:	 // 2 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'm':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "utate_anyext_to_zext", 20) != 0)
        break;
      return 4;	 // "mutate_anyext_to_zext"
    case 'u':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ndef_to_negative_one", 20) != 0)
        break;
      return 45;	 // "undef_to_negative_one"
    }
    break;
  case 22:	 // 2 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'p':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ropagate_undef_any_op", 21) != 0)
        break;
      return 49;	 // "propagate_undef_any_op"
    case 't':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "runc_buildvector_fold", 21) != 0)
        break;
      return 36;	 // "trunc_buildvector_fold"
    }
    break;
  case 23:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "propagate_undef_all_ops", 23) != 0)
      break;
    return 50;	 // "propagate_undef_all_ops"
  case 24:	 // 2 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'b':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "inop_left_undef_to_zero", 23) != 0)
        break;
      return 46;	 // "binop_left_undef_to_zero"
    case 'x':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "or_of_and_with_same_reg", 23) != 0)
        break;
      return 7;	 // "xor_of_and_with_same_reg"
    }
    break;
  case 25:	 // 3 strings to match.
    if (RuleIdentifier[0] != 'b')
      break;
    switch (RuleIdentifier[1]) {
    default: break;
    case 'i':	 // 2 strings to match.
      if (memcmp(RuleIdentifier.data()+2, "tfield_extract_from_", 20) != 0)
        break;
      switch (RuleIdentifier[22]) {
      default: break;
      case 'a':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+23, "nd", 2) != 0)
          break;
        return 13;	 // "bitfield_extract_from_and"
      case 's':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+23, "hr", 2) != 0)
          break;
        return 14;	 // "bitfield_extract_from_shr"
      }
      break;
    case 'u':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+2, "ildvector_identity_fold", 23) != 0)
        break;
      return 35;	 // "buildvector_identity_fold"
    }
    break;
  case 26:	 // 2 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'b':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "inop_right_undef_to_undef", 25) != 0)
        break;
      return 47;	 // "binop_right_undef_to_undef"
    case 'e':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "xtractvecelt_pairwise_add", 25) != 0)
        break;
      return 8;	 // "extractvecelt_pairwise_add"
    }
    break;
  case 27:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "trunc_lshr_buildvector_fold", 27) != 0)
      break;
    return 37;	 // "trunc_lshr_buildvector_fold"
  case 28:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "propagate_undef_shuffle_mask", 28) != 0)
      break;
    return 51;	 // "propagate_undef_shuffle_mask"
  case 29:	 // 2 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'b':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "itfield_extract_from_shr_and", 28) != 0)
        break;
      return 15;	 // "bitfield_extract_from_shr_and"
    case 'i':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "cmp_to_true_false_known_bits", 28) != 0)
        break;
      return 17;	 // "icmp_to_true_false_known_bits"
    }
    break;
  case 32:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "bitfield_extract_from_sext_inreg", 32) != 0)
      break;
    return 12;	 // "bitfield_extract_from_sext_inreg"
  case 36:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "insert_extract_vec_elt_out_of_bounds", 36) != 0)
      break;
    return 54;	 // "insert_extract_vec_elt_out_of_bounds"
  case 37:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "hoist_logic_op_with_same_opcode_hands", 37) != 0)
      break;
    return 5;	 // "hoist_logic_op_with_same_opcode_hands"
  }
#endif // ifndef NDEBUG

  return std::nullopt;
}
static std::optional<std::pair<uint64_t, uint64_t>> getRuleRangeForIdentifier(StringRef RuleIdentifier) {
  std::pair<StringRef, StringRef> RangePair = RuleIdentifier.split('-');
  if (!RangePair.second.empty()) {
    const auto First = getRuleIdxForIdentifier(RangePair.first);
    const auto Last = getRuleIdxForIdentifier(RangePair.second);
    if (!First || !Last)
      return std::nullopt;
    if (First >= Last)
      report_fatal_error("Beginning of range should be before end of range");
    return {{*First, *Last + 1}};
  }
  if (RangePair.first == "*") {
    return {{0, 56}};
  }
  const auto I = getRuleIdxForIdentifier(RangePair.first);
  if (!I)
    return std::nullopt;
  return {{*I, *I + 1}};
}

bool AArch64PostLegalizerCombinerImplRuleConfig::setRuleEnabled(StringRef RuleIdentifier) {
  auto MaybeRange = getRuleRangeForIdentifier(RuleIdentifier);
  if (!MaybeRange)
    return false;
  for (auto I = MaybeRange->first; I < MaybeRange->second; ++I)
    DisabledRules.reset(I);
  return true;
}

bool AArch64PostLegalizerCombinerImplRuleConfig::setRuleDisabled(StringRef RuleIdentifier) {
  auto MaybeRange = getRuleRangeForIdentifier(RuleIdentifier);
  if (!MaybeRange)
    return false;
  for (auto I = MaybeRange->first; I < MaybeRange->second; ++I)
    DisabledRules.set(I);
  return true;
}

static std::vector<std::string> AArch64PostLegalizerCombinerOption;
static cl::list<std::string> AArch64PostLegalizerCombinerDisableOption(
    "aarch64postlegalizercombiner-disable-rule",
    cl::desc("Disable one or more combiner rules temporarily in the AArch64PostLegalizerCombiner pass"),
    cl::CommaSeparated,
    cl::Hidden,
    cl::cat(GICombinerOptionCategory),
    cl::callback([](const std::string &Str) {
      AArch64PostLegalizerCombinerOption.push_back(Str);
    }));
static cl::list<std::string> AArch64PostLegalizerCombinerOnlyEnableOption(
    "aarch64postlegalizercombiner-only-enable-rule",
    cl::desc("Disable all rules in the AArch64PostLegalizerCombiner pass then re-enable the specified ones"),
    cl::Hidden,
    cl::cat(GICombinerOptionCategory),
    cl::callback([](const std::string &CommaSeparatedArg) {
      StringRef Str = CommaSeparatedArg;
      AArch64PostLegalizerCombinerOption.push_back("*");
      do {
        auto X = Str.split(",");
        AArch64PostLegalizerCombinerOption.push_back(("!" + X.first).str());
        Str = X.second;
      } while (!Str.empty());
    }));


bool AArch64PostLegalizerCombinerImplRuleConfig::isRuleEnabled(unsigned RuleID) const {
    return  !DisabledRules.test(RuleID);
}
bool AArch64PostLegalizerCombinerImplRuleConfig::parseCommandLineOption() {
  for (StringRef Identifier : AArch64PostLegalizerCombinerOption) {
    bool Enabled = Identifier.consume_front("!");
    if (Enabled && !setRuleEnabled(Identifier))
      return false;
    if (!Enabled && !setRuleDisabled(Identifier))
      return false;
  }
  return true;
}

#endif // ifdef GET_GICOMBINER_TYPES

#ifdef GET_GICOMBINER_TYPES
const unsigned MAX_SUBTARGET_PREDICATES = 0;
using PredicateBitset = llvm::PredicateBitsetImpl<MAX_SUBTARGET_PREDICATES>;
#endif // ifdef GET_GICOMBINER_TYPES

#ifdef GET_GICOMBINER_CLASS_MEMBERS
PredicateBitset AvailableModuleFeatures;
mutable PredicateBitset AvailableFunctionFeatures;
PredicateBitset getAvailableFeatures() const {
  return AvailableModuleFeatures | AvailableFunctionFeatures;
}
PredicateBitset
computeAvailableModuleFeatures(const AArch64Subtarget *Subtarget) const;
PredicateBitset
computeAvailableFunctionFeatures(const AArch64Subtarget *Subtarget,
                                 const MachineFunction *MF) const;
void setupGeneratedPerFunctionState(MachineFunction &MF) override;
#endif // ifdef GET_GICOMBINER_CLASS_MEMBERS
#ifdef GET_GICOMBINER_CLASS_MEMBERS
  mutable MatcherState State;
  typedef ComplexRendererFns(AArch64PostLegalizerCombinerImpl::*ComplexMatcherMemFn)(MachineOperand &) const;
  typedef void(AArch64PostLegalizerCombinerImpl::*CustomRendererFn)(MachineInstrBuilder &, const MachineInstr &, int) const;
  const ExecInfoTy<PredicateBitset, ComplexMatcherMemFn, CustomRendererFn> ExecInfo;
  static AArch64PostLegalizerCombinerImpl::ComplexMatcherMemFn ComplexPredicateFns[];
  static AArch64PostLegalizerCombinerImpl::CustomRendererFn CustomRenderers[];
  bool testImmPredicate_I64(unsigned PredicateID, int64_t Imm) const override;
  bool testImmPredicate_APInt(unsigned PredicateID, const APInt &Imm) const override;
  bool testImmPredicate_APFloat(unsigned PredicateID, const APFloat &Imm) const override;
  const int64_t *getMatchTable() const override;
  bool testMIPredicate_MI(unsigned PredicateID, const MachineInstr &MI, const MatcherState &State) const override;
  bool testSimplePredicate(unsigned PredicateID) const override;
  void runCustomAction(unsigned FnID, const MatcherState &State) const override;
  struct MatchInfosTy {
    Register MDInfo3;
    std::tuple<unsigned, LLT, Register> MDInfo5;
    unsigned MDInfo8;
    InstructionStepsMatchInfo MDInfo2;
    std::function<void(MachineIRBuilder &)> MDInfo1;
    int64_t MDInfo7;
    std::function<void(MachineIRBuilder&, Register)> MDInfo6;
    PreferredTuple MDInfo0;
    APInt MDInfo9;
    std::pair<Register, Register> MDInfo4;
    PtrAddChain MDInfo10;
  };
  mutable MatchInfosTy MatchInfos;

#endif // ifdef GET_GICOMBINER_CLASS_MEMBERS

#ifdef GET_GICOMBINER_IMPL
// LLT Objects.
enum {
  GILLT_s1,
};
const static size_t NumTypeObjects = 1;
const static LLT TypeObjects[] = {
  LLT::scalar(1),
};

// Bits for subtarget features that participate in instruction matching.
enum SubtargetFeatureBits : uint8_t {
};

PredicateBitset AArch64PostLegalizerCombinerImpl::
computeAvailableModuleFeatures(const AArch64Subtarget *Subtarget) const {
  PredicateBitset Features;
  return Features;
}

void AArch64PostLegalizerCombinerImpl::setupGeneratedPerFunctionState(MachineFunction &MF) {
  AvailableFunctionFeatures = computeAvailableFunctionFeatures((const AArch64Subtarget *)&MF.getSubtarget(), &MF);
}
PredicateBitset AArch64PostLegalizerCombinerImpl::
computeAvailableFunctionFeatures(const AArch64Subtarget *Subtarget, const MachineFunction *MF) const {
  PredicateBitset Features;
  return Features;
}

// Feature bitsets.
enum {
  GIFBS_Invalid,
};
const static PredicateBitset FeatureBitsets[] {
  {}, // GIFBS_Invalid
};

// ComplexPattern predicates.
enum {
  GICP_Invalid,
};
// See constructor for table contents

AArch64PostLegalizerCombinerImpl::ComplexMatcherMemFn
AArch64PostLegalizerCombinerImpl::ComplexPredicateFns[] = {
  nullptr, // GICP_Invalid
};

enum {
  GICXXPred_MI_Predicate_GICombiner0 = GICXXPred_Invalid + 1,
  GICXXPred_MI_Predicate_GICombiner1,
  GICXXPred_MI_Predicate_GICombiner2,
  GICXXPred_MI_Predicate_GICombiner3,
  GICXXPred_MI_Predicate_GICombiner4,
  GICXXPred_MI_Predicate_GICombiner5,
  GICXXPred_MI_Predicate_GICombiner6,
  GICXXPred_MI_Predicate_GICombiner7,
  GICXXPred_MI_Predicate_GICombiner8,
  GICXXPred_MI_Predicate_GICombiner9,
  GICXXPred_MI_Predicate_GICombiner10,
  GICXXPred_MI_Predicate_GICombiner11,
  GICXXPred_MI_Predicate_GICombiner12,
  GICXXPred_MI_Predicate_GICombiner13,
  GICXXPred_MI_Predicate_GICombiner14,
  GICXXPred_MI_Predicate_GICombiner15,
  GICXXPred_MI_Predicate_GICombiner16,
  GICXXPred_MI_Predicate_GICombiner17,
  GICXXPred_MI_Predicate_GICombiner18,
  GICXXPred_MI_Predicate_GICombiner19,
  GICXXPred_MI_Predicate_GICombiner20,
  GICXXPred_MI_Predicate_GICombiner21,
  GICXXPred_MI_Predicate_GICombiner22,
  GICXXPred_MI_Predicate_GICombiner23,
  GICXXPred_MI_Predicate_GICombiner24,
  GICXXPred_MI_Predicate_GICombiner25,
  GICXXPred_MI_Predicate_GICombiner26,
  GICXXPred_MI_Predicate_GICombiner27,
  GICXXPred_MI_Predicate_GICombiner28,
  GICXXPred_MI_Predicate_GICombiner29,
  GICXXPred_MI_Predicate_GICombiner30,
  GICXXPred_MI_Predicate_GICombiner31,
  GICXXPred_MI_Predicate_GICombiner32,
  GICXXPred_MI_Predicate_GICombiner33,
  GICXXPred_MI_Predicate_GICombiner34,
  GICXXPred_MI_Predicate_GICombiner35,
  GICXXPred_MI_Predicate_GICombiner36,
  GICXXPred_MI_Predicate_GICombiner37,
  GICXXPred_MI_Predicate_GICombiner38,
  GICXXPred_MI_Predicate_GICombiner39,
  GICXXPred_MI_Predicate_GICombiner40,
  GICXXPred_MI_Predicate_GICombiner41,
  GICXXPred_MI_Predicate_GICombiner42,
  GICXXPred_MI_Predicate_GICombiner43,
  GICXXPred_MI_Predicate_GICombiner44,
  GICXXPred_MI_Predicate_GICombiner45,
  GICXXPred_MI_Predicate_GICombiner46,
  GICXXPred_MI_Predicate_GICombiner47,
  GICXXPred_MI_Predicate_GICombiner48,
  GICXXPred_MI_Predicate_GICombiner49,
};
bool AArch64PostLegalizerCombinerImpl::testMIPredicate_MI(unsigned PredicateID, const MachineInstr & MI, const MatcherState &State) const {
  switch (PredicateID) {
  case GICXXPred_MI_Predicate_GICombiner0: {
    return Helper.matchCombineCopy(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner1: {
    return Helper.matchCombineExtendingLoads(*State.MIs[0], MatchInfos.MDInfo0);
  }
  case GICXXPred_MI_Predicate_GICombiner2: {
    return Helper.matchCombineLoadWithAndMask(*State.MIs[0], MatchInfos.MDInfo1);
  }
  case GICXXPred_MI_Predicate_GICombiner3: {
    return Helper.matchSextTruncSextLoad(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner4: {
    return matchMutateAnyExtToZExt(*State.MIs[0], MRI);
  }
  case GICXXPred_MI_Predicate_GICombiner5: {
    return Helper.matchHoistLogicOpWithSameOpcodeHands(*State.MIs[0], MatchInfos.MDInfo2);
  }
  case GICXXPred_MI_Predicate_GICombiner6: {
    return Helper.matchRedundantAnd(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner7: {
    return Helper.matchXorOfAndWithSameReg(*State.MIs[0], MatchInfos.MDInfo4);
  }
  case GICXXPred_MI_Predicate_GICombiner8: {
    return matchExtractVecEltPairwiseAdd(*State.MIs[0], MRI, MatchInfos.MDInfo5);
  }
  case GICXXPred_MI_Predicate_GICombiner9: {
    return Helper.matchRedundantOr(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner10: {
    return matchAArch64MulConstCombine(*State.MIs[0], MRI, MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner11: {
    return Helper.matchRedundantSExtInReg(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner12: {
    return Helper.matchBitfieldExtractFromSExtInReg(*State.MIs[0], MatchInfos.MDInfo1);
  }
  case GICXXPred_MI_Predicate_GICombiner13: {
    return Helper.matchBitfieldExtractFromAnd(*State.MIs[0], MatchInfos.MDInfo1);
  }
  case GICXXPred_MI_Predicate_GICombiner14: {
    return Helper.matchBitfieldExtractFromShr(*State.MIs[0], MatchInfos.MDInfo1);
  }
  case GICXXPred_MI_Predicate_GICombiner15: {
    return Helper.matchBitfieldExtractFromShrAnd(*State.MIs[0], MatchInfos.MDInfo1);
  }
  case GICXXPred_MI_Predicate_GICombiner16: {
    return Helper.matchRotateOutOfRange(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner17: {
    return Helper.matchICmpToTrueFalseKnownBits(*State.MIs[0], MatchInfos.MDInfo7);
  }
  case GICXXPred_MI_Predicate_GICombiner18: {
    return Helper.matchCombineMergeUnmerge(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner19: {
    return Helper.matchUndefSelectCmp(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner20: {
    return Helper.matchConstantSelectCmp(*State.MIs[0], MatchInfos.MDInfo8);
  }
  case GICXXPred_MI_Predicate_GICombiner21: {
    return Helper.matchSelectToLogical(*State.MIs[0], MatchInfos.MDInfo1);
  }
  case GICXXPred_MI_Predicate_GICombiner22: {
    return matchFoldMergeToZext(*State.MIs[0], MRI);
  }
  case GICXXPred_MI_Predicate_GICombiner23: {
    return Helper.matchConstantFold(*State.MIs[0], MatchInfos.MDInfo9);
  }
  case GICXXPred_MI_Predicate_GICombiner24: {
    return Helper.matchSelectSameVal(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner25: {
    return Helper.matchConstantOp(State.MIs[0]->getOperand(2), 0);
  }
  case GICXXPred_MI_Predicate_GICombiner26: {
    return Helper.matchBinOpSameVal(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner27: {
    return Helper.matchOperandIsZero(*State.MIs[0], 1);
  }
  case GICXXPred_MI_Predicate_GICombiner28: {
    return Helper.matchOperandIsZero(*State.MIs[0], 2);
  }
  case GICXXPred_MI_Predicate_GICombiner29: {
    return Helper.matchCombineI2PToP2I(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner30: {
    MatchInfos.MDInfo3 = State.MIs[1]->getOperand(1).getReg(); return true;
    llvm_unreachable("GICombiner30 should have returned");
  }
  case GICXXPred_MI_Predicate_GICombiner31: {
    return Helper.matchCombineAnyExtTrunc(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner32: {
    return Helper.matchConstantOp(State.MIs[0]->getOperand(2), 1);
  }
  case GICXXPred_MI_Predicate_GICombiner33: {
    return Helper.matchAddSubSameReg(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner34: {
    return Helper.matchBuildVectorIdentityFold(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner35: {
    return Helper.matchTruncBuildVectorFold(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner36: {
    return Helper.matchTruncLshrBuildVectorFold(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner37: {
    return MRI.getType(State.MIs[1]->getOperand(1).getReg()) == MRI.getType(State.MIs[0]->getOperand(0).getReg());
  }
  case GICXXPred_MI_Predicate_GICombiner38: {
    return Helper.matchPtrAddImmedChain(*State.MIs[0], MatchInfos.MDInfo10);
  }
  case GICXXPred_MI_Predicate_GICombiner39: {
    return Helper.matchOverlappingAnd(*State.MIs[0], MatchInfos.MDInfo1);
  }
  case GICXXPred_MI_Predicate_GICombiner40: {
    return matchSplitStoreZero128(*State.MIs[0], MRI);
  }
  case GICXXPred_MI_Predicate_GICombiner41: {
    return Helper.matchAnyExplicitUseIsUndef(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner42: {
    return Helper.matchOperandIsUndef(*State.MIs[0], 1);
  }
  case GICXXPred_MI_Predicate_GICombiner43: {
    return Helper.matchOperandIsUndef(*State.MIs[0], 2);
  }
  case GICXXPred_MI_Predicate_GICombiner44: {
    return Helper.matchAllExplicitUsesAreUndef(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner45: {
    return Helper.matchUndefShuffleVectorMask(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner46: {
    return Helper.matchUndefStore(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner47: {
    return Helper.matchCombineUnmergeUndef(*State.MIs[0], MatchInfos.MDInfo1);
  }
  case GICXXPred_MI_Predicate_GICombiner48: {
    return Helper.matchInsertExtractVecEltOutOfBounds(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner49: {
    return Helper.matchSimplifySelectToMinMax(*State.MIs[0], MatchInfos.MDInfo1);
  }
  }
  llvm_unreachable("Unknown predicate");
  return false;
}
bool AArch64PostLegalizerCombinerImpl::testImmPredicate_I64(unsigned PredicateID, int64_t Imm) const {
  llvm_unreachable("Unknown predicate");
  return false;
}
bool AArch64PostLegalizerCombinerImpl::testImmPredicate_APFloat(unsigned PredicateID, const APFloat & Imm) const {
  llvm_unreachable("Unknown predicate");
  return false;
}
bool AArch64PostLegalizerCombinerImpl::testImmPredicate_APInt(unsigned PredicateID, const APInt & Imm) const {
  llvm_unreachable("Unknown predicate");
  return false;
}
enum {
  GICXXPred_Simple_IsRule0Enabled = GICXXPred_Invalid + 1,
  GICXXPred_Simple_IsRule1Enabled,
  GICXXPred_Simple_IsRule2Enabled,
  GICXXPred_Simple_IsRule3Enabled,
  GICXXPred_Simple_IsRule4Enabled,
  GICXXPred_Simple_IsRule5Enabled,
  GICXXPred_Simple_IsRule6Enabled,
  GICXXPred_Simple_IsRule7Enabled,
  GICXXPred_Simple_IsRule8Enabled,
  GICXXPred_Simple_IsRule9Enabled,
  GICXXPred_Simple_IsRule10Enabled,
  GICXXPred_Simple_IsRule11Enabled,
  GICXXPred_Simple_IsRule12Enabled,
  GICXXPred_Simple_IsRule13Enabled,
  GICXXPred_Simple_IsRule14Enabled,
  GICXXPred_Simple_IsRule15Enabled,
  GICXXPred_Simple_IsRule16Enabled,
  GICXXPred_Simple_IsRule17Enabled,
  GICXXPred_Simple_IsRule18Enabled,
  GICXXPred_Simple_IsRule19Enabled,
  GICXXPred_Simple_IsRule20Enabled,
  GICXXPred_Simple_IsRule21Enabled,
  GICXXPred_Simple_IsRule22Enabled,
  GICXXPred_Simple_IsRule23Enabled,
  GICXXPred_Simple_IsRule24Enabled,
  GICXXPred_Simple_IsRule25Enabled,
  GICXXPred_Simple_IsRule26Enabled,
  GICXXPred_Simple_IsRule27Enabled,
  GICXXPred_Simple_IsRule28Enabled,
  GICXXPred_Simple_IsRule29Enabled,
  GICXXPred_Simple_IsRule30Enabled,
  GICXXPred_Simple_IsRule31Enabled,
  GICXXPred_Simple_IsRule32Enabled,
  GICXXPred_Simple_IsRule33Enabled,
  GICXXPred_Simple_IsRule34Enabled,
  GICXXPred_Simple_IsRule35Enabled,
  GICXXPred_Simple_IsRule36Enabled,
  GICXXPred_Simple_IsRule37Enabled,
  GICXXPred_Simple_IsRule38Enabled,
  GICXXPred_Simple_IsRule39Enabled,
  GICXXPred_Simple_IsRule40Enabled,
  GICXXPred_Simple_IsRule41Enabled,
  GICXXPred_Simple_IsRule42Enabled,
  GICXXPred_Simple_IsRule43Enabled,
  GICXXPred_Simple_IsRule44Enabled,
  GICXXPred_Simple_IsRule45Enabled,
  GICXXPred_Simple_IsRule46Enabled,
  GICXXPred_Simple_IsRule47Enabled,
  GICXXPred_Simple_IsRule48Enabled,
  GICXXPred_Simple_IsRule49Enabled,
  GICXXPred_Simple_IsRule50Enabled,
  GICXXPred_Simple_IsRule51Enabled,
  GICXXPred_Simple_IsRule52Enabled,
  GICXXPred_Simple_IsRule53Enabled,
  GICXXPred_Simple_IsRule54Enabled,
  GICXXPred_Simple_IsRule55Enabled,
};

bool AArch64PostLegalizerCombinerImpl::testSimplePredicate(unsigned Predicate) const {
    return RuleConfig.isRuleEnabled(Predicate - GICXXPred_Invalid - 1);
}
// Custom renderers.
enum {
  GICR_Invalid,
};
AArch64PostLegalizerCombinerImpl::CustomRendererFn
AArch64PostLegalizerCombinerImpl::CustomRenderers[] = {
  nullptr, // GICR_Invalid
};

bool AArch64PostLegalizerCombinerImpl::tryCombineAll(MachineInstr &I) const {
  const TargetSubtargetInfo &ST = MF.getSubtarget();
  const PredicateBitset AvailableFeatures = getAvailableFeatures();
  NewMIVector OutMIs;
  State.MIs.clear();
  State.MIs.push_back(&I);
  MatchInfos = MatchInfosTy();

  if (executeMatchTable(*this, OutMIs, State, ExecInfo, getMatchTable(), *ST.getInstrInfo(), MRI, *MRI.getTargetRegisterInfo(), *ST.getRegBankInfo(), AvailableFeatures, /*CoverageInfo*/ nullptr)) {
    return true;
  }

  return false;
}

enum {
  GICXXCustomAction_CombineApplyGICombiner0 = GICXXCustomAction_Invalid + 1,
  GICXXCustomAction_CombineApplyGICombiner1,
  GICXXCustomAction_CombineApplyGICombiner2,
  GICXXCustomAction_CombineApplyGICombiner3,
  GICXXCustomAction_CombineApplyGICombiner4,
  GICXXCustomAction_CombineApplyGICombiner5,
  GICXXCustomAction_CombineApplyGICombiner6,
  GICXXCustomAction_CombineApplyGICombiner7,
  GICXXCustomAction_CombineApplyGICombiner8,
  GICXXCustomAction_CombineApplyGICombiner9,
  GICXXCustomAction_CombineApplyGICombiner10,
  GICXXCustomAction_CombineApplyGICombiner11,
  GICXXCustomAction_CombineApplyGICombiner12,
  GICXXCustomAction_CombineApplyGICombiner13,
  GICXXCustomAction_CombineApplyGICombiner14,
  GICXXCustomAction_CombineApplyGICombiner15,
  GICXXCustomAction_CombineApplyGICombiner16,
  GICXXCustomAction_CombineApplyGICombiner17,
  GICXXCustomAction_CombineApplyGICombiner18,
  GICXXCustomAction_CombineApplyGICombiner19,
  GICXXCustomAction_CombineApplyGICombiner20,
  GICXXCustomAction_CombineApplyGICombiner21,
  GICXXCustomAction_CombineApplyGICombiner22,
  GICXXCustomAction_CombineApplyGICombiner23,
  GICXXCustomAction_CombineApplyGICombiner24,
  GICXXCustomAction_CombineApplyGICombiner25,
  GICXXCustomAction_CombineApplyGICombiner26,
  GICXXCustomAction_CombineApplyGICombiner27,
};
void AArch64PostLegalizerCombinerImpl::runCustomAction(unsigned ApplyID, const MatcherState &State) const {
  switch(ApplyID) {
  case GICXXCustomAction_CombineApplyGICombiner0:{
    Helper.applyCombineCopy(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner1:{
    Helper.applyCombineExtendingLoads(*State.MIs[0], MatchInfos.MDInfo0);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner2:{
    Helper.applyBuildFn(*State.MIs[0], MatchInfos.MDInfo1);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner3:{
    Helper.applySextTruncSextLoad(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner4:{
    applyMutateAnyExtToZExt(*State.MIs[0], MRI, B, Observer);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner5:{
    Helper.applyBuildInstructionSteps(*State.MIs[0], MatchInfos.MDInfo2);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner6:{
    Helper.replaceSingleDefInstWithReg(*State.MIs[0], MatchInfos.MDInfo3);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner7:{
    Helper.applyXorOfAndWithSameReg(*State.MIs[0], MatchInfos.MDInfo4);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner8:{
    applyExtractVecEltPairwiseAdd(*State.MIs[0], MRI, B, MatchInfos.MDInfo5);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner9:{
    applyAArch64MulConstCombine(*State.MIs[0], MRI, B, MatchInfos.MDInfo6);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner10:{
    Helper.replaceSingleDefInstWithOperand(*State.MIs[0], 1);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner11:{
    Helper.applyRotateOutOfRange(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner12:{
    Helper.replaceInstWithConstant(*State.MIs[0], MatchInfos.MDInfo7);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner13:{
    Helper.replaceSingleDefInstWithOperand(*State.MIs[0], 2);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner14:{
    Helper.replaceSingleDefInstWithOperand(*State.MIs[0], MatchInfos.MDInfo8);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner15:{
    applyFoldMergeToZext(*State.MIs[0], MRI, B, Observer);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner16:{
    Helper.replaceInstWithConstant(*State.MIs[0], MatchInfos.MDInfo9);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner17:{
    Helper.applyCombineI2PToP2I(*State.MIs[0], MatchInfos.MDInfo3);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner18:{
    Helper.applyCombineP2IToI2P(*State.MIs[0], MatchInfos.MDInfo3);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner19:{
    Helper.replaceSingleDefInstWithReg(*State.MIs[0],
                                                          MatchInfos.MDInfo3);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner20:{
    Helper.replaceSingleDefInstWithReg(*State.MIs[0], State.MIs[1]->getOperand(1).getReg());
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner21:{
    Helper.applyPtrAddImmedChain(*State.MIs[0], MatchInfos.MDInfo10);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner22:{
    applySplitStoreZero128(*State.MIs[0], MRI, B, Observer);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner23:{
    Helper.replaceInstWithFConstant(*State.MIs[0], 0.0);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner24:{
    Helper.replaceInstWithConstant(*State.MIs[0], 0);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner25:{
    Helper.replaceInstWithConstant(*State.MIs[0], -1);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner26:{
    Helper.replaceInstWithUndef(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner27:{
    Helper.eraseInst(*State.MIs[0]);
    return;
  }
}
  llvm_unreachable("Unknown Apply Action");
}
const int64_t *AArch64PostLegalizerCombinerImpl::getMatchTable() const {
  constexpr static int64_t MatchTable0[] = {
    GIM_Try, /*On fail goto*//*Label 0*/ 13, // Rule ID 0 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule0Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::COPY,
      // MIs[0] d
      // No operand predicates
      // MIs[0] s
      // No operand predicates
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner0,
      // Combiner Rule #0: copy_prop
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner0,
      GIR_Done,
    // Label 0: @13
    GIM_Try, /*On fail goto*//*Label 1*/ 26, // Rule ID 1 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule1Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_LOAD,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner1,
      // Combiner Rule #1: extending_loads; wip_match_opcode alternative 'G_LOAD'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner1,
      GIR_Done,
    // Label 1: @26
    GIM_Try, /*On fail goto*//*Label 2*/ 39, // Rule ID 2 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule1Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SEXTLOAD,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner1,
      // Combiner Rule #1: extending_loads; wip_match_opcode alternative 'G_SEXTLOAD'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner1,
      GIR_Done,
    // Label 2: @39
    GIM_Try, /*On fail goto*//*Label 3*/ 52, // Rule ID 3 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule1Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ZEXTLOAD,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner1,
      // Combiner Rule #1: extending_loads; wip_match_opcode alternative 'G_ZEXTLOAD'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner1,
      GIR_Done,
    // Label 3: @52
    GIM_Try, /*On fail goto*//*Label 4*/ 138,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_AND,
      GIM_Try, /*On fail goto*//*Label 5*/ 67, // Rule ID 4 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule2Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner2,
        // Combiner Rule #2: load_and_mask; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner2,
        GIR_Done,
      // Label 5: @67
      GIM_Try, /*On fail goto*//*Label 6*/ 77, // Rule ID 7 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule5Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner5,
        // Combiner Rule #5: hoist_logic_op_with_same_opcode_hands; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner5,
        GIR_Done,
      // Label 6: @77
      GIM_Try, /*On fail goto*//*Label 7*/ 87, // Rule ID 10 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule6Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner6,
        // Combiner Rule #6: redundant_and; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner6,
        GIR_Done,
      // Label 7: @87
      GIM_Try, /*On fail goto*//*Label 8*/ 97, // Rule ID 17 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule13Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner13,
        // Combiner Rule #13: bitfield_extract_from_and; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner2,
        GIR_Done,
      // Label 8: @97
      GIM_Try, /*On fail goto*//*Label 9*/ 107, // Rule ID 33 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule23Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner23,
        // Combiner Rule #23: constant_fold; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner16,
        GIR_Done,
      // Label 9: @107
      GIM_Try, /*On fail goto*//*Label 10*/ 117, // Rule ID 47 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule26Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner26,
        // Combiner Rule #26: binop_same_val; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 10: @117
      GIM_Try, /*On fail goto*//*Label 11*/ 127, // Rule ID 67 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule41Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner39,
        // Combiner Rule #41: overlapping_and; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner2,
        GIR_Done,
      // Label 11: @127
      GIM_Try, /*On fail goto*//*Label 12*/ 137, // Rule ID 71 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule44Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner41,
        // Combiner Rule #44: undef_to_int_zero; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner24,
        GIR_Done,
      // Label 12: @137
      GIM_Reject,
    // Label 4: @138
    GIM_Try, /*On fail goto*//*Label 13*/ 174,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SEXT_INREG,
      GIM_Try, /*On fail goto*//*Label 14*/ 153, // Rule ID 5 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule3Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner3,
        // Combiner Rule #3: sext_trunc_sextload; wip_match_opcode alternative 'G_SEXT_INREG'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner3,
        GIR_Done,
      // Label 14: @153
      GIM_Try, /*On fail goto*//*Label 15*/ 163, // Rule ID 15 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule11Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner11,
        // Combiner Rule #11: redundant_sext_inreg; wip_match_opcode alternative 'G_SEXT_INREG'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 15: @163
      GIM_Try, /*On fail goto*//*Label 16*/ 173, // Rule ID 16 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule12Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner12,
        // Combiner Rule #12: bitfield_extract_from_sext_inreg; wip_match_opcode alternative 'G_SEXT_INREG'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner2,
        GIR_Done,
      // Label 16: @173
      GIM_Reject,
    // Label 13: @174
    GIM_Try, /*On fail goto*//*Label 17*/ 200,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ANYEXT,
      GIM_Try, /*On fail goto*//*Label 18*/ 189, // Rule ID 6 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule4Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner4,
        // Combiner Rule #4: mutate_anyext_to_zext; wip_match_opcode alternative 'G_ANYEXT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 18: @189
      GIM_Try, /*On fail goto*//*Label 19*/ 199, // Rule ID 56 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule31Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner31,
        // Combiner Rule #31: anyext_trunc_fold; wip_match_opcode alternative 'G_ANYEXT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner6,
        GIR_Done,
      // Label 19: @199
      GIM_Reject,
    // Label 17: @200
    GIM_Try, /*On fail goto*//*Label 20*/ 266,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_OR,
      GIM_Try, /*On fail goto*//*Label 21*/ 215, // Rule ID 8 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule5Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner5,
        // Combiner Rule #5: hoist_logic_op_with_same_opcode_hands; wip_match_opcode alternative 'G_OR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner5,
        GIR_Done,
      // Label 21: @215
      GIM_Try, /*On fail goto*//*Label 22*/ 225, // Rule ID 13 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule9Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner9,
        // Combiner Rule #9: redundant_or; wip_match_opcode alternative 'G_OR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner6,
        GIR_Done,
      // Label 22: @225
      GIM_Try, /*On fail goto*//*Label 23*/ 235, // Rule ID 34 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule23Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner23,
        // Combiner Rule #23: constant_fold; wip_match_opcode alternative 'G_OR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner16,
        GIR_Done,
      // Label 23: @235
      GIM_Try, /*On fail goto*//*Label 24*/ 245, // Rule ID 39 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule25Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner25,
        // Combiner Rule #25: right_identity_zero; wip_match_opcode alternative 'G_OR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 24: @245
      GIM_Try, /*On fail goto*//*Label 25*/ 255, // Rule ID 48 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule26Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner26,
        // Combiner Rule #26: binop_same_val; wip_match_opcode alternative 'G_OR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 25: @255
      GIM_Try, /*On fail goto*//*Label 26*/ 265, // Rule ID 73 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule45Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner41,
        // Combiner Rule #45: undef_to_negative_one; wip_match_opcode alternative 'G_OR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
        GIR_Done,
      // Label 26: @265
      GIM_Reject,
    // Label 20: @266
    GIM_Try, /*On fail goto*//*Label 27*/ 322,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_XOR,
      GIM_Try, /*On fail goto*//*Label 28*/ 281, // Rule ID 9 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule5Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner5,
        // Combiner Rule #5: hoist_logic_op_with_same_opcode_hands; wip_match_opcode alternative 'G_XOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner5,
        GIR_Done,
      // Label 28: @281
      GIM_Try, /*On fail goto*//*Label 29*/ 291, // Rule ID 11 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule7Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner7,
        // Combiner Rule #7: xor_of_and_with_same_reg; wip_match_opcode alternative 'G_XOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner7,
        GIR_Done,
      // Label 29: @291
      GIM_Try, /*On fail goto*//*Label 30*/ 301, // Rule ID 35 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule23Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner23,
        // Combiner Rule #23: constant_fold; wip_match_opcode alternative 'G_XOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner16,
        GIR_Done,
      // Label 30: @301
      GIM_Try, /*On fail goto*//*Label 31*/ 311, // Rule ID 40 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule25Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner25,
        // Combiner Rule #25: right_identity_zero; wip_match_opcode alternative 'G_XOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 31: @311
      GIM_Try, /*On fail goto*//*Label 32*/ 321, // Rule ID 85 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule49Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner41,
        // Combiner Rule #49: propagate_undef_any_op; wip_match_opcode alternative 'G_XOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner26,
        GIR_Done,
      // Label 32: @321
      GIM_Reject,
    // Label 27: @322
    GIM_Try, /*On fail goto*//*Label 33*/ 348,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_EXTRACT_VECTOR_ELT,
      GIM_Try, /*On fail goto*//*Label 34*/ 337, // Rule ID 12 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule8Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner8,
        // Combiner Rule #8: extractvecelt_pairwise_add; wip_match_opcode alternative 'G_EXTRACT_VECTOR_ELT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner8,
        GIR_Done,
      // Label 34: @337
      GIM_Try, /*On fail goto*//*Label 35*/ 347, // Rule ID 92 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule54Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner48,
        // Combiner Rule #54: insert_extract_vec_elt_out_of_bounds; wip_match_opcode alternative 'G_EXTRACT_VECTOR_ELT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner26,
        GIR_Done,
      // Label 35: @347
      GIM_Reject,
    // Label 33: @348
    GIM_Try, /*On fail goto*//*Label 36*/ 404,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_MUL,
      GIM_Try, /*On fail goto*//*Label 37*/ 363, // Rule ID 14 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule10Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner10,
        // Combiner Rule #10: mul_const; wip_match_opcode alternative 'G_MUL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 37: @363
      GIM_Try, /*On fail goto*//*Label 38*/ 373, // Rule ID 32 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule23Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner23,
        // Combiner Rule #23: constant_fold; wip_match_opcode alternative 'G_MUL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner16,
        GIR_Done,
      // Label 38: @373
      GIM_Try, /*On fail goto*//*Label 39*/ 383, // Rule ID 53 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule28Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner28,
        // Combiner Rule #28: binop_right_to_zero; wip_match_opcode alternative 'G_MUL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner13,
        GIR_Done,
      // Label 39: @383
      GIM_Try, /*On fail goto*//*Label 40*/ 393, // Rule ID 58 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule33Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner32,
        // Combiner Rule #33: right_identity_one; wip_match_opcode alternative 'G_MUL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 40: @393
      GIM_Try, /*On fail goto*//*Label 41*/ 403, // Rule ID 72 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule44Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner41,
        // Combiner Rule #44: undef_to_int_zero; wip_match_opcode alternative 'G_MUL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner24,
        GIR_Done,
      // Label 41: @403
      GIM_Reject,
    // Label 36: @404
    GIM_Try, /*On fail goto*//*Label 42*/ 450,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ASHR,
      GIM_Try, /*On fail goto*//*Label 43*/ 419, // Rule ID 18 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule14Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner14,
        // Combiner Rule #14: bitfield_extract_from_shr; wip_match_opcode alternative 'G_ASHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner2,
        GIR_Done,
      // Label 43: @419
      GIM_Try, /*On fail goto*//*Label 44*/ 429, // Rule ID 20 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule15Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner15,
        // Combiner Rule #15: bitfield_extract_from_shr_and; wip_match_opcode alternative 'G_ASHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner2,
        GIR_Done,
      // Label 44: @429
      GIM_Try, /*On fail goto*//*Label 45*/ 439, // Rule ID 42 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule25Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner25,
        // Combiner Rule #25: right_identity_zero; wip_match_opcode alternative 'G_ASHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 45: @439
      GIM_Try, /*On fail goto*//*Label 46*/ 449, // Rule ID 78 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule47Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner43,
        // Combiner Rule #47: binop_right_undef_to_undef; wip_match_opcode alternative 'G_ASHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner26,
        GIR_Done,
      // Label 46: @449
      GIM_Reject,
    // Label 42: @450
    GIM_Try, /*On fail goto*//*Label 47*/ 496,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_LSHR,
      GIM_Try, /*On fail goto*//*Label 48*/ 465, // Rule ID 19 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule14Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner14,
        // Combiner Rule #14: bitfield_extract_from_shr; wip_match_opcode alternative 'G_LSHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner2,
        GIR_Done,
      // Label 48: @465
      GIM_Try, /*On fail goto*//*Label 49*/ 475, // Rule ID 21 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule15Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner15,
        // Combiner Rule #15: bitfield_extract_from_shr_and; wip_match_opcode alternative 'G_LSHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner2,
        GIR_Done,
      // Label 49: @475
      GIM_Try, /*On fail goto*//*Label 50*/ 485, // Rule ID 43 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule25Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner25,
        // Combiner Rule #25: right_identity_zero; wip_match_opcode alternative 'G_LSHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 50: @485
      GIM_Try, /*On fail goto*//*Label 51*/ 495, // Rule ID 79 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule47Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner43,
        // Combiner Rule #47: binop_right_undef_to_undef; wip_match_opcode alternative 'G_LSHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner26,
        GIR_Done,
      // Label 51: @495
      GIM_Reject,
    // Label 47: @496
    GIM_Try, /*On fail goto*//*Label 52*/ 522,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ROTR,
      GIM_Try, /*On fail goto*//*Label 53*/ 511, // Rule ID 22 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule16Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner16,
        // Combiner Rule #16: rotate_out_of_range; wip_match_opcode alternative 'G_ROTR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner11,
        GIR_Done,
      // Label 53: @511
      GIM_Try, /*On fail goto*//*Label 54*/ 521, // Rule ID 46 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule25Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner25,
        // Combiner Rule #25: right_identity_zero; wip_match_opcode alternative 'G_ROTR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 54: @521
      GIM_Reject,
    // Label 52: @522
    GIM_Try, /*On fail goto*//*Label 55*/ 548,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ROTL,
      GIM_Try, /*On fail goto*//*Label 56*/ 537, // Rule ID 23 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule16Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner16,
        // Combiner Rule #16: rotate_out_of_range; wip_match_opcode alternative 'G_ROTL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner11,
        GIR_Done,
      // Label 56: @537
      GIM_Try, /*On fail goto*//*Label 57*/ 547, // Rule ID 45 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule25Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner25,
        // Combiner Rule #25: right_identity_zero; wip_match_opcode alternative 'G_ROTL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 57: @547
      GIM_Reject,
    // Label 55: @548
    GIM_Try, /*On fail goto*//*Label 58*/ 561, // Rule ID 24 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule17Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ICMP,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner17,
      // Combiner Rule #17: icmp_to_true_false_known_bits; wip_match_opcode alternative 'G_ICMP'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner12,
      GIR_Done,
    // Label 58: @561
    GIM_Try, /*On fail goto*//*Label 59*/ 587,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_MERGE_VALUES,
      GIM_Try, /*On fail goto*//*Label 60*/ 576, // Rule ID 25 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule18Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner18,
        // Combiner Rule #18: merge_unmerge; wip_match_opcode alternative 'G_MERGE_VALUES'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner6,
        GIR_Done,
      // Label 60: @576
      GIM_Try, /*On fail goto*//*Label 61*/ 586, // Rule ID 29 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule22Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner22,
        // Combiner Rule #22: fold_merge_to_zext; wip_match_opcode alternative 'G_MERGE_VALUES'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner15,
        GIR_Done,
      // Label 61: @586
      GIM_Reject,
    // Label 59: @587
    GIM_Try, /*On fail goto*//*Label 62*/ 643,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SELECT,
      GIM_Try, /*On fail goto*//*Label 63*/ 602, // Rule ID 26 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule19Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner19,
        // Combiner Rule #19: select_undef_cmp; wip_match_opcode alternative 'G_SELECT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner13,
        GIR_Done,
      // Label 63: @602
      GIM_Try, /*On fail goto*//*Label 64*/ 612, // Rule ID 27 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule20Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner20,
        // Combiner Rule #20: select_constant_cmp; wip_match_opcode alternative 'G_SELECT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
        GIR_Done,
      // Label 64: @612
      GIM_Try, /*On fail goto*//*Label 65*/ 622, // Rule ID 28 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule21Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner21,
        // Combiner Rule #21: select_to_logical; wip_match_opcode alternative 'G_SELECT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner2,
        GIR_Done,
      // Label 65: @622
      GIM_Try, /*On fail goto*//*Label 66*/ 632, // Rule ID 36 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule24Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner24,
        // Combiner Rule #24: select_same_val; wip_match_opcode alternative 'G_SELECT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner13,
        GIR_Done,
      // Label 66: @632
      GIM_Try, /*On fail goto*//*Label 67*/ 642, // Rule ID 93 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule55Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner49,
        // Combiner Rule #55: select_to_minmax; wip_match_opcode alternative 'G_SELECT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner2,
        GIR_Done,
      // Label 67: @642
      GIM_Reject,
    // Label 62: @643
    GIM_Try, /*On fail goto*//*Label 68*/ 689,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ADD,
      GIM_Try, /*On fail goto*//*Label 69*/ 658, // Rule ID 30 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule23Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner23,
        // Combiner Rule #23: constant_fold; wip_match_opcode alternative 'G_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner16,
        GIR_Done,
      // Label 69: @658
      GIM_Try, /*On fail goto*//*Label 70*/ 668, // Rule ID 38 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule25Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner25,
        // Combiner Rule #25: right_identity_zero; wip_match_opcode alternative 'G_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 70: @668
      GIM_Try, /*On fail goto*//*Label 71*/ 678, // Rule ID 59 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule34Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner33,
        // Combiner Rule #34: add_sub_reg; wip_match_opcode alternative 'G_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner19,
        GIR_Done,
      // Label 71: @678
      GIM_Try, /*On fail goto*//*Label 72*/ 688, // Rule ID 81 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule49Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner41,
        // Combiner Rule #49: propagate_undef_any_op; wip_match_opcode alternative 'G_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner26,
        GIR_Done,
      // Label 72: @688
      GIM_Reject,
    // Label 68: @689
    GIM_Try, /*On fail goto*//*Label 73*/ 725,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SUB,
      GIM_Try, /*On fail goto*//*Label 74*/ 704, // Rule ID 31 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule23Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner23,
        // Combiner Rule #23: constant_fold; wip_match_opcode alternative 'G_SUB'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner16,
        GIR_Done,
      // Label 74: @704
      GIM_Try, /*On fail goto*//*Label 75*/ 714, // Rule ID 37 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule25Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner25,
        // Combiner Rule #25: right_identity_zero; wip_match_opcode alternative 'G_SUB'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 75: @714
      GIM_Try, /*On fail goto*//*Label 76*/ 724, // Rule ID 84 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule49Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner41,
        // Combiner Rule #49: propagate_undef_any_op; wip_match_opcode alternative 'G_SUB'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner26,
        GIR_Done,
      // Label 76: @724
      GIM_Reject,
    // Label 73: @725
    GIM_Try, /*On fail goto*//*Label 77*/ 761,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SHL,
      GIM_Try, /*On fail goto*//*Label 78*/ 740, // Rule ID 41 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule25Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner25,
        // Combiner Rule #25: right_identity_zero; wip_match_opcode alternative 'G_SHL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 78: @740
      GIM_Try, /*On fail goto*//*Label 79*/ 750, // Rule ID 74 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule46Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner42,
        // Combiner Rule #46: binop_left_undef_to_zero; wip_match_opcode alternative 'G_SHL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner24,
        GIR_Done,
      // Label 79: @750
      GIM_Try, /*On fail goto*//*Label 80*/ 760, // Rule ID 77 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule47Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner43,
        // Combiner Rule #47: binop_right_undef_to_undef; wip_match_opcode alternative 'G_SHL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner26,
        GIR_Done,
      // Label 80: @760
      GIM_Reject,
    // Label 77: @761
    GIM_Try, /*On fail goto*//*Label 81*/ 787,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_PTR_ADD,
      GIM_Try, /*On fail goto*//*Label 82*/ 776, // Rule ID 44 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule25Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner25,
        // Combiner Rule #25: right_identity_zero; wip_match_opcode alternative 'G_PTR_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 82: @776
      GIM_Try, /*On fail goto*//*Label 83*/ 786, // Rule ID 66 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule40Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner38,
        // Combiner Rule #40: ptr_add_immed_chain; wip_match_opcode alternative 'G_PTR_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner21,
        GIR_Done,
      // Label 83: @786
      GIM_Reject,
    // Label 81: @787
    GIM_Try, /*On fail goto*//*Label 84*/ 800, // Rule ID 49 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule27Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SDIV,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner27,
      // Combiner Rule #27: binop_left_to_zero; wip_match_opcode alternative 'G_SDIV'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
      GIR_Done,
    // Label 84: @800
    GIM_Try, /*On fail goto*//*Label 85*/ 826,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_UDIV,
      GIM_Try, /*On fail goto*//*Label 86*/ 815, // Rule ID 50 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule27Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner27,
        // Combiner Rule #27: binop_left_to_zero; wip_match_opcode alternative 'G_UDIV'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 86: @815
      GIM_Try, /*On fail goto*//*Label 87*/ 825, // Rule ID 75 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule46Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner42,
        // Combiner Rule #46: binop_left_undef_to_zero; wip_match_opcode alternative 'G_UDIV'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner24,
        GIR_Done,
      // Label 87: @825
      GIM_Reject,
    // Label 85: @826
    GIM_Try, /*On fail goto*//*Label 88*/ 839, // Rule ID 51 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule27Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SREM,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner27,
      // Combiner Rule #27: binop_left_to_zero; wip_match_opcode alternative 'G_SREM'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
      GIR_Done,
    // Label 88: @839
    GIM_Try, /*On fail goto*//*Label 89*/ 865,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_UREM,
      GIM_Try, /*On fail goto*//*Label 90*/ 854, // Rule ID 52 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule27Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner27,
        // Combiner Rule #27: binop_left_to_zero; wip_match_opcode alternative 'G_UREM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 90: @854
      GIM_Try, /*On fail goto*//*Label 91*/ 864, // Rule ID 76 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule46Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner42,
        // Combiner Rule #46: binop_left_undef_to_zero; wip_match_opcode alternative 'G_UREM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner24,
        GIR_Done,
      // Label 91: @864
      GIM_Reject,
    // Label 89: @865
    GIM_Try, /*On fail goto*//*Label 92*/ 878, // Rule ID 54 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule29Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_INTTOPTR,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner29,
      // Combiner Rule #29: p2i_to_i2p; wip_match_opcode alternative 'G_INTTOPTR'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner17,
      GIR_Done,
    // Label 92: @878
    GIM_Try, /*On fail goto*//*Label 93*/ 900, // Rule ID 55 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule30Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_PTRTOINT,
      // MIs[0] dst
      // No operand predicates
      // MIs[0] t
      GIM_RecordInsn, /*DefineMI*/1, /*MI*/0, /*OpIdx*/1, // MIs[1]
      GIM_CheckOpcode, /*MI*/1, TargetOpcode::G_INTTOPTR,
      // MIs[1] ptr
      // No operand predicates
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner30,
      GIM_CheckIsSafeToFold, /*InsnID*/1,
      // Combiner Rule #30: i2p_to_p2i
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner18,
      GIR_Done,
    // Label 93: @900
    GIM_Try, /*On fail goto*//*Label 94*/ 922, // Rule ID 57 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule32Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FNEG,
      // MIs[0] dst
      // No operand predicates
      // MIs[0] t
      GIM_RecordInsn, /*DefineMI*/1, /*MI*/0, /*OpIdx*/1, // MIs[1]
      GIM_CheckOpcode, /*MI*/1, TargetOpcode::G_FNEG,
      // MIs[1] src
      // No operand predicates
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner30,
      GIM_CheckIsSafeToFold, /*InsnID*/1,
      // Combiner Rule #32: fneg_fneg_fold
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner6,
      GIR_Done,
    // Label 94: @922
    GIM_Try, /*On fail goto*//*Label 95*/ 935, // Rule ID 60 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule35Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_BUILD_VECTOR_TRUNC,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner34,
      // Combiner Rule #35: buildvector_identity_fold; wip_match_opcode alternative 'G_BUILD_VECTOR_TRUNC'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner6,
      GIR_Done,
    // Label 95: @935
    GIM_Try, /*On fail goto*//*Label 96*/ 948, // Rule ID 61 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule35Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_BUILD_VECTOR,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner34,
      // Combiner Rule #35: buildvector_identity_fold; wip_match_opcode alternative 'G_BUILD_VECTOR'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner6,
      GIR_Done,
    // Label 96: @948
    GIM_Try, /*On fail goto*//*Label 97*/ 984,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_TRUNC,
      GIM_Try, /*On fail goto*//*Label 98*/ 963, // Rule ID 62 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule36Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner35,
        // Combiner Rule #36: trunc_buildvector_fold; wip_match_opcode alternative 'G_TRUNC'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner6,
        GIR_Done,
      // Label 98: @963
      GIM_Try, /*On fail goto*//*Label 99*/ 973, // Rule ID 63 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule37Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner36,
        // Combiner Rule #37: trunc_lshr_buildvector_fold; wip_match_opcode alternative 'G_TRUNC'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner6,
        GIR_Done,
      // Label 99: @973
      GIM_Try, /*On fail goto*//*Label 100*/ 983, // Rule ID 86 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule49Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner41,
        // Combiner Rule #49: propagate_undef_any_op; wip_match_opcode alternative 'G_TRUNC'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner26,
        GIR_Done,
      // Label 100: @983
      GIM_Reject,
    // Label 97: @984
    GIM_Try, /*On fail goto*//*Label 101*/ 1006, // Rule ID 64 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule38Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_BITCAST,
      // MIs[0] dst
      // No operand predicates
      // MIs[0] src1
      GIM_RecordInsn, /*DefineMI*/1, /*MI*/0, /*OpIdx*/1, // MIs[1]
      GIM_CheckOpcode, /*MI*/1, TargetOpcode::G_BITCAST,
      // MIs[1] src0
      // No operand predicates
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner37,
      GIM_CheckIsSafeToFold, /*InsnID*/1,
      // Combiner Rule #38: bitcast_bitcast_fold
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner20,
      GIR_Done,
    // Label 101: @1006
    GIM_Try, /*On fail goto*//*Label 102*/ 1028, // Rule ID 65 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule39Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FPTRUNC,
      // MIs[0] dst
      // No operand predicates
      // MIs[0] src1
      GIM_RecordInsn, /*DefineMI*/1, /*MI*/0, /*OpIdx*/1, // MIs[1]
      GIM_CheckOpcode, /*MI*/1, TargetOpcode::G_FPEXT,
      // MIs[1] src0
      // No operand predicates
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner37,
      GIM_CheckIsSafeToFold, /*InsnID*/1,
      // Combiner Rule #39: fptrunc_fpext_fold
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner20,
      GIR_Done,
    // Label 102: @1028
    GIM_Try, /*On fail goto*//*Label 103*/ 1054,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_STORE,
      GIM_Try, /*On fail goto*//*Label 104*/ 1043, // Rule ID 68 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule42Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner40,
        // Combiner Rule #42: split_store_zero_128; wip_match_opcode alternative 'G_STORE'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner22,
        GIR_Done,
      // Label 104: @1043
      GIM_Try, /*On fail goto*//*Label 105*/ 1053, // Rule ID 89 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule52Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner46,
        // Combiner Rule #52: erase_undef_store; wip_match_opcode alternative 'G_STORE'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner27,
        GIR_Done,
      // Label 105: @1053
      GIM_Reject,
    // Label 103: @1054
    GIM_Try, /*On fail goto*//*Label 106*/ 1067, // Rule ID 69 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule43Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_UITOFP,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner41,
      // Combiner Rule #43: undef_to_fp_zero; wip_match_opcode alternative 'G_UITOFP'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner23,
      GIR_Done,
    // Label 106: @1067
    GIM_Try, /*On fail goto*//*Label 107*/ 1080, // Rule ID 70 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule43Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SITOFP,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner41,
      // Combiner Rule #43: undef_to_fp_zero; wip_match_opcode alternative 'G_SITOFP'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner23,
      GIR_Done,
    // Label 107: @1080
    GIM_Try, /*On fail goto*//*Label 108*/ 1093, // Rule ID 80 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule48Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ABS,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner42,
      // Combiner Rule #48: unary_undef_to_zero; wip_match_opcode alternative 'G_ABS'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner24,
      GIR_Done,
    // Label 108: @1093
    GIM_Try, /*On fail goto*//*Label 109*/ 1106, // Rule ID 82 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule49Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FPTOSI,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner41,
      // Combiner Rule #49: propagate_undef_any_op; wip_match_opcode alternative 'G_FPTOSI'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner26,
      GIR_Done,
    // Label 109: @1106
    GIM_Try, /*On fail goto*//*Label 110*/ 1119, // Rule ID 83 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule49Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FPTOUI,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner41,
      // Combiner Rule #49: propagate_undef_any_op; wip_match_opcode alternative 'G_FPTOUI'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner26,
      GIR_Done,
    // Label 110: @1119
    GIM_Try, /*On fail goto*//*Label 111*/ 1145,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SHUFFLE_VECTOR,
      GIM_Try, /*On fail goto*//*Label 112*/ 1134, // Rule ID 87 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule50Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner44,
        // Combiner Rule #50: propagate_undef_all_ops; wip_match_opcode alternative 'G_SHUFFLE_VECTOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner26,
        GIR_Done,
      // Label 112: @1134
      GIM_Try, /*On fail goto*//*Label 113*/ 1144, // Rule ID 88 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule51Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner45,
        // Combiner Rule #51: propagate_undef_shuffle_mask; wip_match_opcode alternative 'G_SHUFFLE_VECTOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner26,
        GIR_Done,
      // Label 113: @1144
      GIM_Reject,
    // Label 111: @1145
    GIM_Try, /*On fail goto*//*Label 114*/ 1158, // Rule ID 90 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule53Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_UNMERGE_VALUES,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner47,
      // Combiner Rule #53: unmerge_undef; wip_match_opcode alternative 'G_UNMERGE_VALUES'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner2,
      GIR_Done,
    // Label 114: @1158
    GIM_Try, /*On fail goto*//*Label 115*/ 1171, // Rule ID 91 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule54Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_INSERT_VECTOR_ELT,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner48,
      // Combiner Rule #54: insert_extract_vec_elt_out_of_bounds; wip_match_opcode alternative 'G_INSERT_VECTOR_ELT'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner26,
      GIR_Done,
    // Label 115: @1171
    GIM_Reject,
    };
  return MatchTable0;
}
#endif // ifdef GET_GICOMBINER_IMPL

#ifdef GET_GICOMBINER_CONSTRUCTOR_INITS
AvailableModuleFeatures(computeAvailableModuleFeatures(&STI)),
AvailableFunctionFeatures()
#endif // ifdef GET_GICOMBINER_CONSTRUCTOR_INITS
#ifdef GET_GICOMBINER_CONSTRUCTOR_INITS
, State(0),
ExecInfo(TypeObjects, NumTypeObjects, FeatureBitsets, ComplexPredicateFns, CustomRenderers)
#endif // ifdef GET_GICOMBINER_CONSTRUCTOR_INITS

