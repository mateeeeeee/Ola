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
# %bb.0:                                # %entry
	mov	rax, qword ptr [rcx + 8]
	ret
                                        # -- End function
	.def	"Base::GetSumX";
	.scl	2;
	.type	32;
	.endef
	.globl	"Base::GetSumX"                 # -- Begin function Base::GetSumX
	.p2align	4, 0x90
"Base::GetSumX":                        # @"Base::GetSumX"
# %bb.0:                                # %entry
	mov	rax, qword ptr [rcx]
	mov	rax, qword ptr [rax]
	rex64 jmp	rax                     # TAILCALL
                                        # -- End function
	.def	"Derived::GetX";
	.scl	2;
	.type	32;
	.endef
	.globl	"Derived::GetX"                 # -- Begin function Derived::GetX
	.p2align	4, 0x90
"Derived::GetX":                        # @"Derived::GetX"
# %bb.0:                                # %entry
	mov	rax, qword ptr [rcx + 16]
	ret
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
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	qword ptr [rsp + 32], rcx       # 8-byte Spill
	mov	rax, qword ptr [rcx]
	call	qword ptr [rax]
	mov	rcx, qword ptr [rsp + 32]       # 8-byte Reload
	mov	rcx, qword ptr [rcx + 8]
	add	rax, rcx
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
	mov	ecx, 1
	call	Assert
	lea	rax, [rip + VTable_Derived]
	mov	qword ptr [rsp + 32], rax
	mov	qword ptr [rsp + 40], 1
	mov	qword ptr [rsp + 48], 10
	mov	ecx, 1
	call	Assert
	mov	rax, qword ptr [rsp + 32]
	lea	rcx, [rsp + 32]
	call	qword ptr [rax]
	cmp	rax, 10
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 32]
	lea	rcx, [rsp + 32]
	call	qword ptr [rax + 8]
	cmp	rax, 11
	sete	cl
	call	Assert
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr"
	.p2align	3, 0x0                          # @VTable_Derived
VTable_Derived:
	.quad	"Derived::GetX"
	.quad	"Derived::GetSumX"

	.addrsig
	.addrsig_sym "Derived::GetX"
	.addrsig_sym "Derived::GetSumX"
	.addrsig_sym VTable_Derived
