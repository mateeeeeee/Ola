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
	movq	$0, 56(%rsp)
	cmpq	$0, 56(%rsp)
	sete	%cl
	callq	Assert
	movq	$1, 56(%rsp)
	cmpq	$1, 56(%rsp)
	sete	%cl
	callq	Assert
	movq	$2, 56(%rsp)
	cmpq	$2, 56(%rsp)
	sete	%cl
	callq	Assert
	movq	$0, 48(%rsp)
	cmpq	$0, 48(%rsp)
	sete	%cl
	callq	Assert
	movq	$5, 48(%rsp)
	cmpq	$5, 48(%rsp)
	sete	%cl
	callq	Assert
	movq	$3, 48(%rsp)
	cmpq	$3, 48(%rsp)
	sete	%cl
	callq	Assert
	movq	$4, 48(%rsp)
	cmpq	$4, 48(%rsp)
	sete	%cl
	callq	Assert
	movl	$1, %ecx
	callq	Assert
	movq	$0, 40(%rsp)
	cmpq	$0, 40(%rsp)
	sete	%cl
	callq	Assert
	movq	$1, 40(%rsp)
	cmpq	$1, 40(%rsp)
	sete	%cl
	callq	Assert
	movq	$2, 40(%rsp)
	cmpq	$2, 40(%rsp)
	sete	%cl
	callq	Assert
	movq	$0, 32(%rsp)
	cmpq	$0, 32(%rsp)
	sete	%cl
	callq	Assert
	movq	$1, 32(%rsp)
	cmpq	$1, 32(%rsp)
	sete	%cl
	callq	Assert
	movq	$3, 32(%rsp)
	cmpq	$3, 32(%rsp)
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
