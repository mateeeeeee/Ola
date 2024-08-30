	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	TestIntIncrementDecrement;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestIntIncrementDecrement
TestIntIncrementDecrement:              # @TestIntIncrementDecrement
.seh_proc TestIntIncrementDecrement
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	rax, qword ptr [rip + GlobalInt1]
	add	rax, 1
	mov	qword ptr [rip + GlobalInt1], rax
	cmp	rax, 6
	sete	cl
	call	Assert
	cmp	qword ptr [rip + GlobalInt1], 6
	sete	cl
	call	Assert
	mov	rax, qword ptr [rip + GlobalInt2]
	add	rax, -1
	mov	qword ptr [rip + GlobalInt2], rax
	cmp	rax, 9
	sete	cl
	call	Assert
	cmp	qword ptr [rip + GlobalInt2], 9
	sete	cl
	call	Assert
	mov	rax, qword ptr [rip + GlobalInt1]
	mov	rcx, rax
	add	rcx, 1
	mov	qword ptr [rip + GlobalInt1], rcx
	cmp	rax, 6
	sete	cl
	call	Assert
	cmp	qword ptr [rip + GlobalInt1], 7
	sete	cl
	call	Assert
	mov	rax, qword ptr [rip + GlobalInt2]
	mov	rcx, rax
	add	rcx, -1
	mov	qword ptr [rip + GlobalInt2], rcx
	cmp	rax, 9
	sete	cl
	call	Assert
	cmp	qword ptr [rip + GlobalInt2], 8
	sete	cl
	call	Assert
	nop
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.def	TestFloatIncrementDecrement;
	.scl	3;
	.type	32;
	.endef
	.globl	__real@401e000000000000         # -- Begin function TestFloatIncrementDecrement
	.section	.rdata,"dr",discard,__real@401e000000000000
	.p2align	3, 0x0
__real@401e000000000000:
	.quad	0x401e000000000000              # double 7.5
	.globl	__real@4021000000000000
	.section	.rdata,"dr",discard,__real@4021000000000000
	.p2align	3, 0x0
__real@4021000000000000:
	.quad	0x4021000000000000              # double 8.5
	.globl	__real@bff0000000000000
	.section	.rdata,"dr",discard,__real@bff0000000000000
	.p2align	3, 0x0
__real@bff0000000000000:
	.quad	0xbff0000000000000              # double -1
	.globl	__real@4012000000000000
	.section	.rdata,"dr",discard,__real@4012000000000000
	.p2align	3, 0x0
__real@4012000000000000:
	.quad	0x4012000000000000              # double 4.5
	.globl	__real@400c000000000000
	.section	.rdata,"dr",discard,__real@400c000000000000
	.p2align	3, 0x0
__real@400c000000000000:
	.quad	0x400c000000000000              # double 3.5
	.globl	__real@3ff0000000000000
	.section	.rdata,"dr",discard,__real@3ff0000000000000
	.p2align	3, 0x0
__real@3ff0000000000000:
	.quad	0x3ff0000000000000              # double 1
	.text
	.p2align	4, 0x90
TestFloatIncrementDecrement:            # @TestFloatIncrementDecrement
.seh_proc TestFloatIncrementDecrement
# %bb.0:                                # %entry
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	movsd	xmm0, qword ptr [rip + GlobalFloat1] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 64], xmm0
	movsd	xmm1, qword ptr [rip + __real@3ff0000000000000] # xmm1 = mem[0],zero
	addsd	xmm0, xmm1
	movsd	qword ptr [rip + GlobalFloat1], xmm0
	mov	rax, qword ptr [rsp + 64]
	mov	qword ptr [rsp + 56], rax
	movsd	xmm0, qword ptr [rsp + 56]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@400c000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	movsd	xmm0, qword ptr [rip + GlobalFloat1] # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@4012000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	movsd	xmm0, qword ptr [rip + GlobalFloat2] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 48], xmm0
	movsd	xmm1, qword ptr [rip + __real@bff0000000000000] # xmm1 = mem[0],zero
	addsd	xmm0, xmm1
	movsd	qword ptr [rip + GlobalFloat2], xmm0
	mov	rax, qword ptr [rsp + 48]
	mov	qword ptr [rsp + 40], rax
	movsd	xmm0, qword ptr [rsp + 40]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@4021000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	movsd	xmm0, qword ptr [rip + GlobalFloat2] # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@401e000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
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
	call	TestIntIncrementDecrement
	call	TestFloatIncrementDecrement
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.data
	.p2align	3, 0x0                          # @GlobalInt1
GlobalInt1:
	.quad	5                               # 0x5

	.p2align	3, 0x0                          # @GlobalInt2
GlobalInt2:
	.quad	10                              # 0xa

	.p2align	3, 0x0                          # @GlobalFloat1
GlobalFloat1:
	.quad	0x400c000000000000              # double 3.5

	.p2align	3, 0x0                          # @GlobalFloat2
GlobalFloat2:
	.quad	0x4021000000000000              # double 8.5

	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestIntIncrementDecrement
	.addrsig_sym TestFloatIncrementDecrement
	.addrsig_sym GlobalInt1
	.addrsig_sym GlobalInt2
	.addrsig_sym GlobalFloat1
	.addrsig_sym GlobalFloat2
	.globl	_fltused
