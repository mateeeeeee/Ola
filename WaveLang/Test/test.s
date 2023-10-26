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
	movq	$0, -16(%rbp)
	movq	$0, -24(%rbp)
.LBB0_1:                                # %dowhile.body
                                        # =>This Inner Loop Header: Depth=1
	movq	-24(%rbp), %rax
	movq	-16(%rbp), %rcx
	addq	%rcx, %rax
	movq	%rax, -24(%rbp)
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
# %bb.2:                                # %dowhile.cond
                                        #   in Loop: Header=BB0_1 Depth=1
	cmpq	$5, -16(%rbp)
	jl	.LBB0_1
# %bb.3:                                # %dowhile.end
	movq	-24(%rbp), %rcx
	subq	$32, %rsp
	callq	PrintInteger
	addq	$32, %rsp
	movq	-24(%rbp), %rax
	subq	$10, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	movl	$16, %eax
	movq	%rax, -56(%rbp)                 # 8-byte Spill
	callq	__chkstk
	subq	%rax, %rsp
	movq	-56(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	movq	%rdx, -48(%rbp)                 # 8-byte Spill
	movq	$10, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -40(%rbp)                 # 8-byte Spill
	movq	$0, (%rax)
.LBB0_4:                                # %dowhile.body1
                                        # =>This Inner Loop Header: Depth=1
	movq	-40(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rcx
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	-40(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rdx
	movq	(%rax), %r8
	movq	%r8, (%rdx)
	addq	$1, %rcx
	movq	%rcx, (%rax)
# %bb.5:                                # %dowhile.cond2
                                        #   in Loop: Header=BB0_4 Depth=1
	movq	-48(%rbp), %rax                 # 8-byte Reload
	cmpq	$10, (%rax)
	jl	.LBB0_4
# %bb.6:                                # %dowhile.end3
	movq	-40(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rcx
	subq	$32, %rsp
	callq	PrintInteger
	movq	-40(%rbp), %rax                 # 8-byte Reload
	addq	$32, %rsp
	movq	(%rax), %rax
	subq	$1, %rax
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
	movq	%rdx, -88(%rbp)                 # 8-byte Spill
	movq	$5, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	-80(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	movq	%rdx, -72(%rbp)                 # 8-byte Spill
	movq	$3, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -64(%rbp)                 # 8-byte Spill
	movq	$0, (%rax)
.LBB0_7:                                # %dowhile.body4
                                        # =>This Inner Loop Header: Depth=1
	movq	-72(%rbp), %rcx                 # 8-byte Reload
	movq	-88(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	cmpq	(%rcx), %rax
	jg	.LBB0_10
	jmp	.LBB0_11
.LBB0_8:                                # %dowhile.cond5
                                        #   in Loop: Header=BB0_7 Depth=1
	movq	-72(%rbp), %rcx                 # 8-byte Reload
	movq	-88(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	testq	%rax, %rax
	setg	%al
	movq	(%rcx), %rcx
	subq	$10, %rcx
	setl	%cl
	andb	%cl, %al
	testb	%al, %al
	jne	.LBB0_7
	jmp	.LBB0_9
.LBB0_9:                                # %dowhile.end6
	movq	-64(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rcx
	subq	$32, %rsp
	callq	PrintInteger
	movq	-64(%rbp), %rax                 # 8-byte Reload
	addq	$32, %rsp
	movq	(%rax), %rax
	subq	$5, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	movl	$16, %eax
	movq	%rax, -112(%rbp)                # 8-byte Spill
	callq	__chkstk
	subq	%rax, %rsp
	movq	-112(%rbp), %rax                # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	movq	%rdx, -104(%rbp)                # 8-byte Spill
	movq	$1, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -96(%rbp)                 # 8-byte Spill
	movq	$0, (%rax)
	jmp	.LBB0_12
.LBB0_10:                               # %if.then
                                        #   in Loop: Header=BB0_7 Depth=1
	movq	-64(%rbp), %rax                 # 8-byte Reload
	movq	-88(%rbp), %rdx                 # 8-byte Reload
	movq	(%rax), %rcx
	addq	(%rdx), %rcx
	movq	%rcx, (%rax)
.LBB0_11:                               # %if.end
                                        #   in Loop: Header=BB0_7 Depth=1
	movq	-72(%rbp), %rcx                 # 8-byte Reload
	movq	-88(%rbp), %rdx                 # 8-byte Reload
	movq	(%rdx), %r8
	movl	$16, %eax
	movq	%rax, -120(%rbp)                # 8-byte Spill
	callq	__chkstk
	subq	%rax, %rsp
	movq	-120(%rbp), %rax                # 8-byte Reload
	movq	%rsp, %r9
	movq	(%rdx), %r10
	movq	%r10, (%r9)
	decq	%r8
	movq	%r8, (%rdx)
	movq	(%rcx), %rcx
	callq	__chkstk
	subq	%rax, %rsp
	movq	-72(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rdx
	movq	(%rax), %r8
	movq	%r8, (%rdx)
	addq	$1, %rcx
	movq	%rcx, (%rax)
	jmp	.LBB0_8
.LBB0_12:                               # %dowhile.body7
                                        # =>This Inner Loop Header: Depth=1
	movq	-96(%rbp), %rax                 # 8-byte Reload
	movq	-104(%rbp), %rdx                # 8-byte Reload
	movq	(%rax), %rcx
	addq	(%rdx), %rcx
	movq	%rcx, (%rax)
	cmpq	$10, (%rax)
	jge	.LBB0_15
	jmp	.LBB0_16
.LBB0_13:                               # %dowhile.cond8
                                        #   in Loop: Header=BB0_12 Depth=1
	movq	-104(%rbp), %rax                # 8-byte Reload
	cmpq	$5, (%rax)
	jle	.LBB0_12
.LBB0_14:                               # %dowhile.end9
	movq	-96(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rcx
	subq	$32, %rsp
	callq	PrintInteger
	movq	-96(%rbp), %rax                 # 8-byte Reload
	addq	$32, %rsp
	cmpq	$10, (%rax)
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	movq	$0, -8(%rbp)
	jmp	.LBB0_17
.LBB0_15:                               # %if.then10
	jmp	.LBB0_14
.LBB0_16:                               # %if.end12
                                        #   in Loop: Header=BB0_12 Depth=1
	movq	-104(%rbp), %rax                # 8-byte Reload
	movq	(%rax), %rcx
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	-104(%rbp), %rax                # 8-byte Reload
	movq	%rsp, %rdx
	movq	(%rax), %r8
	movq	%r8, (%rdx)
	addq	$1, %rcx
	movq	%rcx, (%rax)
	jmp	.LBB0_13
.LBB0_17:                               # %exit
	movq	-8(%rbp), %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym PrintInteger
