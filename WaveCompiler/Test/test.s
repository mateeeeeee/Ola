	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"WaveModule"
	.def	"Foo::SetX";
	.scl	2;
	.type	32;
	.endef
	.globl	"Foo::SetX"                     # -- Begin function Foo::SetX
	.p2align	4, 0x90
"Foo::SetX":                            # @"Foo::SetX"
# %bb.0:                                # %entry
	mov	qword ptr [rcx], rdx
# %bb.1:                                # %exit
	ret
                                        # -- End function
	.def	"Foo::GetX";
	.scl	2;
	.type	32;
	.endef
	.globl	"Foo::GetX"                     # -- Begin function Foo::GetX
	.p2align	4, 0x90
"Foo::GetX":                            # @"Foo::GetX"
.seh_proc "Foo::GetX"
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
	mov	qword ptr [rsp + 48], 5
	mov	qword ptr [rsp + 56], 10
	lea	rcx, [rsp + 48]
	mov	edx, 12
	call	"Foo::SetX"
	mov	rax, qword ptr [rsp + 48]
	mov	qword ptr [rsp + 32], rax
	lea	rcx, [rsp + 48]
	mov	edx, 24
	call	"Foo::SetX"
	lea	rcx, [rsp + 32]
	call	"Foo::GetX"
	mov	qword ptr [rsp + 64], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 64]
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym "Foo::SetX"
	.addrsig_sym "Foo::GetX"
