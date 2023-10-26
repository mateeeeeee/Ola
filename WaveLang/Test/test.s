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
	movq	$2, 40(%rsp)
# %bb.1:                                # %switch.header
	movq	40(%rsp), %rax
	movq	%rax, 32(%rsp)                  # 8-byte Spill
	subq	$1, %rax
	je	.LBB0_4
	jmp	.LBB0_8
.LBB0_8:                                # %switch.header
	movq	32(%rsp), %rax                  # 8-byte Reload
	subq	$2, %rax
	je	.LBB0_5
	jmp	.LBB0_9
.LBB0_9:                                # %switch.header
	movq	32(%rsp), %rax                  # 8-byte Reload
	subq	$3, %rax
	je	.LBB0_6
	jmp	.LBB0_2
.LBB0_2:                                # %switch.default
	xorl	%ecx, %ecx
	callq	Assert
.LBB0_3:                                # %switch.end
	movq	$0, 48(%rsp)
	jmp	.LBB0_7
.LBB0_4:                                # %switch.case1
	xorl	%ecx, %ecx
	callq	Assert
	jmp	.LBB0_3
.LBB0_5:                                # %switch.case2
	movl	$1, %ecx
	callq	Assert
	jmp	.LBB0_3
.LBB0_6:                                # %switch.case3
	xorl	%ecx, %ecx
	callq	Assert
	jmp	.LBB0_3
.LBB0_7:                                # %exit
	movq	48(%rsp), %rax
	addq	$56, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
