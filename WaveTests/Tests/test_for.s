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
	jmp	.LBB0_2
.LBB0_1:                                # %for.body
                                        #   in Loop: Header=BB0_2 Depth=1
	jmp	.LBB0_3
.LBB0_2:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movq	-24(%rbp), %rax                 # 8-byte Reload
	movq	-16(%rbp), %rcx                 # 8-byte Reload
	movq	%rcx, -32(%rbp)                 # 8-byte Spill
	movq	%rax, -8(%rbp)
	cmpq	$6, %rax
	jl	.LBB0_1
	jmp	.LBB0_4
.LBB0_3:                                # %for.iter
                                        #   in Loop: Header=BB0_2 Depth=1
	movq	-32(%rbp), %rax                 # 8-byte Reload
	movq	-8(%rbp), %rcx
	addq	%rcx, %rax
	addq	$1, %rcx
	movq	%rcx, -24(%rbp)                 # 8-byte Spill
	movq	%rax, -16(%rbp)                 # 8-byte Spill
	jmp	.LBB0_2
.LBB0_4:                                # %for.end
	movq	-32(%rbp), %rax                 # 8-byte Reload
	subq	$15, %rax
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
	movq	$1, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -48(%rbp)                 # 8-byte Spill
	movl	$2, %eax
	movq	%rax, -40(%rbp)                 # 8-byte Spill
	jmp	.LBB0_6
.LBB0_5:                                # %for.body1
                                        #   in Loop: Header=BB0_6 Depth=1
	movq	-56(%rbp), %rax                 # 8-byte Reload
	movq	-48(%rbp), %rdx                 # 8-byte Reload
	movq	(%rax), %rcx
	imulq	(%rdx), %rcx
	movq	%rcx, (%rax)
	jmp	.LBB0_7
.LBB0_6:                                # %for.cond2
                                        # =>This Inner Loop Header: Depth=1
	movq	-48(%rbp), %rcx                 # 8-byte Reload
	movq	-40(%rbp), %rax                 # 8-byte Reload
	movq	%rax, (%rcx)
	cmpq	$11, %rax
	jl	.LBB0_5
	jmp	.LBB0_8
.LBB0_7:                                # %for.iter3
                                        #   in Loop: Header=BB0_6 Depth=1
	movq	-48(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	addq	$2, %rax
	movq	%rax, -40(%rbp)                 # 8-byte Spill
	jmp	.LBB0_6
.LBB0_8:                                # %for.end4
	movq	-56(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	subq	$3840, %rax                     # imm = 0xF00
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
	movq	$1, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -72(%rbp)                 # 8-byte Spill
	movq	$5, (%rax)
	jmp	.LBB0_10
.LBB0_9:                                # %for.body5
                                        #   in Loop: Header=BB0_10 Depth=1
	movq	-72(%rbp), %rax                 # 8-byte Reload
	movq	-80(%rbp), %rdx                 # 8-byte Reload
	movq	(%rdx), %r8
	movq	(%rax), %rcx
	imulq	%rcx, %r8
	movq	%r8, (%rdx)
	addq	$-1, %rcx
	movq	%rcx, (%rax)
	jmp	.LBB0_11
.LBB0_10:                               # %for.cond6
                                        # =>This Inner Loop Header: Depth=1
	movq	-72(%rbp), %rax                 # 8-byte Reload
	cmpq	$0, (%rax)
	jg	.LBB0_9
	jmp	.LBB0_12
.LBB0_11:                               # %for.iter7
                                        #   in Loop: Header=BB0_10 Depth=1
	jmp	.LBB0_10
.LBB0_12:                               # %for.end8
	movq	-80(%rbp), %rax                 # 8-byte Reload
	cmpq	$120, (%rax)
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
# %bb.13:                               # %exit
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	movq	%rbp, %rsp
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
