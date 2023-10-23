	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"WaveModule"
	.def	add;
	.scl	2;
	.type	32;
	.endef
	.globl	add                             # -- Begin function add
	.p2align	4, 0x90
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
	subq	$16, %rsp
	.seh_stackalloc 16
	.seh_endprologue
	movq	$0, (%rsp)
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	movl	$10, %ecx
	cmpq	$0, (%rsp)
	cmovneq	%rcx, %rax
	movq	%rax, 8(%rsp)
# %bb.1:                                # %exit
	movq	8(%rsp), %rax
	addq	$16, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
