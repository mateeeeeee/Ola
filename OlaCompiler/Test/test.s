	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	"Base::PrintY";
	.scl	2;
	.type	32;
	.endef
	.globl	"Base::PrintY"                  # -- Begin function Base::PrintY
	.p2align	4, 0x90
"Base::PrintY":                         # @"Base::PrintY"
.seh_proc "Base::PrintY"
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	rcx, qword ptr [rcx]
	call	PrintInt
# %bb.1:                                # %exit
	nop
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.def	"Derived::PrintX";
	.scl	2;
	.type	32;
	.endef
	.globl	"Derived::PrintX"               # -- Begin function Derived::PrintX
	.p2align	4, 0x90
"Derived::PrintX":                      # @"Derived::PrintX"
.seh_proc "Derived::PrintX"
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	qword ptr [rsp + 32], rcx       # 8-byte Spill
	call	"Base::PrintY"
	mov	rcx, qword ptr [rsp + 32]       # 8-byte Reload
	mov	rcx, qword ptr [rcx + 8]
	call	PrintInt
# %bb.1:                                # %exit
	nop
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.def	Test;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function Test
Test:                                   # @Test
.seh_proc Test
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	qword ptr [rsp + 32], rcx
	lea	rcx, [rsp + 32]
	call	"Base::PrintY"
# %bb.1:                                # %exit
	nop
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.def	Test2;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function Test2
Test2:                                  # @Test2
.seh_proc Test2
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	qword ptr [rsp + 32], rcx
	mov	rcx, qword ptr [rsp + 32]
	call	"Base::PrintY"
# %bb.1:                                # %exit
	nop
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
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 48], 10
	mov	qword ptr [rsp + 56], 30
	lea	rax, [rsp + 48]
	mov	qword ptr [rsp + 40], rax
	mov	rax, qword ptr [rsp + 40]
	mov	qword ptr [rsp + 32], rax       # 8-byte Spill
	mov	rcx, qword ptr [rax]
	call	Test
	mov	rcx, qword ptr [rsp + 32]       # 8-byte Reload
	call	Test2
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 64]
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym PrintInt
	.addrsig_sym "Base::PrintY"
	.addrsig_sym Test
	.addrsig_sym Test2
