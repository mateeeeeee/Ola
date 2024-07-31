	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_enum.ola"
	.def	TestEnumValues;
	.scl	2;
	.type	32;
	.endef
	.globl	TestEnumValues                  # -- Begin function TestEnumValues
	.p2align	4, 0x90
TestEnumValues:                         # @TestEnumValues
.seh_proc TestEnumValues
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 40], 2
	cmp	qword ptr [rsp + 40], 2
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 48], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	TestEnumValuesAfterModification;
	.scl	2;
	.type	32;
	.endef
	.globl	TestEnumValuesAfterModification # -- Begin function TestEnumValuesAfterModification
	.p2align	4, 0x90
TestEnumValuesAfterModification:        # @TestEnumValuesAfterModification
.seh_proc TestEnumValuesAfterModification
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 40], 7
	cmp	qword ptr [rsp + 40], 7
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 32], 2
	cmp	qword ptr [rsp + 32], 2
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 48], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	TestEnumSwitch;
	.scl	2;
	.type	32;
	.endef
	.globl	TestEnumSwitch                  # -- Begin function TestEnumSwitch
	.p2align	4, 0x90
TestEnumSwitch:                         # @TestEnumSwitch
.seh_proc TestEnumSwitch
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 32
	.seh_stackalloc 32
	lea	rbp, [rsp + 32]
	.seh_setframe rbp, 32
	.seh_endprologue
	mov	qword ptr [rbp - 16], 1
	mov	qword ptr [rbp - 24], 0
# %bb.1:                                # %switch.header
	mov	rax, qword ptr [rbp - 16]
	mov	qword ptr [rbp - 32], rax       # 8-byte Spill
	test	rax, rax
	je	.LBB2_4
	jmp	.LBB2_8
.LBB2_8:                                # %switch.header
	mov	rax, qword ptr [rbp - 32]       # 8-byte Reload
	sub	rax, 1
	je	.LBB2_5
	jmp	.LBB2_9
.LBB2_9:                                # %switch.header
	mov	rax, qword ptr [rbp - 32]       # 8-byte Reload
	sub	rax, 2
	je	.LBB2_6
	jmp	.LBB2_2
.LBB2_2:                                # %switch.default
	jmp	.LBB2_7
.LBB2_3:                                # %switch.end
	cmp	qword ptr [rbp - 24], 2
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	mov	qword ptr [rbp - 8], 0
	jmp	.LBB2_7
.LBB2_4:                                # %switch.case0
	mov	qword ptr [rbp - 24], 1
	jmp	.LBB2_3
.LBB2_5:                                # %switch.case1
	mov	qword ptr [rbp - 24], 2
	jmp	.LBB2_3
.LBB2_6:                                # %switch.case2
	mov	qword ptr [rbp - 24], 3
	jmp	.LBB2_3
.LBB2_7:                                # %exit
	mov	rax, qword ptr [rbp - 8]
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	TestLocalEnumDeclaration;
	.scl	2;
	.type	32;
	.endef
	.globl	TestLocalEnumDeclaration        # -- Begin function TestLocalEnumDeclaration
	.p2align	4, 0x90
TestLocalEnumDeclaration:               # @TestLocalEnumDeclaration
.seh_proc TestLocalEnumDeclaration
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 40], 0
	cmp	qword ptr [rsp + 40], 0
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 48], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	cmp	qword ptr [rip + globalColor], 0
	sete	cl
	call	Assert
	call	TestLocalEnumDeclaration
	call	TestEnumValues
	call	TestEnumValuesAfterModification
	call	TestEnumSwitch
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.lcomm	globalColor,8,8                 # @globalColor
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestEnumValues
	.addrsig_sym TestEnumValuesAfterModification
	.addrsig_sym TestEnumSwitch
	.addrsig_sym TestLocalEnumDeclaration
	.addrsig_sym globalColor
