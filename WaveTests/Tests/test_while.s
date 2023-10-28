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
	subq	$96, %rsp
	.seh_stackalloc 96
	leaq	96(%rsp), %rbp
	.seh_setframe %rbp, 96
	.seh_endprologue
	movq	$1, -8(%rbp)
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	movq	%rax, -16(%rbp)                 # 8-byte Spill
.LBB0_1:                                # %while.body
                                        # =>This Inner Loop Header: Depth=1
	movq	-16(%rbp), %rdx                 # 8-byte Reload
	movq	-8(%rbp), %rcx
	movq	%rcx, %rax
	addq	%rdx, %rax
	movq	%rax, -24(%rbp)                 # 8-byte Spill
	addq	$1, %rcx
	movq	%rcx, -8(%rbp)
	cmpq	$6, %rcx
	movq	%rax, -16(%rbp)                 # 8-byte Spill
	jl	.LBB0_1
# %bb.2:                                # %while.cond.while.end_crit_edge
	movq	-24(%rbp), %rax                 # 8-byte Reload
	subq	$15, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	movl	$16, %eax
	movq	%rax, -48(%rbp)                 # 8-byte Spill
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	$0, (%rax)
	movq	(%rax), %rax
	testq	%rax, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	movq	-48(%rbp), %rax                 # 8-byte Reload
	addq	$32, %rsp
	callq	__chkstk
	subq	%rax, %rsp
	movq	-48(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	movq	%rdx, -40(%rbp)                 # 8-byte Spill
	movq	$5, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -32(%rbp)                 # 8-byte Spill
	movq	$0, (%rax)
.LBB0_3:                                # %while.body5
                                        # =>This Inner Loop Header: Depth=1
	movq	-32(%rbp), %rcx                 # 8-byte Reload
	movq	(%rcx), %rax
	addq	$1, %rax
	movq	%rax, (%rcx)
	cmpq	$5, %rax
	jne	.LBB0_3
# %bb.4:                                # %if.then
	movq	-40(%rbp), %rcx                 # 8-byte Reload
	movq	-32(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	movq	(%rcx), %rcx
	subq	%rcx, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	movl	$16, %eax
	movq	%rax, -80(%rbp)                 # 8-byte Spill
	callq	__chkstk
	subq	%rax, %rsp
	movq	-80(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	movq	%rdx, -72(%rbp)                 # 8-byte Spill
	movq	$0, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	-72(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, -64(%rbp)                 # 8-byte Spill
	movq	$0, (%rcx)
	movq	(%rax), %rax
	movq	%rax, -56(%rbp)                 # 8-byte Spill
.LBB0_5:                                # %while.body8
                                        # =>This Inner Loop Header: Depth=1
	movq	-56(%rbp), %rdx                 # 8-byte Reload
	movq	-64(%rbp), %rcx                 # 8-byte Reload
	movq	(%rcx), %rax
	addq	$1, %rax
	movq	%rax, (%rcx)
	movq	%rax, %r8
	andq	$1, %r8
	addq	%rdx, %rax
	cmpq	$0, %r8
	cmoveq	%rdx, %rax
	movq	%rax, -88(%rbp)                 # 8-byte Spill
	cmpq	$5, (%rcx)
	movq	%rax, -56(%rbp)                 # 8-byte Spill
	jl	.LBB0_5
# %bb.6:                                # %while.cond7.while.end9_crit_edge
	movq	-72(%rbp), %rax                 # 8-byte Reload
	movq	-88(%rbp), %rcx                 # 8-byte Reload
	movq	%rcx, (%rax)
	cmpq	$9, (%rax)
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	movq	%rbp, %rsp
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
