	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	"Derived::GetY";
	.scl	2;
	.type	32;
	.endef
	.globl	"Derived::GetY"                 # -- Begin function Derived::GetY
	.p2align	4, 0x90
"Derived::GetY":                        # @"Derived::GetY"
.seh_proc "Derived::GetY"
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
	.def	"Derived::GetX";
	.scl	2;
	.type	32;
	.endef
	.globl	"Derived::GetX"                 # -- Begin function Derived::GetX
	.p2align	4, 0x90
"Derived::GetX":                        # @"Derived::GetX"
.seh_proc "Derived::GetX"
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	mov	rax, qword ptr [rcx + 16]
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
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	lea	rax, [rip + VTable_Derived]
	mov	qword ptr [rsp + 40], rax
	mov	qword ptr [rsp + 48], 100
	mov	qword ptr [rsp + 56], 10
	lea	rax, [rsp + 40]
	mov	qword ptr [rsp + 32], rax
	mov	rcx, qword ptr [rsp + 32]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax]
	mov	qword ptr [rsp + 64], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 64]
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr"
	.p2align	3, 0x0                          # @VTable_Base
VTable_Base:
	.zero	8

	.p2align	3, 0x0                          # @VTable_Derived
VTable_Derived:
	.quad	"Derived::GetX"
	.quad	"Derived::GetY"

	.addrsig
	.addrsig_sym "Derived::GetY"
	.addrsig_sym "Derived::GetX"
	.addrsig_sym VTable_Derived
