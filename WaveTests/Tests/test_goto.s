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
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	jmp	.LBB0_1
.LBB0_1:                                # %label.Label1
	movl	$1, %ecx
	callq	Assert
	movl	$1, %ecx
	callq	Assert
	movb	$1, %al
	testb	$1, %al
	jne	.LBB0_3
	jmp	.LBB0_4
.LBB0_2:                                # %label.Label2
	movl	$1, %ecx
	callq	Assert
	movl	$1, %ecx
	callq	Assert
	jmp	.LBB0_5
.LBB0_3:                                # %if.then
	jmp	.LBB0_2
.LBB0_4:                                # %if.end
	jmp	.LBB0_2
.LBB0_5:                                # %exit
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
