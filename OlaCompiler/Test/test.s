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
	mov	rax, qword ptr [rcx]
	mov	qword ptr [rsp], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	pop	rcx
	ret
	.seh_endproc
                                        # -- End function
	.def	"Base::GetSum";
	.scl	2;
	.type	32;
	.endef
	.globl	"Base::GetSum"                  # -- Begin function Base::GetSum
	.p2align	4, 0x90
"Base::GetSum":                         # @"Base::GetSum"
.seh_proc "Base::GetSum"
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	call	"Base::GetX"
	mov	qword ptr [rsp + 32], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
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
	.def	"Derived::GetSum";
	.scl	2;
	.type	32;
	.endef
	.globl	"Derived::GetSum"               # -- Begin function Derived::GetSum
	.p2align	4, 0x90
"Derived::GetSum":                      # @"Derived::GetSum"
.seh_proc "Derived::GetSum"
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 32], rcx       # 8-byte Spill
	call	"Derived::GetY"
	mov	rcx, qword ptr [rsp + 32]       # 8-byte Reload
	mov	qword ptr [rsp + 40], rax       # 8-byte Spill
	call	"Base::GetSum"
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
	.def	"ExtendedDerived::GetZ";
	.scl	2;
	.type	32;
	.endef
	.globl	"ExtendedDerived::GetZ"         # -- Begin function ExtendedDerived::GetZ
	.p2align	4, 0x90
"ExtendedDerived::GetZ":                # @"ExtendedDerived::GetZ"
.seh_proc "ExtendedDerived::GetZ"
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
	.def	"ExtendedDerived::GetSum";
	.scl	2;
	.type	32;
	.endef
	.globl	"ExtendedDerived::GetSum"       # -- Begin function ExtendedDerived::GetSum
	.p2align	4, 0x90
"ExtendedDerived::GetSum":              # @"ExtendedDerived::GetSum"
.seh_proc "ExtendedDerived::GetSum"
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 32], rcx       # 8-byte Spill
	call	"ExtendedDerived::GetZ"
	mov	rcx, qword ptr [rsp + 32]       # 8-byte Reload
	mov	qword ptr [rsp + 40], rax       # 8-byte Spill
	call	"Derived::GetSum"
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
	.def	PassBase__Base;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function PassBase__Base
PassBase__Base:                         # @PassBase__Base
.seh_proc PassBase__Base
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	qword ptr [rsp + 32], rcx
	lea	rcx, [rsp + 32]
	call	"Base::GetX"
	cmp	rax, 1
	sete	cl
	call	Assert
	lea	rcx, [rsp + 32]
	call	"Base::GetSum"
	cmp	rax, 1
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.def	PassBaseRef__Baseref;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function PassBaseRef__Baseref
PassBaseRef__Baseref:                   # @PassBaseRef__Baseref
.seh_proc PassBaseRef__Baseref
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], rcx
	mov	rcx, qword ptr [rsp + 48]
	mov	qword ptr [rsp + 40], rcx       # 8-byte Spill
	call	"Base::GetX"
	cmp	rax, 1
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 40]       # 8-byte Reload
	call	"Base::GetSum"
	cmp	rax, 1
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	PassDerived__Derived;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function PassDerived__Derived
PassDerived__Derived:                   # @PassDerived__Derived
.seh_proc PassDerived__Derived
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 40], rcx
	mov	qword ptr [rsp + 48], rdx
	lea	rcx, [rsp + 40]
	call	"Base::GetX"
	cmp	rax, 1
	sete	cl
	call	Assert
	lea	rcx, [rsp + 40]
	call	"Derived::GetY"
	cmp	rax, 2
	sete	cl
	call	Assert
	lea	rcx, [rsp + 40]
	call	"Derived::GetSum"
	cmp	rax, 3
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	PassDerivedRef__Derivedref;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function PassDerivedRef__Derivedref
PassDerivedRef__Derivedref:             # @PassDerivedRef__Derivedref
.seh_proc PassDerivedRef__Derivedref
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], rcx
	mov	rcx, qword ptr [rsp + 48]
	mov	qword ptr [rsp + 40], rcx       # 8-byte Spill
	call	"Base::GetX"
	cmp	rax, 1
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 40]       # 8-byte Reload
	call	"Derived::GetY"
	cmp	rax, 2
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 40]       # 8-byte Reload
	call	"Derived::GetSum"
	cmp	rax, 3
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.def	TestAssignment;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestAssignment
TestAssignment:                         # @TestAssignment
.seh_proc TestAssignment
# %bb.0:                                # %entry
	sub	rsp, 136
	.seh_stackalloc 136
	.seh_endprologue
	mov	qword ptr [rsp + 120], 1
	mov	qword ptr [rsp + 128], 2
	mov	rax, qword ptr [rsp + 120]
	mov	qword ptr [rsp + 112], rax
	lea	rcx, [rsp + 112]
	mov	qword ptr [rsp + 32], rcx       # 8-byte Spill
	call	"Base::GetX"
	sub	rax, 1
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 32]       # 8-byte Reload
	call	"Base::GetSum"
	sub	rax, 1
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 112]
	call	PassBase__Base
	mov	rcx, qword ptr [rsp + 32]       # 8-byte Reload
	call	PassBaseRef__Baseref
	mov	qword ptr [rsp + 96], 2
	mov	qword ptr [rsp + 88], 1
	mov	qword ptr [rsp + 104], 3
	lea	rcx, [rsp + 88]
	mov	qword ptr [rsp + 40], rcx       # 8-byte Spill
	call	"ExtendedDerived::GetSum"
	sub	rax, 6
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 40]       # 8-byte Reload
	call	"ExtendedDerived::GetZ"
	sub	rax, 3
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 88]
	mov	qword ptr [rsp + 80], rax
	lea	rcx, [rsp + 80]
	mov	qword ptr [rsp + 48], rcx       # 8-byte Spill
	call	"Base::GetX"
	sub	rax, 1
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 48]       # 8-byte Reload
	call	"Base::GetSum"
	sub	rax, 1
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 80]
	call	PassBase__Base
	mov	rcx, qword ptr [rsp + 48]       # 8-byte Reload
	call	PassBaseRef__Baseref
	movups	xmm0, xmmword ptr [rsp + 88]
	movaps	xmmword ptr [rsp + 64], xmm0
	lea	rcx, [rsp + 64]
	mov	qword ptr [rsp + 56], rcx       # 8-byte Spill
	call	"Base::GetX"
	sub	rax, 1
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 56]       # 8-byte Reload
	call	"Derived::GetY"
	sub	rax, 2
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 56]       # 8-byte Reload
	call	"Derived::GetSum"
	sub	rax, 3
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 64]
	mov	rdx, qword ptr [rsp + 72]
	call	PassDerived__Derived
	lea	rcx, [rsp + 64]
	call	PassDerivedRef__Derivedref
