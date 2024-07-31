	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_additive.ola"
	.def	TestIntAddition;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIntAddition
TestIntAddition:                        # @TestIntAddition
.seh_proc TestIntAddition
# %bb.0:                                # %entry
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 64], 5
	mov	qword ptr [rsp + 56], 10
	mov	rax, qword ptr [rsp + 64]
	add	rax, qword ptr [rsp + 56]
	mov	qword ptr [rsp + 48], rax
	cmp	qword ptr [rsp + 48], 15
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 40], 7
	mov	rax, qword ptr [rsp + 64]
	add	rax, qword ptr [rsp + 40]
	mov	qword ptr [rsp + 64], rax
	cmp	qword ptr [rsp + 64], 12
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.def	TestIntSubtraction;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIntSubtraction
TestIntSubtraction:                     # @TestIntSubtraction
.seh_proc TestIntSubtraction
# %bb.0:                                # %entry
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 64], 15
	mov	qword ptr [rsp + 56], 7
	mov	rax, qword ptr [rsp + 64]
	sub	rax, qword ptr [rsp + 56]
	mov	qword ptr [rsp + 48], rax
	cmp	qword ptr [rsp + 48], 8
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 40], 3
	mov	rax, qword ptr [rsp + 64]
	sub	rax, qword ptr [rsp + 40]
	mov	qword ptr [rsp + 64], rax
	cmp	qword ptr [rsp + 64], 12
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.def	TestFloatAddition;
	.scl	3;
	.type	32;
	.endef
	.globl	__real@4012cccccccccccd         # -- Begin function TestFloatAddition
	.section	.rdata,"dr",discard,__real@4012cccccccccccd
	.p2align	3, 0x0
__real@4012cccccccccccd:
	.quad	0x4012cccccccccccd              # double 4.7000000000000002
	.globl	__real@3ff3333333333333
	.section	.rdata,"dr",discard,__real@3ff3333333333333
	.p2align	3, 0x0
__real@3ff3333333333333:
	.quad	0x3ff3333333333333              # double 1.2
	.globl	__real@4018000000000000
	.section	.rdata,"dr",discard,__real@4018000000000000
	.p2align	3, 0x0
__real@4018000000000000:
	.quad	0x4018000000000000              # double 6
	.globl	__real@4004000000000000
	.section	.rdata,"dr",discard,__real@4004000000000000
	.p2align	3, 0x0
__real@4004000000000000:
	.quad	0x4004000000000000              # double 2.5
	.globl	__real@400c000000000000
	.section	.rdata,"dr",discard,__real@400c000000000000
	.p2align	3, 0x0
__real@400c000000000000:
	.quad	0x400c000000000000              # double 3.5
	.text
	.p2align	4, 0x90
TestFloatAddition:                      # @TestFloatAddition
.seh_proc TestFloatAddition
# %bb.0:                                # %entry
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	movsd	xmm0, qword ptr [rip + __real@400c000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 64], xmm0
	movsd	xmm0, qword ptr [rip + __real@4004000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 56], xmm0
	movsd	xmm0, qword ptr [rsp + 64]      # xmm0 = mem[0],zero
	addsd	xmm0, qword ptr [rsp + 56]
	movsd	qword ptr [rsp + 48], xmm0
	movsd	xmm0, qword ptr [rsp + 48]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@4018000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	movsd	xmm0, qword ptr [rip + __real@3ff3333333333333] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 40], xmm0
	movsd	xmm0, qword ptr [rsp + 64]      # xmm0 = mem[0],zero
	addsd	xmm0, qword ptr [rsp + 40]
	movsd	qword ptr [rsp + 64], xmm0
	movsd	xmm0, qword ptr [rsp + 64]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@4012cccccccccccd] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.def	TestFloatSubtraction;
	.scl	3;
	.type	32;
	.endef
	.globl	__real@400e666666666666         # -- Begin function TestFloatSubtraction
	.section	.rdata,"dr",discard,__real@400e666666666666
	.p2align	3, 0x0
__real@400e666666666666:
	.quad	0x400e666666666666              # double 3.7999999999999998
	.globl	__real@4014000000000000
	.section	.rdata,"dr",discard,__real@4014000000000000
	.p2align	3, 0x0
__real@4014000000000000:
	.quad	0x4014000000000000              # double 5
	.text
	.p2align	4, 0x90
TestFloatSubtraction:                   # @TestFloatSubtraction
.seh_proc TestFloatSubtraction
# %bb.0:                                # %entry
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	movsd	xmm0, qword ptr [rip + __real@4014000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 64], xmm0
	movsd	xmm0, qword ptr [rip + __real@4004000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 56], xmm0
	movsd	xmm0, qword ptr [rsp + 64]      # xmm0 = mem[0],zero
	subsd	xmm0, qword ptr [rsp + 56]
	movsd	qword ptr [rsp + 48], xmm0
	movsd	xmm0, qword ptr [rsp + 48]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@4004000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	movsd	xmm0, qword ptr [rip + __real@3ff3333333333333] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 40], xmm0
	movsd	xmm0, qword ptr [rsp + 64]      # xmm0 = mem[0],zero
	subsd	xmm0, qword ptr [rsp + 40]
	movsd	qword ptr [rsp + 64], xmm0
	movsd	xmm0, qword ptr [rsp + 64]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@400e666666666666] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
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
	call	TestIntAddition
	call	TestIntSubtraction
	call	TestFloatAddition
	call	TestFloatSubtraction
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestIntAddition
	.addrsig_sym TestIntSubtraction
	.addrsig_sym TestFloatAddition
	.addrsig_sym TestFloatSubtraction
	.globl	_fltused
