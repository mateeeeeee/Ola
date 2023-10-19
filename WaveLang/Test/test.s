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
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movq	$0, 24(%rsp)
	movq	$0, 16(%rsp)
	movq	$0, 8(%rsp)
	movq	24(%rsp), %rax
	movq	24(%rsp), %rcx
	movq	%rcx, (%rsp)
	addq	$1, %rax
	movq	%rax, 24(%rsp)
	cmpq	$0, (%rsp)
	je	.LBB0_2
# %bb.1:                                # %if.then
	movq	24(%rsp), %rax
	movq	%rax, 32(%rsp)
	jmp	.LBB0_3
.LBB0_2:                                # %if.end
	movq	24(%rsp), %rax
	shlq	%rax
	movq	%rax, 32(%rsp)
.LBB0_3:                                # %exit
	movq	32(%rsp), %rax
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
