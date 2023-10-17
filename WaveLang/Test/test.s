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
	subq	$16, %rsp
	.seh_stackalloc 16
	.seh_endprologue
	movq	$10, 8(%rsp)
	movq	8(%rsp), %rax
	subq	$10, %rax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	addq	$1, %rax
	cmpq	$0, %rax
	je	.LBB0_2
# %bb.1:                                # %if.then
	movq	(%rsp), %rax
	addq	$5, %rax
	movq	%rax, (%rsp)
	movq	(%rsp), %rax
	imulq	(%rsp), %rax
	addq	$16, %rsp
	retq
.LBB0_2:                                # %if.else
	movq	8(%rsp), %rax
	addq	$5, %rax
	movq	%rax, 8(%rsp)
	movq	8(%rsp), %rax
	imulq	8(%rsp), %rax
	addq	$16, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
