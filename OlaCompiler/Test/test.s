	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	"D::D__I";
	.scl	2;
	.type	32;
	.endef
	.globl	"D::D__I"                       # -- Begin function D::D__I
	.p2align	4, 0x90
"D::D__I":                              # @"D::D__I"
.seh_proc "D::D__I"
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
	.def	"D::D__I__I";
	.scl	2;
	.type	32;
	.endef
	.globl	"D::D__I__I"                    # -- Begin function D::D__I__I
	.p2align	4, 0x90
"D::D__I__I":                           # @"D::D__I__I"
.seh_proc "D::D__I__I"
# %bb.0:                                # %entry
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	mov	qword ptr [rsp + 8], rdx
	mov	qword ptr [rsp], r8
	mov	rax, qword ptr [rsp + 8]
	imul	rax, qword ptr [rsp]
	mov	qword ptr [rcx], rax
# %bb.1:                                # %exit
	add	rsp, 16
	ret
	.seh_endproc
                                        # -- End function
	.def	"D::X";
	.scl	2;
	.type	32;
	.endef
	.globl	"D::X"                          # -- Begin function D::X
	.p2align	4, 0x90
"D::X":                                 # @"D::X"
.seh_proc "D::X"
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	mov	rax, qword ptr [rcx]
	mov	qword ptr [rsp], rax
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
	mov	edx, 5
	call	"D::D__I"
	mov	qword ptr [rsp + 32], 0
	lea	rcx, [rsp + 32]
	mov	edx, 2
	mov	r8d, 3
	call	"D::D__I__I"
	lea	rcx, [rsp + 32]
	call	"D::X"
	mov	qword ptr [rsp + 48], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym "D::D__I"
	.addrsig_sym "D::D__I__I"
	.addrsig_sym "D::X"
