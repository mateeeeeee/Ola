	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	"B::B__I";
	.scl	2;
	.type	32;
	.endef
	.globl	"B::B__I"                       # -- Begin function B::B__I
	.p2align	4, 0x90
"B::B__I":                              # @"B::B__I"
.seh_proc "B::B__I"
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
	.def	"B::B__I__I";
	.scl	2;
	.type	32;
	.endef
	.globl	"B::B__I__I"                    # -- Begin function B::B__I__I
	.p2align	4, 0x90
"B::B__I__I":                           # @"B::B__I__I"
.seh_proc "B::B__I__I"
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
	.def	"D::D__I";
	.scl	2;
	.type	32;
	.endef
	.globl	"D::D__I"                       # -- Begin function D::D__I
	.p2align	4, 0x90
"D::D__I":                              # @"D::D__I"
.seh_proc "D::D__I"
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 40], rcx       # 8-byte Spill
	mov	qword ptr [rsp + 48], rdx
	mov	rdx, qword ptr [rsp + 48]
	shl	rdx
	call	"B::B__I"
	mov	rcx, qword ptr [rsp + 40]       # 8-byte Reload
	mov	rax, qword ptr [rsp + 48]
	mov	qword ptr [rcx + 8], rax
# %bb.1:                                # %exit
	add	rsp, 56
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
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 32], rcx       # 8-byte Spill
	mov	qword ptr [rsp + 48], rdx
	mov	qword ptr [rsp + 40], r8
	mov	rdx, qword ptr [rsp + 48]
	shl	rdx
	mov	r8, qword ptr [rsp + 40]
	shl	r8
	call	"B::B__I__I"
	mov	rcx, qword ptr [rsp + 32]       # 8-byte Reload
	mov	rax, qword ptr [rsp + 48]
	imul	rax, qword ptr [rsp + 40]
	mov	qword ptr [rcx + 8], rax
# %bb.1:                                # %exit
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
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 48], 0
	mov	qword ptr [rsp + 56], 0
	lea	rcx, [rsp + 48]
	mov	edx, 5
	call	"D::D__I"
	mov	qword ptr [rsp + 32], 0
	mov	qword ptr [rsp + 40], 0
	lea	rcx, [rsp + 32]
	mov	edx, 2
	mov	r8d, 3
	call	"D::D__I__I"
	cmp	qword ptr [rsp + 56], 5
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 48], 10
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 40], 6
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 32], 24
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 64], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 64]
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym "B::B__I"
	.addrsig_sym "B::B__I__I"
	.addrsig_sym "D::D__I"
	.addrsig_sym "D::D__I__I"
