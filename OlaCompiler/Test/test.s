	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	"S::Init__I__I";
	.scl	2;
	.type	32;
	.endef
	.globl	"S::Init__I__I"                 # -- Begin function S::Init__I__I
	.p2align	4, 0x90
"S::Init__I__I":                        # @"S::Init__I__I"
.seh_proc "S::Init__I__I"
# %bb.0:                                # %entry
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	mov	qword ptr [rsp + 8], rdx
	mov	qword ptr [rsp], r8
	mov	rax, qword ptr [rsp + 8]
	mov	qword ptr [rcx], rax
	mov	rax, qword ptr [rsp]
	mov	qword ptr [rcx + 8], rax
# %bb.1:                                # %exit
	add	rsp, 16
	ret
	.seh_endproc
                                        # -- End function
	.def	"S::SetX__I";
	.scl	2;
	.type	32;
	.endef
	.globl	"S::SetX__I"                    # -- Begin function S::SetX__I
	.p2align	4, 0x90
"S::SetX__I":                           # @"S::SetX__I"
.seh_proc "S::SetX__I"
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
	.def	"S::SetY__I";
	.scl	2;
	.type	32;
	.endef
	.globl	"S::SetY__I"                    # -- Begin function S::SetY__I
	.p2align	4, 0x90
"S::SetY__I":                           # @"S::SetY__I"
.seh_proc "S::SetY__I"
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
	.def	StructByValue__S;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function StructByValue__S
StructByValue__S:                       # @StructByValue__S
.seh_proc StructByValue__S
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 40], rcx
	mov	qword ptr [rsp + 48], rdx
	lea	rcx, [rsp + 40]
	mov	edx, 100
	call	"S::SetX__I"
	lea	rcx, [rsp + 40]
	mov	edx, 100
	call	"S::SetY__I"
	lea	rcx, [rsp + 40]
	call	"S::GetX"
	cmp	rax, 100
	sete	cl
	call	Assert
	lea	rcx, [rsp + 40]
	call	"S::GetY"
	cmp	rax, 100
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	StructByRef__Sref;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function StructByRef__Sref
StructByRef__Sref:                      # @StructByRef__Sref
.seh_proc StructByRef__Sref
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], rcx
	mov	rcx, qword ptr [rsp + 48]
	mov	qword ptr [rsp + 40], rcx       # 8-byte Spill
	mov	edx, 1000
	call	"S::SetX__I"
	mov	rcx, qword ptr [rsp + 40]       # 8-byte Reload
	mov	edx, 1000
	call	"S::SetY__I"
	mov	rcx, qword ptr [rsp + 40]       # 8-byte Reload
	call	"S::GetX"
	cmp	rax, 1000
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 40]       # 8-byte Reload
	call	"S::GetY"
	cmp	rax, 1000
	sete	cl
	call	Assert
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
	sub	rsp, 88
	.seh_stackalloc 88
	.seh_endprologue
	mov	qword ptr [rsp + 64], 0
	mov	qword ptr [rsp + 72], 0
	lea	rcx, [rsp + 64]
	mov	r8d, 10
	mov	rdx, r8
	call	"S::Init__I__I"
	mov	rcx, qword ptr [rsp + 64]
	mov	rdx, qword ptr [rsp + 72]
	call	StructByValue__S
	lea	rcx, [rsp + 64]
	call	"S::GetX"
	cmp	rax, 10
	sete	cl
	call	Assert
	lea	rcx, [rsp + 64]
	call	"S::GetY"
	cmp	rax, 10
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 64]
	mov	qword ptr [rsp + 48], rax
	mov	rax, qword ptr [rsp + 72]
	mov	qword ptr [rsp + 56], rax
	lea	rcx, [rsp + 64]
	mov	edx, 25
	call	"S::SetX__I"
	lea	rcx, [rsp + 64]
	mov	edx, 25
	call	"S::SetY__I"
	lea	rcx, [rsp + 48]
	call	"S::GetX"
	cmp	rax, 10
	sete	cl
	call	Assert
	lea	rcx, [rsp + 48]
	call	"S::GetY"
	cmp	rax, 10
	sete	cl
	call	Assert
	lea	rcx, [rsp + 64]
	call	"S::GetX"
	cmp	rax, 25
	sete	cl
	call	Assert
	lea	rcx, [rsp + 64]
	call	"S::GetY"
	cmp	rax, 25
	sete	cl
	call	Assert
	lea	rcx, [rsp + 64]
	call	StructByRef__Sref
	lea	rcx, [rsp + 64]
	call	"S::GetX"
	cmp	rax, 1000
	sete	cl
	call	Assert
	lea	rcx, [rsp + 64]
	call	"S::GetY"
	cmp	rax, 1000
	sete	cl
	call	Assert
	lea	rax, [rsp + 64]
	mov	qword ptr [rsp + 40], rax
	mov	rcx, qword ptr [rsp + 40]
	mov	qword ptr [rsp + 32], rcx       # 8-byte Spill
	call	"S::GetX"
	cmp	rax, 1000
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 32]       # 8-byte Reload
	call	"S::GetY"
	cmp	rax, 1000
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 32]       # 8-byte Reload
	xor	eax, eax
	mov	edx, eax
	call	"S::SetX__I"
	lea	rcx, [rsp + 64]
	call	"S::GetX"
	cmp	rax, 0
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 80], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 80]
	add	rsp, 88
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym "S::Init__I__I"
	.addrsig_sym "S::SetX__I"
	.addrsig_sym "S::SetY__I"
	.addrsig_sym "S::GetX"
	.addrsig_sym "S::GetY"
	.addrsig_sym StructByValue__S
	.addrsig_sym StructByRef__Sref
