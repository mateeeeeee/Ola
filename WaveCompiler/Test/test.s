	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"WaveModule"
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	movq	$0, 24(%rsp)
# %bb.1:                                # %exit
	movq	24(%rsp), %rax
	addq	$32, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig