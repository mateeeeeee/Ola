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
	.def	StructByRef;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function StructByRef
StructByRef:                            # @StructByRef
.seh_proc StructByRef
# %bb.0:                                # %entry
	sub	rsp, 24
	.seh_stackalloc 24
	.seh_endprologue
	mov	qword ptr [rsp + 16], rcx
	mov	rax, qword ptr [rsp + 16]
	mov	rcx, qword ptr [rax]
	mov	rdx, qword ptr [rax]
	mov	qword ptr [rsp + 8], rdx
	add	rcx, 1
	mov	qword ptr [rax], rcx
	mov	rcx, qword ptr [rax + 8]
	mov	rdx, qword ptr [rax + 8]
	mov	qword ptr [rsp], rdx
	add	rcx, 1
	mov	qword ptr [rax + 8], rcx
# %bb.1:                                # %exit
	add	rsp, 24
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
	sub	rsp, 32
	.seh_stackalloc 32
	.seh_endprologue
	mov	qword ptr [rsp + 16], rcx
	mov	qword ptr [rsp + 24], rdx
	mov	rax, qword ptr [rsp + 16]
	mov	rcx, qword ptr [rsp + 16]
	mov	qword ptr [rsp + 8], rcx
	add	rax, 1
	mov	qword ptr [rsp + 16], rax
	mov	rax, qword ptr [rsp + 24]
	mov	rcx, qword ptr [rsp + 24]
	mov	qword ptr [rsp], rcx
	add	rax, 1
	mov	qword ptr [rsp + 24], rax
# %bb.1:                                # %exit
	add	rsp, 32
	ret
	.seh_endproc
                                        # -- End function
	.def	TestRefStruct;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestRefStruct
TestRefStruct:                          # @TestRefStruct
.seh_proc TestRefStruct
# %bb.0:                                # %entry
	sub	rsp, 104
	.seh_stackalloc 104
	.seh_endprologue
	mov	qword ptr [rsp + 88], 0
	mov	qword ptr [rsp + 96], 0
	lea	rcx, [rsp + 88]
	mov	qword ptr [rsp + 32], rcx       # 8-byte Spill
	mov	r8d, 9
	mov	rdx, r8
	call	"S::Init"
	mov	rcx, qword ptr [rsp + 88]
	mov	rdx, qword ptr [rsp + 96]
	call	StructByValue
	mov	rax, qword ptr [rsp + 88]
	sub	rax, 9
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 96]
	sub	rax, 9
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 32]       # 8-byte Reload
	call	StructByRef
	mov	rax, qword ptr [rsp + 88]
	sub	rax, 10
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 96]
	sub	rax, 10
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 32]       # 8-byte Reload
	mov	qword ptr [rsp + 80], rax
	mov	rax, qword ptr [rsp + 80]
	mov	qword ptr [rsp + 40], rax       # 8-byte Spill
	mov	rcx, qword ptr [rax]
	inc	rcx
	mov	qword ptr [rax], rcx
	mov	rcx, qword ptr [rax + 8]
	inc	rcx
	mov	qword ptr [rax + 8], rcx
	mov	rax, qword ptr [rsp + 88]
	sub	rax, 11
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 96]
	sub	rax, 11
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 40]       # 8-byte Reload
	movups	xmm0, xmmword ptr [rax]
	movaps	xmmword ptr [rsp + 64], xmm0
	mov	rax, qword ptr [rsp + 64]
	inc	rax
	mov	qword ptr [rsp + 64], rax
	mov	rax, qword ptr [rsp + 72]
	inc	rax
	mov	qword ptr [rsp + 72], rax
	mov	rax, qword ptr [rsp + 64]
	sub	rax, 12
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 88]
	sub	rax, 11
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 40]       # 8-byte Reload
	mov	qword ptr [rsp + 56], rax
	mov	rax, qword ptr [rsp + 56]
	mov	qword ptr [rsp + 48], rax       # 8-byte Spill
	mov	rcx, qword ptr [rax]
	inc	rcx
	mov	qword ptr [rax], rcx
	mov	rcx, qword ptr [rax + 8]
	inc	rcx
	mov	qword ptr [rax + 8], rcx
	mov	rax, qword ptr [rsp + 88]
	sub	rax, 12
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 96]
	sub	rax, 12
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 48]       # 8-byte Reload
	call	StructByRef
	mov	rax, qword ptr [rsp + 88]
	sub	rax, 13
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 96]
	sub	rax, 13
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 48]       # 8-byte Reload
	mov	rcx, qword ptr [rax]
	mov	rdx, qword ptr [rax + 8]
	call	StructByValue
	cmp	qword ptr [rsp + 88], 13
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 96], 13
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 104
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
	call	TestRefStruct
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym "S::Init"
	.addrsig_sym StructByRef
	.addrsig_sym StructByValue
	.addrsig_sym TestRefStruct
