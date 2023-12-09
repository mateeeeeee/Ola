	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	"Base::GetX";
	.scl	2;
	.type	32;
	.endef
	.globl	"Base::GetX"                    # -- Begin function Base::GetX
	.p2align	4, 0x90
"Base::GetX":                           # @"Base::GetX"
.seh_proc "Base::GetX"
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
	.def	"Base::GetY";
	.scl	2;
	.type	32;
	.endef
	.globl	"Base::GetY"                    # -- Begin function Base::GetY
	.p2align	4, 0x90
"Base::GetY":                           # @"Base::GetY"
.seh_proc "Base::GetY"
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
	mov	rax, qword ptr [rcx + 24]
	mov	qword ptr [rsp], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	pop	rcx
	ret
	.seh_endproc
                                        # -- End function
	.def	"ExtDerived::GetY";
	.scl	2;
	.type	32;
	.endef
	.globl	"ExtDerived::GetY"              # -- Begin function ExtDerived::GetY
	.p2align	4, 0x90
"ExtDerived::GetY":                     # @"ExtDerived::GetY"
.seh_proc "ExtDerived::GetY"
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	mov	rax, qword ptr [rcx + 32]
	mov	qword ptr [rsp], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	pop	rcx
	ret
	.seh_endproc
                                        # -- End function
	.def	"ExtDerived::GetX";
	.scl	2;
	.type	32;
	.endef
	.globl	"ExtDerived::GetX"              # -- Begin function ExtDerived::GetX
	.p2align	4, 0x90
"ExtDerived::GetX":                     # @"ExtDerived::GetX"
.seh_proc "ExtDerived::GetX"
# %bb.0:                                # %entry
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 40], rcx       # 8-byte Spill
	mov	qword ptr [rsp + 64], rdx
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax + 8]
	mov	rcx, qword ptr [rsp + 40]       # 8-byte Reload
	mov	qword ptr [rsp + 48], rax       # 8-byte Spill
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax + 8]
	mov	rcx, rax
	mov	rax, qword ptr [rsp + 48]       # 8-byte Reload
	add	rax, rcx
	mov	qword ptr [rsp + 56], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 56]
	add	rsp, 72
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
	lea	rax, [rip + VTable_ExtDerived]
	mov	qword ptr [rsp + 40], rax
	mov	qword ptr [rsp + 64], 100
	mov	qword ptr [rsp + 48], 10
	mov	qword ptr [rsp + 56], 20
	mov	qword ptr [rsp + 72], 200
	lea	rax, [rsp + 40]
	mov	qword ptr [rsp + 32], rax
	mov	rax, qword ptr [rsp + 40]
	lea	rcx, [rsp + 40]
	mov	edx, 1
	call	qword ptr [rax + 16]
	mov	qword ptr [rsp + 80], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 80]
	add	rsp, 88
	ret
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr"
	.p2align	3, 0x0                          # @VTable_Base
VTable_Base:
	.quad	"Base::GetX"
	.quad	"Base::GetY"

	.p2align	3, 0x0                          # @VTable_Derived
VTable_Derived:
	.quad	"Derived::GetX"
	.quad	"Base::GetY"

	.p2align	4, 0x0                          # @VTable_ExtDerived
VTable_ExtDerived:
	.quad	"Derived::GetX"
	.quad	"ExtDerived::GetY"
	.quad	"ExtDerived::GetX"

	.addrsig
	.addrsig_sym "Base::GetX"
	.addrsig_sym "Base::GetY"
	.addrsig_sym "Derived::GetX"
	.addrsig_sym "ExtDerived::GetY"
	.addrsig_sym "ExtDerived::GetX"
	.addrsig_sym VTable_ExtDerived
