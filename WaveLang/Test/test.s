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
	movq	$0, 8(%rsp)
	movq	$0, (%rsp)
	jmp	.LBB0_2
.LBB0_1:                                # %for.body
                                        #   in Loop: Header=BB0_2 Depth=1
	jmp	.LBB0_3
.LBB0_2:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	cmpq	$10, (%rsp)
	jl	.LBB0_1
	jmp	.LBB0_4
.LBB0_3:                                # %for.iter
                                        #   in Loop: Header=BB0_2 Depth=1
	movq	(%rsp), %rax
	addq	$1, %rax
	movq	%rax, (%rsp)
	movq	8(%rsp), %rax
	addq	$2, %rax
	movq	%rax, 8(%rsp)
	jmp	.LBB0_2
.LBB0_4:                                # %for.end
	movq	8(%rsp), %rax
	movq	%rax, 16(%rsp)
# %bb.5:                                # %exit
	movq	16(%rsp), %rax
	addq	$24, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
