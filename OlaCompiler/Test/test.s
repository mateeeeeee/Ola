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
	mov	rax, qword ptr [rcx + 8]
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
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	ecx, 5
	call	AllocateInts
	mov	qword ptr [rsp + 40], rax
	mov	rax, qword ptr [rsp + 40]
	mov	rax, qword ptr [rax]
	mov	qword ptr [rsp + 48], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym AllocateInts
