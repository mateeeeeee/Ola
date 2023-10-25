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
	subq	$56, %rsp
	.seh_stackalloc 56
	.seh_endprologue
	movq	$47, 40(%rsp)
	cmpq	$47, 40(%rsp)
	sete	%cl
	callq	Assert
	movq	$15, 40(%rsp)
	cmpq	$15, 40(%rsp)
	sete	%cl
	callq	Assert
	movq	$4, 40(%rsp)
	cmpq	$4, 40(%rsp)
	sete	%cl
	callq	Assert
	movq	$6, 40(%rsp)
	cmpq	$6, 40(%rsp)
	sete	%cl
	callq	Assert
	movq	$5, 40(%rsp)
	movq	40(%rsp), %rax
	shlq	$2, %rax
	movq	%rax, 40(%rsp)
	cmpq	$20, 40(%rsp)
	sete	%cl
	callq	Assert
	movq	$7, 40(%rsp)
	movq	40(%rsp), %rax
	movl	$3, %ecx
	cqto
	idivq	%rcx
	movq	%rax, 40(%rsp)
	cmpq	$2, 40(%rsp)
	sete	%cl
	callq	Assert
	movq	$24, 40(%rsp)
	movq	40(%rsp), %rax
	movl	$5, %ecx
	cqto
	idivq	%rcx
	movq	%rdx, 40(%rsp)
	cmpq	$4, 40(%rsp)
	sete	%cl
	callq	Assert
	movq	$0, 48(%rsp)
# %bb.1:                                # %exit
	movq	48(%rsp), %rax
	addq	$56, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
