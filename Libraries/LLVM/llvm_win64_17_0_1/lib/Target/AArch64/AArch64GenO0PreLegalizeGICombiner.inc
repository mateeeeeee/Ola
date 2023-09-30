/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AArch64O0PreLegalizerCombinerImpl Combiner Match Table                     *|
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
struct AArch64O0PreLegalizerCombinerImplRuleConfig {
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
  case 9:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "copy_prop", 9) != 0)
      break;
    return 0;	 // "copy_prop"
  case 10:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "mul_to_shl", 10) != 0)
      break;
    return 1;	 // "mul_to_shl"
  case 12:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "not_cmp_fold", 12) != 0)
      break;
    return 8;	 // "not_cmp_fold"
  case 13:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "load_and_mask", 13) != 0)
      break;
    return 7;	 // "load_and_mask"
  case 14:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "mul_by_neg_one", 14) != 0)
      break;
    return 3;	 // "mul_by_neg_one"
  case 15:	 // 2 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'e':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "xtending_loads", 14) != 0)
        break;
      return 6;	 // "extending_loads"
    case 'i':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "dempotent_prop", 14) != 0)
        break;
      return 4;	 // "idempotent_prop"
    }
    break;
  case 17:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "add_p2i_to_ptradd", 17) != 0)
      break;
    return 2;	 // "add_p2i_to_ptradd"
  case 19:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "ptr_add_immed_chain", 19) != 0)
      break;
    return 5;	 // "ptr_add_immed_chain"
  case 28:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "opt_brcond_by_inverting_cond", 28) != 0)
      break;
    return 9;	 // "opt_brcond_by_inverting_cond"
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
    return {{0, 10}};
  }
  const auto I = getRuleIdxForIdentifier(RangePair.first);
  if (!I)
    return std::nullopt;
  return {{*I, *I + 1}};
}

bool AArch64O0PreLegalizerCombinerImplRuleConfig::setRuleEnabled(StringRef RuleIdentifier) {
  auto MaybeRange = getRuleRangeForIdentifier(RuleIdentifier);
  if (!MaybeRange)
    return false;
  for (auto I = MaybeRange->first; I < MaybeRange->second; ++I)
    DisabledRules.reset(I);
  return true;
}

bool AArch64O0PreLegalizerCombinerImplRuleConfig::setRuleDisabled(StringRef RuleIdentifier) {
  auto MaybeRange = getRuleRangeForIdentifier(RuleIdentifier);
  if (!MaybeRange)
    return false;
  for (auto I = MaybeRange->first; I < MaybeRange->second; ++I)
    DisabledRules.set(I);
  return true;
}

static std::vector<std::string> AArch64O0PreLegalizerCombinerOption;
static cl::list<std::string> AArch64O0PreLegalizerCombinerDisableOption(
    "aarch64o0prelegalizercombiner-disable-rule",
    cl::desc("Disable one or more combiner rules temporarily in the AArch64O0PreLegalizerCombiner pass"),
    cl::CommaSeparated,
    cl::Hidden,
    cl::cat(GICombinerOptionCategory),
    cl::callback([](const std::string &Str) {
      AArch64O0PreLegalizerCombinerOption.push_back(Str);
    }));
static cl::list<std::string> AArch64O0PreLegalizerCombinerOnlyEnableOption(
    "aarch64o0prelegalizercombiner-only-enable-rule",
    cl::desc("Disable all rules in the AArch64O0PreLegalizerCombiner pass then re-enable the specified ones"),
    cl::Hidden,
    cl::cat(GICombinerOptionCategory),
    cl::callback([](const std::string &CommaSeparatedArg) {
      StringRef Str = CommaSeparatedArg;
      AArch64O0PreLegalizerCombinerOption.push_back("*");
      do {
        auto X = Str.split(",");
        AArch64O0PreLegalizerCombinerOption.push_back(("!" + X.first).str());
        Str = X.second;
      } while (!Str.empty());
    }));


