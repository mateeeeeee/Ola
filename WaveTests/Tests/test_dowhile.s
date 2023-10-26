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
	subq	$128, %rsp
	.seh_stackalloc 128
	leaq	128(%rsp), %rbp
	.seh_setframe %rbp, 128
	.seh_endprologue
	movq	$0, -8(%rbp)
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	movq	%rax, -16(%rbp)                 # 8-byte Spill
.LBB0_1:                                # %dowhile.body
                                        # =>This Inner Loop Header: Depth=1
	movq	-16(%rbp), %rax                 # 8-byte Reload
	movq	%rax, -32(%rbp)                 # 8-byte Spill
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)                 # 8-byte Spill
	addq	$1, %rax
	movq	%rax, -8(%rbp)
# %bb.2:                                # %dowhile.cond
                                        #   in Loop: Header=BB0_1 Depth=1
	movq	-24(%rbp), %rcx                 # 8-byte Reload
	movq	-32(%rbp), %rax                 # 8-byte Reload
	addq	%rcx, %rax
	movq	%rax, -40(%rbp)                 # 8-byte Spill
	cmpq	$5, -8(%rbp)
	movq	%rax, -16(%rbp)                 # 8-byte Spill
	jl	.LBB0_1
# %bb.3:                                # %dowhile.end
	movq	-40(%rbp), %rax                 # 8-byte Reload
	subq	$10, %rax
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
	movq	$10, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -48(%rbp)                 # 8-byte Spill
	movq	$0, (%rax)
.LBB0_4:                                # %dowhile.body1
                                        # =>This Inner Loop Header: Depth=1
	movq	-48(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rcx
	addq	$1, %rcx
	movq	%rcx, (%rax)
# %bb.5:                                # %dowhile.cond2
                                        #   in Loop: Header=BB0_4 Depth=1
	movq	-56(%rbp), %rax                 # 8-byte Reload
	cmpq	$10, (%rax)
	jl	.LBB0_4
# %bb.6:                                # %dowhile.end3
	movq	-48(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	subq	$1, %rax
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
	movq	%rdx, -96(%rbp)                 # 8-byte Spill
	movq	$5, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	-88(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	movq	%rdx, -80(%rbp)                 # 8-byte Spill
	movq	$3, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -72(%rbp)                 # 8-byte Spill
	movq	$0, (%rax)
.LBB0_7:                                # %dowhile.body4
                                        # =>This Inner Loop Header: Depth=1
	movq	-80(%rbp), %rcx                 # 8-byte Reload
	movq	-96(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	cmpq	(%rcx), %rax
	jg	.LBB0_10
	jmp	.LBB0_11
.LBB0_8:                                # %dowhile.cond5
                                        #   in Loop: Header=BB0_7 Depth=1
	movq	-80(%rbp), %rcx                 # 8-byte Reload
	movq	-96(%rbp), %rax                 # 8-byte Reload
	cmpq	$0, (%rax)
	setg	%al
	cmpq	$10, (%rcx)
	setl	%cl
	andb	%cl, %al
	testb	$1, %al
	jne	.LBB0_7
# %bb.9:                                # %dowhile.end6
	movq	-72(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	subq	$5, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	movl	$16, %eax
	movq	%rax, -120(%rbp)                # 8-byte Spill
	callq	__chkstk
	subq	%rax, %rsp
	movq	-120(%rbp), %rax                # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	movq	%rdx, -112(%rbp)                # 8-byte Spill
	movq	$1, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -104(%rbp)                # 8-byte Spill
	movq	$0, (%rax)
	jmp	.LBB0_12
.LBB0_10:                               # %if.then
                                        #   in Loop: Header=BB0_7 Depth=1
	movq	-72(%rbp), %rax                 # 8-byte Reload
	movq	-96(%rbp), %rdx                 # 8-byte Reload
	movq	(%rax), %rcx
	addq	(%rdx), %rcx
	movq	%rcx, (%rax)
.LBB0_11:                               # %if.end
                                        #   in Loop: Header=BB0_7 Depth=1
	movq	-80(%rbp), %rax                 # 8-byte Reload
	movq	-96(%rbp), %rcx                 # 8-byte Reload
	movq	(%rcx), %rdx
	addq	$-1, %rdx
	movq	%rdx, (%rcx)
	movq	(%rax), %rcx
	addq	$1, %rcx
	movq	%rcx, (%rax)
	jmp	.LBB0_8
.LBB0_12:                               # %dowhile.body7
                                        # =>This Inner Loop Header: Depth=1
	movq	-104(%rbp), %rcx                # 8-byte Reload
	movq	-112(%rbp), %rdx                # 8-byte Reload
	movq	(%rcx), %rax
	addq	(%rdx), %rax
	movq	%rax, (%rcx)
	cmpq	$9, %rax
	jg	.LBB0_16
	jmp	.LBB0_17
.LBB0_13:                               # %dowhile.cond8
                                        #   in Loop: Header=BB0_12 Depth=1
	movq	-112(%rbp), %rax                # 8-byte Reload
	cmpq	$6, (%rax)
	jl	.LBB0_12
# %bb.14:                               # %dowhile.end9.loopexit
	jmp	.LBB0_15
.LBB0_15:                               # %dowhile.end9
	movq	-104(%rbp), %rax                # 8-byte Reload
	cmpq	$10, (%rax)
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	jmp	.LBB0_18
.LBB0_16:                               # %if.then10
	jmp	.LBB0_15
.LBB0_17:                               # %if.end12
                                        #   in Loop: Header=BB0_12 Depth=1
	movq	-112(%rbp), %rax                # 8-byte Reload
	movq	(%rax), %rcx
	addq	$1, %rcx
	movq	%rcx, (%rax)
	jmp	.LBB0_13
.LBB0_18:                               # %exit
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	movq	%rbp, %rsp
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
