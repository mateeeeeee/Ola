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
	sub	rsp, 48
	.seh_stackalloc 48
	.seh_endprologue
	mov	qword ptr [rsp + 16], 1
	mov	qword ptr [rsp + 24], 2
	mov	qword ptr [rsp + 32], 3
	lea	rax, [rsp + 16]
	mov	qword ptr [rsp + 8], rax
	mov	rax, qword ptr [rsp + 8]
	mov	qword ptr [rsp], rax
	mov	qword ptr [rsp + 40], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 40]
	add	rsp, 48
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
