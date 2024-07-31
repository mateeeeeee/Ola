	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_increment.ola"
	.def	TestPreIncrementDecrement;
	.scl	3;
	.type	32;
	.endef
	.globl	__real@401e000000000000         # -- Begin function TestPreIncrementDecrement
	.section	.rdata,"dr",discard,__real@401e000000000000
	.p2align	3, 0x0
__real@401e000000000000:
	.quad	0x401e000000000000              # double 7.5
	.globl	__real@3ff0000000000000
	.section	.rdata,"dr",discard,__real@3ff0000000000000
	.p2align	3, 0x0
__real@3ff0000000000000:
	.quad	0x3ff0000000000000              # double 1
	.globl	__real@4012000000000000
	.section	.rdata,"dr",discard,__real@4012000000000000
	.p2align	3, 0x0
__real@4012000000000000:
	.quad	0x4012000000000000              # double 4.5
	.globl	__real@4021000000000000
	.section	.rdata,"dr",discard,__real@4021000000000000
	.p2align	3, 0x0
__real@4021000000000000:
	.quad	0x4021000000000000              # double 8.5
	.globl	__real@400c000000000000
	.section	.rdata,"dr",discard,__real@400c000000000000
	.p2align	3, 0x0
__real@400c000000000000:
	.quad	0x400c000000000000              # double 3.5
	.text
	.p2align	4, 0x90
TestPreIncrementDecrement:              # @TestPreIncrementDecrement
.seh_proc TestPreIncrementDecrement
# %bb.0:                                # %entry
	sub	rsp, 104
	.seh_stackalloc 104
	.seh_endprologue
	mov	qword ptr [rsp + 96], 5
	mov	qword ptr [rsp + 88], 8
	mov	rax, qword ptr [rsp + 96]
	add	rax, 1
	mov	qword ptr [rsp + 96], rax
	mov	qword ptr [rsp + 80], rax
	cmp	qword ptr [rsp + 80], 6
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 96], 6
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 88]
	sub	rax, 1
	mov	qword ptr [rsp + 88], rax
	mov	qword ptr [rsp + 72], rax
	cmp	qword ptr [rsp + 72], 7
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 88], 7
	sete	cl
	call	Assert
	movsd	xmm0, qword ptr [rip + __real@400c000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 64], xmm0
	movsd	xmm0, qword ptr [rip + __real@4021000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 56], xmm0
	movsd	xmm0, qword ptr [rip + __real@3ff0000000000000] # xmm0 = mem[0],zero
	addsd	xmm0, qword ptr [rsp + 64]
	movsd	qword ptr [rsp + 64], xmm0
	movsd	qword ptr [rsp + 48], xmm0
	movsd	xmm0, qword ptr [rsp + 48]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@4012000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	movsd	xmm0, qword ptr [rsp + 64]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@4012000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	movsd	xmm0, qword ptr [rsp + 56]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@3ff0000000000000] # xmm1 = mem[0],zero
	subsd	xmm0, xmm1
	movsd	qword ptr [rsp + 56], xmm0
	movsd	qword ptr [rsp + 40], xmm0
	movsd	xmm0, qword ptr [rsp + 40]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@401e000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 104
	ret
	.seh_endproc
                                        # -- End function
	.def	TestPostIncrementDecrement;
	.scl	3;
	.type	32;
	.endef
	.globl	__real@4027000000000000         # -- Begin function TestPostIncrementDecrement
	.section	.rdata,"dr",discard,__real@4027000000000000
	.p2align	3, 0x0
__real@4027000000000000:
	.quad	0x4027000000000000              # double 11.5
	.globl	__real@4029000000000000
	.section	.rdata,"dr",discard,__real@4029000000000000
	.p2align	3, 0x0
__real@4029000000000000:
	.quad	0x4029000000000000              # double 12.5
	.globl	__real@401a000000000000
	.section	.rdata,"dr",discard,__real@401a000000000000
	.p2align	3, 0x0
__real@401a000000000000:
	.quad	0x401a000000000000              # double 6.5
	.text
	.p2align	4, 0x90
TestPostIncrementDecrement:             # @TestPostIncrementDecrement
.seh_proc TestPostIncrementDecrement
# %bb.0:                                # %entry
	sub	rsp, 136
	.seh_stackalloc 136
	.seh_endprologue
	mov	qword ptr [rsp + 128], 10
	mov	qword ptr [rsp + 120], 15
	mov	rax, qword ptr [rsp + 128]
	mov	rcx, qword ptr [rsp + 128]
	mov	qword ptr [rsp + 112], rcx
	add	rax, 1
	mov	qword ptr [rsp + 128], rax
	mov	rax, qword ptr [rsp + 112]
	mov	qword ptr [rsp + 104], rax
	cmp	qword ptr [rsp + 104], 10
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 128], 11
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 120]
	mov	rcx, qword ptr [rsp + 120]
	mov	qword ptr [rsp + 96], rcx
	sub	rax, 1
	mov	qword ptr [rsp + 120], rax
	mov	rax, qword ptr [rsp + 96]
	mov	qword ptr [rsp + 88], rax
	cmp	qword ptr [rsp + 88], 15
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 120], 14
	sete	cl
	call	Assert
	movsd	xmm0, qword ptr [rip + __real@401a000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 80], xmm0
	movsd	xmm0, qword ptr [rip + __real@4029000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 72], xmm0
	movsd	xmm0, qword ptr [rsp + 80]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rsp + 80]      # xmm1 = mem[0],zero
	movsd	qword ptr [rsp + 64], xmm1
	movsd	xmm1, qword ptr [rip + __real@3ff0000000000000] # xmm1 = mem[0],zero
	addsd	xmm0, xmm1
	movsd	qword ptr [rsp + 80], xmm0
	mov	rax, qword ptr [rsp + 64]
	mov	qword ptr [rsp + 56], rax
	movsd	xmm0, qword ptr [rsp + 56]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@401a000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	movsd	xmm0, qword ptr [rsp + 80]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@401e000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	movsd	xmm0, qword ptr [rsp + 72]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rsp + 72]      # xmm1 = mem[0],zero
	movsd	qword ptr [rsp + 48], xmm1
	movsd	xmm1, qword ptr [rip + __real@3ff0000000000000] # xmm1 = mem[0],zero
	subsd	xmm0, xmm1
	movsd	qword ptr [rsp + 72], xmm0
	mov	rax, qword ptr [rsp + 48]
	mov	qword ptr [rsp + 40], rax
	movsd	xmm0, qword ptr [rsp + 40]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@4029000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	movsd	xmm0, qword ptr [rsp + 72]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@4027000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 136
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
	call	TestPreIncrementDecrement
	call	TestPostIncrementDecrement
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestPreIncrementDecrement
	.addrsig_sym TestPostIncrementDecrement
	.globl	_fltused
