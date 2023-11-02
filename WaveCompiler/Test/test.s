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
	subq	$80, %rsp
	.seh_stackalloc 80
	leaq	80(%rsp), %rbp
	.seh_setframe %rbp, 80
	.seh_endprologue
	movq	$1, -56(%rbp)
	movq	$2, -48(%rbp)
	movq	$3, -40(%rbp)
	movq	$0, -32(%rbp)
	movq	$0, -24(%rbp)
	movq	$0, -16(%rbp)
	movq	$10, -56(%rbp)
	movq	$0, -64(%rbp)
	jmp	.LBB0_2
.LBB0_1:                                # %for.body
                                        #   in Loop: Header=BB0_2 Depth=1
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	-64(%rbp), %rcx
	movq	-56(%rbp,%rcx,8), %rcx
	movq	%rcx, (%rax)
	movq	(%rax), %rcx
	subq	$32, %rsp
	callq	PrintInteger
	addq	$32, %rsp
	jmp	.LBB0_3
.LBB0_2:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	cmpq	$6, -64(%rbp)
	jl	.LBB0_1
	jmp	.LBB0_4
.LBB0_3:                                # %for.iter
                                        #   in Loop: Header=BB0_2 Depth=1
	movq	-64(%rbp), %rax
	movq	%rax, -72(%rbp)                 # 8-byte Spill
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	-72(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	-64(%rbp), %rdx
	movq	%rdx, (%rcx)
	addq	$1, %rax
	movq	%rax, -64(%rbp)
	jmp	.LBB0_2
.LBB0_4:                                # %for.end
	movq	-56(%rbp), %rax
	movq	%rax, -8(%rbp)
# %bb.5:                                # %exit
	movq	-8(%rbp), %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym PrintInteger
