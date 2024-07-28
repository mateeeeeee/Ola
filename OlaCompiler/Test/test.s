	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	add__I__I;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function add__I__I
add__I__I:                              # @add__I__I
# %bb.0:                                # %entry
	mov	rax, rcx
	add	rax, rdx
	ret
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
	mov	ecx, 5
	mov	edx, 7
	call	add__I__I
	add	rax, 10
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym add__I__I
