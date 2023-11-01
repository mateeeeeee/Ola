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
	subq	$96, %rsp
	.seh_stackalloc 96
	.seh_endprologue
	movq	$1, 8(%rsp)
	movq	$2, 16(%rsp)
	movq	$3, 24(%rsp)
	movq	$10, (%rsp)
	movq	$10, 88(%rsp)
# %bb.1:                                # %exit
	movq	88(%rsp), %rax
	addq	$96, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.data
	.p2align	4, 0x0                          # @global_arr
global_arr:
	.quad	1                               # 0x1
	.quad	2                               # 0x2
	.quad	3                               # 0x3
	.quad	0                               # 0x0
	.quad	0                               # 0x0

	.addrsig
