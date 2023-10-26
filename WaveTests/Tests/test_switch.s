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
	jmp	.LBB0_1
.LBB0_1:                                # %switch.header
	movb	$1, %al
	testb	%al, %al
	jne	.LBB0_5
	jmp	.LBB0_20
.LBB0_20:                               # %switch.header
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	testb	%al, %al
	jne	.LBB0_6
	jmp	.LBB0_21
.LBB0_21:                               # %switch.header
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	testb	%al, %al
	jne	.LBB0_4
	jmp	.LBB0_2
.LBB0_2:                                # %switch.default
	jmp	.LBB0_3
.LBB0_3:                                # %switch.end
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -8(%rbp)                  # 8-byte Spill
	movq	$1, (%rax)
	jmp	.LBB0_7
.LBB0_4:                                # %switch.case1
	jmp	.LBB0_3
.LBB0_5:                                # %switch.case2
	movl	$1, %ecx
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	jmp	.LBB0_3
.LBB0_6:                                # %switch.case3
	jmp	.LBB0_3
.LBB0_7:                                # %switch.header4
	movq	-8(%rbp), %rax                  # 8-byte Reload
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)                 # 8-byte Spill
	subq	$1, %rax
	je	.LBB0_10
	jmp	.LBB0_22
.LBB0_22:                               # %switch.header4
	movq	-16(%rbp), %rax                 # 8-byte Reload
	subq	$2, %rax
	je	.LBB0_11
	jmp	.LBB0_23
.LBB0_23:                               # %switch.header4
	movq	-16(%rbp), %rax                 # 8-byte Reload
	subq	$3, %rax
	je	.LBB0_12
	jmp	.LBB0_8
.LBB0_8:                                # %switch.default5
	xorl	%ecx, %ecx
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
.LBB0_9:                                # %switch.end6
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	%rax, -24(%rbp)                 # 8-byte Spill
	movq	$5, (%rax)
	jmp	.LBB0_13
.LBB0_10:                               # %switch.case17
	movl	$1, %ecx
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
.LBB0_11:                               # %switch.case28
	movl	$1, %ecx
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	jmp	.LBB0_9
.LBB0_12:                               # %switch.case310
	xorl	%ecx, %ecx
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	jmp	.LBB0_9
.LBB0_13:                               # %switch.header13
	movq	-24(%rbp), %rax                 # 8-byte Reload
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)                 # 8-byte Spill
	subq	$1, %rax
	je	.LBB0_16
	jmp	.LBB0_24
.LBB0_24:                               # %switch.header13
	movq	-32(%rbp), %rax                 # 8-byte Reload
	subq	$2, %rax
	je	.LBB0_17
	jmp	.LBB0_25
.LBB0_25:                               # %switch.header13
	movq	-32(%rbp), %rax                 # 8-byte Reload
	subq	$3, %rax
	je	.LBB0_18
	jmp	.LBB0_14
.LBB0_14:                               # %switch.default14
	movl	$1, %ecx
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
.LBB0_15:                               # %switch.end15
	jmp	.LBB0_19
.LBB0_16:                               # %switch.case116
	xorl	%ecx, %ecx
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	jmp	.LBB0_15
.LBB0_17:                               # %switch.case218
	xorl	%ecx, %ecx
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	jmp	.LBB0_15
.LBB0_18:                               # %switch.case320
	xorl	%ecx, %ecx
	subq	$32, %rsp
	callq	Assert
	addq	$32, %rsp
	jmp	.LBB0_15
.LBB0_19:                               # %exit
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	movq	%rbp, %rsp
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
