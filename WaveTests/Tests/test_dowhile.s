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
	movq	$0, -8(%rbp)
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	movq	%rax, -16(%rbp)                 # 8-byte Spill
.LBB0_1:                                # %dowhile.body
                                        # =>This Inner Loop Header: Depth=1
	movq	-16(%rbp), %rdx                 # 8-byte Reload
	movq	-8(%rbp), %rax
	movq	%rax, %rcx
	addq	$1, %rcx
	movq	%rcx, -8(%rbp)
	addq	%rdx, %rax
	movq	%rax, -24(%rbp)                 # 8-byte Spill
	cmpq	$5, %rcx
	movq	%rax, -16(%rbp)                 # 8-byte Spill
	jl	.LBB0_1
# %bb.2:                                # %dowhile.end
	movq	-24(%rbp), %rax                 # 8-byte Reload
	subq	$10, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	movl	$16, %eax
	movq	%rax, -56(%rbp)                 # 8-byte Spill
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rcx
	movq	$0, (%rcx)
	movq	(%rcx), %rax
	movq	%rax, %rdx
	incq	%rdx
	movq	%rdx, (%rcx)
	testq	%rax, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	movq	-56(%rbp), %rax                 # 8-byte Reload
	addq	$32, %rsp
	callq	__chkstk
	subq	%rax, %rsp
	movq	-56(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	%rcx, %rdx
	movq	%rdx, -48(%rbp)                 # 8-byte Spill
	movq	$5, (%rcx)
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -40(%rbp)                 # 8-byte Spill
	movq	$3, (%rax)
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	movq	%rax, -32(%rbp)                 # 8-byte Spill
.LBB0_3:                                # %dowhile.body4
                                        # =>This Inner Loop Header: Depth=1
	movq	-32(%rbp), %rax                 # 8-byte Reload
	movq	-48(%rbp), %rcx                 # 8-byte Reload
	movq	-40(%rbp), %r8                  # 8-byte Reload
	movq	(%rcx), %r9
	movq	(%r8), %r10
	movq	%r9, %rdx
	addq	%rax, %rdx
	cmpq	%r10, %r9
	cmovgq	%rdx, %rax
	movq	%rax, -64(%rbp)                 # 8-byte Spill
	movq	(%rcx), %rdx
	addq	$-1, %rdx
	movq	%rdx, (%rcx)
	movq	(%r8), %rdx
	addq	$1, %rdx
	movq	%rdx, (%r8)
	cmpq	$0, (%rcx)
	setg	%cl
	cmpq	$10, %rdx
	setl	%dl
	andb	%dl, %cl
	testb	$1, %cl
	movq	%rax, -32(%rbp)                 # 8-byte Spill
	jne	.LBB0_3
# %bb.4:                                # %dowhile.end6
	movq	-64(%rbp), %rax                 # 8-byte Reload
	subq	$5, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -80(%rbp)                 # 8-byte Spill
	movq	$1, (%rax)
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	movq	%rax, -72(%rbp)                 # 8-byte Spill
.LBB0_5:                                # %dowhile.body7
                                        # =>This Inner Loop Header: Depth=1
	movq	-80(%rbp), %rax                 # 8-byte Reload
	movq	-72(%rbp), %rcx                 # 8-byte Reload
	movq	(%rax), %rax
	movq	%rax, -96(%rbp)                 # 8-byte Spill
	addq	%rcx, %rax
	movq	%rax, -88(%rbp)                 # 8-byte Spill
	cmpq	$9, %rax
	jle	.LBB0_7
.LBB0_6:                                # %dowhile.end9
	movq	-88(%rbp), %rax                 # 8-byte Reload
	cmpq	$10, %rax
	sete	%cl
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	movq	%rbp, %rsp
	popq	%rbp
	retq
.LBB0_7:                                # %if.end12
                                        #   in Loop: Header=BB0_5 Depth=1
	movq	-88(%rbp), %rax                 # 8-byte Reload
	movq	-80(%rbp), %rdx                 # 8-byte Reload
	movq	-96(%rbp), %rcx                 # 8-byte Reload
	addq	$1, %rcx
	movq	%rcx, (%rdx)
	cmpq	$6, %rcx
	movq	%rax, -72(%rbp)                 # 8-byte Spill
	jl	.LBB0_5
	jmp	.LBB0_6
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
