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
.seh_proc square
# %bb.0:                                # %entry
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	imulq	%rcx, %rcx
	movq	%rcx, (%rsp)
# %bb.1:                                # %exit
	movq	(%rsp), %rax
	popq	%rcx
	retq
	.seh_endproc
                                        # -- End function
	.def	add;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function add
add:                                    # @add
.seh_proc add
# %bb.0:                                # %entry
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	addq	%rdx, %rcx
	movq	%rcx, (%rsp)
# %bb.1:                                # %exit
	movq	(%rsp), %rax
	popq	%rcx
	retq
	.seh_endproc
                                        # -- End function
	.def	isEven;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function isEven
isEven:                                 # @isEven
.seh_proc isEven
# %bb.0:                                # %entry
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	movq	%rcx, %rax
	movl	$2, %ecx
	cqto
	idivq	%rcx
	cmpq	$0, %rdx
	sete	%al
	andb	$1, %al
	movb	%al, 7(%rsp)
# %bb.1:                                # %exit
	movb	7(%rsp), %al
	popq	%rcx
	retq
	.seh_endproc
                                        # -- End function
	.def	fma;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function fma
fma:                                    # @fma
.seh_proc fma
# %bb.0:                                # %entry
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	movq	%rcx, %rax
	imulq	%rdx, %rax
	addq	%r8, %rax
	movq	%rax, (%rsp)
# %bb.1:                                # %exit
	movq	(%rsp), %rax
	popq	%rcx
	retq
	.seh_endproc
                                        # -- End function
	.def	isInRange;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function isInRange
isInRange:                              # @isInRange
.seh_proc isInRange
# %bb.0:                                # %entry
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	movq	%rcx, %rax
	subq	%rdx, %rax
	setge	%al
	subq	%r8, %rcx
	setle	%cl
	andb	%cl, %al
	andb	$1, %al
	movb	%al, 7(%rsp)
# %bb.1:                                # %exit
	movb	7(%rsp), %al
	popq	%rcx
	retq
	.seh_endproc
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
	subq	$152, %rsp
	.seh_stackalloc 152
	.seh_endprologue
	movl	$5, %ecx
	movq	%rcx, 48(%rsp)                  # 8-byte Spill
	callq	square
	movq	%rax, 136(%rsp)
	movq	136(%rsp), %rax
	subq	$25, %rax
	sete	%cl
	callq	Assert
	movl	$8, %ecx
	movq	%rcx, 40(%rsp)                  # 8-byte Spill
	callq	isEven
	andb	$1, %al
	movb	%al, 135(%rsp)
	movb	135(%rsp), %cl
	callq	Assert
	movq	$-4, %rcx
	callq	square
	movq	%rax, 120(%rsp)
	movq	120(%rsp), %rax
	subq	$16, %rax
	sete	%cl
	callq	Assert
	movl	$7, %ecx
	callq	isEven
	andb	$1, %al
	movb	%al, 119(%rsp)
	movb	119(%rsp), %cl
	xorb	$1, %cl
	callq	Assert
	movq	48(%rsp), %rcx                  # 8-byte Reload
	movl	$12, %edx
	callq	add
	movq	%rax, 104(%rsp)
	movq	104(%rsp), %rax
	subq	$17, %rax
	sete	%cl
	callq	Assert
	movl	$2, %ecx
	movq	%rcx, 32(%rsp)                  # 8-byte Spill
	movl	$3, %edx
	movl	$4, %r8d
	callq	fma
	movq	%rax, 96(%rsp)
	movq	96(%rsp), %rax
	subq	$10, %rax
	sete	%cl
	callq	Assert
	movq	48(%rsp), %rcx                  # 8-byte Reload
	movl	$1, %edx
	movl	$10, %r8d
	movq	%r8, 64(%rsp)                   # 8-byte Spill
	callq	isInRange
	andb	$1, %al
	movb	%al, 95(%rsp)
	movb	95(%rsp), %cl
	callq	Assert
	movq	32(%rsp), %rdx                  # 8-byte Reload
	movq	40(%rsp), %r8                   # 8-byte Reload
	movl	$6, %ecx
	movq	%rcx, 56(%rsp)                  # 8-byte Spill
	callq	fma
	movq	%rax, 80(%rsp)
	movq	80(%rsp), %rax
	subq	$20, %rax
	sete	%cl
	callq	Assert
	movq	48(%rsp), %rcx                  # 8-byte Reload
	movq	56(%rsp), %rdx                  # 8-byte Reload
	movq	64(%rsp), %r8                   # 8-byte Reload
	callq	isInRange
	andb	$1, %al
	movb	%al, 79(%rsp)
	movb	79(%rsp), %cl
	xorb	$1, %cl
	callq	Assert
	movq	$0, 144(%rsp)
# %bb.1:                                # %exit
	movq	144(%rsp), %rax
	addq	$152, %rsp
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
