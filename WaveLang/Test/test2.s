	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"WaveModule"
	.def	f;
	.scl	2;
	.type	32;
	.endef
	.globl	f                               # -- Begin function f
	.p2align	4, 0x90
f:                                      # @f
.seh_proc f
# %bb.0:                                # %entry
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	shlq	%rcx
	movq	%rcx, (%rsp)
# %bb.1:                                # %exit
	movq	(%rsp), %rax
	popq	%rcx
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
