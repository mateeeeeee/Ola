	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_relational.ola"
	.def	TestLessThanOperators;
	.scl	3;
	.type	32;
	.endef
	.globl	__real@4014000000000000         # -- Begin function TestLessThanOperators
	.section	.rdata,"dr",discard,__real@4014000000000000
	.p2align	3, 0x0
__real@4014000000000000:
	.quad	0x4014000000000000              # double 5
	.globl	__real@4004000000000000
	.section	.rdata,"dr",discard,__real@4004000000000000
	.p2align	3, 0x0
__real@4004000000000000:
	.quad	0x4004000000000000              # double 2.5
	.text
	.p2align	4, 0x90
TestLessThanOperators:                  # @TestLessThanOperators
.seh_proc TestLessThanOperators
# %bb.0:                                # %entry
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 64], 5
	mov	qword ptr [rsp + 56], 10
	movsd	xmm0, qword ptr [rip + __real@4004000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 48], xmm0
	movsd	xmm0, qword ptr [rip + __real@4014000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 40], xmm0
	mov	rax, qword ptr [rsp + 64]
	cmp	rax, qword ptr [rsp + 56]
	setl	cl
	call	Assert
	movsd	xmm1, qword ptr [rsp + 48]      # xmm1 = mem[0],zero
	movsd	xmm0, qword ptr [rsp + 40]      # xmm0 = mem[0],zero
	ucomisd	xmm0, xmm1
	seta	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.def	TestLessThanOrEqualOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestLessThanOrEqualOperators
TestLessThanOrEqualOperators:           # @TestLessThanOrEqualOperators
.seh_proc TestLessThanOrEqualOperators
# %bb.0:                                # %entry
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 64], 5
	mov	qword ptr [rsp + 56], 10
	movsd	xmm0, qword ptr [rip + __real@4004000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 48], xmm0
	movsd	xmm0, qword ptr [rip + __real@4014000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 40], xmm0
	mov	rax, qword ptr [rsp + 64]
	cmp	rax, qword ptr [rsp + 56]
	setle	cl
	call	Assert
	movsd	xmm1, qword ptr [rsp + 48]      # xmm1 = mem[0],zero
	movsd	xmm0, qword ptr [rsp + 40]      # xmm0 = mem[0],zero
	ucomisd	xmm0, xmm1
	setae	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.def	TestGreaterThanOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestGreaterThanOperators
TestGreaterThanOperators:               # @TestGreaterThanOperators
.seh_proc TestGreaterThanOperators
# %bb.0:                                # %entry
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 64], 5
	mov	qword ptr [rsp + 56], 10
	movabs	rax, 4612811918334230528
	mov	qword ptr [rsp + 48], rax
	movabs	rax, 4617315517961601024
	mov	qword ptr [rsp + 40], rax
	mov	rax, qword ptr [rsp + 64]
	mov	rcx, qword ptr [rsp + 56]
	sub	rax, rcx
	setle	cl
	call	Assert
	movsd	xmm0, qword ptr [rsp + 48]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rsp + 40]      # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	setbe	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.def	TestGreaterThanOrEqualOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestGreaterThanOrEqualOperators
TestGreaterThanOrEqualOperators:        # @TestGreaterThanOrEqualOperators
.seh_proc TestGreaterThanOrEqualOperators
# %bb.0:                                # %entry
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 64], 5
	mov	qword ptr [rsp + 56], 10
	movabs	rax, 4612811918334230528
	mov	qword ptr [rsp + 48], rax
	movabs	rax, 4617315517961601024
	mov	qword ptr [rsp + 40], rax
	mov	rax, qword ptr [rsp + 64]
	mov	rcx, qword ptr [rsp + 56]
	sub	rax, rcx
	setl	cl
	call	Assert
	movsd	xmm0, qword ptr [rsp + 48]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rsp + 40]      # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	setb	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.def	TestEqualOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestEqualOperators
TestEqualOperators:                     # @TestEqualOperators
.seh_proc TestEqualOperators
# %bb.0:                                # %entry
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 64], 5
	mov	qword ptr [rsp + 56], 10
	movabs	rax, 4612811918334230528
	mov	qword ptr [rsp + 48], rax
	movabs	rax, 4617315517961601024
	mov	qword ptr [rsp + 40], rax
	mov	rax, qword ptr [rsp + 64]
	mov	rcx, qword ptr [rsp + 56]
	sub	rax, rcx
	setne	cl
	call	Assert
	movsd	xmm0, qword ptr [rsp + 48]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rsp + 40]      # xmm1 = mem[0],zero
	cmpneqsd	xmm0, xmm1
	movq	rax, xmm0
                                        # kill: def $eax killed $eax killed $rax
	and	eax, 1
	mov	cl, al
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.def	TestNotEqualOperators;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestNotEqualOperators
TestNotEqualOperators:                  # @TestNotEqualOperators
.seh_proc TestNotEqualOperators
# %bb.0:                                # %entry
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 64], 5
	mov	qword ptr [rsp + 56], 10
	movabs	rax, 4612811918334230528
	mov	qword ptr [rsp + 48], rax
	movabs	rax, 4617315517961601024
	mov	qword ptr [rsp + 40], rax
	mov	rax, qword ptr [rsp + 64]
	mov	rcx, qword ptr [rsp + 56]
	sub	rax, rcx
	setne	cl
	call	Assert
	movsd	xmm0, qword ptr [rsp + 48]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rsp + 40]      # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	setne	cl
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
	call	TestLessThanOperators
	call	TestLessThanOrEqualOperators
	call	TestGreaterThanOperators
	call	TestGreaterThanOrEqualOperators
	call	TestEqualOperators
	call	TestNotEqualOperators
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestLessThanOperators
	.addrsig_sym TestLessThanOrEqualOperators
	.addrsig_sym TestGreaterThanOperators
	.addrsig_sym TestGreaterThanOrEqualOperators
	.addrsig_sym TestEqualOperators
	.addrsig_sym TestNotEqualOperators
	.globl	_fltused
