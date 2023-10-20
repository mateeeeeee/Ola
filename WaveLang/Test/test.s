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
	cmpq	$0, -16(%rbp)
	jle	.LBB0_2
# %bb.1:                                # %if.then
	movq	-16(%rbp), %rax
	addq	$4, %rax
	movq	%rax, -16(%rbp)
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	-16(%rbp), %rcx
	subq	$1, %rcx
	movq	%rcx, (%rax)
	imulq	$5, (%rax), %rcx
	movq	%rcx, (%rax)
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	jmp	.LBB0_7
.LBB0_2:                                # %if.else
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -24(%rbp)                 # 8-byte Spill
	movq	$0, (%rax)
	jmp	.LBB0_4
.LBB0_3:                                # %for.body
                                        #   in Loop: Header=BB0_4 Depth=1
	movq	-16(%rbp), %rax
	movq	%rax, -32(%rbp)                 # 8-byte Spill
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	-32(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rcx)
	addq	$1, %rax
	movq	%rax, -16(%rbp)
	jmp	.LBB0_5
.LBB0_4:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movq	-24(%rbp), %rax                 # 8-byte Reload
	cmpq	$10, (%rax)
	jl	.LBB0_3
	jmp	.LBB0_6
.LBB0_5:                                # %for.iter
                                        #   in Loop: Header=BB0_4 Depth=1
	movq	-24(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rcx
	addq	$1, %rcx
	movq	%rcx, (%rax)
	jmp	.LBB0_4
.LBB0_6:                                # %for.end
	movq	-16(%rbp), %rax
	movq	%rax, -8(%rbp)
.LBB0_7:                                # %exit
	movq	-8(%rbp), %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
