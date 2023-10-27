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
	movq	%rcx, (%rsp)                    # 8-byte Spill
	jmp	.LBB0_1
.LBB0_1:                                # %exit
	movq	(%rsp), %rax                    # 8-byte Reload
	imulq	%rax, %rax
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
	subq	$16, %rsp
	.seh_stackalloc 16
	.seh_endprologue
	movq	%rdx, (%rsp)                    # 8-byte Spill
	movq	%rcx, 8(%rsp)                   # 8-byte Spill
	jmp	.LBB1_1
.LBB1_1:                                # %exit
	movq	(%rsp), %rcx                    # 8-byte Reload
	movq	8(%rsp), %rax                   # 8-byte Reload
	addq	%rcx, %rax
	addq	$16, %rsp
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
	movq	%rcx, (%rsp)                    # 8-byte Spill
	jmp	.LBB2_1
.LBB2_1:                                # %exit
	movq	(%rsp), %rax                    # 8-byte Reload
                                        # kill: def $al killed $al killed $rax
	testb	$1, %al
	sete	%al
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
	subq	$24, %rsp
	.seh_stackalloc 24
	.seh_endprologue
	movq	%r8, (%rsp)                     # 8-byte Spill
	movq	%rdx, 8(%rsp)                   # 8-byte Spill
	movq	%rcx, 16(%rsp)                  # 8-byte Spill
	jmp	.LBB3_1
.LBB3_1:                                # %exit
	movq	(%rsp), %rcx                    # 8-byte Reload
	movq	8(%rsp), %rdx                   # 8-byte Reload
	movq	16(%rsp), %rax                  # 8-byte Reload
	imulq	%rdx, %rax
	addq	%rcx, %rax
	addq	$24, %rsp
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
	subq	$24, %rsp
	.seh_stackalloc 24
	.seh_endprologue
	movq	%r8, (%rsp)                     # 8-byte Spill
	movq	%rdx, 8(%rsp)                   # 8-byte Spill
	movq	%rcx, 16(%rsp)                  # 8-byte Spill
	jmp	.LBB4_1
.LBB4_1:                                # %exit
	movq	(%rsp), %rdx                    # 8-byte Reload
	movq	16(%rsp), %rcx                  # 8-byte Reload
	movq	8(%rsp), %r8                    # 8-byte Reload
	movq	%rcx, %rax
	subq	%r8, %rax
	setge	%al
	subq	%rdx, %rcx
	setle	%cl
	andb	%cl, %al
	addq	$24, %rsp
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
# %bb.1:                                # %exit
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
