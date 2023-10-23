	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"WaveModule"
	.def	add;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function add
add:                                    # @add
.seh_proc add
# %bb.0:                                # %entry
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	addq	%rdx, %rcx
	movq	%rcx, (%rsp)
# %bb.1:                                # %exit
	movq	(%rsp), %rax
	popq	%rcx
	retq
	.seh_endproc
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
	subq	$56, %rsp
	.seh_stackalloc 56
	.seh_endprologue
	movl	$2, %ecx
	movl	$3, %edx
	callq	add
	movq	%rax, 40(%rsp)
	movq	40(%rsp), %rax
	addq	$5, %rax
	movq	%rax, 48(%rsp)
# %bb.1:                                # %exit
	movq	48(%rsp), %rax
	addq	$56, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym add
