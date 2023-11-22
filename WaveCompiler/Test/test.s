	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"WaveModule"
	.def	"S::SetX";
	.scl	2;
	.type	32;
	.endef
	.globl	"S::SetX"                       # -- Begin function S::SetX
	.p2align	4, 0x90
"S::SetX":                              # @"S::SetX"
.seh_proc "S::SetX"
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
	.def	"S::SetY";
	.scl	2;
	.type	32;
	.endef
	.globl	"S::SetY"                       # -- Begin function S::SetY
	.p2align	4, 0x90
"S::SetY":                              # @"S::SetY"
.seh_proc "S::SetY"
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	mov	qword ptr [rsp], rdx
	mov	rax, qword ptr [rsp]
	mov	qword ptr [rcx + 8], rax
# %bb.1:                                # %exit
	pop	rax
	ret
	.seh_endproc
                                        # -- End function
	.def	"S::GetX";
	.scl	2;
	.type	32;
	.endef
	.globl	"S::GetX"                       # -- Begin function S::GetX
	.p2align	4, 0x90
"S::GetX":                              # @"S::GetX"
.seh_proc "S::GetX"
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
	.def	"S::GetY";
	.scl	2;
	.type	32;
	.endef
	.globl	"S::GetY"                       # -- Begin function S::GetY
	.p2align	4, 0x90
"S::GetY":                              # @"S::GetY"
.seh_proc "S::GetY"
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	mov	rax, qword ptr [rcx + 8]
	mov	qword ptr [rsp], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	pop	rcx
	ret
	.seh_endproc
                                        # -- End function
	.def	ModifyS;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function ModifyS
ModifyS:                                # @ModifyS
.seh_proc ModifyS
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 40], rcx
	mov	qword ptr [rsp + 48], rdx
	mov	rax, qword ptr [rsp + 40]
	shl	rax
	mov	qword ptr [rsp + 40], rax
	mov	rax, qword ptr [rsp + 48]
	shl	rax
	mov	qword ptr [rsp + 48], rax
	mov	rcx, qword ptr [rsp + 40]
	call	PrintInt
	mov	rcx, qword ptr [rsp + 48]
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
	mov	qword ptr [rsp + 32], 0
	mov	qword ptr [rsp + 40], 0
	mov	qword ptr [rsp + 32], 10
	mov	qword ptr [rsp + 40], 10
	mov	rcx, qword ptr [rsp + 32]
	mov	rdx, qword ptr [rsp + 40]
	call	ModifyS
	cmp	qword ptr [rsp + 32], 10
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 40], 10
	sete	cl
	call	Assert
	lea	rcx, [rsp + 32]
	call	"S::GetX"
	cmp	rax, 10
	sete	cl
	call	Assert
	lea	rcx, [rsp + 32]
	call	"S::GetY"
	cmp	rax, 10
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 32]
	add	rax, 10
	mov	qword ptr [rsp + 32], rax
	lea	rcx, [rsp + 32]
	call	"S::GetX"
	cmp	rax, 20
	sete	cl
	call	Assert
	lea	rcx, [rsp + 32]
	call	"S::GetX"
	cmp	rax, 20
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 48], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym PrintInt
	.addrsig_sym "S::GetX"
	.addrsig_sym "S::GetY"
	.addrsig_sym ModifyS
