	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"WaveModule"
	.def	f;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function f
f:                                      # @f
# %bb.0:                                # %entry
	movq	$100, (%rcx)
# %bb.1:                                # %exit
	retq
                                        # -- End function
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
	movq	$1, 40(%rsp)
	movq	$2, 48(%rsp)
	movq	$3, 56(%rsp)
	movq	$10, 40(%rsp)
	movq	40(%rsp), %rcx
	movl	$3, %edx
	callq	f
	movq	40(%rsp), %rax
	movq	%rax, 64(%rsp)
# %bb.1:                                # %exit
	movq	64(%rsp), %rax
	addq	$72, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym f
