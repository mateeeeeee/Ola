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
	subq	$160, %rsp
	.seh_stackalloc 160
	leaq	128(%rsp), %rbp
	.seh_setframe %rbp, 128
	.seh_endprologue
	movq	$1, 24(%rbp)
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	movq	%rax, 16(%rbp)                  # 8-byte Spill
.LBB0_1:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	movq	16(%rbp), %rdx                  # 8-byte Reload
	movq	24(%rbp), %rcx
	movq	%rcx, %rax
	addq	%rdx, %rax
	movq	%rax, 8(%rbp)                   # 8-byte Spill
	addq	$1, %rcx
	movq	%rcx, 24(%rbp)
	cmpq	$6, %rcx
	movq	%rax, 16(%rbp)                  # 8-byte Spill
	jl	.LBB0_1
# %bb.2:                                # %for.cond.for.end_crit_edge
	movq	8(%rbp), %rax                   # 8-byte Reload
	subq	$15, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	movl	$16, %eax
	movq	%rax, -24(%rbp)                 # 8-byte Spill
	callq	__chkstk
	subq	%rax, %rsp
	movq	-24(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	movq	%rdx, -16(%rbp)                 # 8-byte Spill
	movq	$0, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	-16(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, -8(%rbp)                  # 8-byte Spill
	movq	$1, (%rcx)
	movq	(%rax), %rax
	movq	%rax, (%rbp)                    # 8-byte Spill
.LBB0_3:                                # %for.body1
                                        # =>This Inner Loop Header: Depth=1
	movq	(%rbp), %rcx                    # 8-byte Reload
	movq	-8(%rbp), %rdx                  # 8-byte Reload
	movq	(%rdx), %rax
	movq	%rax, %r8
	andq	$1, %r8
	addq	%rcx, %rax
	cmpq	$0, %r8
	cmoveq	%rcx, %rax
	movq	%rax, -32(%rbp)                 # 8-byte Spill
	movq	(%rdx), %rcx
	addq	$1, %rcx
	movq	%rcx, (%rdx)
	cmpq	$6, %rcx
	movq	%rax, (%rbp)                    # 8-byte Spill
	jl	.LBB0_3
# %bb.4:                                # %for.cond2.for.end4_crit_edge
	movq	-16(%rbp), %rax                 # 8-byte Reload
	movq	-32(%rbp), %rcx                 # 8-byte Reload
	movq	%rcx, (%rax)
	movq	(%rax), %rax
	subq	$9, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	movl	$16, %eax
	movq	%rax, -64(%rbp)                 # 8-byte Spill
	callq	__chkstk
	subq	%rax, %rsp
	movq	-64(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	movq	%rdx, -56(%rbp)                 # 8-byte Spill
	movq	$0, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	-56(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, -48(%rbp)                 # 8-byte Spill
	movq	$1, (%rcx)
	movq	(%rax), %rax
	movq	%rax, -40(%rbp)                 # 8-byte Spill
.LBB0_5:                                # %for.body5
                                        # =>This Inner Loop Header: Depth=1
	movq	-48(%rbp), %rax                 # 8-byte Reload
	movq	-40(%rbp), %rdx                 # 8-byte Reload
	movq	(%rax), %rax
	movq	%rax, -80(%rbp)                 # 8-byte Spill
	movq	%rax, %rcx
	addq	%rdx, %rcx
	movq	%rcx, -72(%rbp)                 # 8-byte Spill
	cmpq	$5, %rax
	je	.LBB0_8
	jmp	.LBB0_9
.LBB0_6:                                # %for.cond6.for.end8.loopexit_crit_edge
	movq	-56(%rbp), %rax                 # 8-byte Reload
	movq	-72(%rbp), %rcx                 # 8-byte Reload
	movq	%rcx, (%rax)
.LBB0_7:                                # %for.end8
	movq	-56(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	subq	$15, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	movl	$16, %eax
	movq	%rax, -112(%rbp)                # 8-byte Spill
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	$1, (%rax)
	movq	(%rax), %rcx
	imulq	$3840, %rcx, %rcx               # imm = 0xF00
	movq	%rcx, (%rax)
	movq	(%rax), %rax
	subq	$3840, %rax                     # imm = 0xF00
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	movq	-112(%rbp), %rax                # 8-byte Reload
	addq	$32, %rsp
	callq	__chkstk
	subq	%rax, %rsp
	movq	-112(%rbp), %rax                # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	movq	%rdx, -104(%rbp)                # 8-byte Spill
	movq	$1, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	-104(%rbp), %rax                # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, -96(%rbp)                 # 8-byte Spill
	movq	$5, (%rcx)
	movq	(%rax), %rax
	movq	%rax, -88(%rbp)                 # 8-byte Spill
	jmp	.LBB0_10
.LBB0_8:                                # %if.then9
	movq	-56(%rbp), %rax                 # 8-byte Reload
	movq	-72(%rbp), %rcx                 # 8-byte Reload
	movq	%rcx, (%rax)
	jmp	.LBB0_7
.LBB0_9:                                # %if.end11
                                        #   in Loop: Header=BB0_5 Depth=1
	movq	-72(%rbp), %rax                 # 8-byte Reload
	movq	-48(%rbp), %rdx                 # 8-byte Reload
	movq	-80(%rbp), %rcx                 # 8-byte Reload
	addq	$1, %rcx
	movq	%rcx, (%rdx)
	cmpq	$11, %rcx
	movq	%rax, -40(%rbp)                 # 8-byte Spill
	jl	.LBB0_5
	jmp	.LBB0_6
.LBB0_10:                               # %for.body16
                                        # =>This Inner Loop Header: Depth=1
	movq	-88(%rbp), %rdx                 # 8-byte Reload
	movq	-96(%rbp), %r8                  # 8-byte Reload
	movq	(%r8), %rax
	movq	%rax, %rcx
	addq	$-1, %rcx
	movq	%rcx, (%r8)
	imulq	%rdx, %rax
	movq	%rax, -120(%rbp)                # 8-byte Spill
	cmpq	$0, %rcx
	movq	%rax, -88(%rbp)                 # 8-byte Spill
	jg	.LBB0_10
# %bb.11:                               # %for.cond17.for.end19_crit_edge
	movq	-104(%rbp), %rax                # 8-byte Reload
	movq	-120(%rbp), %rcx                # 8-byte Reload
	movq	%rcx, (%rax)
	cmpq	$120, (%rax)
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	leaq	32(%rbp), %rsp
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
