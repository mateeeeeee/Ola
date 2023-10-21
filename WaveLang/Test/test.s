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
	movq	$0, 16(%rsp)
	movq	$0, 8(%rsp)
# %bb.1:                                # %switch.header
	movq	16(%rsp), %rax
	movq	%rax, (%rsp)                    # 8-byte Spill
	testq	%rax, %rax
	je	.LBB0_4
	jmp	.LBB0_7
.LBB0_7:                                # %switch.header
	movq	(%rsp), %rax                    # 8-byte Reload
	subq	$1, %rax
	je	.LBB0_5
	jmp	.LBB0_2
.LBB0_2:                                # %switch.default
	movq	$5, 8(%rsp)
# %bb.3:                                # %switch.end
	movq	8(%rsp), %rax
	movq	%rax, 24(%rsp)
	jmp	.LBB0_6
.LBB0_4:                                # %switch.case0
	movq	$10, 8(%rsp)
.LBB0_5:                                # %switch.case1
	movq	$15, 8(%rsp)
	jmp	.LBB0_2
.LBB0_6:                                # %exit
	movq	24(%rsp), %rax
	addq	$32, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
