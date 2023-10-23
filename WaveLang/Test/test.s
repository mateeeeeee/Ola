	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"WaveModule"
	.def	f;
	.scl	2;
	.type	32;
	.endef
	.globl	f                               # -- Begin function f
	.p2align	4, 0x90
f:                                      # @f
.seh_proc f
# %bb.0:                                # %entry
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	shlq	%rcx
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
	subq	$24, %rsp
	.seh_stackalloc 24
	.seh_endprologue
	movq	$5, 8(%rsp)
	movq	$7, (%rsp)
	movq	a(%rip), %rax
	addq	8(%rsp), %rax
	movq	%rax, 16(%rsp)
# %bb.1:                                # %exit
	movq	16(%rsp), %rax
	addq	$24, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.data
	.p2align	3, 0x0                          # @a
a:
	.quad	5                               # 0x5

	.addrsig
	.addrsig_sym a
