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
	movl	$1, %ecx
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	movq	%rcx, 8(%rbp)                   # 8-byte Spill
	movq	%rax, 16(%rbp)                  # 8-byte Spill
	jmp	.LBB0_2
.LBB0_1:                                # %for.body
                                        #   in Loop: Header=BB0_2 Depth=1
	jmp	.LBB0_3
.LBB0_2:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	movq	8(%rbp), %rax                   # 8-byte Reload
	movq	16(%rbp), %rcx                  # 8-byte Reload
	movq	%rcx, (%rbp)                    # 8-byte Spill
	movq	%rax, 24(%rbp)
	cmpq	$6, %rax
	jl	.LBB0_1
	jmp	.LBB0_4
.LBB0_3:                                # %for.iter
                                        #   in Loop: Header=BB0_2 Depth=1
	movq	(%rbp), %rax                    # 8-byte Reload
	movq	24(%rbp), %rcx
	addq	%rcx, %rax
	addq	$1, %rcx
	movq	%rcx, 8(%rbp)                   # 8-byte Spill
	movq	%rax, 16(%rbp)                  # 8-byte Spill
	jmp	.LBB0_2
.LBB0_4:                                # %for.end
	movq	(%rbp), %rax                    # 8-byte Reload
	subq	$15, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	movl	$16, %eax
	movq	%rax, -32(%rbp)                 # 8-byte Spill
	callq	__chkstk
	subq	%rax, %rsp
	movq	-32(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	movq	%rdx, -24(%rbp)                 # 8-byte Spill
	movq	$0, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -16(%rbp)                 # 8-byte Spill
	movl	$1, %eax
	movq	%rax, -8(%rbp)                  # 8-byte Spill
	jmp	.LBB0_6
.LBB0_5:                                # %for.body1
                                        #   in Loop: Header=BB0_6 Depth=1
	movq	-16(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	andq	$1, %rax
	cmpq	$0, %rax
	je	.LBB0_9
	jmp	.LBB0_10
.LBB0_6:                                # %for.cond2
                                        # =>This Inner Loop Header: Depth=1
	movq	-16(%rbp), %rcx                 # 8-byte Reload
	movq	-8(%rbp), %rax                  # 8-byte Reload
	movq	%rax, (%rcx)
	cmpq	$6, %rax
	jl	.LBB0_5
	jmp	.LBB0_8
.LBB0_7:                                # %for.iter3
                                        #   in Loop: Header=BB0_6 Depth=1
	movq	-16(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	addq	$1, %rax
	movq	%rax, -8(%rbp)                  # 8-byte Spill
	jmp	.LBB0_6
.LBB0_8:                                # %for.end4
	movq	-24(%rbp), %rax                 # 8-byte Reload
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
	movq	%rsp, %rax
	movq	%rax, -48(%rbp)                 # 8-byte Spill
	movl	$1, %eax
	movq	%rax, -40(%rbp)                 # 8-byte Spill
	jmp	.LBB0_12
.LBB0_9:                                # %if.then
                                        #   in Loop: Header=BB0_6 Depth=1
	jmp	.LBB0_7
.LBB0_10:                               # %if.end
                                        #   in Loop: Header=BB0_6 Depth=1
	movq	-24(%rbp), %rax                 # 8-byte Reload
	movq	-16(%rbp), %rdx                 # 8-byte Reload
	movq	(%rax), %rcx
	addq	(%rdx), %rcx
	movq	%rcx, (%rax)
	jmp	.LBB0_7
.LBB0_11:                               # %for.body5
                                        #   in Loop: Header=BB0_12 Depth=1
	movq	-56(%rbp), %rcx                 # 8-byte Reload
	movq	-48(%rbp), %rax                 # 8-byte Reload
	movq	(%rcx), %rdx
	movq	(%rax), %rax
	addq	%rax, %rdx
	movq	%rdx, (%rcx)
	cmpq	$5, %rax
	je	.LBB0_16
	jmp	.LBB0_17
.LBB0_12:                               # %for.cond6
                                        # =>This Inner Loop Header: Depth=1
	movq	-48(%rbp), %rcx                 # 8-byte Reload
	movq	-40(%rbp), %rax                 # 8-byte Reload
	movq	%rax, (%rcx)
	cmpq	$11, %rax
	jl	.LBB0_11
	jmp	.LBB0_14
.LBB0_13:                               # %for.iter7
                                        #   in Loop: Header=BB0_12 Depth=1
	movq	-48(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	addq	$1, %rax
	movq	%rax, -40(%rbp)                 # 8-byte Spill
	jmp	.LBB0_12
.LBB0_14:                               # %for.end8.loopexit
	jmp	.LBB0_15
.LBB0_15:                               # %for.end8
	movq	-56(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	subq	$15, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	movl	$16, %eax
	movq	%rax, -96(%rbp)                 # 8-byte Spill
	callq	__chkstk
	subq	%rax, %rsp
	movq	-96(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	movq	%rdx, -88(%rbp)                 # 8-byte Spill
	movq	$1, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -80(%rbp)                 # 8-byte Spill
	movl	$2, %eax
	movq	%rax, -72(%rbp)                 # 8-byte Spill
	jmp	.LBB0_19
.LBB0_16:                               # %if.then9
	jmp	.LBB0_15
.LBB0_17:                               # %if.end11
                                        #   in Loop: Header=BB0_12 Depth=1
	jmp	.LBB0_13
.LBB0_18:                               # %for.body12
                                        #   in Loop: Header=BB0_19 Depth=1
	movq	-88(%rbp), %rax                 # 8-byte Reload
	movq	-80(%rbp), %rdx                 # 8-byte Reload
	movq	(%rax), %rcx
	imulq	(%rdx), %rcx
	movq	%rcx, (%rax)
	jmp	.LBB0_20
.LBB0_19:                               # %for.cond13
                                        # =>This Inner Loop Header: Depth=1
	movq	-80(%rbp), %rcx                 # 8-byte Reload
	movq	-72(%rbp), %rax                 # 8-byte Reload
	movq	%rax, (%rcx)
	cmpq	$11, %rax
	jl	.LBB0_18
	jmp	.LBB0_21
.LBB0_20:                               # %for.iter14
                                        #   in Loop: Header=BB0_19 Depth=1
	movq	-80(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	addq	$2, %rax
	movq	%rax, -72(%rbp)                 # 8-byte Spill
	jmp	.LBB0_19
.LBB0_21:                               # %for.end15
	movq	-88(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	subq	$3840, %rax                     # imm = 0xF00
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
	movq	$5, (%rax)
	jmp	.LBB0_23
.LBB0_22:                               # %for.body16
                                        #   in Loop: Header=BB0_23 Depth=1
	movq	-104(%rbp), %rax                # 8-byte Reload
	movq	-112(%rbp), %rdx                # 8-byte Reload
	movq	(%rdx), %r8
	movq	(%rax), %rcx
	imulq	%rcx, %r8
	movq	%r8, (%rdx)
	addq	$-1, %rcx
	movq	%rcx, (%rax)
	jmp	.LBB0_24
.LBB0_23:                               # %for.cond17
                                        # =>This Inner Loop Header: Depth=1
	movq	-104(%rbp), %rax                # 8-byte Reload
	cmpq	$0, (%rax)
	jg	.LBB0_22
	jmp	.LBB0_25
.LBB0_24:                               # %for.iter18
                                        #   in Loop: Header=BB0_23 Depth=1
	jmp	.LBB0_23
.LBB0_25:                               # %for.end19
	movq	-112(%rbp), %rax                # 8-byte Reload
	cmpq	$120, (%rax)
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
# %bb.26:                               # %exit
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	leaq	32(%rbp), %rsp
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
