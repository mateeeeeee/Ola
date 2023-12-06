	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	"S::PrintX";
	.scl	2;
	.type	32;
	.endef
	.globl	"S::PrintX"                     # -- Begin function S::PrintX
	.p2align	4, 0x90
"S::PrintX":                            # @"S::PrintX"
.seh_proc "S::PrintX"
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	qword ptr [rsp + 32], rdx
	mov	rcx, qword ptr [rcx]
	call	PrintInt
# %bb.1:                                # %exit
	nop
	add	rsp, 40
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
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 48], 20
	mov	qword ptr [rsp + 40], 10
	mov	qword ptr [rsp + 56], 30
	lea	rcx, [rsp + 40]
	mov	edx, 100
	call	"S::PrintX"
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 64]
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym PrintInt
	.addrsig_sym "S::PrintX"