# %bb.1:                                # %exit
	nop
	add	rsp, 136
	ret
	.seh_endproc
                                        # -- End function
	.def	TestReferenceAssignment;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestReferenceAssignment
TestReferenceAssignment:                # @TestReferenceAssignment
.seh_proc TestReferenceAssignment
# %bb.0:                                # %entry
	sub	rsp, 152
	.seh_stackalloc 152
	.seh_endprologue
	mov	qword ptr [rsp + 136], 1
	mov	qword ptr [rsp + 144], 2
	lea	rax, [rsp + 136]
	mov	qword ptr [rsp + 128], rax
	mov	rcx, qword ptr [rsp + 128]
	mov	qword ptr [rsp + 40], rcx       # 8-byte Spill
	call	"Base::GetX"
	sub	rax, 1
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 40]       # 8-byte Reload
	call	"Base::GetSum"
	sub	rax, 1
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 112], 2
	mov	qword ptr [rsp + 104], 1
	mov	qword ptr [rsp + 120], 3
	lea	rax, [rsp + 104]
	mov	qword ptr [rsp + 56], rax       # 8-byte Spill
	mov	qword ptr [rsp + 96], rax
	mov	rcx, qword ptr [rsp + 96]
	mov	qword ptr [rsp + 48], rcx       # 8-byte Spill
	call	"Base::GetX"
	sub	rax, 1
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 48]       # 8-byte Reload
	call	"Base::GetSum"
	sub	rax, 1
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 56]       # 8-byte Reload
	mov	qword ptr [rsp + 88], rax
	mov	rcx, qword ptr [rsp + 88]
	mov	qword ptr [rsp + 64], rcx       # 8-byte Spill
	call	"Base::GetX"
	sub	rax, 1
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 64]       # 8-byte Reload
	call	"Derived::GetY"
	sub	rax, 2
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 64]       # 8-byte Reload
	call	"Derived::GetSum"
	sub	rax, 3
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 64]       # 8-byte Reload
	mov	rax, qword ptr [rax]
	mov	qword ptr [rsp + 80], rax
	lea	rcx, [rsp + 80]
	mov	qword ptr [rsp + 72], rcx       # 8-byte Spill
	call	"Base::GetX"
	sub	rax, 1
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 72]       # 8-byte Reload
	call	"Base::GetSum"
	sub	rax, 1
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 80]
	call	PassBase__Base
	lea	rcx, [rsp + 80]
	call	PassBaseRef__Baseref
# %bb.1:                                # %exit
	nop
	add	rsp, 152
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
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	call	TestAssignment
	call	TestReferenceAssignment
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym "Base::GetX"
	.addrsig_sym "Base::GetSum"
	.addrsig_sym "Derived::GetY"
	.addrsig_sym "Derived::GetSum"
	.addrsig_sym "ExtendedDerived::GetZ"
	.addrsig_sym "ExtendedDerived::GetSum"
	.addrsig_sym PassBase__Base
	.addrsig_sym PassBaseRef__Baseref
	.addrsig_sym PassDerived__Derived
	.addrsig_sym PassDerivedRef__Derivedref
	.addrsig_sym TestAssignment
	.addrsig_sym TestReferenceAssignment
