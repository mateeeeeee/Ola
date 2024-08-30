	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	__real@402c000000000000         # -- Begin function main
	.section	.rdata,"dr",discard,__real@402c000000000000
	.p2align	3, 0x0
__real@402c000000000000:
	.quad	0x402c000000000000              # double 14
	.text
	.globl	main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
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
	cmp	qword ptr [rip + GlobalInt], 7
	sete	cl
	call	Assert
	movsd	xmm0, qword ptr [rip + GlobalFloat] # xmm0 = mem[0],zero
	movsd	xmm1, qword ptr [rip + __real@402c000000000000] # xmm1 = mem[0],zero
	ucomisd	xmm0, xmm1
	sete	cl
	setnp	al
	and	cl, al
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.data
	.p2align	3, 0x0                          # @GlobalInt
GlobalInt:
	.quad	7                               # 0x7

	.p2align	3, 0x0                          # @GlobalFloat
GlobalFloat:
	.quad	0x402c000000000000              # double 14

	.addrsig
	.addrsig_sym Assert
	.addrsig_sym GlobalInt
	.addrsig_sym GlobalFloat
	.globl	_fltused
