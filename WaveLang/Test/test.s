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
.LBB0_1:                                # %dowhile.body
                                        # =>This Inner Loop Header: Depth=1
	movq	8(%rsp), %rax
	addq	$2, %rax
	movq	%rax, 8(%rsp)
# %bb.2:                                # %dowhile.cond
                                        #   in Loop: Header=BB0_1 Depth=1
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	testb	$1, %al
	jne	.LBB0_1
	jmp	.LBB0_3
.LBB0_3:                                # %dowhile.end
	movq	8(%rsp), %rax
	movq	%rax, 16(%rsp)
# %bb.4:                                # %exit
	movq	16(%rsp), %rax
	addq	$24, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
