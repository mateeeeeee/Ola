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
	movl	$1, %ecx
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	movq	%rcx, -24(%rbp)                 # 8-byte Spill
	movq	%rax, -16(%rbp)                 # 8-byte Spill
.LBB0_1:                                # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	movq	-24(%rbp), %rax                 # 8-byte Reload
	movq	-16(%rbp), %rcx                 # 8-byte Reload
	movq	%rcx, -32(%rbp)                 # 8-byte Spill
	movq	%rax, -8(%rbp)
	cmpq	$6, %rax
	jge	.LBB0_3
# %bb.2:                                # %while.body
                                        #   in Loop: Header=BB0_1 Depth=1
	movq	-32(%rbp), %rax                 # 8-byte Reload
	movq	-8(%rbp), %rcx
	addq	%rcx, %rax
	addq	$1, %rcx
	movq	%rcx, -24(%rbp)                 # 8-byte Spill
	movq	%rax, -16(%rbp)                 # 8-byte Spill
	jmp	.LBB0_1
.LBB0_3:                                # %while.end
	movq	-32(%rbp), %rax                 # 8-byte Reload
	subq	$15, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -40(%rbp)                 # 8-byte Spill
	movq	$0, (%rax)
.LBB0_4:                                # %while.cond1
                                        # =>This Inner Loop Header: Depth=1
	movq	-40(%rbp), %rax                 # 8-byte Reload
	cmpq	$0, (%rax)
	jle	.LBB0_6
# %bb.5:                                # %while.body2
                                        #   in Loop: Header=BB0_4 Depth=1
	xorl	%ecx, %ecx
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	jmp	.LBB0_4
.LBB0_6:                                # %while.end3
	movq	-40(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	testq	%rax, %rax
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
	movq	$5, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -48(%rbp)                 # 8-byte Spill
	movq	$0, (%rax)
.LBB0_7:                                # %while.cond4
                                        # =>This Inner Loop Header: Depth=1
	movb	$1, %al
	testb	$1, %al
	jne	.LBB0_8
	jmp	.LBB0_9
.LBB0_8:                                # %while.body5
                                        #   in Loop: Header=BB0_7 Depth=1
	movq	-56(%rbp), %rcx                 # 8-byte Reload
	movq	-48(%rbp), %rdx                 # 8-byte Reload
	movq	(%rdx), %rax
	addq	$1, %rax
	movq	%rax, (%rdx)
	cmpq	(%rcx), %rax
	je	.LBB0_11
	jmp	.LBB0_12
.LBB0_9:                                # %while.end6.loopexit
	jmp	.LBB0_10
.LBB0_10:                               # %while.end6
	movq	-56(%rbp), %rcx                 # 8-byte Reload
	movq	-48(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	movq	(%rcx), %rcx
	subq	%rcx, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	movl	$16, %eax
	movq	%rax, -88(%rbp)                 # 8-byte Spill
	callq	__chkstk
	subq	%rax, %rsp
	movq	-88(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	movq	%rdx, -80(%rbp)                 # 8-byte Spill
	movq	$0, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -72(%rbp)                 # 8-byte Spill
	movq	$0, (%rax)
	jmp	.LBB0_13
.LBB0_11:                               # %if.then
	jmp	.LBB0_10
.LBB0_12:                               # %if.end
                                        #   in Loop: Header=BB0_7 Depth=1
	jmp	.LBB0_7
.LBB0_13:                               # %while.cond7
                                        # =>This Inner Loop Header: Depth=1
	movq	-72(%rbp), %rax                 # 8-byte Reload
	cmpq	$5, (%rax)
	jge	.LBB0_15
# %bb.14:                               # %while.body8
                                        #   in Loop: Header=BB0_13 Depth=1
	movq	-72(%rbp), %rcx                 # 8-byte Reload
	movq	(%rcx), %rax
	addq	$1, %rax
	movq	%rax, (%rcx)
	andq	$1, %rax
	cmpq	$0, %rax
	je	.LBB0_16
	jmp	.LBB0_18
.LBB0_15:                               # %while.end9
	movq	-80(%rbp), %rax                 # 8-byte Reload
	cmpq	$9, (%rax)
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	jmp	.LBB0_19
.LBB0_16:                               # %if.then10
                                        #   in Loop: Header=BB0_13 Depth=1
	jmp	.LBB0_17
.LBB0_17:                               # %while.cond7.backedge
                                        #   in Loop: Header=BB0_13 Depth=1
	jmp	.LBB0_13
.LBB0_18:                               # %if.end12
                                        #   in Loop: Header=BB0_13 Depth=1
	movq	-80(%rbp), %rax                 # 8-byte Reload
	movq	-72(%rbp), %rdx                 # 8-byte Reload
	movq	(%rax), %rcx
	addq	(%rdx), %rcx
	movq	%rcx, (%rax)
	jmp	.LBB0_17
.LBB0_19:                               # %exit
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	movq	%rbp, %rsp
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
