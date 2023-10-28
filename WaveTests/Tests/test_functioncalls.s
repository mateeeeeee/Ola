	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"WaveModule"
	.def	square;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function square
square:                                 # @square
# %bb.0:                                # %entry
	movq	%rcx, %rax
	imulq	%rax, %rax
	retq
                                        # -- End function
	.def	add;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function add
add:                                    # @add
# %bb.0:                                # %entry
	movq	%rdx, %rax
	addq	%rcx, %rax
	retq
                                        # -- End function
	.def	isEven;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function isEven
isEven:                                 # @isEven
# %bb.0:                                # %entry
	movb	%cl, %al
	testb	$1, %al
	sete	%al
	retq
                                        # -- End function
	.def	fma;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function fma
fma:                                    # @fma
# %bb.0:                                # %entry
	movq	%rdx, %rax
	imulq	%rcx, %rax
	addq	%r8, %rax
	retq
                                        # -- End function
	.def	isInRange;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function isInRange
isInRange:                              # @isInRange
# %bb.0:                                # %entry
	movq	%rcx, %rax
	subq	%rdx, %rax
	setge	%al
	subq	%r8, %rcx
	setle	%cl
	andb	%cl, %al
	retq
                                        # -- End function
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movl	$5, %ecx
	callq	square
	cmpq	$25, %rax
	sete	%cl
	callq	Assert
	movl	$8, %ecx
	callq	isEven
	movb	%al, %cl
	callq	Assert
	movq	$-4, %rcx
	callq	square
	cmpq	$16, %rax
	sete	%cl
	callq	Assert
	movl	$7, %ecx
	callq	isEven
	movb	%al, %cl
	xorb	$-1, %cl
	callq	Assert
	movl	$5, %ecx
	movl	$12, %edx
	callq	add
	cmpq	$17, %rax
	sete	%cl
	callq	Assert
	movl	$2, %ecx
	movl	$3, %edx
	movl	$4, %r8d
	callq	fma
	cmpq	$10, %rax
	sete	%cl
	callq	Assert
	movl	$5, %ecx
	movl	$1, %edx
	movl	$10, %r8d
	callq	isInRange
	movb	%al, %cl
	callq	Assert
	movl	$6, %ecx
	movl	$2, %edx
	movl	$8, %r8d
	callq	fma
	cmpq	$20, %rax
	sete	%cl
	callq	Assert
	movl	$5, %ecx
	movl	$6, %edx
	movl	$10, %r8d
	callq	isInRange
	movb	%al, %cl
	xorb	$-1, %cl
	callq	Assert
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym square
	.addrsig_sym add
	.addrsig_sym isEven
	.addrsig_sym fma
	.addrsig_sym isInRange
