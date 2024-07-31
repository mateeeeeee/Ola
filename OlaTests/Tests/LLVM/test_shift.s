	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_shift.ola"
	.def	TestShiftOperatorsIntegers;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestShiftOperatorsIntegers
TestShiftOperatorsIntegers:             # @TestShiftOperatorsIntegers
.seh_proc TestShiftOperatorsIntegers
# %bb.0:                                # %entry
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 64], 5
	mov	qword ptr [rsp + 56], 2
	mov	rax, qword ptr [rsp + 64]
	mov	rcx, qword ptr [rsp + 56]
                                        # kill: def $cl killed $rcx
	shl	rax, cl
	mov	qword ptr [rsp + 48], rax
	cmp	qword ptr [rsp + 48], 20
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 64]
	mov	rcx, qword ptr [rsp + 56]
                                        # kill: def $cl killed $rcx
	sar	rax, cl
	mov	qword ptr [rsp + 40], rax
	cmp	qword ptr [rsp + 40], 1
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.def	TestCompoundShiftOperatorsIntegers;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestCompoundShiftOperatorsIntegers
TestCompoundShiftOperatorsIntegers:     # @TestCompoundShiftOperatorsIntegers
.seh_proc TestCompoundShiftOperatorsIntegers
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], 5
	mov	qword ptr [rsp + 40], 2
	mov	rax, qword ptr [rsp + 48]
	mov	rcx, qword ptr [rsp + 40]
                                        # kill: def $cl killed $rcx
	shl	rax, cl
	mov	qword ptr [rsp + 48], rax
	cmp	qword ptr [rsp + 48], 20
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 48]
	mov	rcx, qword ptr [rsp + 40]
                                        # kill: def $cl killed $rcx
	sar	rax, cl
	mov	qword ptr [rsp + 48], rax
	cmp	qword ptr [rsp + 48], 5
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
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
	call	TestShiftOperatorsIntegers
	call	TestCompoundShiftOperatorsIntegers
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestShiftOperatorsIntegers
	.addrsig_sym TestCompoundShiftOperatorsIntegers
