	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_plusminus.ola"
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	__real@c024000000000000         # -- Begin function main
	.section	.rdata,"dr",discard,__real@c024000000000000
	.p2align	3, 0x0
__real@c024000000000000:
	.quad	0xc024000000000000              # double -10
	.globl	__real@4024000000000000
	.section	.rdata,"dr",discard,__real@4024000000000000
	.p2align	3, 0x0
__real@4024000000000000:
	.quad	0x4024000000000000              # double 10
	.text
	.globl	main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	sub	rsp, 104
	.seh_stackalloc 104
	.seh_endprologue
	mov	qword ptr [rsp + 88], 5
	xor	eax, eax
                                        # kill: def $rax killed $eax
	sub	rax, qword ptr [rsp + 88]
	mov	qword ptr [rsp + 80], rax
	cmp	qword ptr [rsp + 80], -5
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 72], 10
	mov	rax, qword ptr [rsp + 72]
	mov	qword ptr [rsp + 64], rax
	cmp	qword ptr [rsp + 64], 10
	sete	cl
	call	Assert
	movsd	xmm0, qword ptr [rip + __real@4024000000000000] # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 56], xmm0
	movsd	xmm0, qword ptr [rsp + 56]      # xmm0 = mem[0],zero
	movsd	qword ptr [rsp + 48], xmm0
	movsd	xmm0, qword ptr [rsp + 48]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@4024000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	movsd	xmm0, qword ptr [rsp + 56]      # xmm0 = mem[0],zero
	movq	rax, xmm0
	movabs	rcx, -9223372036854775808
	xor	rax, rcx
	movq	xmm0, rax
	movsd	qword ptr [rsp + 40], xmm0
	movsd	xmm0, qword ptr [rsp + 40]      # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@c024000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	mov	qword ptr [rsp + 96], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 96]
	add	rsp, 104
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.globl	_fltused
