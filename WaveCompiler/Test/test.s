	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
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
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	mov	qword ptr [rsp], 5
	mov	rax, qword ptr [rsp]
	mov	qword ptr [rsp + 8], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 8]
	add	rsp, 16
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
