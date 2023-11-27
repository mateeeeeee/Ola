	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"WaveModule"
	.def	ModifyInt;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function ModifyInt
ModifyInt:                              # @ModifyInt
.seh_proc ModifyInt
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], rcx
	mov	rax, qword ptr [rsp + 48]
	mov	qword ptr [rax], 10
	mov	rax, qword ptr [rax]
	add	rax, 10
	mov	qword ptr [rsp + 40], rax
	mov	rcx, qword ptr [rsp + 40]
	call	PrintInt
# %bb.1:                                # %exit
	nop
	add	rsp, 56
	ret
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
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 40], 0
	lea	rcx, [rsp + 40]
	call	ModifyInt
	mov	rcx, qword ptr [rsp + 40]
	call	PrintInt
	mov	qword ptr [rsp + 48], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym PrintInt
	.addrsig_sym ModifyInt
