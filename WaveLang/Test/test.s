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
	movq	$0, -24(%rbp)
.LBB0_1:                                # %label.label
                                        # =>This Inner Loop Header: Depth=1
	movq	-24(%rbp), %rax
	movq	%rax, -32(%rbp)                 # 8-byte Spill
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	-32(%rbp), %rax                 # 8-byte Reload
	movq	%rsp, %rcx
	movq	-24(%rbp), %rdx
	movq	%rdx, (%rcx)
	addq	$1, %rax
	movq	%rax, -24(%rbp)
	cmpq	$5, -24(%rbp)
	jl	.LBB0_3
	jmp	.LBB0_4
.LBB0_2:                                # %label.end
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.LBB0_5
.LBB0_3:                                # %if.then
                                        #   in Loop: Header=BB0_1 Depth=1
	jmp	.LBB0_1
.LBB0_4:                                # %if.else
	jmp	.LBB0_2
.LBB0_5:                                # %exit
	movq	-8(%rbp), %rax
	movq	%rbp, %rsp
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
