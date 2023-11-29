	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.wv"
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	mov	eax, 24
	mov	qword ptr [rsp], rax
	mov	rax, qword ptr [rsp]
	pop	rcx
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
