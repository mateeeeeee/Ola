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
	movq	$0, (%rsp)
	movb	$1, %al
	testb	$1, %al
	jne	.LBB0_1
	jmp	.LBB0_2
.LBB0_1:                                # %if.then
	movq	$5, (%rsp)
	jmp	.LBB0_3
.LBB0_2:                                # %if.else
	jmp	.LBB0_3
.LBB0_3:                                # %if.end
	movq	(%rsp), %rax
	movq	%rax, 8(%rsp)
# %bb.4:                                # %exit
	movq	8(%rsp), %rax
	addq	$16, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
