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
	.def	"Base::GetSumX";
	.scl	2;
	.type	32;
	.endef
	.globl	"Base::GetSumX"                 # -- Begin function Base::GetSumX
	.p2align	4, 0x90
"Base::GetSumX":                        # @"Base::GetSumX"
.seh_proc "Base::GetSumX"
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax]
	mov	qword ptr [rsp + 32], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
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
	.def	"Derived::GetSumX";
	.scl	2;
	.type	32;
	.endef
	.globl	"Derived::GetSumX"              # -- Begin function Derived::GetSumX
	.p2align	4, 0x90
"Derived::GetSumX":                     # @"Derived::GetSumX"
.seh_proc "Derived::GetSumX"
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 32], rcx       # 8-byte Spill
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax]
	mov	rcx, qword ptr [rsp + 32]       # 8-byte Reload
	mov	qword ptr [rsp + 40], rax       # 8-byte Spill
	call	"Base::GetX"
	mov	rcx, rax
	mov	rax, qword ptr [rsp + 40]       # 8-byte Reload
	add	rax, rcx
	mov	qword ptr [rsp + 48], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	TestBase;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestBase
TestBase:                               # @TestBase
.seh_proc TestBase
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	qword ptr [rsp + 32], rcx
	mov	rcx, qword ptr [rsp + 32]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax]
	cmp	rax, 1
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.def	TestDerived;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestDerived
TestDerived:                            # @TestDerived
.seh_proc TestDerived
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	qword ptr [rsp + 32], rcx
	mov	rcx, qword ptr [rsp + 32]
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax]
	cmp	rax, 10
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.def	TestDerived2;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestDerived2
TestDerived2:                           # @TestDerived2
.seh_proc TestDerived2
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], rcx
	mov	rcx, qword ptr [rsp + 48]
	mov	qword ptr [rsp + 40], rcx       # 8-byte Spill
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax]
	cmp	rax, 10
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 40]       # 8-byte Reload
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax + 8]
	cmp	rax, 11
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
	lea	rax, [rip + VTable_Base]
	mov	qword ptr [rsp + 64], rax
	mov	qword ptr [rsp + 72], 1
	lea	rcx, [rsp + 64]
	call	TestBase
	lea	rax, [rip + VTable_Derived]
	mov	qword ptr [rsp + 40], rax
	mov	qword ptr [rsp + 48], 1
	mov	qword ptr [rsp + 56], 10
	lea	rcx, [rsp + 40]
	call	TestDerived
	lea	rcx, [rsp + 40]
	call	TestDerived2
	mov	qword ptr [rsp + 80], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 80]
	add	rsp, 88
	ret
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr"
	.p2align	3, 0x0                          # @VTable_Abstract
VTable_Abstract:
	.zero	8

	.p2align	3, 0x0                          # @VTable_Base
VTable_Base:
	.quad	"Base::GetX"
	.quad	"Base::GetSumX"

	.p2align	3, 0x0                          # @VTable_Derived
VTable_Derived:
	.quad	"Derived::GetX"
	.quad	"Derived::GetSumX"

	.addrsig
	.addrsig_sym Assert
	.addrsig_sym "Base::GetX"
	.addrsig_sym "Base::GetSumX"
	.addrsig_sym "Derived::GetX"
	.addrsig_sym "Derived::GetSumX"
	.addrsig_sym TestBase
	.addrsig_sym TestDerived
	.addrsig_sym TestDerived2
	.addrsig_sym VTable_Base
	.addrsig_sym VTable_Derived
