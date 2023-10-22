	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"WaveModule"
	.def	add;
	.scl	2;
	.type	32;
	.endef
	.globl	add                             # -- Begin function add
	.p2align	4, 0x90
add:                                    # @add
.seh_proc add
# %bb.0:                                # %entry
	subq	$16, %rsp
	.seh_stackalloc 16
	.seh_endprologue
	movq	%rdx, (%rsp)                    # 8-byte Spill
	movq	%rcx, 8(%rsp)                   # 8-byte Spill
	jmp	.LBB0_1
.LBB0_1:                                # %exit
	movq	(%rsp), %rcx                    # 8-byte Reload
	movq	8(%rsp), %rax                   # 8-byte Reload
	addq	%rcx, %rax
	addq	$16, %rsp
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
	movl	$4, %edx
	callq	add
	movq	%rax, 32(%rsp)                  # 8-byte Spill
# %bb.1:                                # %exit
	movq	32(%rsp), %rax                  # 8-byte Reload
	addq	$1, %rax
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym add
