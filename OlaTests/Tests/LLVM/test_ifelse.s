	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_ifelse.ola"
	.def	TestIfElseBasic;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIfElseBasic
TestIfElseBasic:                        # @TestIfElseBasic
.seh_proc TestIfElseBasic
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 16
	.seh_stackalloc 16
	lea	rbp, [rsp + 16]
	.seh_setframe rbp, 16
	.seh_endprologue
	mov	qword ptr [rbp - 8], 10
	mov	qword ptr [rbp - 16], 20
	mov	rax, qword ptr [rbp - 8]
	cmp	rax, qword ptr [rbp - 16]
	jge	.LBB0_2
# %bb.1:                                # %if.then
	mov	ecx, 1
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB0_3
.LBB0_2:                                # %if.else
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
.LBB0_3:                                # %if.end
# %bb.4:                                # %exit
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	TestIfElseMultipleConditions;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIfElseMultipleConditions
TestIfElseMultipleConditions:           # @TestIfElseMultipleConditions
.seh_proc TestIfElseMultipleConditions
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 16
	.seh_stackalloc 16
	lea	rbp, [rsp + 16]
	.seh_setframe rbp, 16
	.seh_endprologue
	mov	qword ptr [rbp - 8], 5
	mov	qword ptr [rbp - 16], 5
	mov	rax, qword ptr [rbp - 8]
	cmp	rax, qword ptr [rbp - 16]
	jle	.LBB1_2
# %bb.1:                                # %if.then
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB1_3
.LBB1_2:                                # %if.else
	mov	rax, qword ptr [rbp - 8]
	cmp	rax, qword ptr [rbp - 16]
	jl	.LBB1_4
	jmp	.LBB1_5
.LBB1_3:                                # %if.end
	jmp	.LBB1_7
.LBB1_4:                                # %if.then1
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB1_6
.LBB1_5:                                # %if.else2
	mov	ecx, 1
	sub	rsp, 32
	call	Assert
	add	rsp, 32
.LBB1_6:                                # %if.end3
	jmp	.LBB1_3
.LBB1_7:                                # %exit
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	TestNestedIfElse;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestNestedIfElse
TestNestedIfElse:                       # @TestNestedIfElse
.seh_proc TestNestedIfElse
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 16
	.seh_stackalloc 16
	lea	rbp, [rsp + 16]
	.seh_setframe rbp, 16
	.seh_endprologue
	mov	qword ptr [rbp - 8], 42
	mov	rax, qword ptr [rbp - 8]
	mov	ecx, 2
	cqo
	idiv	rcx
	cmp	rdx, 0
	jne	.LBB2_2
# %bb.1:                                # %if.then
	cmp	qword ptr [rbp - 8], 0
	jg	.LBB2_4
	jmp	.LBB2_5
.LBB2_2:                                # %if.else
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
.LBB2_3:                                # %if.end
	jmp	.LBB2_7
.LBB2_4:                                # %if.then1
	mov	ecx, 1
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB2_6
.LBB2_5:                                # %if.else2
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
.LBB2_6:                                # %if.end3
	jmp	.LBB2_3
.LBB2_7:                                # %exit
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	TestComplexNestedIfElse;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestComplexNestedIfElse
TestComplexNestedIfElse:                # @TestComplexNestedIfElse
.seh_proc TestComplexNestedIfElse
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 32
	.seh_stackalloc 32
	lea	rbp, [rsp + 32]
	.seh_setframe rbp, 32
	.seh_endprologue
	mov	qword ptr [rbp - 8], 1
	mov	qword ptr [rbp - 16], 5
	mov	qword ptr [rbp - 24], 5
	cmp	qword ptr [rbp - 8], 0
	jle	.LBB3_2
# %bb.1:                                # %if.then
	cmp	qword ptr [rbp - 16], 10
	jl	.LBB3_4
	jmp	.LBB3_5
.LBB3_2:                                # %if.else
	cmp	qword ptr [rbp - 16], 0
	je	.LBB3_10
	jmp	.LBB3_11
.LBB3_3:                                # %if.end
	jmp	.LBB3_16
.LBB3_4:                                # %if.then1
	cmp	qword ptr [rbp - 24], 5
	je	.LBB3_7
	jmp	.LBB3_8
.LBB3_5:                                # %if.else2
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
.LBB3_6:                                # %if.end3
	jmp	.LBB3_3
.LBB3_7:                                # %if.then4
	mov	ecx, 1
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB3_9
.LBB3_8:                                # %if.else5
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
.LBB3_9:                                # %if.end6
	jmp	.LBB3_6
.LBB3_10:                               # %if.then7
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB3_12
.LBB3_11:                               # %if.else8
	cmp	qword ptr [rbp - 24], 0
	jg	.LBB3_13
	jmp	.LBB3_14
.LBB3_12:                               # %if.end9
	jmp	.LBB3_3
.LBB3_13:                               # %if.then10
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB3_15
.LBB3_14:                               # %if.else11
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
.LBB3_15:                               # %if.end12
	jmp	.LBB3_12
.LBB3_16:                               # %exit
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	TestIfElseLogicalOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIfElseLogicalOperators
TestIfElseLogicalOperators:             # @TestIfElseLogicalOperators
.seh_proc TestIfElseLogicalOperators
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 16
	.seh_stackalloc 16
	lea	rbp, [rsp + 16]
	.seh_setframe rbp, 16
	.seh_endprologue
	mov	qword ptr [rbp - 8], 15
	mov	rcx, qword ptr [rbp - 8]
	mov	rax, rcx
	sub	rax, 11
	setge	al
	sub	rcx, 20
	setl	cl
	and	al, cl
	je	.LBB4_2
	jmp	.LBB4_1
.LBB4_1:                                # %if.then
	mov	ecx, 1
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB4_3
.LBB4_2:                                # %if.else
	xor	ecx, ecx
	sub	rsp, 32
	call	Assert
	add	rsp, 32
.LBB4_3:                                # %if.end
# %bb.4:                                # %exit
	mov	rsp, rbp
	pop	rbp
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
	call	TestIfElseBasic
	call	TestIfElseMultipleConditions
	call	TestNestedIfElse
	call	TestComplexNestedIfElse
	call	TestIfElseLogicalOperators
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestIfElseBasic
	.addrsig_sym TestIfElseMultipleConditions
	.addrsig_sym TestNestedIfElse
	.addrsig_sym TestComplexNestedIfElse
	.addrsig_sym TestIfElseLogicalOperators
