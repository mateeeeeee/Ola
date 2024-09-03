	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	TestTernaryOperatorIntegers;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestTernaryOperatorIntegers
TestTernaryOperatorIntegers:            # @TestTernaryOperatorIntegers
.seh_proc TestTernaryOperatorIntegers
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	ecx, 1
	call	Assert
	mov	rcx, qword ptr [rip + GlobalIntB]
	mov	rax, rcx
	sub	rax, 6
	mov	eax, 5
	cmovge	rax, rcx
	cmp	rax, 7
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rip + GlobalIntA]
	mov	rax, qword ptr [rip + GlobalIntB]
	mov	rdx, rcx
	sub	rdx, rax
	cmovg	rax, rcx
	cmp	rax, 12
	sete	cl
	call	Assert
	cmp	qword ptr [rip + GlobalIntA], 16
	setl	cl
	call	Assert
	mov	ecx, 1
	call	Assert
	nop
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.def	TestTernaryOperatorFloats;
	.scl	3;
	.type	32;
	.endef
	.globl	__real@4014000000000000         # -- Begin function TestTernaryOperatorFloats
	.section	.rdata,"dr",discard,__real@4014000000000000
	.p2align	3, 0x0
__real@4014000000000000:
	.quad	0x4014000000000000              # double 5
	.globl	__real@4022000000000000
	.section	.rdata,"dr",discard,__real@4022000000000000
	.p2align	3, 0x0
__real@4022000000000000:
	.quad	0x4022000000000000              # double 9
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
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	ecx, 1
	call	Assert
	movsd	xmm2, qword ptr [rip + GlobalFloatD] # xmm2 = mem[0],zero
	movsd	xmm3, qword ptr [rip + __real@4004000000000000] # xmm3 = mem[0],zero
	movaps	xmm0, xmm2
	cmpltsd	xmm0, xmm3
	movaps	xmm1, xmm0
	andpd	xmm1, xmm3
	andnpd	xmm0, xmm2
	orpd	xmm0, xmm1
	movsd	xmm1, qword ptr [rip + __real@4022000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	movsd	xmm3, qword ptr [rip + GlobalFloatC] # xmm3 = mem[0],zero
	movsd	xmm2, qword ptr [rip + GlobalFloatD] # xmm2 = mem[0],zero
	movaps	xmm0, xmm2
	cmpltsd	xmm0, xmm3
	movaps	xmm1, xmm0
	andpd	xmm1, xmm3
	andnpd	xmm0, xmm2
	orpd	xmm0, xmm1
	movsd	xmm1, qword ptr [rip + __real@4022000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	movsd	xmm3, qword ptr [rip + GlobalFloatC] # xmm3 = mem[0],zero
	movsd	xmm2, qword ptr [rip + __real@4014000000000000] # xmm2 = mem[0],zero
	movaps	xmm0, xmm2
	cmpltsd	xmm0, xmm3
	movaps	xmm1, xmm0
	andpd	xmm1, xmm3
	andnpd	xmm0, xmm2
	orpd	xmm0, xmm1
	movsd	xmm1, qword ptr [rip + __real@4014000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	mov	ecx, 1
	call	Assert
	nop
	add	rsp, 40
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
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	ecx, 1
	call	Assert
	mov	cl, byte ptr [rip + GlobalCondition]
	xor	cl, -1
	call	Assert
	mov	cl, byte ptr [rip + GlobalCondition]
	mov	rax, qword ptr [rip + GlobalIntA]
	test	cl, 1
	cmove	rax, qword ptr [rip + GlobalIntB]
	cmp	rax, 7
	sete	cl
	call	Assert
	mov	cl, byte ptr [rip + GlobalCondition]
	xor	cl, -1
	call	Assert
	mov	ecx, 1
	call	Assert
	nop
	add	rsp, 40
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
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.data
	.p2align	3, 0x0                          # @GlobalIntA
GlobalIntA:
	.quad	12                              # 0xc

	.p2align	3, 0x0                          # @GlobalIntB
GlobalIntB:
	.quad	7                               # 0x7

	.p2align	3, 0x0                          # @GlobalFloatC
GlobalFloatC:
	.quad	0x4012000000000000              # double 4.5

	.p2align	3, 0x0                          # @GlobalFloatD
GlobalFloatD:
	.quad	0x4022000000000000              # double 9

	.lcomm	GlobalCondition,1               # @GlobalCondition
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestTernaryOperatorIntegers
	.addrsig_sym TestTernaryOperatorFloats
	.addrsig_sym TestTernaryOperatorBools
	.addrsig_sym GlobalIntA
	.addrsig_sym GlobalIntB
	.addrsig_sym GlobalFloatC
	.addrsig_sym GlobalFloatD
	.addrsig_sym GlobalCondition
	.globl	_fltused
