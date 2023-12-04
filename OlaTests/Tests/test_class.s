	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_class.ola"
	.def	"S::Init";
	.scl	2;
	.type	32;
	.endef
	.globl	"S::Init"                       # -- Begin function S::Init
	.p2align	4, 0x90
"S::Init":                              # @"S::Init"
# %bb.0:                                # %entry
	mov	qword ptr [rcx], rdx
	mov	qword ptr [rcx + 8], r8
	ret
                                        # -- End function
	.def	"S::SetX";
	.scl	2;
	.type	32;
	.endef
	.globl	"S::SetX"                       # -- Begin function S::SetX
	.p2align	4, 0x90
"S::SetX":                              # @"S::SetX"
# %bb.0:                                # %entry
	mov	qword ptr [rcx], rdx
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
	mov	rax, qword ptr [rsp]
	pop	rcx
	ret
	.seh_endproc
                                        # -- End function
	.def	StructByValue;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function StructByValue
StructByValue:                          # @StructByValue
.seh_proc StructByValue
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 40], rcx
	mov	qword ptr [rsp + 48], rdx
	lea	rcx, [rsp + 40]
	mov	edx, 100
	call	"S::SetX"
	lea	rcx, [rsp + 40]
	mov	edx, 100
	call	"S::SetY"
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
	nop
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	StructByRef;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function StructByRef
StructByRef:                            # @StructByRef
.seh_proc StructByRef
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], rcx       # 8-byte Spill
	mov	edx, 1000
	mov	qword ptr [rsp + 40], rdx       # 8-byte Spill
	call	"S::SetX"
	mov	rdx, qword ptr [rsp + 40]       # 8-byte Reload
	mov	rcx, qword ptr [rsp + 48]       # 8-byte Reload
	call	"S::SetY"
	mov	rcx, qword ptr [rsp + 48]       # 8-byte Reload
	call	"S::GetX"
	sub	rax, 1000
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 48]       # 8-byte Reload
	call	"S::GetY"
	sub	rax, 1000
	sete	cl
	add	rsp, 56
	jmp	Assert                          # TAILCALL
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
	mov	qword ptr [rsp + 56], 0
	mov	qword ptr [rsp + 64], 0
	lea	rcx, [rsp + 56]
	mov	r8d, 10
	mov	rdx, r8
	call	"S::Init"
	mov	rcx, qword ptr [rsp + 56]
	mov	rdx, qword ptr [rsp + 64]
	call	StructByValue
	lea	rcx, [rsp + 56]
	call	"S::GetX"
	cmp	rax, 10
	sete	cl
	call	Assert
	lea	rcx, [rsp + 56]
	call	"S::GetY"
	cmp	rax, 10
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 56]
	mov	qword ptr [rsp + 40], rax
	mov	rax, qword ptr [rsp + 64]
	mov	qword ptr [rsp + 48], rax
	lea	rcx, [rsp + 56]
	mov	edx, 25
	call	"S::SetX"
	lea	rcx, [rsp + 56]
	mov	edx, 25
	call	"S::SetY"
	lea	rcx, [rsp + 40]
	call	"S::GetX"
	cmp	rax, 10
	sete	cl
	call	Assert
	lea	rcx, [rsp + 40]
	call	"S::GetY"
	cmp	rax, 10
	sete	cl
	call	Assert
	lea	rcx, [rsp + 56]
	call	"S::GetX"
	cmp	rax, 25
	sete	cl
	call	Assert
	lea	rcx, [rsp + 56]
	call	"S::GetY"
	cmp	rax, 25
	sete	cl
	call	Assert
	lea	rcx, [rsp + 56]
	call	StructByRef
	lea	rcx, [rsp + 56]
	call	"S::GetX"
	cmp	rax, 1000
	sete	cl
	call	Assert
	lea	rcx, [rsp + 56]
	call	"S::GetY"
	cmp	rax, 1000
	sete	cl
	call	Assert
	lea	rcx, [rsp + 56]
	call	"S::GetX"
	cmp	rax, 1000
	sete	cl
	call	Assert
	lea	rcx, [rsp + 56]
	call	"S::GetY"
	cmp	rax, 1000
	sete	cl
	call	Assert
	lea	rcx, [rsp + 56]
	xor	eax, eax
	mov	edx, eax
	call	"S::SetX"
	lea	rcx, [rsp + 56]
	call	"S::GetX"
	cmp	rax, 0
	sete	cl
	call	Assert
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym "S::Init"
	.addrsig_sym "S::SetX"
	.addrsig_sym "S::SetY"
	.addrsig_sym "S::GetX"
	.addrsig_sym "S::GetY"
	.addrsig_sym StructByValue
	.addrsig_sym StructByRef
