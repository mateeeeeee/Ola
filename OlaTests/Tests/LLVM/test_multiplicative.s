	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_multiplicative.ola"
	.def	TestMultiplication;
	.scl	3;
	.type	32;
	.endef
	.globl	__real@400e000000000000         # -- Begin function TestMultiplication
	.section	.rdata,"dr",discard,__real@400e000000000000
	.p2align	3, 0x0
__real@400e000000000000:
	.quad	0x400e000000000000              # double 3.75
	.globl	__real@3ff8000000000000
	.section	.rdata,"dr",discard,__real@3ff8000000000000
	.p2align	3, 0x0
__real@3ff8000000000000:
	.quad	0x3ff8000000000000              # double 1.5
	.globl	__real@4008000000000000
	.section	.rdata,"dr",discard,__real@4008000000000000
	.p2align	3, 0x0
__real@4008000000000000:
	.quad	0x4008000000000000              # double 3
	.globl	__real@3ff3333333333333
	.section	.rdata,"dr",discard,__real@3ff3333333333333
	.p2align	3, 0x0
__real@3ff3333333333333:
	.quad	0x3ff3333333333333              # double 1.2
	.globl	__real@4004000000000000
	.section	.rdata,"dr",discard,__real@4004000000000000
	.p2align	3, 0x0
__real@4004000000000000:
	.quad	0x4004000000000000              # double 2.5
	.text
	.p2align	4, 0x90
TestMultiplication:                     # @TestMultiplication
.seh_proc TestMultiplication
# %bb.0:                                # %entry
	sub	rsp, 88
	.seh_stackalloc 88
	.seh_endprologue
	mov	qword ptr [rsp + 80], 5
	mov	qword ptr [rsp + 72], 3
	movsd	xmm0, qword ptr [rip + __real@4004000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 64], xmm0
	movsd	xmm0, qword ptr [rip + __real@3ff3333333333333] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 56], xmm0
	mov	rax, qword ptr [rsp + 80]
	imul	rax, qword ptr [rsp + 72]
	mov	qword ptr [rsp + 48], rax
	cmp	qword ptr [rsp + 48], 15
	sete	cl
	call	Assert
	movsd	xmm0, qword ptr [rsp + 64]      # xmm0 = mem[0],zero
	mulsd	xmm0, qword ptr [rsp + 56]
	movsd	qword ptr [rsp + 40], xmm0
	movsd	xmm0, qword ptr [rsp + 40]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@4008000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	mov	rax, qword ptr [rsp + 80]
	shl	rax
	mov	qword ptr [rsp + 80], rax
	cmp	qword ptr [rsp + 80], 10
	sete	cl
	call	Assert
	movsd	xmm0, qword ptr [rip + __real@3ff8000000000000] # xmm0 = mem[0],zero
	mulsd	xmm0, qword ptr [rsp + 64]
	movsd	qword ptr [rsp + 64], xmm0
	movsd	xmm0, qword ptr [rsp + 64]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@400e000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 88
	ret
	.seh_endproc
                                        # -- End function
	.def	TestDivision;
	.scl	3;
	.type	32;
	.endef
	.globl	__real@4000000000000000         # -- Begin function TestDivision
	.section	.rdata,"dr",discard,__real@4000000000000000
	.p2align	3, 0x0
__real@4000000000000000:
	.quad	0x4000000000000000              # double 2
	.globl	__real@4014000000000000
	.section	.rdata,"dr",discard,__real@4014000000000000
	.p2align	3, 0x0
__real@4014000000000000:
	.quad	0x4014000000000000              # double 5
	.text
	.p2align	4, 0x90
TestDivision:                           # @TestDivision
.seh_proc TestDivision
# %bb.0:                                # %entry
	sub	rsp, 88
	.seh_stackalloc 88
	.seh_endprologue
	mov	qword ptr [rsp + 80], 15
	mov	qword ptr [rsp + 72], 3
	movsd	xmm0, qword ptr [rip + __real@4014000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 64], xmm0
	movsd	xmm0, qword ptr [rip + __real@4000000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 56], xmm0
	mov	rax, qword ptr [rsp + 80]
	cqo
	idiv	qword ptr [rsp + 72]
	mov	qword ptr [rsp + 48], rax
	cmp	qword ptr [rsp + 48], 5
	sete	cl
	call	Assert
	movsd	xmm0, qword ptr [rsp + 64]      # xmm0 = mem[0],zero
	divsd	xmm0, qword ptr [rsp + 56]
	movsd	qword ptr [rsp + 40], xmm0
	movsd	xmm0, qword ptr [rsp + 40]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@4004000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	mov	rax, qword ptr [rsp + 80]
	mov	ecx, 2
	cqo
	idiv	rcx
	mov	qword ptr [rsp + 80], rax
	cmp	qword ptr [rsp + 80], 7
	sete	cl
	call	Assert
	movsd	xmm0, qword ptr [rsp + 64]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@4000000000000000] # xmm1 = mem[0],zero
	divsd	xmm0, xmm1
	movsd	qword ptr [rsp + 64], xmm0
# %bb.1:                                # %exit
	add	rsp, 88
	ret
	.seh_endproc
                                        # -- End function
	.def	TestModulo;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestModulo
TestModulo:                             # @TestModulo
.seh_proc TestModulo
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], 17
	mov	qword ptr [rsp + 40], 4
	mov	rax, qword ptr [rsp + 48]
	cqo
	idiv	qword ptr [rsp + 40]
	mov	qword ptr [rsp + 32], rdx
	cmp	qword ptr [rsp + 32], 1
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 48]
	mov	ecx, 3
	cqo
	idiv	rcx
	mov	qword ptr [rsp + 48], rdx
	cmp	qword ptr [rsp + 48], 2
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
	call	TestMultiplication
	call	TestDivision
	call	TestModulo
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestMultiplication
	.addrsig_sym TestDivision
	.addrsig_sym TestModulo
	.globl	_fltused
