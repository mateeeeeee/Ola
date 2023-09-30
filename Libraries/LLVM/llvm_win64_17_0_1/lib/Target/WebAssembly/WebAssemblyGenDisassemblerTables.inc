/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|*  * WebAssembly Disassembler                                                *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#include "MCTargetDesc/WebAssemblyMCTargetDesc.h"

namespace llvm {

static constexpr int WebAssemblyInstructionTableSize = 256;

enum EntryType : uint8_t { ET_Unused, ET_Prefix, ET_Instruction };

struct WebAssemblyInstruction {
  uint16_t Opcode;
  EntryType ET;
  uint8_t NumOperands;
  uint16_t OperandStart;
};

WebAssemblyInstruction InstructionTable0[] = {
  // 0x0: unreachable
  { 1665, ET_Instruction, 0, 0  },
  // 0x1: nop
  { 1373, ET_Instruction, 0, 0  },
  // 0x2: block   	$sig
  { 627, ET_Instruction, 1, 0  },
  // 0x3: loop    	$sig
  { 1211, ET_Instruction, 1, 0  },
  // 0x4: if    	$sig
  { 1005, ET_Instruction, 1, 0  },
  // 0x5: else
  { 737, ET_Instruction, 0, 0  },
  // 0x6: try     	$sig
  { 1663, ET_Instruction, 1, 0  },
  // 0x7: catch   	$tag
  { 645, ET_Instruction, 1, 1  },
  // 0x8: throw   	$tag
  { 1653, ET_Instruction, 1, 1  },
  // 0x9: rethrow 	$depth
  { 1437, ET_Instruction, 1, 2  },
  { 0, ET_Unused, 0, 0  },
  // 0xb: end
  { 747, ET_Instruction, 0, 0  },
  // 0xc: br      	$dst
  { 631, ET_Instruction, 1, 3  },
  // 0xd: br_if   	$dst
  { 630, ET_Instruction, 1, 3  },
  // 0xe: br_table 	$brl
  { 633, ET_Instruction, 1, 4  },
  // 0xf: return
  { 1439, ET_Instruction, 0, 0  },
  // 0x10: call	$callee
  { 641, ET_Instruction, 1, 5  },
  // 0x11: call_indirect	$type, $table
  { 640, ET_Instruction, 2, 6  },
  // 0x12: return_call	$callee
  { 1443, ET_Instruction, 1, 5  },
  // 0x13: return_call_indirect	$type, $table
  { 1442, ET_Instruction, 2, 6  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0x18: delegate 	 $dst
  { 703, ET_Instruction, 1, 3  },
  // 0x19: catch_all
  { 644, ET_Instruction, 0, 0  },
  // 0x1a: drop
  { 723, ET_Instruction, 0, 0  },
  // 0x1b: f32.select
  { 1455, ET_Instruction, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0x20: local.get	$local
  { 1169, ET_Instruction, 1, 8  },
  // 0x21: local.set	$local
  { 1183, ET_Instruction, 1, 8  },
  // 0x22: local.tee	$local
  { 1197, ET_Instruction, 1, 8  },
  // 0x23: global.get	$addr
  { 895, ET_Instruction, 1, 9  },
  // 0x24: global.set	$addr
  { 909, ET_Instruction, 1, 9  },
  // 0x25: table.get	$table
  { 1625, ET_Instruction, 1, 7  },
  // 0x26: table.set	$table
  { 1633, ET_Instruction, 1, 7  },
  { 0, ET_Unused, 0, 0  },
  // 0x28: i32.load	${off}${p2align}
  { 1133, ET_Instruction, 2, 10  },
  // 0x29: i64.load	${off}${p2align}
  { 1137, ET_Instruction, 2, 10  },
  // 0x2a: f32.load	${off}${p2align}
  { 1125, ET_Instruction, 2, 10  },
  // 0x2b: f64.load	${off}${p2align}
  { 1129, ET_Instruction, 2, 10  },
  // 0x2c: i32.load8_s	${off}${p2align}
  { 1085, ET_Instruction, 2, 10  },
  // 0x2d: i32.load8_u	${off}${p2align}
  { 1093, ET_Instruction, 2, 10  },
  // 0x2e: i32.load16_s	${off}${p2align}
  { 1049, ET_Instruction, 2, 10  },
  // 0x2f: i32.load16_u	${off}${p2align}
  { 1057, ET_Instruction, 2, 10  },
  // 0x30: i64.load8_s	${off}${p2align}
  { 1089, ET_Instruction, 2, 10  },
  // 0x31: i64.load8_u	${off}${p2align}
  { 1097, ET_Instruction, 2, 10  },
  // 0x32: i64.load16_s	${off}${p2align}
  { 1053, ET_Instruction, 2, 10  },
  // 0x33: i64.load16_u	${off}${p2align}
  { 1061, ET_Instruction, 2, 10  },
  // 0x34: i64.load32_s	${off}${p2align}
  { 1069, ET_Instruction, 2, 10  },
  // 0x35: i64.load32_u	${off}${p2align}
  { 1073, ET_Instruction, 2, 10  },
  // 0x36: i32.store	${off}${p2align}
  { 1561, ET_Instruction, 2, 10  },
  // 0x37: i64.store	${off}${p2align}
  { 1565, ET_Instruction, 2, 10  },
  // 0x38: f32.store	${off}${p2align}
  { 1553, ET_Instruction, 2, 10  },
  // 0x39: f64.store	${off}${p2align}
  { 1557, ET_Instruction, 2, 10  },
  // 0x3a: i32.store8	${off}${p2align}
  { 1545, ET_Instruction, 2, 10  },
  // 0x3b: i32.store16	${off}${p2align}
  { 1533, ET_Instruction, 2, 10  },
  // 0x3c: i64.store8	${off}${p2align}
  { 1549, ET_Instruction, 2, 10  },
  // 0x3d: i64.store16	${off}${p2align}
  { 1537, ET_Instruction, 2, 10  },
  // 0x3e: i64.store32	${off}${p2align}
  { 1541, ET_Instruction, 2, 10  },
  // 0x3f: memory.size	$flags
  { 1675, ET_Instruction, 1, 2  },
  // 0x40: memory.grow	$flags
  { 1673, ET_Instruction, 1, 2  },
  // 0x41: i32.const	$imm
  { 663, ET_Instruction, 1, 12  },
  // 0x42: i64.const	$imm
  { 665, ET_Instruction, 1, 13  },
  // 0x43: f32.const	$imm
  { 659, ET_Instruction, 1, 14  },
  // 0x44: f64.const	$imm
  { 661, ET_Instruction, 1, 15  },
  // 0x45: i32.eqz
  { 751, ET_Instruction, 0, 0  },
  // 0x46: i32.eq  
  { 765, ET_Instruction, 0, 0  },
  // 0x47: i32.ne  
  { 1359, ET_Instruction, 0, 0  },
  // 0x48: i32.lt_s
  { 1223, ET_Instruction, 0, 0  },
  // 0x49: i32.lt_u
  { 1235, ET_Instruction, 0, 0  },
  // 0x4a: i32.gt_s
  { 933, ET_Instruction, 0, 0  },
  // 0x4b: i32.gt_u
  { 945, ET_Instruction, 0, 0  },
  // 0x4c: i32.le_s
  { 1025, ET_Instruction, 0, 0  },
  // 0x4d: i32.le_u
  { 1037, ET_Instruction, 0, 0  },
  // 0x4e: i32.ge_s
  { 875, ET_Instruction, 0, 0  },
  // 0x4f: i32.ge_u
  { 887, ET_Instruction, 0, 0  },
  // 0x50: i64.eqz
  { 753, ET_Instruction, 0, 0  },
  // 0x51: i64.eq  
  { 769, ET_Instruction, 0, 0  },
  // 0x52: i64.ne  
  { 1363, ET_Instruction, 0, 0  },
  // 0x53: i64.lt_s
  { 1227, ET_Instruction, 0, 0  },
  // 0x54: i64.lt_u
  { 1239, ET_Instruction, 0, 0  },
  // 0x55: i64.gt_s
  { 937, ET_Instruction, 0, 0  },
  // 0x56: i64.gt_u
  { 949, ET_Instruction, 0, 0  },
  // 0x57: i64.le_s
  { 1029, ET_Instruction, 0, 0  },
  // 0x58: i64.le_u
  { 1041, ET_Instruction, 0, 0  },
  // 0x59: i64.ge_s
  { 879, ET_Instruction, 0, 0  },
  // 0x5a: i64.ge_u
  { 891, ET_Instruction, 0, 0  },
  // 0x5b: f32.eq  
  { 755, ET_Instruction, 0, 0  },
  // 0x5c: f32.ne  
  { 1349, ET_Instruction, 0, 0  },
  // 0x5d: f32.lt  
  { 1213, ET_Instruction, 0, 0  },
  // 0x5e: f32.gt  
  { 923, ET_Instruction, 0, 0  },
  // 0x5f: f32.le  
  { 1015, ET_Instruction, 0, 0  },
  // 0x60: f32.ge  
  { 865, ET_Instruction, 0, 0  },
  // 0x61: f64.eq  
  { 759, ET_Instruction, 0, 0  },
  // 0x62: f64.ne  
  { 1353, ET_Instruction, 0, 0  },
  // 0x63: f64.lt  
  { 1217, ET_Instruction, 0, 0  },
  // 0x64: f64.gt  
  { 927, ET_Instruction, 0, 0  },
  // 0x65: f64.le  
  { 1019, ET_Instruction, 0, 0  },
  // 0x66: f64.ge  
  { 869, ET_Instruction, 0, 0  },
  // 0x67: i32.clz 
  { 655, ET_Instruction, 0, 0  },
  // 0x68: i32.ctz 
  { 697, ET_Instruction, 0, 0  },
  // 0x69: i32.popcnt
  { 1391, ET_Instruction, 0, 0  },
  // 0x6a: i32.add 
  { 295, ET_Instruction, 0, 0  },
  // 0x6b: i32.sub 
  { 1599, ET_Instruction, 0, 0  },
  // 0x6c: i32.mul 
  { 1309, ET_Instruction, 0, 0  },
  // 0x6d: i32.div_s
  { 713, ET_Instruction, 0, 0  },
  // 0x6e: i32.div_u
  { 717, ET_Instruction, 0, 0  },
  // 0x6f: i32.rem_s
  { 1417, ET_Instruction, 0, 0  },
  // 0x70: i32.rem_u
  { 1421, ET_Instruction, 0, 0  },
  // 0x71: i32.and 
  { 328, ET_Instruction, 0, 0  },
  // 0x72: i32.or  
  { 1378, ET_Instruction, 0, 0  },
  // 0x73: i32.xor 
  { 1668, ET_Instruction, 0, 0  },
  // 0x74: i32.shl 
  { 1469, ET_Instruction, 0, 0  },
  // 0x75: i32.shr_s
  { 1481, ET_Instruction, 0, 0  },
  // 0x76: i32.shr_u
  { 1493, ET_Instruction, 0, 0  },
  // 0x77: i32.rotl
  { 1445, ET_Instruction, 0, 0  },
  // 0x78: i32.rotr
  { 1449, ET_Instruction, 0, 0  },
  // 0x79: i64.clz 
  { 657, ET_Instruction, 0, 0  },
  // 0x7a: i64.ctz 
  { 699, ET_Instruction, 0, 0  },
  // 0x7b: i64.popcnt
  { 1393, ET_Instruction, 0, 0  },
  // 0x7c: i64.add 
  { 299, ET_Instruction, 0, 0  },
  // 0x7d: i64.sub 
  { 1603, ET_Instruction, 0, 0  },
  // 0x7e: i64.mul 
  { 1313, ET_Instruction, 0, 0  },
  // 0x7f: i64.div_s
  { 715, ET_Instruction, 0, 0  },
  // 0x80: i64.div_u
  { 719, ET_Instruction, 0, 0  },
  // 0x81: i64.rem_s
  { 1419, ET_Instruction, 0, 0  },
  // 0x82: i64.rem_u
  { 1423, ET_Instruction, 0, 0  },
  // 0x83: i64.and 
  { 330, ET_Instruction, 0, 0  },
  // 0x84: i64.or  
  { 1380, ET_Instruction, 0, 0  },
  // 0x85: i64.xor 
  { 1670, ET_Instruction, 0, 0  },
  // 0x86: i64.shl 
  { 1473, ET_Instruction, 0, 0  },
  // 0x87: i64.shr_s
  { 1485, ET_Instruction, 0, 0  },
  // 0x88: i64.shr_u
  { 1497, ET_Instruction, 0, 0  },
  // 0x89: i64.rotl
  { 1447, ET_Instruction, 0, 0  },
  // 0x8a: i64.rotr
  { 1451, ET_Instruction, 0, 0  },
  // 0x8b: f32.abs 
  { 269, ET_Instruction, 0, 0  },
  // 0x8c: f32.neg 
  { 1333, ET_Instruction, 0, 0  },
  // 0x8d: f32.ceil
  { 647, ET_Instruction, 0, 0  },
  // 0x8e: f32.floor
  { 841, ET_Instruction, 0, 0  },
  // 0x8f: f32.trunc
  { 1655, ET_Instruction, 0, 0  },
  // 0x90: f32.nearest
  { 1325, ET_Instruction, 0, 0  },
  // 0x91: f32.sqrt
  { 1525, ET_Instruction, 0, 0  },
  // 0x92: f32.add 
  { 285, ET_Instruction, 0, 0  },
  // 0x93: f32.sub 
  { 1589, ET_Instruction, 0, 0  },
  // 0x94: f32.mul 
  { 1299, ET_Instruction, 0, 0  },
  // 0x95: f32.div 
  { 705, ET_Instruction, 0, 0  },
  // 0x96: f32.min 
  { 1279, ET_Instruction, 0, 0  },
  // 0x97: f32.max 
  { 1247, ET_Instruction, 0, 0  },
  // 0x98: f32.copysign
  { 679, ET_Instruction, 0, 0  },
  // 0x99: f64.abs 
  { 273, ET_Instruction, 0, 0  },
  // 0x9a: f64.neg 
  { 1337, ET_Instruction, 0, 0  },
  // 0x9b: f64.ceil
  { 651, ET_Instruction, 0, 0  },
  // 0x9c: f64.floor
  { 845, ET_Instruction, 0, 0  },
  // 0x9d: f64.trunc
  { 1659, ET_Instruction, 0, 0  },
  // 0x9e: f64.nearest
  { 1329, ET_Instruction, 0, 0  },
  // 0x9f: f64.sqrt
  { 1529, ET_Instruction, 0, 0  },
  // 0xa0: f64.add 
  { 289, ET_Instruction, 0, 0  },
  // 0xa1: f64.sub 
  { 1593, ET_Instruction, 0, 0  },
  // 0xa2: f64.mul 
  { 1303, ET_Instruction, 0, 0  },
  // 0xa3: f64.div 
  { 709, ET_Instruction, 0, 0  },
  // 0xa4: f64.min 
  { 1283, ET_Instruction, 0, 0  },
  // 0xa5: f64.max 
  { 1251, ET_Instruction, 0, 0  },
  // 0xa6: f64.copysign
  { 681, ET_Instruction, 0, 0  },
  // 0xa7: i32.wrap_i64
  { 975, ET_Instruction, 0, 0  },
  // 0xa8: i32.trunc_f32_s
  { 959, ET_Instruction, 0, 0  },
  // 0xa9: i32.trunc_f32_u
  { 967, ET_Instruction, 0, 0  },
  // 0xaa: i32.trunc_f64_s
  { 961, ET_Instruction, 0, 0  },
  // 0xab: i32.trunc_f64_u
  { 969, ET_Instruction, 0, 0  },
  // 0xac: i64.extend_i32_s
  { 983, ET_Instruction, 0, 0  },
  // 0xad: i64.extend_i32_u
  { 985, ET_Instruction, 0, 0  },
  // 0xae: i64.trunc_f32_s
  { 989, ET_Instruction, 0, 0  },
  // 0xaf: i64.trunc_f32_u
  { 997, ET_Instruction, 0, 0  },
  // 0xb0: i64.trunc_f64_s
  { 991, ET_Instruction, 0, 0  },
  // 0xb1: i64.trunc_f64_u
  { 999, ET_Instruction, 0, 0  },
  // 0xb2: f32.convert_i32_s
  { 815, ET_Instruction, 0, 0  },
  // 0xb3: f32.convert_i32_u
  { 819, ET_Instruction, 0, 0  },
  // 0xb4: f32.convert_i64_s
  { 817, ET_Instruction, 0, 0  },
  // 0xb5: f32.convert_i64_u
  { 821, ET_Instruction, 0, 0  },
  // 0xb6: f32.demote_f64
  { 823, ET_Instruction, 0, 0  },
  // 0xb7: f64.convert_i32_s
  { 827, ET_Instruction, 0, 0  },
  // 0xb8: f64.convert_i32_u
  { 831, ET_Instruction, 0, 0  },
  // 0xb9: f64.convert_i64_s
  { 829, ET_Instruction, 0, 0  },
  // 0xba: f64.convert_i64_u
  { 833, ET_Instruction, 0, 0  },
  // 0xbb: f64.promote_f32
  { 835, ET_Instruction, 0, 0  },
  // 0xbc: i32.reinterpret_f32
  { 957, ET_Instruction, 0, 0  },
  // 0xbd: i64.reinterpret_f64
  { 987, ET_Instruction, 0, 0  },
  // 0xbe: f32.reinterpret_i32
  { 825, ET_Instruction, 0, 0  },
  // 0xbf: f64.reinterpret_i64
  { 837, ET_Instruction, 0, 0  },
  // 0xc0: i32.extend8_s
  { 955, ET_Instruction, 0, 0  },
  // 0xc1: i32.extend16_s
  { 953, ET_Instruction, 0, 0  },
  // 0xc2: i64.extend8_s
  { 981, ET_Instruction, 0, 0  },
  // 0xc3: i64.extend16_s
  { 977, ET_Instruction, 0, 0  },
  // 0xc4: i64.extend32_s
  { 979, ET_Instruction, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Prefix, 0, 0  },
  // 0xd1: ref.is_null
  { 1399, ET_Instruction, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Prefix, 0, 0  },
  { 0, ET_Prefix, 0, 0  },
  { 0, ET_Prefix, 0, 0  },
  { 0, ET_Unused, 0, 0  },
};

WebAssemblyInstruction InstructionTable208[] = {
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0x6f: ref.null_extern
  { 1403, ET_Instruction, 0, 0  },
  // 0x70: ref.null_func
  { 1405, ET_Instruction, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
};

WebAssemblyInstruction InstructionTable252[] = {
  // 0x0: i32.trunc_sat_f32_s
  { 963, ET_Instruction, 0, 0  },
  // 0x1: i32.trunc_sat_f32_u
  { 971, ET_Instruction, 0, 0  },
  // 0x2: i32.trunc_sat_f64_s
  { 965, ET_Instruction, 0, 0  },
  // 0x3: i32.trunc_sat_f64_u
  { 973, ET_Instruction, 0, 0  },
  // 0x4: i64.trunc_sat_f32_s
  { 993, ET_Instruction, 0, 0  },
  // 0x5: i64.trunc_sat_f32_u
  { 1001, ET_Instruction, 0, 0  },
  // 0x6: i64.trunc_sat_f64_s
  { 995, ET_Instruction, 0, 0  },
  // 0x7: i64.trunc_sat_f64_u
  { 1003, ET_Instruction, 0, 0  },
  // 0x8: memory.init	$seg, $idx
  { 1687, ET_Instruction, 2, 16  },
  // 0x9: data.drop	$seg
  { 1681, ET_Instruction, 1, 12  },
  // 0xa: memory.copy	$src_idx, $dst_idx
  { 1683, ET_Instruction, 2, 16  },
  // 0xb: memory.fill	$idx
  { 1685, ET_Instruction, 1, 12  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0xe: table.copy	$table1, $table2
  { 1619, ET_Instruction, 2, 18  },
  // 0xf: table.grow	$table
  { 1629, ET_Instruction, 1, 7  },
  // 0x10: table.size	$table
  { 1637, ET_Instruction, 1, 7  },
  // 0x11: table.fill	$table
  { 1621, ET_Instruction, 1, 7  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
};

WebAssemblyInstruction InstructionTable253[] = {
  // 0x0: v128.load	$off$p2align
  { 1157, ET_Instruction, 2, 10  },
  // 0x1: i16x8.load8x8_s	$off$p2align
  { 1101, ET_Instruction, 2, 10  },
  // 0x2: i16x8.load8x8_u	$off$p2align
  { 1113, ET_Instruction, 2, 10  },
  // 0x3: i32x4.load16x4_s	$off$p2align
  { 1105, ET_Instruction, 2, 10  },
  // 0x4: i32x4.load16x4_u	$off$p2align
  { 1117, ET_Instruction, 2, 10  },
  // 0x5: i64x2.load32x2_s	$off$p2align
  { 1109, ET_Instruction, 2, 10  },
  // 0x6: i64x2.load32x2_u	$off$p2align
  { 1121, ET_Instruction, 2, 10  },
  // 0x7: v128.load8_splat	$off$p2align
  { 1081, ET_Instruction, 2, 10  },
  // 0x8: v128.load16_splat	$off$p2align
  { 1045, ET_Instruction, 2, 10  },
  // 0x9: v128.load32_splat	$off$p2align
  { 1065, ET_Instruction, 2, 10  },
  // 0xa: v128.load64_splat	$off$p2align
  { 1077, ET_Instruction, 2, 10  },
  // 0xb: v128.store	$off$p2align
  { 1585, ET_Instruction, 2, 10  },
  // 0xc: v128.const	$i0, $i1, $i2, $i3
  { 673, ET_Instruction, 4, 20  },
  // 0xd: i8x16.shuffle	$m0, $m1, $m2, $m3, $m4, $m5, $m6, $m7, $m8, $m9, $mA, $mB, $mC, $mD, $mE, $mF
  { 1503, ET_Instruction, 16, 24  },
  // 0xe: i8x16.swizzle
  { 1617, ET_Instruction, 0, 0  },
  // 0xf: i8x16.splat
  { 1523, ET_Instruction, 0, 0  },
  // 0x10: i16x8.splat
  { 1517, ET_Instruction, 0, 0  },
  // 0x11: i32x4.splat
  { 1519, ET_Instruction, 0, 0  },
  // 0x12: i64x2.splat
  { 1521, ET_Instruction, 0, 0  },
  // 0x13: f32x4.splat
  { 1513, ET_Instruction, 0, 0  },
  // 0x14: f64x2.splat
  { 1515, ET_Instruction, 0, 0  },
  // 0x15: i8x16.extract_lane_s	$idx
  { 811, ET_Instruction, 1, 24  },
  // 0x16: i8x16.extract_lane_u	$idx
  { 813, ET_Instruction, 1, 24  },
  // 0x17: i8x16.replace_lane	$idx
  { 1435, ET_Instruction, 1, 24  },
  // 0x18: i16x8.extract_lane_s	$idx
  { 803, ET_Instruction, 1, 24  },
  // 0x19: i16x8.extract_lane_u	$idx
  { 805, ET_Instruction, 1, 24  },
  // 0x1a: i16x8.replace_lane	$idx
  { 1429, ET_Instruction, 1, 24  },
  // 0x1b: i32x4.extract_lane	$idx
  { 807, ET_Instruction, 1, 24  },
  // 0x1c: i32x4.replace_lane	$idx
  { 1431, ET_Instruction, 1, 24  },
  // 0x1d: i64x2.extract_lane	$idx
  { 809, ET_Instruction, 1, 24  },
  // 0x1e: i64x2.replace_lane	$idx
  { 1433, ET_Instruction, 1, 24  },
  // 0x1f: f32x4.extract_lane	$idx
  { 799, ET_Instruction, 1, 24  },
  // 0x20: f32x4.replace_lane	$idx
  { 1425, ET_Instruction, 1, 24  },
  // 0x21: f64x2.extract_lane	$idx
  { 801, ET_Instruction, 1, 24  },
  // 0x22: f64x2.replace_lane	$idx
  { 1427, ET_Instruction, 1, 24  },
  // 0x23: i8x16.eq
  { 773, ET_Instruction, 0, 0  },
  // 0x24: i8x16.ne
  { 1367, ET_Instruction, 0, 0  },
  // 0x25: i8x16.lt_s
  { 1231, ET_Instruction, 0, 0  },
  // 0x26: i8x16.lt_u
  { 1241, ET_Instruction, 0, 0  },
  // 0x27: i8x16.gt_s
  { 941, ET_Instruction, 0, 0  },
  // 0x28: i8x16.gt_u
  { 951, ET_Instruction, 0, 0  },
  // 0x29: i8x16.le_s
  { 1033, ET_Instruction, 0, 0  },
  // 0x2a: i8x16.le_u
  { 1043, ET_Instruction, 0, 0  },
  // 0x2b: i8x16.ge_s
  { 883, ET_Instruction, 0, 0  },
  // 0x2c: i8x16.ge_u
  { 893, ET_Instruction, 0, 0  },
  // 0x2d: i16x8.eq
  { 763, ET_Instruction, 0, 0  },
  // 0x2e: i16x8.ne
  { 1357, ET_Instruction, 0, 0  },
  // 0x2f: i16x8.lt_s
  { 1221, ET_Instruction, 0, 0  },
  // 0x30: i16x8.lt_u
  { 1233, ET_Instruction, 0, 0  },
  // 0x31: i16x8.gt_s
  { 931, ET_Instruction, 0, 0  },
  // 0x32: i16x8.gt_u
  { 943, ET_Instruction, 0, 0  },
  // 0x33: i16x8.le_s
  { 1023, ET_Instruction, 0, 0  },
  // 0x34: i16x8.le_u
  { 1035, ET_Instruction, 0, 0  },
  // 0x35: i16x8.ge_s
  { 873, ET_Instruction, 0, 0  },
  // 0x36: i16x8.ge_u
  { 885, ET_Instruction, 0, 0  },
  // 0x37: i32x4.eq
  { 767, ET_Instruction, 0, 0  },
  // 0x38: i32x4.ne
  { 1361, ET_Instruction, 0, 0  },
  // 0x39: i32x4.lt_s
  { 1225, ET_Instruction, 0, 0  },
  // 0x3a: i32x4.lt_u
  { 1237, ET_Instruction, 0, 0  },
  // 0x3b: i32x4.gt_s
  { 935, ET_Instruction, 0, 0  },
  // 0x3c: i32x4.gt_u
  { 947, ET_Instruction, 0, 0  },
  // 0x3d: i32x4.le_s
  { 1027, ET_Instruction, 0, 0  },
  // 0x3e: i32x4.le_u
  { 1039, ET_Instruction, 0, 0  },
  // 0x3f: i32x4.ge_s
  { 877, ET_Instruction, 0, 0  },
  // 0x40: i32x4.ge_u
  { 889, ET_Instruction, 0, 0  },
  // 0x41: f32x4.eq
  { 757, ET_Instruction, 0, 0  },
  // 0x42: f32x4.ne
  { 1351, ET_Instruction, 0, 0  },
  // 0x43: f32x4.lt
  { 1215, ET_Instruction, 0, 0  },
  // 0x44: f32x4.gt
  { 925, ET_Instruction, 0, 0  },
  // 0x45: f32x4.le
  { 1017, ET_Instruction, 0, 0  },
  // 0x46: f32x4.ge
  { 867, ET_Instruction, 0, 0  },
  // 0x47: f64x2.eq
  { 761, ET_Instruction, 0, 0  },
  // 0x48: f64x2.ne
  { 1355, ET_Instruction, 0, 0  },
  // 0x49: f64x2.lt
  { 1219, ET_Instruction, 0, 0  },
  // 0x4a: f64x2.gt
  { 929, ET_Instruction, 0, 0  },
  // 0x4b: f64x2.le
  { 1021, ET_Instruction, 0, 0  },
  // 0x4c: f64x2.ge
  { 871, ET_Instruction, 0, 0  },
  // 0x4d: v128.not
  { 1375, ET_Instruction, 0, 0  },
  // 0x4e: v128.and
  { 331, ET_Instruction, 0, 0  },
  // 0x4f: v128.andnot
  { 326, ET_Instruction, 0, 0  },
  // 0x50: v128.or
  { 1381, ET_Instruction, 0, 0  },
  // 0x51: v128.xor
  { 1671, ET_Instruction, 0, 0  },
  // 0x52: v128.bitselect
  { 625, ET_Instruction, 0, 0  },
  // 0x53: v128.any_true
  { 333, ET_Instruction, 0, 0  },
  // 0x54: v128.load8_lane	$off$p2align, $idx
  { 1153, ET_Instruction, 3, 40  },
  // 0x55: v128.load16_lane	$off$p2align, $idx
  { 1141, ET_Instruction, 3, 40  },
  // 0x56: v128.load32_lane	$off$p2align, $idx
  { 1145, ET_Instruction, 3, 40  },
  // 0x57: v128.load64_lane	$off$p2align, $idx
  { 1149, ET_Instruction, 3, 40  },
  // 0x58: v128.store8_lane	$off$p2align, $idx
  { 1581, ET_Instruction, 3, 40  },
  // 0x59: v128.store16_lane	$off$p2align, $idx
  { 1569, ET_Instruction, 3, 40  },
  // 0x5a: v128.store32_lane	$off$p2align, $idx
  { 1573, ET_Instruction, 3, 40  },
  // 0x5b: v128.store64_lane	$off$p2align, $idx
  { 1577, ET_Instruction, 3, 40  },
  // 0x5c: v128.load32_zero	$off$p2align
  { 1161, ET_Instruction, 2, 10  },
  // 0x5d: v128.load64_zero	$off$p2align
  { 1165, ET_Instruction, 2, 10  },
  // 0x5e: f32x4.demote_f64x2_zero
  { 1701, ET_Instruction, 0, 0  },
  // 0x5f: f64x2.promote_low_f32x4
  { 1747, ET_Instruction, 0, 0  },
  // 0x60: i8x16.abs
  { 283, ET_Instruction, 0, 0  },
  // 0x61: i8x16.neg
  { 1347, ET_Instruction, 0, 0  },
  // 0x62: i8x16.popcnt
  { 1395, ET_Instruction, 0, 0  },
  // 0x63: i8x16.all_true
  { 323, ET_Instruction, 0, 0  },
  // 0x64: i8x16.bitmask
  { 623, ET_Instruction, 0, 0  },
  // 0x65: i8x16.narrow_i16x8_s
  { 1319, ET_Instruction, 0, 0  },
  // 0x66: i8x16.narrow_i16x8_u
  { 1323, ET_Instruction, 0, 0  },
  // 0x67: f32x4.ceil
  { 649, ET_Instruction, 0, 0  },
  // 0x68: f32x4.floor
  { 843, ET_Instruction, 0, 0  },
  // 0x69: f32x4.trunc
  { 1657, ET_Instruction, 0, 0  },
  // 0x6a: f32x4.nearest
  { 1327, ET_Instruction, 0, 0  },
  // 0x6b: i8x16.shl
  { 1477, ET_Instruction, 0, 0  },
  // 0x6c: i8x16.shr_s
  { 1489, ET_Instruction, 0, 0  },
  // 0x6d: i8x16.shr_u
  { 1501, ET_Instruction, 0, 0  },
  // 0x6e: i8x16.add
  { 303, ET_Instruction, 0, 0  },
  // 0x6f: i8x16.add_sat_s
  { 307, ET_Instruction, 0, 0  },
  // 0x70: i8x16.add_sat_u
  { 311, ET_Instruction, 0, 0  },
  // 0x71: i8x16.sub
  { 1607, ET_Instruction, 0, 0  },
  // 0x72: i8x16.sub_sat_s
  { 1611, ET_Instruction, 0, 0  },
  // 0x73: i8x16.sub_sat_u
  { 1615, ET_Instruction, 0, 0  },
  // 0x74: f64x2.ceil
  { 653, ET_Instruction, 0, 0  },
  // 0x75: f64x2.floor
  { 847, ET_Instruction, 0, 0  },
  // 0x76: i8x16.min_s
  { 1291, ET_Instruction, 0, 0  },
  // 0x77: i8x16.min_u
  { 1297, ET_Instruction, 0, 0  },
  // 0x78: i8x16.max_s
  { 1259, ET_Instruction, 0, 0  },
  // 0x79: i8x16.max_u
  { 1265, ET_Instruction, 0, 0  },
  // 0x7a: f64x2.trunc
  { 1661, ET_Instruction, 0, 0  },
  // 0x7b: i8x16.avgr_u
  { 615, ET_Instruction, 0, 0  },
  // 0x7c: i16x8.extadd_pairwise_i8x16_s
  { 1731, ET_Instruction, 0, 0  },
  // 0x7d: i16x8.extadd_pairwise_i8x16_u
  { 1735, ET_Instruction, 0, 0  },
  // 0x7e: i32x4.extadd_pairwise_i16x8_s
  { 1733, ET_Instruction, 0, 0  },
  // 0x7f: i32x4.extadd_pairwise_i16x8_u
  { 1737, ET_Instruction, 0, 0  },
  // 0x80: i16x8.abs
  { 277, ET_Instruction, 0, 0  },
  // 0x81: i16x8.neg
  { 1341, ET_Instruction, 0, 0  },
  // 0x82: i16x8.q15mulr_sat_s
  { 1397, ET_Instruction, 0, 0  },
  // 0x83: i16x8.all_true
  { 317, ET_Instruction, 0, 0  },
  // 0x84: i16x8.bitmask
  { 617, ET_Instruction, 0, 0  },
  // 0x85: i16x8.narrow_i32x4_s
  { 1317, ET_Instruction, 0, 0  },
  // 0x86: i16x8.narrow_i32x4_u
  { 1321, ET_Instruction, 0, 0  },
  // 0x87: i16x8.extend_low_i8x16_s
  { 1715, ET_Instruction, 0, 0  },
  // 0x88: i16x8.extend_high_i8x16_s
  { 1703, ET_Instruction, 0, 0  },
  // 0x89: i16x8.extend_low_i8x16_u
  { 1721, ET_Instruction, 0, 0  },
  // 0x8a: i16x8.extend_high_i8x16_u
  { 1709, ET_Instruction, 0, 0  },
  // 0x8b: i16x8.shl
  { 1467, ET_Instruction, 0, 0  },
  // 0x8c: i16x8.shr_s
  { 1479, ET_Instruction, 0, 0  },
  // 0x8d: i16x8.shr_u
  { 1491, ET_Instruction, 0, 0  },
  // 0x8e: i16x8.add
  { 293, ET_Instruction, 0, 0  },
  // 0x8f: i16x8.add_sat_s
  { 305, ET_Instruction, 0, 0  },
  // 0x90: i16x8.add_sat_u
  { 309, ET_Instruction, 0, 0  },
  // 0x91: i16x8.sub
  { 1597, ET_Instruction, 0, 0  },
  // 0x92: i16x8.sub_sat_s
  { 1609, ET_Instruction, 0, 0  },
  // 0x93: i16x8.sub_sat_u
  { 1613, ET_Instruction, 0, 0  },
  // 0x94: f64x2.nearest
  { 1331, ET_Instruction, 0, 0  },
  // 0x95: i16x8.mul
  { 1307, ET_Instruction, 0, 0  },
  // 0x96: i16x8.min_s
  { 1287, ET_Instruction, 0, 0  },
  // 0x97: i16x8.min_u
  { 1293, ET_Instruction, 0, 0  },
  // 0x98: i16x8.max_s
  { 1255, ET_Instruction, 0, 0  },
  // 0x99: i16x8.max_u
  { 1261, ET_Instruction, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0x9b: i16x8.avgr_u
  { 613, ET_Instruction, 0, 0  },
  // 0x9c: i16x8.extmul_low_i8x16_s
  { 787, ET_Instruction, 0, 0  },
  // 0x9d: i16x8.extmul_high_i8x16_s
  { 775, ET_Instruction, 0, 0  },
  // 0x9e: i16x8.extmul_low_i8x16_u
  { 793, ET_Instruction, 0, 0  },
  // 0x9f: i16x8.extmul_high_i8x16_u
  { 781, ET_Instruction, 0, 0  },
  // 0xa0: i32x4.abs
  { 279, ET_Instruction, 0, 0  },
  // 0xa1: i32x4.neg
  { 1343, ET_Instruction, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0xa3: i32x4.all_true
  { 319, ET_Instruction, 0, 0  },
  // 0xa4: i32x4.bitmask
  { 619, ET_Instruction, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0xa7: i32x4.extend_low_i16x8_s
  { 1717, ET_Instruction, 0, 0  },
  // 0xa8: i32x4.extend_high_i16x8_s
  { 1705, ET_Instruction, 0, 0  },
  // 0xa9: i32x4.extend_low_i16x8_u
  { 1723, ET_Instruction, 0, 0  },
  // 0xaa: i32x4.extend_high_i16x8_u
  { 1711, ET_Instruction, 0, 0  },
  // 0xab: i32x4.shl
  { 1471, ET_Instruction, 0, 0  },
  // 0xac: i32x4.shr_s
  { 1483, ET_Instruction, 0, 0  },
  // 0xad: i32x4.shr_u
  { 1495, ET_Instruction, 0, 0  },
  // 0xae: i32x4.add
  { 297, ET_Instruction, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0xb1: i32x4.sub
  { 1601, ET_Instruction, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0xb5: i32x4.mul
  { 1311, ET_Instruction, 0, 0  },
  // 0xb6: i32x4.min_s
  { 1289, ET_Instruction, 0, 0  },
  // 0xb7: i32x4.min_u
  { 1295, ET_Instruction, 0, 0  },
  // 0xb8: i32x4.max_s
  { 1257, ET_Instruction, 0, 0  },
  // 0xb9: i32x4.max_u
  { 1263, ET_Instruction, 0, 0  },
  // 0xba: i32x4.dot_i16x8_s
  { 721, ET_Instruction, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0xbc: i32x4.extmul_low_i16x8_s
  { 789, ET_Instruction, 0, 0  },
  // 0xbd: i32x4.extmul_high_i16x8_s
  { 777, ET_Instruction, 0, 0  },
  // 0xbe: i32x4.extmul_low_i16x8_u
  { 795, ET_Instruction, 0, 0  },
  // 0xbf: i32x4.extmul_high_i16x8_u
  { 783, ET_Instruction, 0, 0  },
  // 0xc0: i64x2.abs
  { 281, ET_Instruction, 0, 0  },
  // 0xc1: i64x2.neg
  { 1345, ET_Instruction, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0xc3: i64x2.all_true
  { 321, ET_Instruction, 0, 0  },
  // 0xc4: i64x2.bitmask
  { 621, ET_Instruction, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0xc7: i64x2.extend_low_i32x4_s
  { 1719, ET_Instruction, 0, 0  },
  // 0xc8: i64x2.extend_high_i32x4_s
  { 1707, ET_Instruction, 0, 0  },
  // 0xc9: i64x2.extend_low_i32x4_u
  { 1725, ET_Instruction, 0, 0  },
  // 0xca: i64x2.extend_high_i32x4_u
  { 1713, ET_Instruction, 0, 0  },
  // 0xcb: i64x2.shl
  { 1475, ET_Instruction, 0, 0  },
  // 0xcc: i64x2.shr_s
  { 1487, ET_Instruction, 0, 0  },
  // 0xcd: i64x2.shr_u
  { 1499, ET_Instruction, 0, 0  },
  // 0xce: i64x2.add
  { 301, ET_Instruction, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0xd1: i64x2.sub
  { 1605, ET_Instruction, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0xd5: i64x2.mul
  { 1315, ET_Instruction, 0, 0  },
  // 0xd6: i64x2.eq
  { 771, ET_Instruction, 0, 0  },
  // 0xd7: i64x2.ne
  { 1365, ET_Instruction, 0, 0  },
  // 0xd8: i64x2.lt_s
  { 1229, ET_Instruction, 0, 0  },
  // 0xd9: i64x2.gt_s
  { 939, ET_Instruction, 0, 0  },
  // 0xda: i64x2.le_s
  { 1031, ET_Instruction, 0, 0  },
  // 0xdb: i64x2.ge_s
  { 881, ET_Instruction, 0, 0  },
  // 0xdc: i64x2.extmul_low_i32x4_s
  { 791, ET_Instruction, 0, 0  },
  // 0xdd: i64x2.extmul_high_i32x4_s
  { 779, ET_Instruction, 0, 0  },
  // 0xde: i64x2.extmul_low_i32x4_u
  { 797, ET_Instruction, 0, 0  },
  // 0xdf: i64x2.extmul_high_i32x4_u
  { 785, ET_Instruction, 0, 0  },
  // 0xe0: f32x4.abs
  { 271, ET_Instruction, 0, 0  },
  // 0xe1: f32x4.neg
  { 1335, ET_Instruction, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0xe3: f32x4.sqrt
  { 1527, ET_Instruction, 0, 0  },
  // 0xe4: f32x4.add
  { 287, ET_Instruction, 0, 0  },
  // 0xe5: f32x4.sub
  { 1591, ET_Instruction, 0, 0  },
  // 0xe6: f32x4.mul
  { 1301, ET_Instruction, 0, 0  },
  // 0xe7: f32x4.div
  { 707, ET_Instruction, 0, 0  },
  // 0xe8: f32x4.min
  { 1281, ET_Instruction, 0, 0  },
  // 0xe9: f32x4.max
  { 1249, ET_Instruction, 0, 0  },
  // 0xea: f32x4.pmin
  { 1387, ET_Instruction, 0, 0  },
  // 0xeb: f32x4.pmax
  { 1383, ET_Instruction, 0, 0  },
  // 0xec: f64x2.abs
  { 275, ET_Instruction, 0, 0  },
  // 0xed: f64x2.neg
  { 1339, ET_Instruction, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0xef: f64x2.sqrt
  { 1531, ET_Instruction, 0, 0  },
  // 0xf0: f64x2.add
  { 291, ET_Instruction, 0, 0  },
  // 0xf1: f64x2.sub
  { 1595, ET_Instruction, 0, 0  },
  // 0xf2: f64x2.mul
  { 1305, ET_Instruction, 0, 0  },
  // 0xf3: f64x2.div
  { 711, ET_Instruction, 0, 0  },
  // 0xf4: f64x2.min
  { 1285, ET_Instruction, 0, 0  },
  // 0xf5: f64x2.max
  { 1253, ET_Instruction, 0, 0  },
  // 0xf6: f64x2.pmin
  { 1389, ET_Instruction, 0, 0  },
  // 0xf7: f64x2.pmax
  { 1385, ET_Instruction, 0, 0  },
  // 0xf8: i32x4.trunc_sat_f32x4_s
  { 1727, ET_Instruction, 0, 0  },
  // 0xf9: i32x4.trunc_sat_f32x4_u
  { 1729, ET_Instruction, 0, 0  },
  // 0xfa: f32x4.convert_i32x4_s
  { 1749, ET_Instruction, 0, 0  },
  // 0xfb: f32x4.convert_i32x4_u
  { 1755, ET_Instruction, 0, 0  },
  // 0xfc: i32x4.trunc_sat_f64x2_s_zero
  { 1751, ET_Instruction, 0, 0  },
  // 0xfd: i32x4.trunc_sat_f64x2_u_zero
  { 1753, ET_Instruction, 0, 0  },
  // 0xfe: f64x2.convert_low_i32x4_s
  { 1697, ET_Instruction, 0, 0  },
  // 0xff: f64x2.convert_low_i32x4_u
  { 1699, ET_Instruction, 0, 0  },
};

WebAssemblyInstruction InstructionTable254[] = {
  // 0x0: memory.atomic.notify 	${off}${p2align}
  { 1267, ET_Instruction, 2, 10  },
  // 0x1: memory.atomic.wait32 	${off}${p2align}
  { 1271, ET_Instruction, 2, 10  },
  // 0x2: memory.atomic.wait64 	${off}${p2align}
  { 1275, ET_Instruction, 2, 10  },
  // 0x3: atomic.fence
  { 359, ET_Instruction, 1, 2  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0x10: i32.atomic.load	${off}${p2align}
  { 381, ET_Instruction, 2, 10  },
  // 0x11: i64.atomic.load	${off}${p2align}
  { 385, ET_Instruction, 2, 10  },
  // 0x12: i32.atomic.load8_u	${off}${p2align}
  { 373, ET_Instruction, 2, 10  },
  // 0x13: i32.atomic.load16_u	${off}${p2align}
  { 361, ET_Instruction, 2, 10  },
  // 0x14: i64.atomic.load8_u	${off}${p2align}
  { 377, ET_Instruction, 2, 10  },
  // 0x15: i64.atomic.load16_u	${off}${p2align}
  { 365, ET_Instruction, 2, 10  },
  // 0x16: i64.atomic.load32_u	${off}${p2align}
  { 369, ET_Instruction, 2, 10  },
  // 0x17: i32.atomic.store	${off}${p2align}
  { 605, ET_Instruction, 2, 10  },
  // 0x18: i64.atomic.store	${off}${p2align}
  { 609, ET_Instruction, 2, 10  },
  // 0x19: i32.atomic.store8	${off}${p2align}
  { 597, ET_Instruction, 2, 10  },
  // 0x1a: i32.atomic.store16	${off}${p2align}
  { 585, ET_Instruction, 2, 10  },
  // 0x1b: i64.atomic.store8	${off}${p2align}
  { 601, ET_Instruction, 2, 10  },
  // 0x1c: i64.atomic.store16	${off}${p2align}
  { 589, ET_Instruction, 2, 10  },
  // 0x1d: i64.atomic.store32	${off}${p2align}
  { 593, ET_Instruction, 2, 10  },
  // 0x1e: i32.atomic.rmw.add	${off}${p2align}
  { 529, ET_Instruction, 2, 10  },
  // 0x1f: i64.atomic.rmw.add	${off}${p2align}
  { 533, ET_Instruction, 2, 10  },
  // 0x20: i32.atomic.rmw8.add_u	${off}${p2align}
  { 473, ET_Instruction, 2, 10  },
  // 0x21: i32.atomic.rmw16.add_u	${off}${p2align}
  { 389, ET_Instruction, 2, 10  },
  // 0x22: i64.atomic.rmw8.add_u	${off}${p2align}
  { 477, ET_Instruction, 2, 10  },
  // 0x23: i64.atomic.rmw16.add_u	${off}${p2align}
  { 393, ET_Instruction, 2, 10  },
  // 0x24: i64.atomic.rmw32.add_u	${off}${p2align}
  { 445, ET_Instruction, 2, 10  },
  // 0x25: i32.atomic.rmw.sub	${off}${p2align}
  { 561, ET_Instruction, 2, 10  },
  // 0x26: i64.atomic.rmw.sub	${off}${p2align}
  { 565, ET_Instruction, 2, 10  },
  // 0x27: i32.atomic.rmw8.sub_u	${off}${p2align}
  { 505, ET_Instruction, 2, 10  },
  // 0x28: i32.atomic.rmw16.sub_u	${off}${p2align}
  { 421, ET_Instruction, 2, 10  },
  // 0x29: i64.atomic.rmw8.sub_u	${off}${p2align}
  { 509, ET_Instruction, 2, 10  },
  // 0x2a: i64.atomic.rmw16.sub_u	${off}${p2align}
  { 425, ET_Instruction, 2, 10  },
  // 0x2b: i64.atomic.rmw32.sub_u	${off}${p2align}
  { 461, ET_Instruction, 2, 10  },
  // 0x2c: i32.atomic.rmw.and	${off}${p2align}
  { 537, ET_Instruction, 2, 10  },
  // 0x2d: i64.atomic.rmw.and	${off}${p2align}
  { 541, ET_Instruction, 2, 10  },
  // 0x2e: i32.atomic.rmw8.and_u	${off}${p2align}
  { 481, ET_Instruction, 2, 10  },
  // 0x2f: i32.atomic.rmw16.and_u	${off}${p2align}
  { 397, ET_Instruction, 2, 10  },
  // 0x30: i64.atomic.rmw8.and_u	${off}${p2align}
  { 485, ET_Instruction, 2, 10  },
  // 0x31: i64.atomic.rmw16.and_u	${off}${p2align}
  { 401, ET_Instruction, 2, 10  },
  // 0x32: i64.atomic.rmw32.and_u	${off}${p2align}
  { 449, ET_Instruction, 2, 10  },
  // 0x33: i32.atomic.rmw.or	${off}${p2align}
  { 553, ET_Instruction, 2, 10  },
  // 0x34: i64.atomic.rmw.or	${off}${p2align}
  { 557, ET_Instruction, 2, 10  },
  // 0x35: i32.atomic.rmw8.or_u	${off}${p2align}
  { 497, ET_Instruction, 2, 10  },
  // 0x36: i32.atomic.rmw16.or_u	${off}${p2align}
  { 413, ET_Instruction, 2, 10  },
  // 0x37: i64.atomic.rmw8.or_u	${off}${p2align}
  { 501, ET_Instruction, 2, 10  },
  // 0x38: i64.atomic.rmw16.or_u	${off}${p2align}
  { 417, ET_Instruction, 2, 10  },
  // 0x39: i64.atomic.rmw32.or_u	${off}${p2align}
  { 457, ET_Instruction, 2, 10  },
  // 0x3a: i32.atomic.rmw.xor	${off}${p2align}
  { 577, ET_Instruction, 2, 10  },
  // 0x3b: i64.atomic.rmw.xor	${off}${p2align}
  { 581, ET_Instruction, 2, 10  },
  // 0x3c: i32.atomic.rmw8.xor_u	${off}${p2align}
  { 521, ET_Instruction, 2, 10  },
  // 0x3d: i32.atomic.rmw16.xor_u	${off}${p2align}
  { 437, ET_Instruction, 2, 10  },
  // 0x3e: i64.atomic.rmw8.xor_u	${off}${p2align}
  { 525, ET_Instruction, 2, 10  },
  // 0x3f: i64.atomic.rmw16.xor_u	${off}${p2align}
  { 441, ET_Instruction, 2, 10  },
  // 0x40: i64.atomic.rmw32.xor_u	${off}${p2align}
  { 469, ET_Instruction, 2, 10  },
  // 0x41: i32.atomic.rmw.xchg	${off}${p2align}
  { 569, ET_Instruction, 2, 10  },
  // 0x42: i64.atomic.rmw.xchg	${off}${p2align}
  { 573, ET_Instruction, 2, 10  },
  // 0x43: i32.atomic.rmw8.xchg_u	${off}${p2align}
  { 513, ET_Instruction, 2, 10  },
  // 0x44: i32.atomic.rmw16.xchg_u	${off}${p2align}
  { 429, ET_Instruction, 2, 10  },
  // 0x45: i64.atomic.rmw8.xchg_u	${off}${p2align}
  { 517, ET_Instruction, 2, 10  },
  // 0x46: i64.atomic.rmw16.xchg_u	${off}${p2align}
  { 433, ET_Instruction, 2, 10  },
  // 0x47: i64.atomic.rmw32.xchg_u	${off}${p2align}
  { 465, ET_Instruction, 2, 10  },
  // 0x48: i32.atomic.rmw.cmpxchg	${off}${p2align}
  { 545, ET_Instruction, 2, 10  },
  // 0x49: i64.atomic.rmw.cmpxchg	${off}${p2align}
  { 549, ET_Instruction, 2, 10  },
  // 0x4a: i32.atomic.rmw8.cmpxchg_u	${off}${p2align}
  { 489, ET_Instruction, 2, 10  },
  // 0x4b: i32.atomic.rmw16.cmpxchg_u	${off}${p2align}
  { 405, ET_Instruction, 2, 10  },
  // 0x4c: i64.atomic.rmw8.cmpxchg_u	${off}${p2align}
  { 493, ET_Instruction, 2, 10  },
  // 0x4d: i64.atomic.rmw16.cmpxchg_u	${off}${p2align}
  { 409, ET_Instruction, 2, 10  },
  // 0x4e: i64.atomic.rmw32.cmpxchg_u	${off}${p2align}
  { 453, ET_Instruction, 2, 10  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  { 0, ET_Unused, 0, 0  },
  // 0xff: compiler_fence
  { 265, ET_Instruction, 0, 0  },
};

const uint8_t OperandTable[] = {
  WebAssembly::OPERAND_SIGNATURE,
  WebAssembly::OPERAND_TAG,
  MCOI::OPERAND_IMMEDIATE,
  WebAssembly::OPERAND_BASIC_BLOCK,
  WebAssembly::OPERAND_BRLIST,
  WebAssembly::OPERAND_FUNCTION32,
  WebAssembly::OPERAND_TYPEINDEX,
  WebAssembly::OPERAND_TABLE,
  WebAssembly::OPERAND_LOCAL,
  WebAssembly::OPERAND_GLOBAL,
  WebAssembly::OPERAND_P2ALIGN,
  WebAssembly::OPERAND_OFFSET32,
  WebAssembly::OPERAND_I32IMM,
  WebAssembly::OPERAND_I64IMM,
  WebAssembly::OPERAND_F32IMM,
  WebAssembly::OPERAND_F64IMM,
  WebAssembly::OPERAND_I32IMM,
  WebAssembly::OPERAND_I32IMM,
  WebAssembly::OPERAND_TABLE,
  WebAssembly::OPERAND_TABLE,
  WebAssembly::OPERAND_VEC_I32IMM,
  WebAssembly::OPERAND_VEC_I32IMM,
  WebAssembly::OPERAND_VEC_I32IMM,
  WebAssembly::OPERAND_VEC_I32IMM,
  WebAssembly::OPERAND_VEC_I8IMM,
  WebAssembly::OPERAND_VEC_I8IMM,
  WebAssembly::OPERAND_VEC_I8IMM,
  WebAssembly::OPERAND_VEC_I8IMM,
  WebAssembly::OPERAND_VEC_I8IMM,
  WebAssembly::OPERAND_VEC_I8IMM,
  WebAssembly::OPERAND_VEC_I8IMM,
  WebAssembly::OPERAND_VEC_I8IMM,
  WebAssembly::OPERAND_VEC_I8IMM,
  WebAssembly::OPERAND_VEC_I8IMM,
  WebAssembly::OPERAND_VEC_I8IMM,
  WebAssembly::OPERAND_VEC_I8IMM,
  WebAssembly::OPERAND_VEC_I8IMM,
  WebAssembly::OPERAND_VEC_I8IMM,
  WebAssembly::OPERAND_VEC_I8IMM,
  WebAssembly::OPERAND_VEC_I8IMM,
  WebAssembly::OPERAND_P2ALIGN,
  WebAssembly::OPERAND_OFFSET32,
  WebAssembly::OPERAND_VEC_I8IMM,
};

struct { uint8_t Prefix; const WebAssemblyInstruction *Table; }
PrefixTable[] = {
  { 208, InstructionTable208 },
  { 252, InstructionTable252 },
  { 253, InstructionTable253 },
  { 254, InstructionTable254 },
  { 0, nullptr }
};

} // end namespace llvm
