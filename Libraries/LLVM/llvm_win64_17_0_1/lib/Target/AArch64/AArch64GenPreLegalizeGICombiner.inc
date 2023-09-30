/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AArch64PreLegalizerCombinerImpl Combiner Match Table                       *|
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
struct AArch64PreLegalizerCombinerImplRuleConfig {
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
  case 9:	 // 4 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'a':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ddo_by_0", 8) != 0)
        break;
      return 80;	 // "addo_by_0"
    case 'c':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "opy_prop", 8) != 0)
        break;
      return 0;	 // "copy_prop"
    case 'm':	 // 2 strings to match.
      if (memcmp(RuleIdentifier.data()+1, "ulo_by_", 7) != 0)
        break;
      switch (RuleIdentifier[8]) {
      default: break;
      case '0':	 // 1 string to match.
        return 79;	 // "mulo_by_0"
      case '2':	 // 1 string to match.
        return 78;	 // "mulo_by_2"
      }
      break;
    }
    break;
  case 10:	 // 3 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'i':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "2p_to_p2i", 9) != 0)
        break;
      return 29;	 // "i2p_to_p2i"
    case 'm':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ul_to_shl", 9) != 0)
        break;
      return 1;	 // "mul_to_shl"
    case 'p':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "2i_to_i2p", 9) != 0)
        break;
      return 28;	 // "p2i_to_i2p"
    }
    break;
  case 11:	 // 4 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'a':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "dd_sub_reg", 10) != 0)
        break;
      return 33;	 // "add_sub_reg"
    case 's':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ub_add_reg", 10) != 0)
        break;
      return 112;	 // "sub_add_reg"
    case 't':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "runc_shift", 10) != 0)
        break;
      return 70;	 // "trunc_shift"
    case 'u':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "nmerge_cst", 10) != 0)
        break;
      return 65;	 // "unmerge_cst"
    }
    break;
  case 12:	 // 6 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'a':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "dde_to_addo", 11) != 0)
        break;
      return 81;	 // "adde_to_addo"
    case 'e':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "xt_ext_fold", 11) != 0)
        break;
      return 61;	 // "ext_ext_fold"
    case 'f':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "sub_to_fneg", 11) != 0)
        break;
      return 115;	 // "fsub_to_fneg"
    case 'm':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ulh_to_lshr", 11) != 0)
        break;
      return 100;	 // "mulh_to_lshr"
    case 'n':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ot_cmp_fold", 11) != 0)
        break;
      return 62;	 // "not_cmp_fold"
    case 'r':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "edundant_or", 11) != 0)
        break;
      return 55;	 // "redundant_or"
    }
    break;
  case 13:	 // 9 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'c':	 // 2 strings to match.
      if (RuleIdentifier[1] != 'o')
        break;
      switch (RuleIdentifier[2]) {
      default: break;
      case 'm':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+3, "mute_shift", 10) != 0)
          break;
        return 91;	 // "commute_shift"
      case 'n':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+3, "stant_fold", 10) != 0)
          break;
        return 96;	 // "constant_fold"
      }
      break;
    case 'l':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "oad_and_mask", 12) != 0)
        break;
      return 9;	 // "load_and_mask"
    case 'm':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "erge_unmerge", 12) != 0)
        break;
      return 68;	 // "merge_unmerge"
    case 'r':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "edundant_and", 12) != 0)
        break;
      return 53;	 // "redundant_and"
    case 's':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "div_by_const", 12) != 0)
        break;
      return 99;	 // "sdiv_by_const"
    case 'u':	 // 3 strings to match.
      switch (RuleIdentifier[1]) {
      default: break;
      case 'd':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "iv_by_const", 11) != 0)
          break;
        return 98;	 // "udiv_by_const"
      case 'n':	 // 2 strings to match.
        if (memcmp(RuleIdentifier.data()+2, "merge_", 6) != 0)
          break;
        switch (RuleIdentifier[8]) {
        default: break;
        case 'm':	 // 1 string to match.
          if (memcmp(RuleIdentifier.data()+9, "erge", 4) != 0)
            break;
          return 64;	 // "unmerge_merge"
        case 'u':	 // 1 string to match.
          if (memcmp(RuleIdentifier.data()+9, "ndef", 4) != 0)
            break;
          return 21;	 // "unmerge_undef"
        }
        break;
      }
      break;
    }
    break;
  case 14:	 // 7 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'b':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "inop_same_val", 13) != 0)
        break;
      return 25;	 // "binop_same_val"
    case 'f':	 // 2 strings to match.
      switch (RuleIdentifier[1]) {
      default: break;
      case 'a':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "bs_fneg_fold", 12) != 0)
          break;
        return 97;	 // "fabs_fneg_fold"
      case 'n':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "eg_fneg_fold", 12) != 0)
          break;
        return 31;	 // "fneg_fneg_fold"
      }
      break;
    case 'm':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ul_by_neg_one", 13) != 0)
        break;
      return 3;	 // "mul_by_neg_one"
    case 'r':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "eassoc_ptradd", 13) != 0)
        break;
      return 43;	 // "reassoc_ptradd"
    case 's':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "hifts_too_big", 13) != 0)
        break;
      return 42;	 // "shifts_too_big"
    case 't':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "runc_ext_fold", 13) != 0)
        break;
      return 69;	 // "trunc_ext_fold"
    }
    break;
  case 15:	 // 6 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'e':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "xtending_loads", 14) != 0)
        break;
      return 8;	 // "extending_loads"
    case 'i':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "dempotent_prop", 14) != 0)
        break;
      return 4;	 // "idempotent_prop"
    case 'l':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "oad_or_combine", 14) != 0)
        break;
      return 87;	 // "load_or_combine"
    case 'o':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "verlapping_and", 14) != 0)
        break;
      return 77;	 // "overlapping_and"
    case 's':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "elect_same_val", 14) != 0)
        break;
      return 23;	 // "select_same_val"
    case 'z':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ext_trunc_fold", 14) != 0)
        break;
      return 57;	 // "zext_trunc_fold"
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
        return 113;	 // "select_to_minmax"
      case 'u':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+8, "ndef_cmp", 8) != 0)
          break;
        return 50;	 // "select_undef_cmp"
      }
      break;
    case 'u':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ndef_to_fp_zero", 15) != 0)
        break;
      return 11;	 // "undef_to_fp_zero"
    }
    break;
  case 17:	 // 9 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'a':	 // 2 strings to match.
      switch (RuleIdentifier[1]) {
      default: break;
      case 'd':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "d_p2i_to_ptradd", 15) != 0)
          break;
        return 2;	 // "add_p2i_to_ptradd"
      case 'n':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "yext_trunc_fold", 15) != 0)
          break;
        return 30;	 // "anyext_trunc_fold"
      }
      break;
    case 'd':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "iv_rem_to_divrem", 16) != 0)
        break;
      return 88;	 // "div_rem_to_divrem"
    case 'e':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "rase_undef_store", 16) != 0)
        break;
      return 20;	 // "erase_undef_store"
    case 'p':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "tr_add_with_zero", 16) != 0)
        break;
      return 84;	 // "ptr_add_with_zero"
    case 's':	 // 2 strings to match.
      switch (RuleIdentifier[1]) {
      default: break;
      case 'e':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "lect_to_logical", 15) != 0)
          break;
        return 52;	 // "select_to_logical"
      case 'h':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "ift_immed_chain", 15) != 0)
          break;
        return 85;	 // "shift_immed_chain"
      }
      break;
    case 'u':	 // 2 strings to match.
      switch (RuleIdentifier[1]) {
      default: break;
      case 'n':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "def_to_int_zero", 15) != 0)
          break;
        return 12;	 // "undef_to_int_zero"
      case 'r':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "em_pow2_to_mask", 15) != 0)
          break;
        return 56;	 // "urem_pow2_to_mask"
      }
      break;
    }
    break;
  case 18:	 // 8 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'b':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "inop_left_to_zero", 17) != 0)
        break;
      return 26;	 // "binop_left_to_zero"
    case 'c':	 // 3 strings to match.
      if (RuleIdentifier[1] != 'o')
        break;
      switch (RuleIdentifier[2]) {
      default: break;
      case 'm':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+3, "bine_minmax_nan", 15) != 0)
          break;
        return 82;	 // "combine_minmax_nan"
      case 'n':	 // 2 strings to match.
        if (memcmp(RuleIdentifier.data()+3, "stant_fold_f", 12) != 0)
          break;
        switch (RuleIdentifier[15]) {
        default: break;
        case 'a':	 // 1 string to match.
          if (memcmp(RuleIdentifier.data()+16, "bs", 2) != 0)
            break;
          return 72;	 // "constant_fold_fabs"
        case 'n':	 // 1 string to match.
          if (memcmp(RuleIdentifier.data()+16, "eg", 2) != 0)
            break;
          return 71;	 // "constant_fold_fneg"
        }
        break;
      }
      break;
    case 'f':	 // 2 strings to match.
      switch (RuleIdentifier[1]) {
      default: break;
      case 'o':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "ld_global_offset", 16) != 0)
          break;
        return 119;	 // "fold_global_offset"
      case 'p':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "trunc_fpext_fold", 16) != 0)
          break;
        return 38;	 // "fptrunc_fpext_fold"
      }
      break;
    case 'r':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ight_identity_one", 17) != 0)
        break;
      return 32;	 // "right_identity_one"
    case 's':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ext_inreg_of_load", 17) != 0)
        break;
      return 47;	 // "sext_inreg_of_load"
    }
    break;
  case 19:	 // 11 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'b':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "inop_right_to_zero", 18) != 0)
        break;
      return 27;	 // "binop_right_to_zero"
    case 'c':	 // 3 strings to match.
      if (memcmp(RuleIdentifier.data()+1, "onst", 4) != 0)
        break;
      switch (RuleIdentifier[5]) {
      default: break;
      case '_':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+6, "ptradd_to_i2p", 13) != 0)
          break;
        return 76;	 // "const_ptradd_to_i2p"
      case 'a':	 // 2 strings to match.
        if (memcmp(RuleIdentifier.data()+6, "nt_fold_f", 9) != 0)
          break;
        switch (RuleIdentifier[15]) {
        default: break;
        case 'l':	 // 1 string to match.
          if (memcmp(RuleIdentifier.data()+16, "og2", 3) != 0)
            break;
          return 74;	 // "constant_fold_flog2"
        case 's':	 // 1 string to match.
          if (memcmp(RuleIdentifier.data()+16, "qrt", 3) != 0)
            break;
          return 73;	 // "constant_fold_fsqrt"
        }
        break;
      }
      break;
    case 'e':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "xtend_through_phis", 18) != 0)
        break;
      return 39;	 // "extend_through_phis"
    case 'p':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "tr_add_immed_chain", 18) != 0)
        break;
      return 45;	 // "ptr_add_immed_chain"
    case 'r':	 // 2 strings to match.
      switch (RuleIdentifier[1]) {
      default: break;
      case 'e':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "assoc_comm_binops", 17) != 0)
          break;
        return 44;	 // "reassoc_comm_binops"
      case 'i':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "ght_identity_zero", 17) != 0)
          break;
        return 24;	 // "right_identity_zero"
      }
      break;
    case 's':	 // 2 strings to match.
      switch (RuleIdentifier[1]) {
      default: break;
      case 'e':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "lect_constant_cmp", 17) != 0)
          break;
        return 51;	 // "select_constant_cmp"
      case 'i':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "mplify_add_to_sub", 17) != 0)
          break;
        return 40;	 // "simplify_add_to_sub"
      }
      break;
    case 'u':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "nary_undef_to_zero", 18) != 0)
        break;
      return 16;	 // "unary_undef_to_zero"
    }
    break;
  case 20:	 // 6 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'a':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "nd_or_disjoint_mask", 19) != 0)
        break;
      return 102;	 // "and_or_disjoint_mask"
    case 'b':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "itcast_bitcast_fold", 19) != 0)
        break;
      return 37;	 // "bitcast_bitcast_fold"
    case 'i':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "cmp_redundant_trunc", 19) != 0)
        break;
      return 118;	 // "icmp_redundant_trunc"
    case 'r':	 // 2 strings to match.
      if (memcmp(RuleIdentifier.data()+1, "edu", 3) != 0)
        break;
      switch (RuleIdentifier[4]) {
      default: break;
      case 'c':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+5, "e_shl_of_extend", 15) != 0)
          break;
        return 48;	 // "reduce_shl_of_extend"
      case 'n':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+5, "dant_sext_inreg", 15) != 0)
          break;
        return 54;	 // "redundant_sext_inreg"
      }
      break;
    case 'u':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "nmerge_zext_to_zext", 19) != 0)
        break;
      return 67;	 // "unmerge_zext_to_zext"
    }
    break;
  case 21:	 // 4 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'c':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "onstant_fold_fptrunc", 20) != 0)
        break;
      return 75;	 // "constant_fold_fptrunc"
    case 'f':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "constant_to_constant", 20) != 0)
        break;
      return 117;	 // "fconstant_to_constant"
    case 'u':	 // 2 strings to match.
      if (RuleIdentifier[1] != 'n')
        break;
      switch (RuleIdentifier[2]) {
      default: break;
      case 'd':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+3, "ef_to_negative_one", 18) != 0)
          break;
        return 13;	 // "undef_to_negative_one"
      case 'm':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+3, "erge_dead_to_trunc", 18) != 0)
          break;
        return 66;	 // "unmerge_dead_to_trunc"
      }
      break;
    }
    break;
  case 22:	 // 7 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'f':	 // 2 strings to match.
      switch (RuleIdentifier[1]) {
      default: break;
      case 'o':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "ld_binop_into_select", 20) != 0)
          break;
        return 111;	 // "fold_binop_into_select"
      case 'u':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "nnel_shift_to_rotate", 20) != 0)
          break;
        return 90;	 // "funnel_shift_to_rotate"
      }
      break;
    case 'i':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "cmp_to_lhs_known_bits", 21) != 0)
        break;
      return 59;	 // "icmp_to_lhs_known_bits"
    case 'p':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ropagate_undef_any_op", 21) != 0)
        break;
      return 17;	 // "propagate_undef_any_op"
    case 'r':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "edundant_neg_operands", 21) != 0)
        break;
      return 101;	 // "redundant_neg_operands"
    case 's':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "hl_ashr_to_sext_inreg", 21) != 0)
        break;
      return 46;	 // "shl_ashr_to_sext_inreg"
    case 't':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "runc_buildvector_fold", 21) != 0)
        break;
      return 35;	 // "trunc_buildvector_fold"
    }
    break;
  case 23:	 // 2 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'c':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ommute_constant_to_rhs", 22) != 0)
        break;
      return 116;	 // "commute_constant_to_rhs"
    case 'p':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ropagate_undef_all_ops", 22) != 0)
        break;
      return 18;	 // "propagate_undef_all_ops"
    }
    break;
  case 24:	 // 4 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'b':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "inop_left_undef_to_zero", 23) != 0)
        break;
      return 14;	 // "binop_left_undef_to_zero"
    case 'n':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "arrow_binop_feeding_and", 23) != 0)
        break;
      return 49;	 // "narrow_binop_feeding_and"
    case 's':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ext_inreg_to_zext_inreg", 23) != 0)
        break;
      return 60;	 // "sext_inreg_to_zext_inreg"
    case 'x':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "or_of_and_with_same_reg", 23) != 0)
        break;
      return 83;	 // "xor_of_and_with_same_reg"
    }
    break;
  case 25:	 // 4 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'b':	 // 3 strings to match.
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
          return 93;	 // "bitfield_extract_from_and"
        case 's':	 // 1 string to match.
          if (memcmp(RuleIdentifier.data()+23, "hr", 2) != 0)
            break;
          return 94;	 // "bitfield_extract_from_shr"
        }
        break;
      case 'u':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+2, "ildvector_identity_fold", 23) != 0)
          break;
        return 34;	 // "buildvector_identity_fold"
      }
      break;
    case 'e':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "xtract_vec_elt_build_vec", 24) != 0)
        break;
      return 6;	 // "extract_vec_elt_build_vec"
    }
    break;
  case 26:	 // 3 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'b':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "inop_right_undef_to_undef", 25) != 0)
        break;
      return 15;	 // "binop_right_undef_to_undef"
    case 'c':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ombine_indexed_load_store", 25) != 0)
        break;
      return 10;	 // "combine_indexed_load_store"
    case 'f':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "unnel_shift_from_or_shift", 25) != 0)
        break;
      return 89;	 // "funnel_shift_from_or_shift"
    }
    break;
  case 27:	 // 2 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'r':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "edundant_binop_in_equality", 26) != 0)
        break;
      return 114;	 // "redundant_binop_in_equality"
    case 't':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "runc_lshr_buildvector_fold", 26) != 0)
        break;
      return 36;	 // "trunc_lshr_buildvector_fold"
    }
    break;
  case 28:	 // 3 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'o':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "pt_brcond_by_inverting_cond", 27) != 0)
        break;
      return 63;	 // "opt_brcond_by_inverting_cond"
    case 'p':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ropagate_undef_shuffle_mask", 27) != 0)
        break;
      return 19;	 // "propagate_undef_shuffle_mask"
    case 's':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "hift_of_shifted_logic_chain", 27) != 0)
        break;
      return 86;	 // "shift_of_shifted_logic_chain"
    }
    break;
  case 29:	 // 2 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'b':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "itfield_extract_from_shr_and", 28) != 0)
        break;
      return 95;	 // "bitfield_extract_from_shr_and"
    case 'i':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "cmp_to_true_false_known_bits", 28) != 0)
        break;
      return 58;	 // "icmp_to_true_false_known_bits"
    }
    break;
  case 32:	 // 3 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'b':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "itfield_extract_from_sext_inreg", 31) != 0)
        break;
      return 92;	 // "bitfield_extract_from_sext_inreg"
    case 'c':	 // 2 strings to match.
      if (memcmp(RuleIdentifier.data()+1, "ombine_f", 8) != 0)
        break;
      switch (RuleIdentifier[9]) {
      default: break;
      case 'a':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+10, "dd_fmul_to_fmad_or_fma", 22) != 0)
          break;
        return 103;	 // "combine_fadd_fmul_to_fmad_or_fma"
      case 's':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+10, "ub_fmul_to_fmad_or_fma", 22) != 0)
          break;
        return 107;	 // "combine_fsub_fmul_to_fmad_or_fma"
      }
      break;
    }
    break;
  case 34:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "extract_all_elts_from_build_vector", 34) != 0)
      break;
    return 7;	 // "extract_all_elts_from_build_vector"
  case 36:	 // 3 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'c':	 // 2 strings to match.
      if (memcmp(RuleIdentifier.data()+1, "ombine_", 7) != 0)
        break;
      switch (RuleIdentifier[8]) {
      default: break;
      case 'f':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+9, "add_fma_fmul_to_fmad_or_fma", 27) != 0)
          break;
        return 105;	 // "combine_fadd_fma_fmul_to_fmad_or_fma"
      case 'i':	 // 1 string to match.
        if (memcmp(RuleIdentifier.data()+9, "nsert_vec_elts_build_vector", 27) != 0)
          break;
        return 5;	 // "combine_insert_vec_elts_build_vector"
      }
      break;
    case 'i':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "nsert_extract_vec_elt_out_of_bounds", 35) != 0)
        break;
      return 22;	 // "insert_extract_vec_elt_out_of_bounds"
    }
    break;
  case 37:	 // 2 strings to match.
    switch (RuleIdentifier[0]) {
    default: break;
    case 'c':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "ombine_fsub_fneg_fmul_to_fmad_or_fma", 36) != 0)
        break;
      return 108;	 // "combine_fsub_fneg_fmul_to_fmad_or_fma"
    case 'h':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+1, "oist_logic_op_with_same_opcode_hands", 36) != 0)
        break;
      return 41;	 // "hoist_logic_op_with_same_opcode_hands"
    }
    break;
  case 38:	 // 2 strings to match.
    if (memcmp(RuleIdentifier.data()+0, "combine_f", 9) != 0)
      break;
    switch (RuleIdentifier[9]) {
    default: break;
    case 'a':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+10, "dd_fpext_fmul_to_fmad_or_fma", 28) != 0)
        break;
      return 104;	 // "combine_fadd_fpext_fmul_to_fmad_or_fma"
    case 's':	 // 1 string to match.
      if (memcmp(RuleIdentifier.data()+10, "ub_fpext_fmul_to_fmad_or_fma", 28) != 0)
        break;
      return 109;	 // "combine_fsub_fpext_fmul_to_fmad_or_fma"
    }
    break;
  case 42:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "combine_fadd_fpext_fma_fmul_to_fmad_or_fma", 42) != 0)
      break;
    return 106;	 // "combine_fadd_fpext_fma_fmul_to_fmad_or_fma"
  case 43:	 // 1 string to match.
    if (memcmp(RuleIdentifier.data()+0, "combine_fsub_fpext_fneg_fmul_to_fmad_or_fma", 43) != 0)
      break;
    return 110;	 // "combine_fsub_fpext_fneg_fmul_to_fmad_or_fma"
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
    return {{0, 120}};
  }
  const auto I = getRuleIdxForIdentifier(RangePair.first);
  if (!I)
    return std::nullopt;
  return {{*I, *I + 1}};
}

