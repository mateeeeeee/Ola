	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"WaveModule"
	.def	"S::Init";
	.scl	2;
	.type	32;
	.endef
	.globl	"S::Init"                       # -- Begin function S::Init
	.p2align	4, 0x90
"S::Init":                              # @"S::Init"
.seh_proc "S::Init"
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	mov	qword ptr [rsp], rdx
	mov	rax, qword ptr [rsp]
	mov	qword ptr [rcx], rax
# %bb.1:                                # %exit
	pop	rax
	ret
	.seh_endproc
                                        # -- End function
	.def	"S::X";
	.scl	2;
	.type	32;
	.endef
	.globl	"S::X"                          # -- Begin function S::X
	.p2align	4, 0x90
"S::X":                                 # @"S::X"
.seh_proc "S::X"
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	mov	qword ptr [rsp], rcx
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	pop	rcx
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
	mov	edx, 10
	call	"S::Init"
	lea	rcx, [rsp + 40]
	call	"S::X"
	mov	qword ptr [rsp + 32], rax
	mov	rax, qword ptr [rsp + 32]
	mov	rcx, qword ptr [rax]
	add	rcx, 1
	mov	qword ptr [rax], rcx
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
	.addrsig_sym "S::Init"
	.addrsig_sym "S::X"
