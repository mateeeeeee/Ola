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
	subq	$24, %rsp
	.seh_stackalloc 24
	.seh_endprologue
	movq	$100, 8(%rsp)
	cmpq	$0, 8(%rsp)
	setne	%al
	andb	$1, %al
	movb	%al, 7(%rsp)
	movb	7(%rsp), %al
	andb	$1, %al
	movzbl	%al, %eax
                                        # kill: def $rax killed $eax
	movq	%rax, 16(%rsp)
# %bb.1:                                # %exit
	movq	16(%rsp), %rax
	addq	$24, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
