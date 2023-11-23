	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"WaveModule"
	.def	"S::Init";
	.scl	2;
	.type	32;
	.endef
	.globl	"S::Init"                       # -- Begin function S::Init
	.p2align	4, 0x90
"S::Init":                              # @"S::Init"
.seh_proc "S::Init"
# %bb.0:                                # %entry
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	mov	qword ptr [rsp + 8], rdx
	mov	qword ptr [rsp], r8
	mov	rax, qword ptr [rsp + 8]
	mov	qword ptr [rcx], rax
	mov	rax, qword ptr [rsp]
	mov	qword ptr [rcx + 8], rax
# %bb.1:                                # %exit
	add	rsp, 16
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
	mov	rax, qword ptr [rsp + 40]
	shl	rax
	mov	qword ptr [rsp + 40], rax
	mov	rax, qword ptr [rsp + 48]
	shl	rax
	mov	qword ptr [rsp + 48], rax
	cmp	qword ptr [rsp + 40], 20
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 48], 20
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
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	mov	qword ptr [rsp + 48], 0
	mov	qword ptr [rsp + 56], 0
	lea	rcx, [rsp + 48]
	mov	r8d, 10
	mov	rdx, r8
	call	"S::Init"
	mov	rcx, qword ptr [rsp + 48]
	mov	rdx, qword ptr [rsp + 56]
	call	StructByValue
	cmp	qword ptr [rsp + 48], 10
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 56], 10
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 48]
	mov	qword ptr [rsp + 32], rax
	mov	rax, qword ptr [rsp + 56]
	mov	qword ptr [rsp + 40], rax
	mov	rax, qword ptr [rsp + 48]
	shl	rax
	mov	qword ptr [rsp + 48], rax
	mov	rax, qword ptr [rsp + 56]
	shl	rax
	mov	qword ptr [rsp + 56], rax
	cmp	qword ptr [rsp + 32], 10
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 40], 10
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 56], 20
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 56], 20
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 64], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 64]
	add	rsp, 72
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym "S::Init"
	.addrsig_sym StructByValue
