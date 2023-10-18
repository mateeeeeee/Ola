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
	pushq	%rbp
	.seh_pushreg %rbp
	subq	$32, %rsp
	.seh_stackalloc 32
	leaq	32(%rsp), %rbp
	.seh_setframe %rbp, 32
	.seh_endprologue
	movq	$0, -16(%rbp)
	movq	$0, -24(%rbp)
	movq	$10, -32(%rbp)
	cmpq	$0, -16(%rbp)
	je	.LBB0_2
# %bb.1:                                # %if.then
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.LBB0_5
.LBB0_2:                                # %if.else
	cmpq	$0, -24(%rbp)
	jne	.LBB0_4
# %bb.3:                                # %if.end
	jmp	.LBB0_5
.LBB0_4:                                # %if.then1
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
.LBB0_5:                                # %exit
	movq	-8(%rbp), %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
