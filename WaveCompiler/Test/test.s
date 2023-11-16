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
	sub	rsp, 32
	.seh_stackalloc 32
	.seh_endprologue
	mov	qword ptr [rsp], 1
	mov	qword ptr [rsp + 8], 2
	mov	qword ptr [rsp + 16], 3
	mov	qword ptr [rsp], 10
	mov	qword ptr [rsp + 24], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 24]
	add	rsp, 32
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
