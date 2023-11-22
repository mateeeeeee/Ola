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
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	mov	qword ptr [rsp + 8], rcx
	mov	rax, qword ptr [rsp + 8]
	mov	rcx, qword ptr [rax]
	add	rcx, 1
	mov	qword ptr [rax], rcx
	mov	rax, qword ptr [rax]
	mov	rax, qword ptr [rax]
	mov	qword ptr [rsp], rax
	mov	rax, qword ptr [rsp]
	add	rax, 1
	mov	qword ptr [rsp], rax
# %bb.1:                                # %exit
	add	rsp, 16
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
	mov	qword ptr [rsp + 40], 9
	lea	rcx, [rsp + 40]
	call	ModifyInt
	mov	rax, qword ptr [rsp + 40]
	mov	qword ptr [rsp + 48], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym ModifyInt
