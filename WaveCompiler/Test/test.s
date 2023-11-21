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
# %bb.0:                                # %entry
	mov	qword ptr [rcx], rdx
# %bb.1:                                # %exit
	ret
                                        # -- End function
	.def	"S::SetY";
	.scl	2;
	.type	32;
	.endef
	.globl	"S::SetY"                       # -- Begin function S::SetY
	.p2align	4, 0x90
"S::SetY":                              # @"S::SetY"
# %bb.0:                                # %entry
	mov	qword ptr [rcx + 8], rdx
# %bb.1:                                # %exit
	ret
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
# %bb.0:                                # %entry
	mov	rax, qword ptr [rcx]
	shl	rax
	mov	qword ptr [rcx], rax
	mov	rax, qword ptr [rcx + 8]
	shl	rax
	mov	qword ptr [rcx + 8], rax
# %bb.1:                                # %exit
	ret
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
	mov	qword ptr [rsp + 48], 10
	mov	qword ptr [rsp + 56], 10
	lea	rcx, [rsp + 48]
	call	ModifyS
	cmp	qword ptr [rsp + 48], 20
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 56], 20
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 48]
	mov	qword ptr [rsp + 32], rax
	lea	rcx, [rsp + 48]
	call	"S::GetY"
	mov	rcx, rax
	call	PrintInt
	lea	rcx, [rsp + 32]
	call	"S::GetX"
	cmp	rax, 20
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 32]
	add	rax, 10
	mov	qword ptr [rsp + 32], rax
	lea	rcx, [rsp + 48]
	call	"S::GetX"
	cmp	rax, 20
	sete	cl
	call	Assert
	lea	rcx, [rsp + 32]
	call	"S::GetX"
	cmp	rax, 30
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
	.addrsig_sym PrintInt
	.addrsig_sym "S::GetX"
	.addrsig_sym "S::GetY"
	.addrsig_sym ModifyS
