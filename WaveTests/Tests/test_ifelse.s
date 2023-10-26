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
	subq	$16, %rsp
	.seh_stackalloc 16
	leaq	16(%rsp), %rbp
	.seh_setframe %rbp, 16
	.seh_endprologue
	movb	$1, %al
	testb	$1, %al
	jne	.LBB0_1
	jmp	.LBB0_2
.LBB0_1:                                # %if.then
	movl	$1, %ecx
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	jmp	.LBB0_3
.LBB0_2:                                # %if.else
	jmp	.LBB0_3
.LBB0_3:                                # %if.end
	movb	$1, %al
	testb	$1, %al
	jne	.LBB0_4
	jmp	.LBB0_5
.LBB0_4:                                # %if.then1
	movl	$1, %ecx
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	jmp	.LBB0_6
.LBB0_5:                                # %if.else2
	jmp	.LBB0_6
.LBB0_6:                                # %if.end3
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	testb	$1, %al
	jne	.LBB0_7
	jmp	.LBB0_8
.LBB0_7:                                # %if.then4
	jmp	.LBB0_9
.LBB0_8:                                # %if.else5
	movl	$1, %ecx
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
.LBB0_9:                                # %if.end6
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -8(%rbp)                  # 8-byte Spill
	movq	$15, (%rax)
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	testb	$1, %al
	jne	.LBB0_10
	jmp	.LBB0_11
.LBB0_10:                               # %if.then7
	jmp	.LBB0_12
.LBB0_11:                               # %if.else8
	movq	-8(%rbp), %rax                  # 8-byte Reload
	cmpq	$20, (%rax)
	jl	.LBB0_13
	jmp	.LBB0_14
.LBB0_12:                               # %if.end9
	movb	$1, %al
	testb	$1, %al
	jne	.LBB0_16
	jmp	.LBB0_17
.LBB0_13:                               # %if.then10
	movl	$1, %ecx
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	jmp	.LBB0_15
.LBB0_14:                               # %if.else11
	xorl	%ecx, %ecx
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
.LBB0_15:                               # %if.end12
	jmp	.LBB0_22
.LBB0_16:                               # %if.then13
                                        # implicit-def: $al
	testb	$1, %al
	jne	.LBB0_19
	jmp	.LBB0_20
.LBB0_17:                               # %if.else14
	jmp	.LBB0_18
.LBB0_18:                               # %if.end15
	jmp	.LBB0_22
.LBB0_19:                               # %if.then16
	jmp	.LBB0_21
.LBB0_20:                               # %if.else17
	jmp	.LBB0_21
.LBB0_21:                               # %if.end18
	jmp	.LBB0_22
.LBB0_22:                               # %exit
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	movq	%rbp, %rsp
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
