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
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	qword ptr [rsp + 8], 1
	mov	qword ptr [rsp + 16], 2
	mov	qword ptr [rsp + 24], 3
	lea	rax, [rsp + 8]
	mov	qword ptr [rsp], rax
	mov	qword ptr [rsp + 24], 100
	mov	rax, qword ptr [rsp]
	mov	rax, qword ptr [rax + 16]
	mov	qword ptr [rsp + 32], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
