	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	GetX;
	.scl	2;
	.type	32;
	.endef
	.globl	GetX                            # -- Begin function GetX
	.p2align	4, 0x90
GetX:                                   # @GetX
.seh_proc GetX
# %bb.0:                                # %entry
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	mov	qword ptr [rsp], 20
	mov	rax, qword ptr [rsp]
	add	rax, 10
	mov	qword ptr [rsp + 8], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 8]
	add	rsp, 16
	ret
	.seh_endproc
                                        # -- End function
	.def	GetY;
	.scl	2;
	.type	32;
	.endef
	.globl	GetY                            # -- Begin function GetY
	.p2align	4, 0x90
GetY:                                   # @GetY
.seh_proc GetY
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	call	GetX
	shl	rax
	mov	qword ptr [rsp + 32], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
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
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	mov	qword ptr [rsp], 25
	mov	rax, qword ptr [rsp]
	add	rax, 10
	mov	qword ptr [rsp + 8], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 8]
	add	rsp, 16
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
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	call	"S::GetX"
	shl	rax
	mov	qword ptr [rsp + 32], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
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
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	lea	rcx, [rsp + 40]
	call	"S::GetY"
	mov	qword ptr [rsp + 32], rax       # 8-byte Spill
	call	GetY
	mov	rcx, rax
	mov	rax, qword ptr [rsp + 32]       # 8-byte Reload
	add	rax, rcx
	mov	qword ptr [rsp + 48], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym GetX
	.addrsig_sym GetY
	.addrsig_sym "S::GetX"
	.addrsig_sym "S::GetY"
