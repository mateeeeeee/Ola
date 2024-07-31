	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_ternary.ola"
	.def	TestTernaryOperatorIntegers;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestTernaryOperatorIntegers
TestTernaryOperatorIntegers:            # @TestTernaryOperatorIntegers
.seh_proc TestTernaryOperatorIntegers
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], 5
	mov	qword ptr [rsp + 40], 10
	mov	rcx, qword ptr [rsp + 48]
	mov	rdx, qword ptr [rsp + 40]
	mov	rax, qword ptr [rsp + 48]
	cmp	rcx, rdx
	cmovle	rax, qword ptr [rsp + 40]
	mov	qword ptr [rsp + 32], rax
	cmp	qword ptr [rsp + 32], 10
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	TestTernaryOperatorFloats;
	.scl	3;
	.type	32;
	.endef
	.globl	__real@4008000000000000         # -- Begin function TestTernaryOperatorFloats
	.section	.rdata,"dr",discard,__real@4008000000000000
	.p2align	3, 0x0
__real@4008000000000000:
	.quad	0x4008000000000000              # double 3
	.globl	__real@4004000000000000
	.section	.rdata,"dr",discard,__real@4004000000000000
	.p2align	3, 0x0
__real@4004000000000000:
	.quad	0x4004000000000000              # double 2.5
	.text
	.p2align	4, 0x90
TestTernaryOperatorFloats:              # @TestTernaryOperatorFloats
.seh_proc TestTernaryOperatorFloats
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	movsd	xmm0, qword ptr [rip + __real@4004000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 48], xmm0
	movsd	xmm0, qword ptr [rip + __real@4008000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 40], xmm0
	movsd	xmm1, qword ptr [rsp + 48]      # xmm1 = mem[0],zero
	movsd	xmm0, qword ptr [rsp + 40]      # xmm0 = mem[0],zero
	movsd	xmm3, qword ptr [rsp + 48]      # xmm3 = mem[0],zero
	movsd	xmm2, qword ptr [rsp + 40]      # xmm2 = mem[0],zero
	cmpltsd	xmm0, xmm1
	movaps	xmm1, xmm0
	andpd	xmm1, xmm3
	andnpd	xmm0, xmm2
	orpd	xmm0, xmm1
	movsd	qword ptr [rsp + 32], xmm0
	movsd	xmm0, qword ptr [rsp + 32]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@4008000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	TestTernaryOperatorBools;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestTernaryOperatorBools
TestTernaryOperatorBools:               # @TestTernaryOperatorBools
.seh_proc TestTernaryOperatorBools
# %bb.0:                                # %entry
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	byte ptr [rsp + 71], 1
	mov	qword ptr [rsp + 56], 5
	mov	qword ptr [rsp + 48], 10
	mov	cl, byte ptr [rsp + 71]
	mov	rax, qword ptr [rsp + 56]
	test	cl, 1
	cmove	rax, qword ptr [rsp + 48]
	mov	qword ptr [rsp + 40], rax
	cmp	qword ptr [rsp + 40], 5
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 72
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
	call	TestTernaryOperatorIntegers
	call	TestTernaryOperatorFloats
	call	TestTernaryOperatorBools
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestTernaryOperatorIntegers
	.addrsig_sym TestTernaryOperatorFloats
	.addrsig_sym TestTernaryOperatorBools
	.globl	_fltused