bool AArch64PreLegalizerCombinerImplRuleConfig::setRuleEnabled(StringRef RuleIdentifier) {
  auto MaybeRange = getRuleRangeForIdentifier(RuleIdentifier);
  if (!MaybeRange)
    return false;
  for (auto I = MaybeRange->first; I < MaybeRange->second; ++I)
    DisabledRules.reset(I);
  return true;
}

bool AArch64PreLegalizerCombinerImplRuleConfig::setRuleDisabled(StringRef RuleIdentifier) {
  auto MaybeRange = getRuleRangeForIdentifier(RuleIdentifier);
  if (!MaybeRange)
    return false;
  for (auto I = MaybeRange->first; I < MaybeRange->second; ++I)
    DisabledRules.set(I);
  return true;
}

static std::vector<std::string> AArch64PreLegalizerCombinerOption;
static cl::list<std::string> AArch64PreLegalizerCombinerDisableOption(
    "aarch64prelegalizercombiner-disable-rule",
    cl::desc("Disable one or more combiner rules temporarily in the AArch64PreLegalizerCombiner pass"),
    cl::CommaSeparated,
    cl::Hidden,
    cl::cat(GICombinerOptionCategory),
    cl::callback([](const std::string &Str) {
      AArch64PreLegalizerCombinerOption.push_back(Str);
    }));
static cl::list<std::string> AArch64PreLegalizerCombinerOnlyEnableOption(
    "aarch64prelegalizercombiner-only-enable-rule",
    cl::desc("Disable all rules in the AArch64PreLegalizerCombiner pass then re-enable the specified ones"),
    cl::Hidden,
    cl::cat(GICombinerOptionCategory),
    cl::callback([](const std::string &CommaSeparatedArg) {
      StringRef Str = CommaSeparatedArg;
      AArch64PreLegalizerCombinerOption.push_back("*");
      do {
        auto X = Str.split(",");
        AArch64PreLegalizerCombinerOption.push_back(("!" + X.first).str());
        Str = X.second;
      } while (!Str.empty());
    }));


