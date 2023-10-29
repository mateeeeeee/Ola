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
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	$5, 56(%rsp)
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	subq	56(%rsp), %rax
	movq	%rax, 48(%rsp)
	cmpq	$-5, 48(%rsp)
	sete	%cl
	callq	Assert
	movq	$10, 40(%rsp)
	movq	40(%rsp), %rax
	movq	%rax, 32(%rsp)
	cmpq	$10, 32(%rsp)
	sete	%cl
	callq	Assert
	movq	$0, 64(%rsp)
# %bb.1:                                # %exit
	movq	64(%rsp), %rax
	addq	$72, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