bool AArch64O0PreLegalizerCombinerImplRuleConfig::isRuleEnabled(unsigned RuleID) const {
    return  !DisabledRules.test(RuleID);
}
bool AArch64O0PreLegalizerCombinerImplRuleConfig::parseCommandLineOption() {
  for (StringRef Identifier : AArch64O0PreLegalizerCombinerOption) {
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
  typedef ComplexRendererFns(AArch64O0PreLegalizerCombinerImpl::*ComplexMatcherMemFn)(MachineOperand &) const;
  typedef void(AArch64O0PreLegalizerCombinerImpl::*CustomRendererFn)(MachineInstrBuilder &, const MachineInstr &, int) const;
  const ExecInfoTy<PredicateBitset, ComplexMatcherMemFn, CustomRendererFn> ExecInfo;
  static AArch64O0PreLegalizerCombinerImpl::ComplexMatcherMemFn ComplexPredicateFns[];
  static AArch64O0PreLegalizerCombinerImpl::CustomRendererFn CustomRenderers[];
  bool testImmPredicate_I64(unsigned PredicateID, int64_t Imm) const override;
  bool testImmPredicate_APInt(unsigned PredicateID, const APInt &Imm) const override;
  bool testImmPredicate_APFloat(unsigned PredicateID, const APFloat &Imm) const override;
  const int64_t *getMatchTable() const override;
  bool testMIPredicate_MI(unsigned PredicateID, const MachineInstr &MI, const MatcherState &State) const override;
  bool testSimplePredicate(unsigned PredicateID) const override;
  void runCustomAction(unsigned FnID, const MatcherState &State) const override;
  struct MatchInfosTy {
    unsigned MDInfo0;
    std::pair<Register, bool> MDInfo1;
    MachineInstr * MDInfo6;
    std::function<void(MachineIRBuilder &)> MDInfo4;
    PreferredTuple MDInfo3;
    SmallVector<Register, 4> MDInfo5;
    PtrAddChain MDInfo2;
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

PredicateBitset AArch64O0PreLegalizerCombinerImpl::
computeAvailableModuleFeatures(const AArch64Subtarget *Subtarget) const {
  PredicateBitset Features;
  return Features;
}

void AArch64O0PreLegalizerCombinerImpl::setupGeneratedPerFunctionState(MachineFunction &MF) {
  AvailableFunctionFeatures = computeAvailableFunctionFeatures((const AArch64Subtarget *)&MF.getSubtarget(), &MF);
}
PredicateBitset AArch64O0PreLegalizerCombinerImpl::
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

AArch64O0PreLegalizerCombinerImpl::ComplexMatcherMemFn
AArch64O0PreLegalizerCombinerImpl::ComplexPredicateFns[] = {
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
};
bool AArch64O0PreLegalizerCombinerImpl::testMIPredicate_MI(unsigned PredicateID, const MachineInstr & MI, const MatcherState &State) const {
  switch (PredicateID) {
  case GICXXPred_MI_Predicate_GICombiner0: {
    return Helper.matchCombineCopy(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner1: {
    return Helper.matchCombineMulToShl(*State.MIs[0], MatchInfos.MDInfo0);
  }
  case GICXXPred_MI_Predicate_GICombiner2: {
    return Helper.matchCombineAddP2IToPtrAdd(*State.MIs[0], MatchInfos.MDInfo1);
  }
  case GICXXPred_MI_Predicate_GICombiner3: {
    return Helper.matchConstantOp(State.MIs[0]->getOperand(2), -1);
  }
  case GICXXPred_MI_Predicate_GICombiner4: {
    return MRI.getVRegDef(State.MIs[0]->getOperand(1).getReg())->getOpcode() ==
                        State.MIs[0]->getOpcode();
  }
  case GICXXPred_MI_Predicate_GICombiner5: {
    return Helper.matchPtrAddImmedChain(*State.MIs[0], MatchInfos.MDInfo2);
  }
  case GICXXPred_MI_Predicate_GICombiner6: {
    return Helper.matchCombineExtendingLoads(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner7: {
    return Helper.matchCombineLoadWithAndMask(*State.MIs[0], MatchInfos.MDInfo4);
  }
  case GICXXPred_MI_Predicate_GICombiner8: {
    return Helper.matchNotCmp(*State.MIs[0], MatchInfos.MDInfo5);
  }
  case GICXXPred_MI_Predicate_GICombiner9: {
    return Helper.matchOptBrCondByInvertingCond(*State.MIs[0], MatchInfos.MDInfo6);
  }
  }
  llvm_unreachable("Unknown predicate");
  return false;
}
bool AArch64O0PreLegalizerCombinerImpl::testImmPredicate_I64(unsigned PredicateID, int64_t Imm) const {
  llvm_unreachable("Unknown predicate");
  return false;
}
bool AArch64O0PreLegalizerCombinerImpl::testImmPredicate_APFloat(unsigned PredicateID, const APFloat & Imm) const {
  llvm_unreachable("Unknown predicate");
  return false;
}
bool AArch64O0PreLegalizerCombinerImpl::testImmPredicate_APInt(unsigned PredicateID, const APInt & Imm) const {
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
};

bool AArch64O0PreLegalizerCombinerImpl::testSimplePredicate(unsigned Predicate) const {
    return RuleConfig.isRuleEnabled(Predicate - GICXXPred_Invalid - 1);
}
// Custom renderers.
enum {
  GICR_Invalid,
};
AArch64O0PreLegalizerCombinerImpl::CustomRendererFn
AArch64O0PreLegalizerCombinerImpl::CustomRenderers[] = {
  nullptr, // GICR_Invalid
};

bool AArch64O0PreLegalizerCombinerImpl::tryCombineAll(MachineInstr &I) const {
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
};
void AArch64O0PreLegalizerCombinerImpl::runCustomAction(unsigned ApplyID, const MatcherState &State) const {
  switch(ApplyID) {
  case GICXXCustomAction_CombineApplyGICombiner0:{
    Helper.applyCombineCopy(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner1:{
    Helper.applyCombineMulToShl(*State.MIs[0], MatchInfos.MDInfo0);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner2:{
    Helper.applyCombineAddP2IToPtrAdd(*State.MIs[0], MatchInfos.MDInfo1);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner3:{
    Helper.applyCombineMulByNegativeOne(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner4:{
    Helper.replaceSingleDefInstWithOperand(*State.MIs[0], 1);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner5:{
    Helper.applyPtrAddImmedChain(*State.MIs[0], MatchInfos.MDInfo2);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner6:{
    Helper.applyCombineExtendingLoads(*State.MIs[0], MatchInfos.MDInfo3);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner7:{
    Helper.applyBuildFn(*State.MIs[0], MatchInfos.MDInfo4);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner8:{
    Helper.applyNotCmp(*State.MIs[0], MatchInfos.MDInfo5);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner9:{
    Helper.applyOptBrCondByInvertingCond(*State.MIs[0], MatchInfos.MDInfo6);
    return;
  }
}
  llvm_unreachable("Unknown Apply Action");
}
const int64_t *AArch64O0PreLegalizerCombinerImpl::getMatchTable() const {
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
    GIM_Try, /*On fail goto*//*Label 1*/ 39,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_MUL,
      GIM_Try, /*On fail goto*//*Label 2*/ 28, // Rule ID 3 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule3Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner3,
        // Combiner Rule #3: mul_by_neg_one; wip_match_opcode alternative 'G_MUL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner3,
        GIR_Done,
      // Label 2: @28
      GIM_Try, /*On fail goto*//*Label 3*/ 38, // Rule ID 1 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule1Enabled,
        // MIs[0] d
        // No operand predicates
        // MIs[0] op1
        // No operand predicates
        // MIs[0] op2
        // No operand predicates
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner1,
        // Combiner Rule #1: mul_to_shl
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner1,
        GIR_Done,
      // Label 3: @38
      GIM_Reject,
    // Label 1: @39
    GIM_Try, /*On fail goto*//*Label 4*/ 52, // Rule ID 2 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule2Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ADD,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner2,
      // Combiner Rule #2: add_p2i_to_ptradd; wip_match_opcode alternative 'G_ADD'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner2,
      GIR_Done,
    // Label 4: @52
    GIM_Try, /*On fail goto*//*Label 5*/ 65, // Rule ID 4 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule4Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FREEZE,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner4,
      // Combiner Rule #4: idempotent_prop; wip_match_opcode alternative 'G_FREEZE'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
      GIR_Done,
    // Label 5: @65
    GIM_Try, /*On fail goto*//*Label 6*/ 78, // Rule ID 5 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule4Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FABS,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner4,
      // Combiner Rule #4: idempotent_prop; wip_match_opcode alternative 'G_FABS'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
      GIR_Done,
    // Label 6: @78
    GIM_Try, /*On fail goto*//*Label 7*/ 91, // Rule ID 6 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule4Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FCANONICALIZE,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner4,
      // Combiner Rule #4: idempotent_prop; wip_match_opcode alternative 'G_FCANONICALIZE'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
      GIR_Done,
    // Label 7: @91
    GIM_Try, /*On fail goto*//*Label 8*/ 104, // Rule ID 7 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule5Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_PTR_ADD,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner5,
      // Combiner Rule #5: ptr_add_immed_chain; wip_match_opcode alternative 'G_PTR_ADD'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner5,
      GIR_Done,
    // Label 8: @104
    GIM_Try, /*On fail goto*//*Label 9*/ 117, // Rule ID 8 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule6Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_LOAD,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner6,
      // Combiner Rule #6: extending_loads; wip_match_opcode alternative 'G_LOAD'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner6,
      GIR_Done,
    // Label 9: @117
    GIM_Try, /*On fail goto*//*Label 10*/ 130, // Rule ID 9 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule6Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SEXTLOAD,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner6,
      // Combiner Rule #6: extending_loads; wip_match_opcode alternative 'G_SEXTLOAD'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner6,
      GIR_Done,
    // Label 10: @130
    GIM_Try, /*On fail goto*//*Label 11*/ 143, // Rule ID 10 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule6Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ZEXTLOAD,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner6,
      // Combiner Rule #6: extending_loads; wip_match_opcode alternative 'G_ZEXTLOAD'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner6,
      GIR_Done,
    // Label 11: @143
    GIM_Try, /*On fail goto*//*Label 12*/ 156, // Rule ID 11 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule7Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_AND,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner7,
      // Combiner Rule #7: load_and_mask; wip_match_opcode alternative 'G_AND'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner7,
      GIR_Done,
    // Label 12: @156
    GIM_Try, /*On fail goto*//*Label 13*/ 169, // Rule ID 12 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule8Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_XOR,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner8,
      // Combiner Rule #8: not_cmp_fold; wip_match_opcode alternative 'G_XOR'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner8,
      GIR_Done,
    // Label 13: @169
    GIM_Try, /*On fail goto*//*Label 14*/ 182, // Rule ID 13 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule9Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_BR,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner9,
      // Combiner Rule #9: opt_brcond_by_inverting_cond; wip_match_opcode alternative 'G_BR'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
      GIR_Done,
    // Label 14: @182
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