bool AArch64PreLegalizerCombinerImplRuleConfig::isRuleEnabled(unsigned RuleID) const {
    return  !DisabledRules.test(RuleID);
}
bool AArch64PreLegalizerCombinerImplRuleConfig::parseCommandLineOption() {
  for (StringRef Identifier : AArch64PreLegalizerCombinerOption) {
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
  typedef ComplexRendererFns(AArch64PreLegalizerCombinerImpl::*ComplexMatcherMemFn)(MachineOperand &) const;
  typedef void(AArch64PreLegalizerCombinerImpl::*CustomRendererFn)(MachineInstrBuilder &, const MachineInstr &, int) const;
  const ExecInfoTy<PredicateBitset, ComplexMatcherMemFn, CustomRendererFn> ExecInfo;
  static AArch64PreLegalizerCombinerImpl::ComplexMatcherMemFn ComplexPredicateFns[];
  static AArch64PreLegalizerCombinerImpl::CustomRendererFn CustomRenderers[];
  bool testImmPredicate_I64(unsigned PredicateID, int64_t Imm) const override;
  bool testImmPredicate_APInt(unsigned PredicateID, const APInt &Imm) const override;
  bool testImmPredicate_APFloat(unsigned PredicateID, const APFloat &Imm) const override;
  const int64_t *getMatchTable() const override;
  bool testMIPredicate_MI(unsigned PredicateID, const MachineInstr &MI, const MatcherState &State) const override;
  bool testSimplePredicate(unsigned PredicateID) const override;
  void runCustomAction(unsigned FnID, const MatcherState &State) const override;
  struct MatchInfosTy {
    std::pair<Register, bool> MDInfo1;
    InstructionStepsMatchInfo MDInfo10;
    IndexedLoadStoreMatchInfo MDInfo7;
    MachineInstr* MDInfo8;
    SmallVector<Register, 4> MDInfo2;
    RegisterImmPair MDInfo14;
    Register MDInfo3;
    std::pair<Register, unsigned> MDInfo19;
    APInt MDInfo21;
    std::pair<uint64_t, uint64_t> MDInfo24;
    unsigned MDInfo0;
    SmallVector<std::pair<Register, MachineInstr*>> MDInfo4;
    std::tuple<Register, unsigned> MDInfo13;
    MachineInstr * MDInfo16;
    ShiftOfShiftedLogic MDInfo23;
    std::pair<MachineInstr*, LLT> MDInfo20;
    PreferredTuple MDInfo5;
    SmallVector<APInt, 8> MDInfo18;
    std::tuple<Register, Register> MDInfo9;
    std::tuple<Register, int64_t> MDInfo12;
    SmallVector<Register, 8> MDInfo17;
    std::function<void(MachineIRBuilder &)> MDInfo6;
    int64_t MDInfo15;
    std::pair<Register, Register> MDInfo22;
    PtrAddChain MDInfo11;
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

PredicateBitset AArch64PreLegalizerCombinerImpl::
computeAvailableModuleFeatures(const AArch64Subtarget *Subtarget) const {
  PredicateBitset Features;
  return Features;
}

void AArch64PreLegalizerCombinerImpl::setupGeneratedPerFunctionState(MachineFunction &MF) {
  AvailableFunctionFeatures = computeAvailableFunctionFeatures((const AArch64Subtarget *)&MF.getSubtarget(), &MF);
}
PredicateBitset AArch64PreLegalizerCombinerImpl::
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

AArch64PreLegalizerCombinerImpl::ComplexMatcherMemFn
AArch64PreLegalizerCombinerImpl::ComplexPredicateFns[] = {
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
  GICXXPred_MI_Predicate_GICombiner50,
  GICXXPred_MI_Predicate_GICombiner51,
  GICXXPred_MI_Predicate_GICombiner52,
  GICXXPred_MI_Predicate_GICombiner53,
  GICXXPred_MI_Predicate_GICombiner54,
  GICXXPred_MI_Predicate_GICombiner55,
  GICXXPred_MI_Predicate_GICombiner56,
  GICXXPred_MI_Predicate_GICombiner57,
  GICXXPred_MI_Predicate_GICombiner58,
  GICXXPred_MI_Predicate_GICombiner59,
  GICXXPred_MI_Predicate_GICombiner60,
  GICXXPred_MI_Predicate_GICombiner61,
  GICXXPred_MI_Predicate_GICombiner62,
  GICXXPred_MI_Predicate_GICombiner63,
  GICXXPred_MI_Predicate_GICombiner64,
  GICXXPred_MI_Predicate_GICombiner65,
  GICXXPred_MI_Predicate_GICombiner66,
  GICXXPred_MI_Predicate_GICombiner67,
  GICXXPred_MI_Predicate_GICombiner68,
  GICXXPred_MI_Predicate_GICombiner69,
  GICXXPred_MI_Predicate_GICombiner70,
  GICXXPred_MI_Predicate_GICombiner71,
  GICXXPred_MI_Predicate_GICombiner72,
  GICXXPred_MI_Predicate_GICombiner73,
  GICXXPred_MI_Predicate_GICombiner74,
  GICXXPred_MI_Predicate_GICombiner75,
  GICXXPred_MI_Predicate_GICombiner76,
  GICXXPred_MI_Predicate_GICombiner77,
  GICXXPred_MI_Predicate_GICombiner78,
  GICXXPred_MI_Predicate_GICombiner79,
  GICXXPred_MI_Predicate_GICombiner80,
  GICXXPred_MI_Predicate_GICombiner81,
  GICXXPred_MI_Predicate_GICombiner82,
  GICXXPred_MI_Predicate_GICombiner83,
  GICXXPred_MI_Predicate_GICombiner84,
  GICXXPred_MI_Predicate_GICombiner85,
  GICXXPred_MI_Predicate_GICombiner86,
  GICXXPred_MI_Predicate_GICombiner87,
  GICXXPred_MI_Predicate_GICombiner88,
  GICXXPred_MI_Predicate_GICombiner89,
  GICXXPred_MI_Predicate_GICombiner90,
  GICXXPred_MI_Predicate_GICombiner91,
  GICXXPred_MI_Predicate_GICombiner92,
  GICXXPred_MI_Predicate_GICombiner93,
  GICXXPred_MI_Predicate_GICombiner94,
  GICXXPred_MI_Predicate_GICombiner95,
  GICXXPred_MI_Predicate_GICombiner96,
  GICXXPred_MI_Predicate_GICombiner97,
  GICXXPred_MI_Predicate_GICombiner98,
  GICXXPred_MI_Predicate_GICombiner99,
  GICXXPred_MI_Predicate_GICombiner100,
  GICXXPred_MI_Predicate_GICombiner101,
  GICXXPred_MI_Predicate_GICombiner102,
  GICXXPred_MI_Predicate_GICombiner103,
  GICXXPred_MI_Predicate_GICombiner104,
  GICXXPred_MI_Predicate_GICombiner105,
  GICXXPred_MI_Predicate_GICombiner106,
  GICXXPred_MI_Predicate_GICombiner107,
  GICXXPred_MI_Predicate_GICombiner108,
};
bool AArch64PreLegalizerCombinerImpl::testMIPredicate_MI(unsigned PredicateID, const MachineInstr & MI, const MatcherState &State) const {
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
    return Helper.matchCombineInsertVecElts(*State.MIs[0], MatchInfos.MDInfo2);
  }
  case GICXXPred_MI_Predicate_GICombiner6: {
    return Helper.matchExtractVecEltBuildVec(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner7: {
    return Helper.matchExtractAllEltsFromBuildVector(*State.MIs[0], MatchInfos.MDInfo4);
  }
  case GICXXPred_MI_Predicate_GICombiner8: {
    return Helper.matchCombineExtendingLoads(*State.MIs[0], MatchInfos.MDInfo5);
  }
  case GICXXPred_MI_Predicate_GICombiner9: {
    return Helper.matchCombineLoadWithAndMask(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner10: {
    return Helper.matchCombineIndexedLoadStore(*State.MIs[0], MatchInfos.MDInfo7);
  }
  case GICXXPred_MI_Predicate_GICombiner11: {
    return Helper.matchAnyExplicitUseIsUndef(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner12: {
    return Helper.matchOperandIsUndef(*State.MIs[0], 1);
  }
  case GICXXPred_MI_Predicate_GICombiner13: {
    return Helper.matchOperandIsUndef(*State.MIs[0], 2);
  }
  case GICXXPred_MI_Predicate_GICombiner14: {
    return Helper.matchAllExplicitUsesAreUndef(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner15: {
    return Helper.matchUndefShuffleVectorMask(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner16: {
    return Helper.matchUndefStore(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner17: {
    return Helper.matchCombineUnmergeUndef(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner18: {
    return Helper.matchInsertExtractVecEltOutOfBounds(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner19: {
    return Helper.matchSelectSameVal(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner20: {
    return Helper.matchConstantOp(State.MIs[0]->getOperand(2), 0);
  }
  case GICXXPred_MI_Predicate_GICombiner21: {
    return Helper.matchBinOpSameVal(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner22: {
    return Helper.matchOperandIsZero(*State.MIs[0], 1);
  }
  case GICXXPred_MI_Predicate_GICombiner23: {
    return Helper.matchOperandIsZero(*State.MIs[0], 2);
  }
  case GICXXPred_MI_Predicate_GICombiner24: {
    return Helper.matchCombineI2PToP2I(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner25: {
    MatchInfos.MDInfo3 = State.MIs[1]->getOperand(1).getReg(); return true;
    llvm_unreachable("GICombiner25 should have returned");
  }
  case GICXXPred_MI_Predicate_GICombiner26: {
    return Helper.matchCombineAnyExtTrunc(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner27: {
    return Helper.matchConstantOp(State.MIs[0]->getOperand(2), 1);
  }
  case GICXXPred_MI_Predicate_GICombiner28: {
    return Helper.matchAddSubSameReg(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner29: {
    return Helper.matchBuildVectorIdentityFold(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner30: {
    return Helper.matchTruncBuildVectorFold(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner31: {
    return Helper.matchTruncLshrBuildVectorFold(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner32: {
    return MRI.getType(State.MIs[1]->getOperand(1).getReg()) == MRI.getType(State.MIs[0]->getOperand(0).getReg());
  }
  case GICXXPred_MI_Predicate_GICombiner33: {
    return Helper.matchExtendThroughPhis(*State.MIs[0], MatchInfos.MDInfo8);
  }
  case GICXXPred_MI_Predicate_GICombiner34: {
    return Helper.matchSimplifyAddToSub(*State.MIs[0], MatchInfos.MDInfo9);
  }
  case GICXXPred_MI_Predicate_GICombiner35: {
    return Helper.matchHoistLogicOpWithSameOpcodeHands(*State.MIs[0], MatchInfos.MDInfo10);
  }
  case GICXXPred_MI_Predicate_GICombiner36: {
    return Helper.matchShiftsTooBig(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner37: {
    return Helper.matchReassocPtrAdd(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner38: {
    return Helper.matchReassocCommBinOp(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner39: {
    return Helper.matchPtrAddImmedChain(*State.MIs[0], MatchInfos.MDInfo11);
  }
  case GICXXPred_MI_Predicate_GICombiner40: {
    return Helper.matchAshrShlToSextInreg(*State.MIs[0], MatchInfos.MDInfo12);
  }
  case GICXXPred_MI_Predicate_GICombiner41: {
    return Helper.matchSextInRegOfLoad(*State.MIs[0], MatchInfos.MDInfo13);
  }
  case GICXXPred_MI_Predicate_GICombiner42: {
    return Helper.matchCombineShlOfExtend(*State.MIs[0], MatchInfos.MDInfo14);
  }
  case GICXXPred_MI_Predicate_GICombiner43: {
    return Helper.matchNarrowBinopFeedingAnd(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner44: {
    return Helper.matchUndefSelectCmp(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner45: {
    return Helper.matchConstantSelectCmp(*State.MIs[0], MatchInfos.MDInfo0);
  }
  case GICXXPred_MI_Predicate_GICombiner46: {
    return Helper.matchSelectToLogical(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner47: {
    return Helper.matchRedundantAnd(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner48: {
    return Helper.matchRedundantSExtInReg(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner49: {
    return Helper.matchRedundantOr(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner50: {
    return Helper.matchOperandIsKnownToBeAPowerOfTwo(*State.MIs[0], 2);
  }
  case GICXXPred_MI_Predicate_GICombiner51: {
    return Helper.matchCombineZextTrunc(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner52: {
    return Helper.matchICmpToTrueFalseKnownBits(*State.MIs[0], MatchInfos.MDInfo15);
  }
  case GICXXPred_MI_Predicate_GICombiner53: {
    return Helper.matchICmpToLHSKnownBits(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner54: {
    unsigned BitWidth = MRI.getType(State.MIs[0]->getOperand(1).getReg()).getScalarSizeInBits();
            return Helper.getKnownBits()->maskedValueIsZero(State.MIs[0]->getOperand(1).getReg(),
                     APInt::getOneBitSet(BitWidth, State.MIs[0]->getOperand(2).getImm() - 1));
    llvm_unreachable("GICombiner54 should have returned");
  }
  case GICXXPred_MI_Predicate_GICombiner55: {
    return Helper.matchCombineExtOfExt(*State.MIs[0], MatchInfos.MDInfo13);
  }
  case GICXXPred_MI_Predicate_GICombiner56: {
    return Helper.matchNotCmp(*State.MIs[0], MatchInfos.MDInfo2);
  }
  case GICXXPred_MI_Predicate_GICombiner57: {
    return Helper.matchOptBrCondByInvertingCond(*State.MIs[0], MatchInfos.MDInfo16);
  }
  case GICXXPred_MI_Predicate_GICombiner58: {
    return Helper.matchCombineUnmergeMergeToPlainValues(*State.MIs[0], MatchInfos.MDInfo17);
  }
  case GICXXPred_MI_Predicate_GICombiner59: {
    return Helper.matchCombineUnmergeConstant(*State.MIs[0], MatchInfos.MDInfo18);
  }
  case GICXXPred_MI_Predicate_GICombiner60: {
    return Helper.matchCombineUnmergeWithDeadLanesToTrunc(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner61: {
    return Helper.matchCombineUnmergeZExtToZExt(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner62: {
    return Helper.matchCombineMergeUnmerge(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner63: {
    return Helper.matchCombineTruncOfExt(*State.MIs[0], MatchInfos.MDInfo19);
  }
  case GICXXPred_MI_Predicate_GICombiner64: {
    return Helper.matchCombineTruncOfShift(*State.MIs[0], MatchInfos.MDInfo20);
  }
  case GICXXPred_MI_Predicate_GICombiner65: {
    return Helper.matchCombineConstPtrAddToI2P(*State.MIs[0], MatchInfos.MDInfo21);
  }
  case GICXXPred_MI_Predicate_GICombiner66: {
    return Helper.matchOverlappingAnd(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner67: {
    return Helper.matchMulOBy2(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner68: {
    return Helper.matchMulOBy0(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner69: {
    return Helper.matchAddOBy0(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner70: {
    return Helper.matchAddEToAddO(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner71: {
    return Helper.matchCombineFMinMaxNaN(*State.MIs[0], MatchInfos.MDInfo0);
  }
  case GICXXPred_MI_Predicate_GICombiner72: {
    return Helper.matchXorOfAndWithSameReg(*State.MIs[0], MatchInfos.MDInfo22);
  }
  case GICXXPred_MI_Predicate_GICombiner73: {
    return Helper.matchPtrAddZero(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner74: {
    return Helper.matchShiftImmedChain(*State.MIs[0], MatchInfos.MDInfo14);
  }
  case GICXXPred_MI_Predicate_GICombiner75: {
    return Helper.matchShiftOfShiftedLogic(*State.MIs[0], MatchInfos.MDInfo23);
  }
  case GICXXPred_MI_Predicate_GICombiner76: {
    return Helper.matchLoadOrCombine(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner77: {
    return Helper.matchCombineDivRem(*State.MIs[0], MatchInfos.MDInfo16);
  }
  case GICXXPred_MI_Predicate_GICombiner78: {
    return Helper.matchOrShiftToFunnelShift(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner79: {
    return Helper.matchFunnelShiftToRotate(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner80: {
    return Helper.matchCommuteShift(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner81: {
    return Helper.matchBitfieldExtractFromSExtInReg(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner82: {
    return Helper.matchBitfieldExtractFromAnd(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner83: {
    return Helper.matchBitfieldExtractFromShr(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner84: {
    return Helper.matchBitfieldExtractFromShrAnd(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner85: {
    return Helper.matchConstantFold(*State.MIs[0], MatchInfos.MDInfo21);
  }
  case GICXXPred_MI_Predicate_GICombiner86: {
    return Helper.matchCombineFAbsOfFNeg(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner87: {
    return Helper.matchUDivByConst(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner88: {
    return Helper.matchSDivByConst(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner89: {
    return Helper.matchUMulHToLShr(*State.MIs[0]);
  }
  case GICXXPred_MI_Predicate_GICombiner90: {
    return Helper.matchRedundantNegOperands(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner91: {
    return Helper.matchAndOrDisjointMask(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner92: {
    return Helper.matchCombineFAddFMulToFMadOrFMA(*State.MIs[0],
                                                              MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner93: {
    return Helper.matchCombineFAddFpExtFMulToFMadOrFMA(*State.MIs[0],
                                                                   MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner94: {
    return Helper.matchCombineFAddFMAFMulToFMadOrFMA(*State.MIs[0],
                                                                 MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner95: {
    return Helper.matchCombineFAddFpExtFMulToFMadOrFMAAggressive(
                                                      *State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner96: {
    return Helper.matchCombineFSubFMulToFMadOrFMA(*State.MIs[0],
                                                              MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner97: {
    return Helper.matchCombineFSubFNegFMulToFMadOrFMA(*State.MIs[0],
                                                                  MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner98: {
    return Helper.matchCombineFSubFpExtFMulToFMadOrFMA(*State.MIs[0],
                                                                   MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner99: {
    return Helper.matchCombineFSubFpExtFNegFMulToFMadOrFMA(
                                                *State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner100: {
    return Helper.matchFoldBinOpIntoSelect(*State.MIs[0], MatchInfos.MDInfo0);
  }
  case GICXXPred_MI_Predicate_GICombiner101: {
    return Helper.matchSubAddSameReg(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner102: {
    return Helper.matchSimplifySelectToMinMax(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner103: {
    return Helper.matchRedundantBinOpInEquality(*State.MIs[0], MatchInfos.MDInfo6);
  }
  case GICXXPred_MI_Predicate_GICombiner104: {
    return Helper.matchFsubToFneg(*State.MIs[0], MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner105: {
    return getIConstantVRegVal(State.MIs[0]->getOperand(1).getReg(), MRI).has_value();
  }
  case GICXXPred_MI_Predicate_GICombiner106: {
    return matchFConstantToConstant(*State.MIs[0], MRI);
  }
  case GICXXPred_MI_Predicate_GICombiner107: {
    return matchICmpRedundantTrunc(*State.MIs[0], MRI, Helper.getKnownBits(), MatchInfos.MDInfo3);
  }
  case GICXXPred_MI_Predicate_GICombiner108: {
    return matchFoldGlobalOffset(*State.MIs[0], MRI, MatchInfos.MDInfo24);
  }
  }
  llvm_unreachable("Unknown predicate");
  return false;
}
bool AArch64PreLegalizerCombinerImpl::testImmPredicate_I64(unsigned PredicateID, int64_t Imm) const {
  llvm_unreachable("Unknown predicate");
  return false;
}
bool AArch64PreLegalizerCombinerImpl::testImmPredicate_APFloat(unsigned PredicateID, const APFloat & Imm) const {
  llvm_unreachable("Unknown predicate");
  return false;
}
bool AArch64PreLegalizerCombinerImpl::testImmPredicate_APInt(unsigned PredicateID, const APInt & Imm) const {
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
  GICXXPred_Simple_IsRule56Enabled,
  GICXXPred_Simple_IsRule57Enabled,
  GICXXPred_Simple_IsRule58Enabled,
  GICXXPred_Simple_IsRule59Enabled,
  GICXXPred_Simple_IsRule60Enabled,
  GICXXPred_Simple_IsRule61Enabled,
  GICXXPred_Simple_IsRule62Enabled,
  GICXXPred_Simple_IsRule63Enabled,
  GICXXPred_Simple_IsRule64Enabled,
  GICXXPred_Simple_IsRule65Enabled,
  GICXXPred_Simple_IsRule66Enabled,
  GICXXPred_Simple_IsRule67Enabled,
  GICXXPred_Simple_IsRule68Enabled,
  GICXXPred_Simple_IsRule69Enabled,
  GICXXPred_Simple_IsRule70Enabled,
  GICXXPred_Simple_IsRule71Enabled,
  GICXXPred_Simple_IsRule72Enabled,
  GICXXPred_Simple_IsRule73Enabled,
  GICXXPred_Simple_IsRule74Enabled,
  GICXXPred_Simple_IsRule75Enabled,
  GICXXPred_Simple_IsRule76Enabled,
  GICXXPred_Simple_IsRule77Enabled,
  GICXXPred_Simple_IsRule78Enabled,
  GICXXPred_Simple_IsRule79Enabled,
  GICXXPred_Simple_IsRule80Enabled,
  GICXXPred_Simple_IsRule81Enabled,
  GICXXPred_Simple_IsRule82Enabled,
  GICXXPred_Simple_IsRule83Enabled,
  GICXXPred_Simple_IsRule84Enabled,
  GICXXPred_Simple_IsRule85Enabled,
  GICXXPred_Simple_IsRule86Enabled,
  GICXXPred_Simple_IsRule87Enabled,
  GICXXPred_Simple_IsRule88Enabled,
  GICXXPred_Simple_IsRule89Enabled,
  GICXXPred_Simple_IsRule90Enabled,
  GICXXPred_Simple_IsRule91Enabled,
  GICXXPred_Simple_IsRule92Enabled,
  GICXXPred_Simple_IsRule93Enabled,
  GICXXPred_Simple_IsRule94Enabled,
  GICXXPred_Simple_IsRule95Enabled,
  GICXXPred_Simple_IsRule96Enabled,
  GICXXPred_Simple_IsRule97Enabled,
  GICXXPred_Simple_IsRule98Enabled,
  GICXXPred_Simple_IsRule99Enabled,
  GICXXPred_Simple_IsRule100Enabled,
  GICXXPred_Simple_IsRule101Enabled,
  GICXXPred_Simple_IsRule102Enabled,
  GICXXPred_Simple_IsRule103Enabled,
  GICXXPred_Simple_IsRule104Enabled,
  GICXXPred_Simple_IsRule105Enabled,
  GICXXPred_Simple_IsRule106Enabled,
  GICXXPred_Simple_IsRule107Enabled,
  GICXXPred_Simple_IsRule108Enabled,
  GICXXPred_Simple_IsRule109Enabled,
  GICXXPred_Simple_IsRule110Enabled,
  GICXXPred_Simple_IsRule111Enabled,
  GICXXPred_Simple_IsRule112Enabled,
  GICXXPred_Simple_IsRule113Enabled,
  GICXXPred_Simple_IsRule114Enabled,
  GICXXPred_Simple_IsRule115Enabled,
  GICXXPred_Simple_IsRule116Enabled,
  GICXXPred_Simple_IsRule117Enabled,
  GICXXPred_Simple_IsRule118Enabled,
  GICXXPred_Simple_IsRule119Enabled,
};

bool AArch64PreLegalizerCombinerImpl::testSimplePredicate(unsigned Predicate) const {
    return RuleConfig.isRuleEnabled(Predicate - GICXXPred_Invalid - 1);
}
// Custom renderers.
enum {
  GICR_Invalid,
};
AArch64PreLegalizerCombinerImpl::CustomRendererFn
AArch64PreLegalizerCombinerImpl::CustomRenderers[] = {
  nullptr, // GICR_Invalid
};

bool AArch64PreLegalizerCombinerImpl::tryCombineAll(MachineInstr &I) const {
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
  GICXXCustomAction_CombineApplyGICombiner28,
  GICXXCustomAction_CombineApplyGICombiner29,
  GICXXCustomAction_CombineApplyGICombiner30,
  GICXXCustomAction_CombineApplyGICombiner31,
  GICXXCustomAction_CombineApplyGICombiner32,
  GICXXCustomAction_CombineApplyGICombiner33,
  GICXXCustomAction_CombineApplyGICombiner34,
  GICXXCustomAction_CombineApplyGICombiner35,
  GICXXCustomAction_CombineApplyGICombiner36,
  GICXXCustomAction_CombineApplyGICombiner37,
  GICXXCustomAction_CombineApplyGICombiner38,
  GICXXCustomAction_CombineApplyGICombiner39,
  GICXXCustomAction_CombineApplyGICombiner40,
  GICXXCustomAction_CombineApplyGICombiner41,
  GICXXCustomAction_CombineApplyGICombiner42,
  GICXXCustomAction_CombineApplyGICombiner43,
  GICXXCustomAction_CombineApplyGICombiner44,
  GICXXCustomAction_CombineApplyGICombiner45,
  GICXXCustomAction_CombineApplyGICombiner46,
  GICXXCustomAction_CombineApplyGICombiner47,
  GICXXCustomAction_CombineApplyGICombiner48,
  GICXXCustomAction_CombineApplyGICombiner49,
  GICXXCustomAction_CombineApplyGICombiner50,
  GICXXCustomAction_CombineApplyGICombiner51,
  GICXXCustomAction_CombineApplyGICombiner52,
  GICXXCustomAction_CombineApplyGICombiner53,
  GICXXCustomAction_CombineApplyGICombiner54,
  GICXXCustomAction_CombineApplyGICombiner55,
  GICXXCustomAction_CombineApplyGICombiner56,
  GICXXCustomAction_CombineApplyGICombiner57,
  GICXXCustomAction_CombineApplyGICombiner58,
  GICXXCustomAction_CombineApplyGICombiner59,
  GICXXCustomAction_CombineApplyGICombiner60,
};
void AArch64PreLegalizerCombinerImpl::runCustomAction(unsigned ApplyID, const MatcherState &State) const {
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
    Helper.applyCombineInsertVecElts(*State.MIs[0], MatchInfos.MDInfo2);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner6:{
    Helper.applyExtractVecEltBuildVec(*State.MIs[0], MatchInfos.MDInfo3);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner7:{
    Helper.applyExtractAllEltsFromBuildVector(*State.MIs[0], MatchInfos.MDInfo4);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner8:{
    Helper.applyCombineExtendingLoads(*State.MIs[0], MatchInfos.MDInfo5);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner9:{
    Helper.applyBuildFn(*State.MIs[0], MatchInfos.MDInfo6);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner10:{
    Helper.applyCombineIndexedLoadStore(*State.MIs[0], MatchInfos.MDInfo7);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner11:{
    Helper.replaceInstWithFConstant(*State.MIs[0], 0.0);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner12:{
    Helper.replaceInstWithConstant(*State.MIs[0], 0);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner13:{
    Helper.replaceInstWithConstant(*State.MIs[0], -1);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner14:{
    Helper.replaceInstWithUndef(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner15:{
    Helper.eraseInst(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner16:{
    Helper.replaceSingleDefInstWithOperand(*State.MIs[0], 2);
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
    Helper.replaceSingleDefInstWithReg(*State.MIs[0], MatchInfos.MDInfo3);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner20:{
    Helper.replaceSingleDefInstWithReg(*State.MIs[0],
                                                          MatchInfos.MDInfo3);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner21:{
    Helper.replaceSingleDefInstWithReg(*State.MIs[0], State.MIs[1]->getOperand(1).getReg());
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner22:{
    Helper.applyExtendThroughPhis(*State.MIs[0], MatchInfos.MDInfo8);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner23:{
    Helper.applySimplifyAddToSub(*State.MIs[0], MatchInfos.MDInfo9);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner24:{
    Helper.applyBuildInstructionSteps(*State.MIs[0], MatchInfos.MDInfo10);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner25:{
    Helper.applyBuildFnNoErase(*State.MIs[0], MatchInfos.MDInfo6);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner26:{
    Helper.applyPtrAddImmedChain(*State.MIs[0], MatchInfos.MDInfo11);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner27:{
    Helper.applyAshShlToSextInreg(*State.MIs[0], MatchInfos.MDInfo12);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner28:{
    Helper.applySextInRegOfLoad(*State.MIs[0], MatchInfos.MDInfo13);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner29:{
    Helper.applyCombineShlOfExtend(*State.MIs[0], MatchInfos.MDInfo14);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner30:{
    Helper.replaceSingleDefInstWithOperand(*State.MIs[0], MatchInfos.MDInfo0);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner31:{
    Helper.applySimplifyURemByPow2(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner32:{
    Helper.replaceInstWithConstant(*State.MIs[0], MatchInfos.MDInfo15);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner33:{
    Helper.getBuilder().setInstrAndDebugLoc(*State.MIs[0]);
          Helper.getBuilder().buildZExtInReg(State.MIs[0]->getOperand(0), State.MIs[0]->getOperand(1), State.MIs[0]->getOperand(2).getImm());
          State.MIs[0]->eraseFromParent();
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner34:{
    Helper.applyCombineExtOfExt(*State.MIs[0], MatchInfos.MDInfo13);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner35:{
    Helper.applyNotCmp(*State.MIs[0], MatchInfos.MDInfo2);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner36:{
    Helper.applyOptBrCondByInvertingCond(*State.MIs[0], MatchInfos.MDInfo16);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner37:{
    Helper.applyCombineUnmergeMergeToPlainValues(*State.MIs[0], MatchInfos.MDInfo17);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner38:{
    Helper.applyCombineUnmergeConstant(*State.MIs[0], MatchInfos.MDInfo18);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner39:{
    Helper.applyCombineUnmergeWithDeadLanesToTrunc(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner40:{
    Helper.applyCombineUnmergeZExtToZExt(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner41:{
    Helper.applyCombineTruncOfExt(*State.MIs[0], MatchInfos.MDInfo19);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner42:{
    Helper.applyCombineTruncOfShift(*State.MIs[0], MatchInfos.MDInfo20);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner43:{
    Helper.applyCombineConstantFoldFpUnary(*State.MIs[0], State.MIs[1]->getOperand(1).getFPImm());
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner44:{
    Helper.applyCombineConstPtrAddToI2P(*State.MIs[0], MatchInfos.MDInfo21);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner45:{
    Helper.applyXorOfAndWithSameReg(*State.MIs[0], MatchInfos.MDInfo22);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner46:{
    Helper.applyPtrAddZero(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner47:{
    Helper.applyShiftImmedChain(*State.MIs[0], MatchInfos.MDInfo14);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner48:{
    Helper.applyShiftOfShiftedLogic(*State.MIs[0], MatchInfos.MDInfo23);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner49:{
    Helper.applyCombineDivRem(*State.MIs[0], MatchInfos.MDInfo16);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner50:{
    Helper.applyFunnelShiftToRotate(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner51:{
    Helper.replaceInstWithConstant(*State.MIs[0], MatchInfos.MDInfo21);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner52:{
    Helper.applyUDivByConst(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner53:{
    Helper.applySDivByConst(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner54:{
    Helper.applyUMulHToLShr(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner55:{
    Helper.applyFoldBinOpIntoSelect(*State.MIs[0], MatchInfos.MDInfo0);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner56:{
    Helper.applyFsubToFneg(*State.MIs[0], MatchInfos.MDInfo3);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner57:{
    Observer.changingInstr(*State.MIs[0]);
        Register LHSReg = State.MIs[0]->getOperand(1).getReg();
        Register RHSReg = State.MIs[0]->getOperand(2).getReg();
        State.MIs[0]->getOperand(1).setReg(RHSReg);
        State.MIs[0]->getOperand(2).setReg(LHSReg);
        Observer.changedInstr(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner58:{
    applyFConstantToConstant(*State.MIs[0]);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner59:{
    applyICmpRedundantTrunc(*State.MIs[0], MRI, B, Observer, MatchInfos.MDInfo3);
    return;
  }
  case GICXXCustomAction_CombineApplyGICombiner60:{
    applyFoldGlobalOffset(*State.MIs[0], MRI, B, Observer, MatchInfos.MDInfo24);
    return;
  }
}
  llvm_unreachable("Unknown Apply Action");
}
const int64_t *AArch64PreLegalizerCombinerImpl::getMatchTable() const {
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
    GIM_Try, /*On fail goto*//*Label 1*/ 89,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_MUL,
      GIM_Try, /*On fail goto*//*Label 2*/ 28, // Rule ID 3 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule3Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner3,
        // Combiner Rule #3: mul_by_neg_one; wip_match_opcode alternative 'G_MUL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner3,
        GIR_Done,
      // Label 2: @28
      GIM_Try, /*On fail goto*//*Label 3*/ 38, // Rule ID 21 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule12Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner11,
        // Combiner Rule #12: undef_to_int_zero; wip_match_opcode alternative 'G_MUL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner12,
        GIR_Done,
      // Label 3: @38
      GIM_Try, /*On fail goto*//*Label 4*/ 48, // Rule ID 59 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule27Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner23,
        // Combiner Rule #27: binop_right_to_zero; wip_match_opcode alternative 'G_MUL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner16,
        GIR_Done,
      // Label 4: @48
      GIM_Try, /*On fail goto*//*Label 5*/ 58, // Rule ID 64 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule32Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner27,
        // Combiner Rule #32: right_identity_one; wip_match_opcode alternative 'G_MUL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 5: @58
      GIM_Try, /*On fail goto*//*Label 6*/ 68, // Rule ID 160 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule96Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner85,
        // Combiner Rule #96: constant_fold; wip_match_opcode alternative 'G_MUL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner51,
        GIR_Done,
      // Label 6: @68
      GIM_Try, /*On fail goto*//*Label 7*/ 78, // Rule ID 214 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule116Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner105,
        // Combiner Rule #116: commute_constant_to_rhs; wip_match_opcode alternative 'G_MUL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner57,
        GIR_Done,
      // Label 7: @78
      GIM_Try, /*On fail goto*//*Label 8*/ 88, // Rule ID 1 //
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
      // Label 8: @88
      GIM_Reject,
    // Label 1: @89
    GIM_Try, /*On fail goto*//*Label 9*/ 185,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ADD,
      GIM_Try, /*On fail goto*//*Label 10*/ 104, // Rule ID 2 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule2Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner2,
        // Combiner Rule #2: add_p2i_to_ptradd; wip_match_opcode alternative 'G_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner2,
        GIR_Done,
      // Label 10: @104
      GIM_Try, /*On fail goto*//*Label 11*/ 114, // Rule ID 30 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule17Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner11,
        // Combiner Rule #17: propagate_undef_any_op; wip_match_opcode alternative 'G_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
        GIR_Done,
      // Label 11: @114
      GIM_Try, /*On fail goto*//*Label 12*/ 124, // Rule ID 44 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule24Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner20,
        // Combiner Rule #24: right_identity_zero; wip_match_opcode alternative 'G_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 12: @124
      GIM_Try, /*On fail goto*//*Label 13*/ 134, // Rule ID 65 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule33Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner28,
        // Combiner Rule #33: add_sub_reg; wip_match_opcode alternative 'G_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner20,
        GIR_Done,
      // Label 13: @134
      GIM_Try, /*On fail goto*//*Label 14*/ 144, // Rule ID 73 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule40Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner34,
        // Combiner Rule #40: simplify_add_to_sub; wip_match_opcode alternative 'G_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner23,
        GIR_Done,
      // Label 14: @144
      GIM_Try, /*On fail goto*//*Label 15*/ 154, // Rule ID 158 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule96Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner85,
        // Combiner Rule #96: constant_fold; wip_match_opcode alternative 'G_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner51,
        GIR_Done,
      // Label 15: @154
      GIM_Try, /*On fail goto*//*Label 16*/ 164, // Rule ID 183 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 16: @164
      GIM_Try, /*On fail goto*//*Label 17*/ 174, // Rule ID 213 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule116Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner105,
        // Combiner Rule #116: commute_constant_to_rhs; wip_match_opcode alternative 'G_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner57,
        GIR_Done,
      // Label 17: @174
      GIM_Try, /*On fail goto*//*Label 18*/ 184, // Rule ID 81 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule44Enabled,
        // MIs[0] root
        // No operand predicates
        // MIs[0] src1
        // No operand predicates
        // MIs[0] src2
        // No operand predicates
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner38,
        // Combiner Rule #44: reassoc_comm_binops
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 18: @184
      GIM_Reject,
    // Label 9: @185
    GIM_Try, /*On fail goto*//*Label 19*/ 198, // Rule ID 4 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule4Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FREEZE,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner4,
      // Combiner Rule #4: idempotent_prop; wip_match_opcode alternative 'G_FREEZE'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
      GIR_Done,
    // Label 19: @198
    GIM_Try, /*On fail goto*//*Label 20*/ 240,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FABS,
      GIM_Try, /*On fail goto*//*Label 21*/ 213, // Rule ID 5 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule4Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner4,
        // Combiner Rule #4: idempotent_prop; wip_match_opcode alternative 'G_FABS'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 21: @213
      GIM_Try, /*On fail goto*//*Label 22*/ 223, // Rule ID 164 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule97Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner86,
        // Combiner Rule #97: fabs_fneg_fold; wip_match_opcode alternative 'G_FABS'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
        GIR_Done,
      // Label 22: @223
      GIM_Try, /*On fail goto*//*Label 23*/ 239, // Rule ID 111 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule72Enabled,
        // MIs[0] dst
        // No operand predicates
        // MIs[0] src0
        GIM_RecordInsn, /*DefineMI*/1, /*MI*/0, /*OpIdx*/1, // MIs[1]
        GIM_CheckOpcode, /*MI*/1, TargetOpcode::G_FCONSTANT,
        // MIs[1] cst
        // No operand predicates
        GIM_CheckIsSafeToFold, /*InsnID*/1,
        // Combiner Rule #72: constant_fold_fabs
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner43,
        GIR_Done,
      // Label 23: @239
      GIM_Reject,
    // Label 20: @240
    GIM_Try, /*On fail goto*//*Label 24*/ 253, // Rule ID 6 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule4Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FCANONICALIZE,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner4,
      // Combiner Rule #4: idempotent_prop; wip_match_opcode alternative 'G_FCANONICALIZE'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
      GIR_Done,
    // Label 24: @253
    GIM_Try, /*On fail goto*//*Label 25*/ 279,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_INSERT_VECTOR_ELT,
      GIM_Try, /*On fail goto*//*Label 26*/ 268, // Rule ID 7 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule5Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner5,
        // Combiner Rule #5: combine_insert_vec_elts_build_vector; wip_match_opcode alternative 'G_INSERT_VECTOR_ELT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner5,
        GIR_Done,
      // Label 26: @268
      GIM_Try, /*On fail goto*//*Label 27*/ 278, // Rule ID 40 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule22Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner18,
        // Combiner Rule #22: insert_extract_vec_elt_out_of_bounds; wip_match_opcode alternative 'G_INSERT_VECTOR_ELT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
        GIR_Done,
      // Label 27: @278
      GIM_Reject,
    // Label 25: @279
    GIM_Try, /*On fail goto*//*Label 28*/ 305,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_EXTRACT_VECTOR_ELT,
      GIM_Try, /*On fail goto*//*Label 29*/ 294, // Rule ID 8 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule6Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner6,
        // Combiner Rule #6: extract_vec_elt_build_vec; wip_match_opcode alternative 'G_EXTRACT_VECTOR_ELT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner6,
        GIR_Done,
      // Label 29: @294
      GIM_Try, /*On fail goto*//*Label 30*/ 304, // Rule ID 41 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule22Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner18,
        // Combiner Rule #22: insert_extract_vec_elt_out_of_bounds; wip_match_opcode alternative 'G_EXTRACT_VECTOR_ELT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
        GIR_Done,
      // Label 30: @304
      GIM_Reject,
    // Label 28: @305
    GIM_Try, /*On fail goto*//*Label 31*/ 331,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_BUILD_VECTOR,
      GIM_Try, /*On fail goto*//*Label 32*/ 320, // Rule ID 9 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule7Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner7,
        // Combiner Rule #7: extract_all_elts_from_build_vector; wip_match_opcode alternative 'G_BUILD_VECTOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner7,
        GIR_Done,
      // Label 32: @320
      GIM_Try, /*On fail goto*//*Label 33*/ 330, // Rule ID 67 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule34Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner29,
        // Combiner Rule #34: buildvector_identity_fold; wip_match_opcode alternative 'G_BUILD_VECTOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner19,
        GIR_Done,
      // Label 33: @330
      GIM_Reject,
    // Label 31: @331
    GIM_Try, /*On fail goto*//*Label 34*/ 357,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_LOAD,
      GIM_Try, /*On fail goto*//*Label 35*/ 346, // Rule ID 10 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule8Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner8,
        // Combiner Rule #8: extending_loads; wip_match_opcode alternative 'G_LOAD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner8,
        GIR_Done,
      // Label 35: @346
      GIM_Try, /*On fail goto*//*Label 36*/ 356, // Rule ID 14 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule10Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner10,
        // Combiner Rule #10: combine_indexed_load_store; wip_match_opcode alternative 'G_LOAD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 36: @356
      GIM_Reject,
    // Label 34: @357
    GIM_Try, /*On fail goto*//*Label 37*/ 383,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SEXTLOAD,
      GIM_Try, /*On fail goto*//*Label 38*/ 372, // Rule ID 11 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule8Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner8,
        // Combiner Rule #8: extending_loads; wip_match_opcode alternative 'G_SEXTLOAD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner8,
        GIR_Done,
      // Label 38: @372
      GIM_Try, /*On fail goto*//*Label 39*/ 382, // Rule ID 15 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule10Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner10,
        // Combiner Rule #10: combine_indexed_load_store; wip_match_opcode alternative 'G_SEXTLOAD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 39: @382
      GIM_Reject,
    // Label 37: @383
    GIM_Try, /*On fail goto*//*Label 40*/ 409,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ZEXTLOAD,
      GIM_Try, /*On fail goto*//*Label 41*/ 398, // Rule ID 12 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule8Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner8,
        // Combiner Rule #8: extending_loads; wip_match_opcode alternative 'G_ZEXTLOAD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner8,
        GIR_Done,
      // Label 41: @398
      GIM_Try, /*On fail goto*//*Label 42*/ 408, // Rule ID 16 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule10Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner10,
        // Combiner Rule #10: combine_indexed_load_store; wip_match_opcode alternative 'G_ZEXTLOAD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 42: @408
      GIM_Reject,
    // Label 40: @409
    GIM_Try, /*On fail goto*//*Label 43*/ 535,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_AND,
      GIM_Try, /*On fail goto*//*Label 44*/ 424, // Rule ID 13 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule9Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner9,
        // Combiner Rule #9: load_and_mask; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 44: @424
      GIM_Try, /*On fail goto*//*Label 45*/ 434, // Rule ID 20 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule12Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner11,
        // Combiner Rule #12: undef_to_int_zero; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner12,
        GIR_Done,
      // Label 45: @434
      GIM_Try, /*On fail goto*//*Label 46*/ 444, // Rule ID 53 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule25Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner21,
        // Combiner Rule #25: binop_same_val; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 46: @444
      GIM_Try, /*On fail goto*//*Label 47*/ 454, // Rule ID 74 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule41Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner35,
        // Combiner Rule #41: hoist_logic_op_with_same_opcode_hands; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner24,
        GIR_Done,
      // Label 47: @454
      GIM_Try, /*On fail goto*//*Label 48*/ 464, // Rule ID 86 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule49Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner43,
        // Combiner Rule #49: narrow_binop_feeding_and; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
        GIR_Done,
      // Label 48: @464
      GIM_Try, /*On fail goto*//*Label 49*/ 474, // Rule ID 90 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule53Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner47,
        // Combiner Rule #53: redundant_and; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner19,
        GIR_Done,
      // Label 49: @474
      GIM_Try, /*On fail goto*//*Label 50*/ 484, // Rule ID 116 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule77Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner66,
        // Combiner Rule #77: overlapping_and; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 50: @484
      GIM_Try, /*On fail goto*//*Label 51*/ 494, // Rule ID 153 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule93Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner82,
        // Combiner Rule #93: bitfield_extract_from_and; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 51: @494
      GIM_Try, /*On fail goto*//*Label 52*/ 504, // Rule ID 161 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule96Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner85,
        // Combiner Rule #96: constant_fold; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner51,
        GIR_Done,
      // Label 52: @504
      GIM_Try, /*On fail goto*//*Label 53*/ 514, // Rule ID 174 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule102Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner91,
        // Combiner Rule #102: and_or_disjoint_mask; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
        GIR_Done,
      // Label 53: @514
      GIM_Try, /*On fail goto*//*Label 54*/ 524, // Rule ID 186 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 54: @524
      GIM_Try, /*On fail goto*//*Label 55*/ 534, // Rule ID 215 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule116Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner105,
        // Combiner Rule #116: commute_constant_to_rhs; wip_match_opcode alternative 'G_AND'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner57,
        GIR_Done,
      // Label 55: @534
      GIM_Reject,
    // Label 43: @535
    GIM_Try, /*On fail goto*//*Label 56*/ 561,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_STORE,
      GIM_Try, /*On fail goto*//*Label 57*/ 550, // Rule ID 17 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule10Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner10,
        // Combiner Rule #10: combine_indexed_load_store; wip_match_opcode alternative 'G_STORE'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner10,
        GIR_Done,
      // Label 57: @550
      GIM_Try, /*On fail goto*//*Label 58*/ 560, // Rule ID 38 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule20Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner16,
        // Combiner Rule #20: erase_undef_store; wip_match_opcode alternative 'G_STORE'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner15,
        GIR_Done,
      // Label 58: @560
      GIM_Reject,
    // Label 56: @561
    GIM_Try, /*On fail goto*//*Label 59*/ 574, // Rule ID 18 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule11Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_UITOFP,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner11,
      // Combiner Rule #11: undef_to_fp_zero; wip_match_opcode alternative 'G_UITOFP'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner11,
      GIR_Done,
    // Label 59: @574
    GIM_Try, /*On fail goto*//*Label 60*/ 587, // Rule ID 19 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule11Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SITOFP,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner11,
      // Combiner Rule #11: undef_to_fp_zero; wip_match_opcode alternative 'G_SITOFP'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner11,
      GIR_Done,
    // Label 60: @587
    GIM_Try, /*On fail goto*//*Label 61*/ 693,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_OR,
      GIM_Try, /*On fail goto*//*Label 62*/ 602, // Rule ID 22 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule13Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner11,
        // Combiner Rule #13: undef_to_negative_one; wip_match_opcode alternative 'G_OR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner13,
        GIR_Done,
      // Label 62: @602
      GIM_Try, /*On fail goto*//*Label 63*/ 612, // Rule ID 45 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule24Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner20,
        // Combiner Rule #24: right_identity_zero; wip_match_opcode alternative 'G_OR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 63: @612
      GIM_Try, /*On fail goto*//*Label 64*/ 622, // Rule ID 54 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule25Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner21,
        // Combiner Rule #25: binop_same_val; wip_match_opcode alternative 'G_OR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 64: @622
      GIM_Try, /*On fail goto*//*Label 65*/ 632, // Rule ID 75 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule41Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner35,
        // Combiner Rule #41: hoist_logic_op_with_same_opcode_hands; wip_match_opcode alternative 'G_OR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner24,
        GIR_Done,
      // Label 65: @632
      GIM_Try, /*On fail goto*//*Label 66*/ 642, // Rule ID 92 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule55Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner49,
        // Combiner Rule #55: redundant_or; wip_match_opcode alternative 'G_OR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner19,
        GIR_Done,
      // Label 66: @642
      GIM_Try, /*On fail goto*//*Label 67*/ 652, // Rule ID 143 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule87Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner76,
        // Combiner Rule #87: load_or_combine; wip_match_opcode alternative 'G_OR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 67: @652
      GIM_Try, /*On fail goto*//*Label 68*/ 662, // Rule ID 148 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule89Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner78,
        // Combiner Rule #89: funnel_shift_from_or_shift; wip_match_opcode alternative 'G_OR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 68: @662
      GIM_Try, /*On fail goto*//*Label 69*/ 672, // Rule ID 162 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule96Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner85,
        // Combiner Rule #96: constant_fold; wip_match_opcode alternative 'G_OR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner51,
        GIR_Done,
      // Label 69: @672
      GIM_Try, /*On fail goto*//*Label 70*/ 682, // Rule ID 187 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_OR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 70: @682
      GIM_Try, /*On fail goto*//*Label 71*/ 692, // Rule ID 216 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule116Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner105,
        // Combiner Rule #116: commute_constant_to_rhs; wip_match_opcode alternative 'G_OR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner57,
        GIR_Done,
      // Label 71: @692
      GIM_Reject,
    // Label 61: @693
    GIM_Try, /*On fail goto*//*Label 72*/ 789,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SHL,
      GIM_Try, /*On fail goto*//*Label 73*/ 708, // Rule ID 23 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule14Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner12,
        // Combiner Rule #14: binop_left_undef_to_zero; wip_match_opcode alternative 'G_SHL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner12,
        GIR_Done,
      // Label 73: @708
      GIM_Try, /*On fail goto*//*Label 74*/ 718, // Rule ID 26 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule15Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner13,
        // Combiner Rule #15: binop_right_undef_to_undef; wip_match_opcode alternative 'G_SHL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
        GIR_Done,
      // Label 74: @718
      GIM_Try, /*On fail goto*//*Label 75*/ 728, // Rule ID 47 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule24Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner20,
        // Combiner Rule #24: right_identity_zero; wip_match_opcode alternative 'G_SHL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 75: @728
      GIM_Try, /*On fail goto*//*Label 76*/ 738, // Rule ID 77 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule42Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner36,
        // Combiner Rule #42: shifts_too_big; wip_match_opcode alternative 'G_SHL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
        GIR_Done,
      // Label 76: @738
      GIM_Try, /*On fail goto*//*Label 77*/ 748, // Rule ID 133 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule85Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner74,
        // Combiner Rule #85: shift_immed_chain; wip_match_opcode alternative 'G_SHL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner47,
        GIR_Done,
      // Label 77: @748
      GIM_Try, /*On fail goto*//*Label 78*/ 758, // Rule ID 138 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule86Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner75,
        // Combiner Rule #86: shift_of_shifted_logic_chain; wip_match_opcode alternative 'G_SHL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner48,
        GIR_Done,
      // Label 78: @758
      GIM_Try, /*On fail goto*//*Label 79*/ 768, // Rule ID 151 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule91Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner80,
        // Combiner Rule #91: commute_shift; wip_match_opcode alternative 'G_SHL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 79: @768
      GIM_Try, /*On fail goto*//*Label 80*/ 778, // Rule ID 195 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_SHL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 80: @778
      GIM_Try, /*On fail goto*//*Label 81*/ 788, // Rule ID 85 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule48Enabled,
        // MIs[0] dst
        // No operand predicates
        // MIs[0] src0
        // No operand predicates
        // MIs[0] src1
        // No operand predicates
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner42,
        // Combiner Rule #48: reduce_shl_of_extend
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner29,
        GIR_Done,
      // Label 81: @788
      GIM_Reject,
    // Label 72: @789
    GIM_Try, /*On fail goto*//*Label 82*/ 845,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_UDIV,
      GIM_Try, /*On fail goto*//*Label 83*/ 804, // Rule ID 24 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule14Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner12,
        // Combiner Rule #14: binop_left_undef_to_zero; wip_match_opcode alternative 'G_UDIV'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner12,
        GIR_Done,
      // Label 83: @804
      GIM_Try, /*On fail goto*//*Label 84*/ 814, // Rule ID 56 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule26Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner22,
        // Combiner Rule #26: binop_left_to_zero; wip_match_opcode alternative 'G_UDIV'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 84: @814
      GIM_Try, /*On fail goto*//*Label 85*/ 824, // Rule ID 145 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule88Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner77,
        // Combiner Rule #88: div_rem_to_divrem; wip_match_opcode alternative 'G_UDIV'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner49,
        GIR_Done,
      // Label 85: @824
      GIM_Try, /*On fail goto*//*Label 86*/ 834, // Rule ID 165 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule98Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner87,
        // Combiner Rule #98: udiv_by_const; wip_match_opcode alternative 'G_UDIV'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner52,
        GIR_Done,
      // Label 86: @834
      GIM_Try, /*On fail goto*//*Label 87*/ 844, // Rule ID 191 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_UDIV'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 87: @844
      GIM_Reject,
    // Label 82: @845
    GIM_Try, /*On fail goto*//*Label 88*/ 901,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_UREM,
      GIM_Try, /*On fail goto*//*Label 89*/ 860, // Rule ID 25 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule14Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner12,
        // Combiner Rule #14: binop_left_undef_to_zero; wip_match_opcode alternative 'G_UREM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner12,
        GIR_Done,
      // Label 89: @860
      GIM_Try, /*On fail goto*//*Label 90*/ 870, // Rule ID 58 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule26Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner22,
        // Combiner Rule #26: binop_left_to_zero; wip_match_opcode alternative 'G_UREM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 90: @870
      GIM_Try, /*On fail goto*//*Label 91*/ 880, // Rule ID 93 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule56Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner50,
        // Combiner Rule #56: urem_pow2_to_mask; wip_match_opcode alternative 'G_UREM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner31,
        GIR_Done,
      // Label 91: @880
      GIM_Try, /*On fail goto*//*Label 92*/ 890, // Rule ID 147 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule88Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner77,
        // Combiner Rule #88: div_rem_to_divrem; wip_match_opcode alternative 'G_UREM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner49,
        GIR_Done,
      // Label 92: @890
      GIM_Try, /*On fail goto*//*Label 93*/ 900, // Rule ID 192 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_UREM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 93: @900
      GIM_Reject,
    // Label 88: @901
    GIM_Try, /*On fail goto*//*Label 94*/ 997,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ASHR,
      GIM_Try, /*On fail goto*//*Label 95*/ 916, // Rule ID 27 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule15Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner13,
        // Combiner Rule #15: binop_right_undef_to_undef; wip_match_opcode alternative 'G_ASHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
        GIR_Done,
      // Label 95: @916
      GIM_Try, /*On fail goto*//*Label 96*/ 926, // Rule ID 48 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule24Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner20,
        // Combiner Rule #24: right_identity_zero; wip_match_opcode alternative 'G_ASHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 96: @926
      GIM_Try, /*On fail goto*//*Label 97*/ 936, // Rule ID 78 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule42Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner36,
        // Combiner Rule #42: shifts_too_big; wip_match_opcode alternative 'G_ASHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
        GIR_Done,
      // Label 97: @936
      GIM_Try, /*On fail goto*//*Label 98*/ 946, // Rule ID 83 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule46Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner40,
        // Combiner Rule #46: shl_ashr_to_sext_inreg; wip_match_opcode alternative 'G_ASHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner27,
        GIR_Done,
      // Label 98: @946
      GIM_Try, /*On fail goto*//*Label 99*/ 956, // Rule ID 134 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule85Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner74,
        // Combiner Rule #85: shift_immed_chain; wip_match_opcode alternative 'G_ASHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner47,
        GIR_Done,
      // Label 99: @956
      GIM_Try, /*On fail goto*//*Label 100*/ 966, // Rule ID 139 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule86Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner75,
        // Combiner Rule #86: shift_of_shifted_logic_chain; wip_match_opcode alternative 'G_ASHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner48,
        GIR_Done,
      // Label 100: @966
      GIM_Try, /*On fail goto*//*Label 101*/ 976, // Rule ID 154 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule94Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner83,
        // Combiner Rule #94: bitfield_extract_from_shr; wip_match_opcode alternative 'G_ASHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 101: @976
      GIM_Try, /*On fail goto*//*Label 102*/ 986, // Rule ID 156 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule95Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner84,
        // Combiner Rule #95: bitfield_extract_from_shr_and; wip_match_opcode alternative 'G_ASHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 102: @986
      GIM_Try, /*On fail goto*//*Label 103*/ 996, // Rule ID 194 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_ASHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 103: @996
      GIM_Reject,
    // Label 94: @997
    GIM_Try, /*On fail goto*//*Label 104*/ 1083,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_LSHR,
      GIM_Try, /*On fail goto*//*Label 105*/ 1012, // Rule ID 28 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule15Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner13,
        // Combiner Rule #15: binop_right_undef_to_undef; wip_match_opcode alternative 'G_LSHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
        GIR_Done,
      // Label 105: @1012
      GIM_Try, /*On fail goto*//*Label 106*/ 1022, // Rule ID 49 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule24Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner20,
        // Combiner Rule #24: right_identity_zero; wip_match_opcode alternative 'G_LSHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 106: @1022
      GIM_Try, /*On fail goto*//*Label 107*/ 1032, // Rule ID 79 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule42Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner36,
        // Combiner Rule #42: shifts_too_big; wip_match_opcode alternative 'G_LSHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
        GIR_Done,
      // Label 107: @1032
      GIM_Try, /*On fail goto*//*Label 108*/ 1042, // Rule ID 135 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule85Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner74,
        // Combiner Rule #85: shift_immed_chain; wip_match_opcode alternative 'G_LSHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner47,
        GIR_Done,
      // Label 108: @1042
      GIM_Try, /*On fail goto*//*Label 109*/ 1052, // Rule ID 140 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule86Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner75,
        // Combiner Rule #86: shift_of_shifted_logic_chain; wip_match_opcode alternative 'G_LSHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner48,
        GIR_Done,
      // Label 109: @1052
      GIM_Try, /*On fail goto*//*Label 110*/ 1062, // Rule ID 155 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule94Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner83,
        // Combiner Rule #94: bitfield_extract_from_shr; wip_match_opcode alternative 'G_LSHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 110: @1062
      GIM_Try, /*On fail goto*//*Label 111*/ 1072, // Rule ID 157 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule95Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner84,
        // Combiner Rule #95: bitfield_extract_from_shr_and; wip_match_opcode alternative 'G_LSHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 111: @1072
      GIM_Try, /*On fail goto*//*Label 112*/ 1082, // Rule ID 193 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_LSHR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 112: @1082
      GIM_Reject,
    // Label 104: @1083
    GIM_Try, /*On fail goto*//*Label 113*/ 1096, // Rule ID 29 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule16Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ABS,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner12,
      // Combiner Rule #16: unary_undef_to_zero; wip_match_opcode alternative 'G_ABS'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner12,
      GIR_Done,
    // Label 113: @1096
    GIM_Try, /*On fail goto*//*Label 114*/ 1109, // Rule ID 31 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule17Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FPTOSI,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner11,
      // Combiner Rule #17: propagate_undef_any_op; wip_match_opcode alternative 'G_FPTOSI'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
      GIR_Done,
    // Label 114: @1109
    GIM_Try, /*On fail goto*//*Label 115*/ 1122, // Rule ID 32 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule17Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FPTOUI,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner11,
      // Combiner Rule #17: propagate_undef_any_op; wip_match_opcode alternative 'G_FPTOUI'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
      GIR_Done,
    // Label 115: @1122
    GIM_Try, /*On fail goto*//*Label 116*/ 1178,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SUB,
      GIM_Try, /*On fail goto*//*Label 117*/ 1137, // Rule ID 33 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule17Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner11,
        // Combiner Rule #17: propagate_undef_any_op; wip_match_opcode alternative 'G_SUB'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
        GIR_Done,
      // Label 117: @1137
      GIM_Try, /*On fail goto*//*Label 118*/ 1147, // Rule ID 43 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule24Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner20,
        // Combiner Rule #24: right_identity_zero; wip_match_opcode alternative 'G_SUB'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 118: @1147
      GIM_Try, /*On fail goto*//*Label 119*/ 1157, // Rule ID 159 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule96Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner85,
        // Combiner Rule #96: constant_fold; wip_match_opcode alternative 'G_SUB'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner51,
        GIR_Done,
      // Label 119: @1157
      GIM_Try, /*On fail goto*//*Label 120*/ 1167, // Rule ID 184 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_SUB'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 120: @1167
      GIM_Try, /*On fail goto*//*Label 121*/ 1177, // Rule ID 209 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule112Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner101,
        // Combiner Rule #112: sub_add_reg; wip_match_opcode alternative 'G_SUB'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 121: @1177
      GIM_Reject,
    // Label 116: @1178
    GIM_Try, /*On fail goto*//*Label 122*/ 1264,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_XOR,
      GIM_Try, /*On fail goto*//*Label 123*/ 1193, // Rule ID 34 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule17Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner11,
        // Combiner Rule #17: propagate_undef_any_op; wip_match_opcode alternative 'G_XOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
        GIR_Done,
      // Label 123: @1193
      GIM_Try, /*On fail goto*//*Label 124*/ 1203, // Rule ID 46 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule24Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner20,
        // Combiner Rule #24: right_identity_zero; wip_match_opcode alternative 'G_XOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 124: @1203
      GIM_Try, /*On fail goto*//*Label 125*/ 1213, // Rule ID 76 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule41Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner35,
        // Combiner Rule #41: hoist_logic_op_with_same_opcode_hands; wip_match_opcode alternative 'G_XOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner24,
        GIR_Done,
      // Label 125: @1213
      GIM_Try, /*On fail goto*//*Label 126*/ 1223, // Rule ID 101 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule62Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner56,
        // Combiner Rule #62: not_cmp_fold; wip_match_opcode alternative 'G_XOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner35,
        GIR_Done,
      // Label 126: @1223
      GIM_Try, /*On fail goto*//*Label 127*/ 1233, // Rule ID 131 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule83Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner72,
        // Combiner Rule #83: xor_of_and_with_same_reg; wip_match_opcode alternative 'G_XOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner45,
        GIR_Done,
      // Label 127: @1233
      GIM_Try, /*On fail goto*//*Label 128*/ 1243, // Rule ID 163 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule96Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner85,
        // Combiner Rule #96: constant_fold; wip_match_opcode alternative 'G_XOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner51,
        GIR_Done,
      // Label 128: @1243
      GIM_Try, /*On fail goto*//*Label 129*/ 1253, // Rule ID 188 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_XOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 129: @1253
      GIM_Try, /*On fail goto*//*Label 130*/ 1263, // Rule ID 217 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule116Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner105,
        // Combiner Rule #116: commute_constant_to_rhs; wip_match_opcode alternative 'G_XOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner57,
        GIR_Done,
      // Label 130: @1263
      GIM_Reject,
    // Label 122: @1264
    GIM_Try, /*On fail goto*//*Label 131*/ 1320,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_TRUNC,
      GIM_Try, /*On fail goto*//*Label 132*/ 1279, // Rule ID 35 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule17Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner11,
        // Combiner Rule #17: propagate_undef_any_op; wip_match_opcode alternative 'G_TRUNC'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
        GIR_Done,
      // Label 132: @1279
      GIM_Try, /*On fail goto*//*Label 133*/ 1289, // Rule ID 68 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule35Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner30,
        // Combiner Rule #35: trunc_buildvector_fold; wip_match_opcode alternative 'G_TRUNC'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner19,
        GIR_Done,
      // Label 133: @1289
      GIM_Try, /*On fail goto*//*Label 134*/ 1299, // Rule ID 69 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule36Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner31,
        // Combiner Rule #36: trunc_lshr_buildvector_fold; wip_match_opcode alternative 'G_TRUNC'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner19,
        GIR_Done,
      // Label 134: @1299
      GIM_Try, /*On fail goto*//*Label 135*/ 1309, // Rule ID 108 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule69Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner63,
        // Combiner Rule #69: trunc_ext_fold; wip_match_opcode alternative 'G_TRUNC'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner41,
        GIR_Done,
      // Label 135: @1309
      GIM_Try, /*On fail goto*//*Label 136*/ 1319, // Rule ID 109 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule70Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner64,
        // Combiner Rule #70: trunc_shift; wip_match_opcode alternative 'G_TRUNC'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner42,
        GIR_Done,
      // Label 136: @1319
      GIM_Reject,
    // Label 131: @1320
    GIM_Try, /*On fail goto*//*Label 137*/ 1346,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SHUFFLE_VECTOR,
      GIM_Try, /*On fail goto*//*Label 138*/ 1335, // Rule ID 36 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule18Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner14,
        // Combiner Rule #18: propagate_undef_all_ops; wip_match_opcode alternative 'G_SHUFFLE_VECTOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
        GIR_Done,
      // Label 138: @1335
      GIM_Try, /*On fail goto*//*Label 139*/ 1345, // Rule ID 37 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule19Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner15,
        // Combiner Rule #19: propagate_undef_shuffle_mask; wip_match_opcode alternative 'G_SHUFFLE_VECTOR'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner14,
        GIR_Done,
      // Label 139: @1345
      GIM_Reject,
    // Label 137: @1346
    GIM_Try, /*On fail goto*//*Label 140*/ 1402,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_UNMERGE_VALUES,
      GIM_Try, /*On fail goto*//*Label 141*/ 1361, // Rule ID 39 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule21Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner17,
        // Combiner Rule #21: unmerge_undef; wip_match_opcode alternative 'G_UNMERGE_VALUES'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 141: @1361
      GIM_Try, /*On fail goto*//*Label 142*/ 1371, // Rule ID 103 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule64Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner58,
        // Combiner Rule #64: unmerge_merge; wip_match_opcode alternative 'G_UNMERGE_VALUES'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner37,
        GIR_Done,
      // Label 142: @1371
      GIM_Try, /*On fail goto*//*Label 143*/ 1381, // Rule ID 104 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule65Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner59,
        // Combiner Rule #65: unmerge_cst; wip_match_opcode alternative 'G_UNMERGE_VALUES'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner38,
        GIR_Done,
      // Label 143: @1381
      GIM_Try, /*On fail goto*//*Label 144*/ 1391, // Rule ID 105 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule66Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner60,
        // Combiner Rule #66: unmerge_dead_to_trunc; wip_match_opcode alternative 'G_UNMERGE_VALUES'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner39,
        GIR_Done,
      // Label 144: @1391
      GIM_Try, /*On fail goto*//*Label 145*/ 1401, // Rule ID 106 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule67Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner61,
        // Combiner Rule #67: unmerge_zext_to_zext; wip_match_opcode alternative 'G_UNMERGE_VALUES'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner40,
        GIR_Done,
      // Label 145: @1401
      GIM_Reject,
    // Label 140: @1402
    GIM_Try, /*On fail goto*//*Label 146*/ 1458,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SELECT,
      GIM_Try, /*On fail goto*//*Label 147*/ 1417, // Rule ID 42 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule23Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner19,
        // Combiner Rule #23: select_same_val; wip_match_opcode alternative 'G_SELECT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner16,
        GIR_Done,
      // Label 147: @1417
      GIM_Try, /*On fail goto*//*Label 148*/ 1427, // Rule ID 87 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule50Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner44,
        // Combiner Rule #50: select_undef_cmp; wip_match_opcode alternative 'G_SELECT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner16,
        GIR_Done,
      // Label 148: @1427
      GIM_Try, /*On fail goto*//*Label 149*/ 1437, // Rule ID 88 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule51Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner45,
        // Combiner Rule #51: select_constant_cmp; wip_match_opcode alternative 'G_SELECT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner30,
        GIR_Done,
      // Label 149: @1437
      GIM_Try, /*On fail goto*//*Label 150*/ 1447, // Rule ID 89 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule52Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner46,
        // Combiner Rule #52: select_to_logical; wip_match_opcode alternative 'G_SELECT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 150: @1447
      GIM_Try, /*On fail goto*//*Label 151*/ 1457, // Rule ID 210 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule113Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner102,
        // Combiner Rule #113: select_to_minmax; wip_match_opcode alternative 'G_SELECT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 151: @1457
      GIM_Reject,
    // Label 146: @1458
    GIM_Try, /*On fail goto*//*Label 152*/ 1524,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_PTR_ADD,
      GIM_Try, /*On fail goto*//*Label 153*/ 1473, // Rule ID 50 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule24Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner20,
        // Combiner Rule #24: right_identity_zero; wip_match_opcode alternative 'G_PTR_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 153: @1473
      GIM_Try, /*On fail goto*//*Label 154*/ 1483, // Rule ID 80 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule43Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner37,
        // Combiner Rule #43: reassoc_ptradd; wip_match_opcode alternative 'G_PTR_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
        GIR_Done,
      // Label 154: @1483
      GIM_Try, /*On fail goto*//*Label 155*/ 1493, // Rule ID 82 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule45Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner39,
        // Combiner Rule #45: ptr_add_immed_chain; wip_match_opcode alternative 'G_PTR_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner26,
        GIR_Done,
      // Label 155: @1493
      GIM_Try, /*On fail goto*//*Label 156*/ 1503, // Rule ID 115 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule76Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner65,
        // Combiner Rule #76: const_ptradd_to_i2p; wip_match_opcode alternative 'G_PTR_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner44,
        GIR_Done,
      // Label 156: @1503
      GIM_Try, /*On fail goto*//*Label 157*/ 1513, // Rule ID 132 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule84Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner73,
        // Combiner Rule #84: ptr_add_with_zero; wip_match_opcode alternative 'G_PTR_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner46,
        GIR_Done,
      // Label 157: @1513
      GIM_Try, /*On fail goto*//*Label 158*/ 1523, // Rule ID 185 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_PTR_ADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 158: @1523
      GIM_Reject,
    // Label 152: @1524
    GIM_Try, /*On fail goto*//*Label 159*/ 1537, // Rule ID 51 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule24Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ROTL,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner20,
      // Combiner Rule #24: right_identity_zero; wip_match_opcode alternative 'G_ROTL'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
      GIR_Done,
    // Label 159: @1537
    GIM_Try, /*On fail goto*//*Label 160*/ 1550, // Rule ID 52 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule24Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ROTR,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner20,
      // Combiner Rule #24: right_identity_zero; wip_match_opcode alternative 'G_ROTR'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
      GIR_Done,
    // Label 160: @1550
    GIM_Try, /*On fail goto*//*Label 161*/ 1596,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SDIV,
      GIM_Try, /*On fail goto*//*Label 162*/ 1565, // Rule ID 55 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule26Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner22,
        // Combiner Rule #26: binop_left_to_zero; wip_match_opcode alternative 'G_SDIV'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 162: @1565
      GIM_Try, /*On fail goto*//*Label 163*/ 1575, // Rule ID 144 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule88Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner77,
        // Combiner Rule #88: div_rem_to_divrem; wip_match_opcode alternative 'G_SDIV'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner49,
        GIR_Done,
      // Label 163: @1575
      GIM_Try, /*On fail goto*//*Label 164*/ 1585, // Rule ID 166 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule99Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner88,
        // Combiner Rule #99: sdiv_by_const; wip_match_opcode alternative 'G_SDIV'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner53,
        GIR_Done,
      // Label 164: @1585
      GIM_Try, /*On fail goto*//*Label 165*/ 1595, // Rule ID 189 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_SDIV'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 165: @1595
      GIM_Reject,
    // Label 161: @1596
    GIM_Try, /*On fail goto*//*Label 166*/ 1632,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SREM,
      GIM_Try, /*On fail goto*//*Label 167*/ 1611, // Rule ID 57 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule26Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner22,
        // Combiner Rule #26: binop_left_to_zero; wip_match_opcode alternative 'G_SREM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 167: @1611
      GIM_Try, /*On fail goto*//*Label 168*/ 1621, // Rule ID 146 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule88Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner77,
        // Combiner Rule #88: div_rem_to_divrem; wip_match_opcode alternative 'G_SREM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner49,
        GIR_Done,
      // Label 168: @1621
      GIM_Try, /*On fail goto*//*Label 169*/ 1631, // Rule ID 190 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_SREM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 169: @1631
      GIM_Reject,
    // Label 166: @1632
    GIM_Try, /*On fail goto*//*Label 170*/ 1645, // Rule ID 60 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule28Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_INTTOPTR,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner24,
      // Combiner Rule #28: p2i_to_i2p; wip_match_opcode alternative 'G_INTTOPTR'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner17,
      GIR_Done,
    // Label 170: @1645
    GIM_Try, /*On fail goto*//*Label 171*/ 1667, // Rule ID 61 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule29Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_PTRTOINT,
      // MIs[0] dst
      // No operand predicates
      // MIs[0] t
      GIM_RecordInsn, /*DefineMI*/1, /*MI*/0, /*OpIdx*/1, // MIs[1]
      GIM_CheckOpcode, /*MI*/1, TargetOpcode::G_INTTOPTR,
      // MIs[1] ptr
      // No operand predicates
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner25,
      GIM_CheckIsSafeToFold, /*InsnID*/1,
      // Combiner Rule #29: i2p_to_p2i
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner18,
      GIR_Done,
    // Label 171: @1667
    GIM_Try, /*On fail goto*//*Label 172*/ 1693,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ANYEXT,
      GIM_Try, /*On fail goto*//*Label 173*/ 1682, // Rule ID 62 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule30Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner26,
        // Combiner Rule #30: anyext_trunc_fold; wip_match_opcode alternative 'G_ANYEXT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner19,
        GIR_Done,
      // Label 173: @1682
      GIM_Try, /*On fail goto*//*Label 174*/ 1692, // Rule ID 98 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule61Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner55,
        // Combiner Rule #61: ext_ext_fold; wip_match_opcode alternative 'G_ANYEXT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner34,
        GIR_Done,
      // Label 174: @1692
      GIM_Reject,
    // Label 172: @1693
    GIM_Try, /*On fail goto*//*Label 175*/ 1734,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FNEG,
      GIM_Try, /*On fail goto*//*Label 176*/ 1717, // Rule ID 63 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule31Enabled,
        // MIs[0] dst
        // No operand predicates
        // MIs[0] t
        GIM_RecordInsn, /*DefineMI*/1, /*MI*/0, /*OpIdx*/1, // MIs[1]
        GIM_CheckOpcode, /*MI*/1, TargetOpcode::G_FNEG,
        // MIs[1] src
        // No operand predicates
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner25,
        GIM_CheckIsSafeToFold, /*InsnID*/1,
        // Combiner Rule #31: fneg_fneg_fold
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner19,
        GIR_Done,
      // Label 176: @1717
      GIM_Try, /*On fail goto*//*Label 177*/ 1733, // Rule ID 110 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule71Enabled,
        // MIs[0] dst
        // No operand predicates
        // MIs[0] src0
        GIM_RecordInsn, /*DefineMI*/1, /*MI*/0, /*OpIdx*/1, // MIs[1]
        GIM_CheckOpcode, /*MI*/1, TargetOpcode::G_FCONSTANT,
        // MIs[1] cst
        // No operand predicates
        GIM_CheckIsSafeToFold, /*InsnID*/1,
        // Combiner Rule #71: constant_fold_fneg
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner43,
        GIR_Done,
      // Label 177: @1733
      GIM_Reject,
    // Label 175: @1734
    GIM_Try, /*On fail goto*//*Label 178*/ 1747, // Rule ID 66 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule34Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_BUILD_VECTOR_TRUNC,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner29,
      // Combiner Rule #34: buildvector_identity_fold; wip_match_opcode alternative 'G_BUILD_VECTOR_TRUNC'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner19,
      GIR_Done,
    // Label 178: @1747
    GIM_Try, /*On fail goto*//*Label 179*/ 1769, // Rule ID 70 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule37Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_BITCAST,
      // MIs[0] dst
      // No operand predicates
      // MIs[0] src1
      GIM_RecordInsn, /*DefineMI*/1, /*MI*/0, /*OpIdx*/1, // MIs[1]
      GIM_CheckOpcode, /*MI*/1, TargetOpcode::G_BITCAST,
      // MIs[1] src0
      // No operand predicates
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner32,
      GIM_CheckIsSafeToFold, /*InsnID*/1,
      // Combiner Rule #37: bitcast_bitcast_fold
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner21,
      GIR_Done,
    // Label 179: @1769
    GIM_Try, /*On fail goto*//*Label 180*/ 1810,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FPTRUNC,
      GIM_Try, /*On fail goto*//*Label 181*/ 1793, // Rule ID 71 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule38Enabled,
        // MIs[0] dst
        // No operand predicates
        // MIs[0] src1
        GIM_RecordInsn, /*DefineMI*/1, /*MI*/0, /*OpIdx*/1, // MIs[1]
        GIM_CheckOpcode, /*MI*/1, TargetOpcode::G_FPEXT,
        // MIs[1] src0
        // No operand predicates
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner32,
        GIM_CheckIsSafeToFold, /*InsnID*/1,
        // Combiner Rule #38: fptrunc_fpext_fold
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner21,
        GIR_Done,
      // Label 181: @1793
      GIM_Try, /*On fail goto*//*Label 182*/ 1809, // Rule ID 114 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule75Enabled,
        // MIs[0] dst
        // No operand predicates
        // MIs[0] src0
        GIM_RecordInsn, /*DefineMI*/1, /*MI*/0, /*OpIdx*/1, // MIs[1]
        GIM_CheckOpcode, /*MI*/1, TargetOpcode::G_FCONSTANT,
        // MIs[1] cst
        // No operand predicates
        GIM_CheckIsSafeToFold, /*InsnID*/1,
        // Combiner Rule #75: constant_fold_fptrunc
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner43,
        GIR_Done,
      // Label 182: @1809
      GIM_Reject,
    // Label 180: @1810
    GIM_Try, /*On fail goto*//*Label 183*/ 1823, // Rule ID 72 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule39Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_PHI,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner33,
      // Combiner Rule #39: extend_through_phis; wip_match_opcode alternative 'G_PHI'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner22,
      GIR_Done,
    // Label 183: @1823
    GIM_Try, /*On fail goto*//*Label 184*/ 1869,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SEXT_INREG,
      GIM_Try, /*On fail goto*//*Label 185*/ 1838, // Rule ID 84 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule47Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner41,
        // Combiner Rule #47: sext_inreg_of_load; wip_match_opcode alternative 'G_SEXT_INREG'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner28,
        GIR_Done,
      // Label 185: @1838
      GIM_Try, /*On fail goto*//*Label 186*/ 1848, // Rule ID 91 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule54Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner48,
        // Combiner Rule #54: redundant_sext_inreg; wip_match_opcode alternative 'G_SEXT_INREG'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner4,
        GIR_Done,
      // Label 186: @1848
      GIM_Try, /*On fail goto*//*Label 187*/ 1858, // Rule ID 152 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule92Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner81,
        // Combiner Rule #92: bitfield_extract_from_sext_inreg; wip_match_opcode alternative 'G_SEXT_INREG'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 187: @1858
      GIM_Try, /*On fail goto*//*Label 188*/ 1868, // Rule ID 97 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule60Enabled,
        // MIs[0] dst
        // No operand predicates
        // MIs[0] src
        // No operand predicates
        // MIs[0] imm
        // No operand predicates
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner54,
        // Combiner Rule #60: sext_inreg_to_zext_inreg
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner33,
        GIR_Done,
      // Label 188: @1868
      GIM_Reject,
    // Label 184: @1869
    GIM_Try, /*On fail goto*//*Label 189*/ 1895,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ZEXT,
      GIM_Try, /*On fail goto*//*Label 190*/ 1884, // Rule ID 94 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule57Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner51,
        // Combiner Rule #57: zext_trunc_fold; wip_match_opcode alternative 'G_ZEXT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner19,
        GIR_Done,
      // Label 190: @1884
      GIM_Try, /*On fail goto*//*Label 191*/ 1894, // Rule ID 100 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule61Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner55,
        // Combiner Rule #61: ext_ext_fold; wip_match_opcode alternative 'G_ZEXT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner34,
        GIR_Done,
      // Label 191: @1894
      GIM_Reject,
    // Label 189: @1895
    GIM_Try, /*On fail goto*//*Label 192*/ 1941,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_ICMP,
      GIM_Try, /*On fail goto*//*Label 193*/ 1910, // Rule ID 95 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule58Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner52,
        // Combiner Rule #58: icmp_to_true_false_known_bits; wip_match_opcode alternative 'G_ICMP'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner32,
        GIR_Done,
      // Label 193: @1910
      GIM_Try, /*On fail goto*//*Label 194*/ 1920, // Rule ID 96 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule59Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner53,
        // Combiner Rule #59: icmp_to_lhs_known_bits; wip_match_opcode alternative 'G_ICMP'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 194: @1920
      GIM_Try, /*On fail goto*//*Label 195*/ 1930, // Rule ID 211 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule114Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner103,
        // Combiner Rule #114: redundant_binop_in_equality; wip_match_opcode alternative 'G_ICMP'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 195: @1930
      GIM_Try, /*On fail goto*//*Label 196*/ 1940, // Rule ID 219 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule118Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner107,
        // Combiner Rule #118: icmp_redundant_trunc; wip_match_opcode alternative 'G_ICMP'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner59,
        GIR_Done,
      // Label 196: @1940
      GIM_Reject,
    // Label 192: @1941
    GIM_Try, /*On fail goto*//*Label 197*/ 1954, // Rule ID 99 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule61Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SEXT,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner55,
      // Combiner Rule #61: ext_ext_fold; wip_match_opcode alternative 'G_SEXT'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner34,
      GIR_Done,
    // Label 197: @1954
    GIM_Try, /*On fail goto*//*Label 198*/ 1967, // Rule ID 102 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule63Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_BR,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner57,
      // Combiner Rule #63: opt_brcond_by_inverting_cond; wip_match_opcode alternative 'G_BR'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner36,
      GIR_Done,
    // Label 198: @1967
    GIM_Try, /*On fail goto*//*Label 199*/ 1980, // Rule ID 107 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule68Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_MERGE_VALUES,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner62,
      // Combiner Rule #68: merge_unmerge; wip_match_opcode alternative 'G_MERGE_VALUES'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner19,
      GIR_Done,
    // Label 199: @1980
    GIM_Try, /*On fail goto*//*Label 200*/ 1999, // Rule ID 112 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule73Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FSQRT,
      // MIs[0] dst
      // No operand predicates
      // MIs[0] src0
      GIM_RecordInsn, /*DefineMI*/1, /*MI*/0, /*OpIdx*/1, // MIs[1]
      GIM_CheckOpcode, /*MI*/1, TargetOpcode::G_FCONSTANT,
      // MIs[1] cst
      // No operand predicates
      GIM_CheckIsSafeToFold, /*InsnID*/1,
      // Combiner Rule #73: constant_fold_fsqrt
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner43,
      GIR_Done,
    // Label 200: @1999
    GIM_Try, /*On fail goto*//*Label 201*/ 2018, // Rule ID 113 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule74Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FLOG2,
      // MIs[0] dst
      // No operand predicates
      // MIs[0] src0
      GIM_RecordInsn, /*DefineMI*/1, /*MI*/0, /*OpIdx*/1, // MIs[1]
      GIM_CheckOpcode, /*MI*/1, TargetOpcode::G_FCONSTANT,
      // MIs[1] cst
      // No operand predicates
      GIM_CheckIsSafeToFold, /*InsnID*/1,
      // Combiner Rule #74: constant_fold_flog2
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner43,
      GIR_Done,
    // Label 201: @2018
    GIM_Try, /*On fail goto*//*Label 202*/ 2044,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_UMULO,
      GIM_Try, /*On fail goto*//*Label 203*/ 2033, // Rule ID 117 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule78Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner67,
        // Combiner Rule #78: mulo_by_2; wip_match_opcode alternative 'G_UMULO'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
        GIR_Done,
      // Label 203: @2033
      GIM_Try, /*On fail goto*//*Label 204*/ 2043, // Rule ID 119 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule79Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner68,
        // Combiner Rule #79: mulo_by_0; wip_match_opcode alternative 'G_UMULO'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 204: @2043
      GIM_Reject,
    // Label 202: @2044
    GIM_Try, /*On fail goto*//*Label 205*/ 2070,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SMULO,
      GIM_Try, /*On fail goto*//*Label 206*/ 2059, // Rule ID 118 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule78Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner67,
        // Combiner Rule #78: mulo_by_2; wip_match_opcode alternative 'G_SMULO'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
        GIR_Done,
      // Label 206: @2059
      GIM_Try, /*On fail goto*//*Label 207*/ 2069, // Rule ID 120 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule79Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner68,
        // Combiner Rule #79: mulo_by_0; wip_match_opcode alternative 'G_SMULO'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 207: @2069
      GIM_Reject,
    // Label 205: @2070
    GIM_Try, /*On fail goto*//*Label 208*/ 2083, // Rule ID 121 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule80Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_UADDO,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner69,
      // Combiner Rule #80: addo_by_0; wip_match_opcode alternative 'G_UADDO'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
      GIR_Done,
    // Label 208: @2083
    GIM_Try, /*On fail goto*//*Label 209*/ 2096, // Rule ID 122 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule80Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SADDO,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner69,
      // Combiner Rule #80: addo_by_0; wip_match_opcode alternative 'G_SADDO'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
      GIR_Done,
    // Label 209: @2096
    GIM_Try, /*On fail goto*//*Label 210*/ 2109, // Rule ID 123 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule81Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_UADDE,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner70,
      // Combiner Rule #81: adde_to_addo; wip_match_opcode alternative 'G_UADDE'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
      GIR_Done,
    // Label 210: @2109
    GIM_Try, /*On fail goto*//*Label 211*/ 2122, // Rule ID 124 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule81Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SADDE,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner70,
      // Combiner Rule #81: adde_to_addo; wip_match_opcode alternative 'G_SADDE'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
      GIR_Done,
    // Label 211: @2122
    GIM_Try, /*On fail goto*//*Label 212*/ 2135, // Rule ID 125 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule81Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_USUBE,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner70,
      // Combiner Rule #81: adde_to_addo; wip_match_opcode alternative 'G_USUBE'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
      GIR_Done,
    // Label 212: @2135
    GIM_Try, /*On fail goto*//*Label 213*/ 2148, // Rule ID 126 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule81Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SSUBE,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner70,
      // Combiner Rule #81: adde_to_addo; wip_match_opcode alternative 'G_SSUBE'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
      GIR_Done,
    // Label 213: @2148
    GIM_Try, /*On fail goto*//*Label 214*/ 2174,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FMINNUM,
      GIM_Try, /*On fail goto*//*Label 215*/ 2163, // Rule ID 127 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule82Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner71,
        // Combiner Rule #82: combine_minmax_nan; wip_match_opcode alternative 'G_FMINNUM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner30,
        GIR_Done,
      // Label 215: @2163
      GIM_Try, /*On fail goto*//*Label 216*/ 2173, // Rule ID 205 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_FMINNUM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 216: @2173
      GIM_Reject,
    // Label 214: @2174
    GIM_Try, /*On fail goto*//*Label 217*/ 2200,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FMAXNUM,
      GIM_Try, /*On fail goto*//*Label 218*/ 2189, // Rule ID 128 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule82Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner71,
        // Combiner Rule #82: combine_minmax_nan; wip_match_opcode alternative 'G_FMAXNUM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner30,
        GIR_Done,
      // Label 218: @2189
      GIM_Try, /*On fail goto*//*Label 219*/ 2199, // Rule ID 206 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_FMAXNUM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 219: @2199
      GIM_Reject,
    // Label 217: @2200
    GIM_Try, /*On fail goto*//*Label 220*/ 2226,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FMINIMUM,
      GIM_Try, /*On fail goto*//*Label 221*/ 2215, // Rule ID 129 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule82Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner71,
        // Combiner Rule #82: combine_minmax_nan; wip_match_opcode alternative 'G_FMINIMUM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner30,
        GIR_Done,
      // Label 221: @2215
      GIM_Try, /*On fail goto*//*Label 222*/ 2225, // Rule ID 207 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_FMINIMUM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 222: @2225
      GIM_Reject,
    // Label 220: @2226
    GIM_Try, /*On fail goto*//*Label 223*/ 2252,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FMAXIMUM,
      GIM_Try, /*On fail goto*//*Label 224*/ 2241, // Rule ID 130 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule82Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner71,
        // Combiner Rule #82: combine_minmax_nan; wip_match_opcode alternative 'G_FMAXIMUM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner30,
        GIR_Done,
      // Label 224: @2241
      GIM_Try, /*On fail goto*//*Label 225*/ 2251, // Rule ID 208 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_FMAXIMUM'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 225: @2251
      GIM_Reject,
    // Label 223: @2252
    GIM_Try, /*On fail goto*//*Label 226*/ 2278,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SSHLSAT,
      GIM_Try, /*On fail goto*//*Label 227*/ 2267, // Rule ID 136 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule85Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner74,
        // Combiner Rule #85: shift_immed_chain; wip_match_opcode alternative 'G_SSHLSAT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner47,
        GIR_Done,
      // Label 227: @2267
      GIM_Try, /*On fail goto*//*Label 228*/ 2277, // Rule ID 142 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule86Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner75,
        // Combiner Rule #86: shift_of_shifted_logic_chain; wip_match_opcode alternative 'G_SSHLSAT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner48,
        GIR_Done,
      // Label 228: @2277
      GIM_Reject,
    // Label 226: @2278
    GIM_Try, /*On fail goto*//*Label 229*/ 2304,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_USHLSAT,
      GIM_Try, /*On fail goto*//*Label 230*/ 2293, // Rule ID 137 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule85Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner74,
        // Combiner Rule #85: shift_immed_chain; wip_match_opcode alternative 'G_USHLSAT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner47,
        GIR_Done,
      // Label 230: @2293
      GIM_Try, /*On fail goto*//*Label 231*/ 2303, // Rule ID 141 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule86Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner75,
        // Combiner Rule #86: shift_of_shifted_logic_chain; wip_match_opcode alternative 'G_USHLSAT'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner48,
        GIR_Done,
      // Label 231: @2303
      GIM_Reject,
    // Label 229: @2304
    GIM_Try, /*On fail goto*//*Label 232*/ 2317, // Rule ID 149 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule90Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FSHL,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner79,
      // Combiner Rule #90: funnel_shift_to_rotate; wip_match_opcode alternative 'G_FSHL'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner50,
      GIR_Done,
    // Label 232: @2317
    GIM_Try, /*On fail goto*//*Label 233*/ 2330, // Rule ID 150 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule90Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FSHR,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner79,
      // Combiner Rule #90: funnel_shift_to_rotate; wip_match_opcode alternative 'G_FSHR'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner50,
      GIR_Done,
    // Label 233: @2330
    GIM_Try, /*On fail goto*//*Label 234*/ 2343, // Rule ID 167 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule100Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_UMULH,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner89,
      // Combiner Rule #100: mulh_to_lshr; wip_match_opcode alternative 'G_UMULH'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner54,
      GIR_Done,
    // Label 234: @2343
    GIM_Try, /*On fail goto*//*Label 235*/ 2409,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FADD,
      GIM_Try, /*On fail goto*//*Label 236*/ 2358, // Rule ID 168 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule101Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner90,
        // Combiner Rule #101: redundant_neg_operands; wip_match_opcode alternative 'G_FADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
        GIR_Done,
      // Label 236: @2358
      GIM_Try, /*On fail goto*//*Label 237*/ 2368, // Rule ID 175 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule103Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner92,
        // Combiner Rule #103: combine_fadd_fmul_to_fmad_or_fma; wip_match_opcode alternative 'G_FADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 237: @2368
      GIM_Try, /*On fail goto*//*Label 238*/ 2378, // Rule ID 176 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule104Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner93,
        // Combiner Rule #104: combine_fadd_fpext_fmul_to_fmad_or_fma; wip_match_opcode alternative 'G_FADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 238: @2378
      GIM_Try, /*On fail goto*//*Label 239*/ 2388, // Rule ID 177 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule105Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner94,
        // Combiner Rule #105: combine_fadd_fma_fmul_to_fmad_or_fma; wip_match_opcode alternative 'G_FADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 239: @2388
      GIM_Try, /*On fail goto*//*Label 240*/ 2398, // Rule ID 178 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule106Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner95,
        // Combiner Rule #106: combine_fadd_fpext_fma_fmul_to_fmad_or_fma; wip_match_opcode alternative 'G_FADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 240: @2398
      GIM_Try, /*On fail goto*//*Label 241*/ 2408, // Rule ID 201 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_FADD'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 241: @2408
      GIM_Reject,
    // Label 235: @2409
    GIM_Try, /*On fail goto*//*Label 242*/ 2485,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FSUB,
      GIM_Try, /*On fail goto*//*Label 243*/ 2424, // Rule ID 169 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule101Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner90,
        // Combiner Rule #101: redundant_neg_operands; wip_match_opcode alternative 'G_FSUB'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
        GIR_Done,
      // Label 243: @2424
      GIM_Try, /*On fail goto*//*Label 244*/ 2434, // Rule ID 179 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule107Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner96,
        // Combiner Rule #107: combine_fsub_fmul_to_fmad_or_fma; wip_match_opcode alternative 'G_FSUB'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 244: @2434
      GIM_Try, /*On fail goto*//*Label 245*/ 2444, // Rule ID 180 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule108Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner97,
        // Combiner Rule #108: combine_fsub_fneg_fmul_to_fmad_or_fma; wip_match_opcode alternative 'G_FSUB'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 245: @2444
      GIM_Try, /*On fail goto*//*Label 246*/ 2454, // Rule ID 181 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule109Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner98,
        // Combiner Rule #109: combine_fsub_fpext_fmul_to_fmad_or_fma; wip_match_opcode alternative 'G_FSUB'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 246: @2454
      GIM_Try, /*On fail goto*//*Label 247*/ 2464, // Rule ID 182 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule110Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner99,
        // Combiner Rule #110: combine_fsub_fpext_fneg_fmul_to_fmad_or_fma; wip_match_opcode alternative 'G_FSUB'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner9,
        GIR_Done,
      // Label 247: @2464
      GIM_Try, /*On fail goto*//*Label 248*/ 2474, // Rule ID 202 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_FSUB'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 248: @2474
      GIM_Try, /*On fail goto*//*Label 249*/ 2484, // Rule ID 212 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule115Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner104,
        // Combiner Rule #115: fsub_to_fneg; wip_match_opcode alternative 'G_FSUB'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner56,
        GIR_Done,
      // Label 249: @2484
      GIM_Reject,
    // Label 242: @2485
    GIM_Try, /*On fail goto*//*Label 250*/ 2511,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FMUL,
      GIM_Try, /*On fail goto*//*Label 251*/ 2500, // Rule ID 170 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule101Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner90,
        // Combiner Rule #101: redundant_neg_operands; wip_match_opcode alternative 'G_FMUL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
        GIR_Done,
      // Label 251: @2500
      GIM_Try, /*On fail goto*//*Label 252*/ 2510, // Rule ID 200 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_FMUL'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 252: @2510
      GIM_Reject,
    // Label 250: @2511
    GIM_Try, /*On fail goto*//*Label 253*/ 2537,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FDIV,
      GIM_Try, /*On fail goto*//*Label 254*/ 2526, // Rule ID 171 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule101Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner90,
        // Combiner Rule #101: redundant_neg_operands; wip_match_opcode alternative 'G_FDIV'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
        GIR_Done,
      // Label 254: @2526
      GIM_Try, /*On fail goto*//*Label 255*/ 2536, // Rule ID 203 //
        GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
        GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
        // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_FDIV'
        GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
        GIR_Done,
      // Label 255: @2536
      GIM_Reject,
    // Label 253: @2537
    GIM_Try, /*On fail goto*//*Label 256*/ 2550, // Rule ID 172 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule101Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FMAD,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner90,
      // Combiner Rule #101: redundant_neg_operands; wip_match_opcode alternative 'G_FMAD'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
      GIR_Done,
    // Label 256: @2550
    GIM_Try, /*On fail goto*//*Label 257*/ 2563, // Rule ID 173 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule101Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FMA,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner90,
      // Combiner Rule #101: redundant_neg_operands; wip_match_opcode alternative 'G_FMA'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner25,
      GIR_Done,
    // Label 257: @2563
    GIM_Try, /*On fail goto*//*Label 258*/ 2576, // Rule ID 196 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SMIN,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
      // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_SMIN'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
      GIR_Done,
    // Label 258: @2576
    GIM_Try, /*On fail goto*//*Label 259*/ 2589, // Rule ID 197 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_SMAX,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
      // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_SMAX'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
      GIR_Done,
    // Label 259: @2589
    GIM_Try, /*On fail goto*//*Label 260*/ 2602, // Rule ID 198 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_UMIN,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
      // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_UMIN'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
      GIR_Done,
    // Label 260: @2602
    GIM_Try, /*On fail goto*//*Label 261*/ 2615, // Rule ID 199 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_UMAX,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
      // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_UMAX'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
      GIR_Done,
    // Label 261: @2615
    GIM_Try, /*On fail goto*//*Label 262*/ 2628, // Rule ID 204 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule111Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FREM,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner100,
      // Combiner Rule #111: fold_binop_into_select; wip_match_opcode alternative 'G_FREM'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner55,
      GIR_Done,
    // Label 262: @2628
    GIM_Try, /*On fail goto*//*Label 263*/ 2641, // Rule ID 218 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule117Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_FCONSTANT,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner106,
      // Combiner Rule #117: fconstant_to_constant; wip_match_opcode alternative 'G_FCONSTANT'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner58,
      GIR_Done,
    // Label 263: @2641
    GIM_Try, /*On fail goto*//*Label 264*/ 2654, // Rule ID 220 //
      GIM_CheckSimplePredicate, GICXXPred_Simple_IsRule119Enabled,
      GIM_CheckOpcode, /*MI*/0, TargetOpcode::G_GLOBAL_VALUE,
      GIM_CheckCxxInsnPredicate, /*MI*/0, /*FnId*/GICXXPred_MI_Predicate_GICombiner108,
      // Combiner Rule #119: fold_global_offset; wip_match_opcode alternative 'G_GLOBAL_VALUE'
      GIR_CustomAction, GICXXCustomAction_CombineApplyGICombiner60,
      GIR_Done,
    // Label 264: @2654
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

