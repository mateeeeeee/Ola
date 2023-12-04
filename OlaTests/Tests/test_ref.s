	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_ref.ola"
	.def	IntByRef;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function IntByRef
IntByRef:                               # @IntByRef
# %bb.0:                                # %entry
	mov	rax, qword ptr [rcx]
	add	rax, 1
	mov	qword ptr [rcx], rax
	ret
                                        # -- End function
	.def	IntByValue;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function IntByValue
IntByValue:                             # @IntByValue
# %bb.0:                                # %entry
	ret
                                        # -- End function
	.def	TestRefSimple;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestRefSimple
TestRefSimple:                          # @TestRefSimple
.seh_proc TestRefSimple
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	qword ptr [rsp + 32], 9
	lea	rcx, [rsp + 32]
	call	IntByRef
	cmp	qword ptr [rsp + 32], 10
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 32]
	add	rax, 1
	mov	qword ptr [rsp + 32], rax
	cmp	rax, 11
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 32], 11
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 32], 11
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 32]
	add	rax, 1
	mov	qword ptr [rsp + 32], rax
	cmp	rax, 12
	sete	cl
	call	Assert
	lea	rcx, [rsp + 32]
	call	IntByRef
	cmp	qword ptr [rsp + 32], 13
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 32]
	call	IntByValue
	cmp	qword ptr [rsp + 32], 13
	sete	cl
	call	Assert
	nop
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.def	ReturnRef;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function ReturnRef
ReturnRef:                              # @ReturnRef
# %bb.0:                                # %entry
	lea	rax, [rip + g]
	ret
                                        # -- End function
	.def	ReturnValue;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function ReturnValue
ReturnValue:                            # @ReturnValue
.seh_proc ReturnValue
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	lea	rax, [rip + g]
	mov	qword ptr [rsp], rax
	mov	rax, qword ptr [rsp]
	pop	rcx
	ret
	.seh_endproc
                                        # -- End function
	.def	TestRefReturnSimple;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestRefReturnSimple
TestRefReturnSimple:                    # @TestRefReturnSimple
.seh_proc TestRefReturnSimple
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	call	ReturnRef
	mov	rcx, qword ptr [rax]
	inc	rcx
	mov	qword ptr [rax], rcx
	mov	rax, qword ptr [rip + g]
	sub	rax, 10
	sete	cl
	call	Assert
	call	ReturnRef
	mov	rax, qword ptr [rip + g]
	sub	rax, 10
	sete	cl
	call	Assert
	call	ReturnValue
	mov	rax, qword ptr [rip + g]
	sub	rax, 10
	sete	cl
	add	rsp, 40
	jmp	Assert                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	"S::Init";
	.scl	2;
	.type	32;
	.endef
	.globl	"S::Init"                       # -- Begin function S::Init
	.p2align	4, 0x90
"S::Init":                              # @"S::Init"
# %bb.0:                                # %entry
	mov	qword ptr [rcx], rdx
	mov	qword ptr [rcx + 8], r8
	ret
                                        # -- End function
	.def	StructByRef;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function StructByRef
StructByRef:                            # @StructByRef
# %bb.0:                                # %entry
	mov	rax, qword ptr [rcx]
	add	rax, 1
	mov	qword ptr [rcx], rax
	mov	rax, qword ptr [rcx + 8]
	add	rax, 1
	mov	qword ptr [rcx + 8], rax
	ret
                                        # -- End function
	.def	StructByValue;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function StructByValue
StructByValue:                          # @StructByValue
# %bb.0:                                # %entry
	ret
                                        # -- End function
	.def	TestRefStruct;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestRefStruct
TestRefStruct:                          # @TestRefStruct
.seh_proc TestRefStruct
# %bb.0:                                # %entry
	sub	rsp, 88
	.seh_stackalloc 88
	.seh_endprologue
	mov	qword ptr [rsp + 72], 0
	mov	qword ptr [rsp + 80], 0
	lea	rcx, [rsp + 72]
	mov	qword ptr [rsp + 40], rcx       # 8-byte Spill
	mov	r8d, 9
	mov	rdx, r8
	call	"S::Init"
	mov	rcx, qword ptr [rsp + 72]
	mov	rdx, qword ptr [rsp + 80]
	call	StructByValue
	mov	rax, qword ptr [rsp + 72]
	sub	rax, 9
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 80]
	sub	rax, 9
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 40]       # 8-byte Reload
	call	StructByRef
	mov	rax, qword ptr [rsp + 72]
	sub	rax, 10
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 80]
	sub	rax, 10
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 72]
	inc	rax
	mov	qword ptr [rsp + 72], rax
	mov	rcx, qword ptr [rsp + 80]
	inc	rcx
	mov	qword ptr [rsp + 80], rcx
	sub	rax, 11
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 80]
	sub	rax, 11
	sete	cl
	call	Assert
	movups	xmm0, xmmword ptr [rsp + 72]
	movaps	xmmword ptr [rsp + 48], xmm0
	mov	rax, qword ptr [rsp + 48]
	inc	rax
	mov	qword ptr [rsp + 48], rax
	mov	rcx, qword ptr [rsp + 56]
	inc	rcx
	mov	qword ptr [rsp + 56], rcx
	sub	rax, 12
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 72]
	sub	rax, 11
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 72]
	inc	rax
	mov	qword ptr [rsp + 72], rax
	mov	rcx, qword ptr [rsp + 80]
	inc	rcx
	mov	qword ptr [rsp + 80], rcx
	sub	rax, 12
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 80]
	sub	rax, 12
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 40]       # 8-byte Reload
	call	StructByRef
	mov	rax, qword ptr [rsp + 72]
	sub	rax, 13
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 80]
	sub	rax, 13
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 72]
	mov	rdx, qword ptr [rsp + 80]
	call	StructByValue
	cmp	qword ptr [rsp + 72], 13
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 80], 13
	sete	cl
	call	Assert
	nop
	add	rsp, 88
	ret
	.seh_endproc
                                        # -- End function
	.def	ReturnValueS;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function ReturnValueS
ReturnValueS:                           # @ReturnValueS
# %bb.0:                                # %entry
	lea	rax, [rip + s]
	mov	qword ptr [rcx], rax
	ret
                                        # -- End function
	.def	ReturnRefS;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function ReturnRefS
ReturnRefS:                             # @ReturnRefS
# %bb.0:                                # %entry
	lea	rax, [rip + s]
	ret
                                        # -- End function
	.def	TestRefReturnStruct;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestRefReturnStruct
TestRefReturnStruct:                    # @TestRefReturnStruct
.seh_proc TestRefReturnStruct
# %bb.0:                                # %entry
	sub	rsp, 72
	.seh_stackalloc 72
	.seh_endprologue
	lea	rcx, [rip + s]
	mov	r8d, 9
	mov	rdx, r8
	call	"S::Init"
	call	ReturnRefS
	mov	rcx, qword ptr [rax]
	add	rcx, 1
	mov	qword ptr [rax], rcx
	mov	rcx, qword ptr [rax + 8]
	add	rcx, 1
	mov	qword ptr [rax + 8], rcx
	cmp	qword ptr [rip + s], 10
	sete	cl
	call	Assert
	cmp	qword ptr [rip + s+8], 10
	sete	cl
	call	Assert
	call	ReturnRefS
	mov	rcx, qword ptr [rax]
	mov	qword ptr [rsp + 56], rcx
	mov	rax, qword ptr [rax + 8]
	mov	qword ptr [rsp + 64], rax
	mov	rax, qword ptr [rsp + 56]
	add	rax, 2
	mov	qword ptr [rsp + 56], rax
	cmp	qword ptr [rip + s], 10
	sete	cl
	call	Assert
	cmp	qword ptr [rip + s+8], 10
	sete	cl
	call	Assert
	lea	rcx, [rsp + 48]
	call	ReturnValueS
	mov	rax, qword ptr [rsp + 48]
	mov	qword ptr [rsp + 32], rax
	mov	rax, qword ptr [rsp + 56]
	mov	qword ptr [rsp + 40], rax
	mov	rax, qword ptr [rsp + 32]
	add	rax, 2
	mov	qword ptr [rsp + 32], rax
	cmp	qword ptr [rip + s], 10
	sete	cl
	call	Assert
	cmp	qword ptr [rip + s+8], 10
	sete	cl
	call	Assert
	nop
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
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	call	TestRefSimple
	call	TestRefReturnSimple
	call	TestRefStruct
	call	TestRefReturnStruct
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.data
	.p2align	3, 0x0                          # @g
g:
	.quad	9                               # 0x9

	.bss
	.globl	s                               # @s
	.p2align	3, 0x0
s:
	.zero	16

	.addrsig
	.addrsig_sym Assert
	.addrsig_sym IntByRef
	.addrsig_sym IntByValue
	.addrsig_sym TestRefSimple
	.addrsig_sym ReturnRef
	.addrsig_sym ReturnValue
	.addrsig_sym TestRefReturnSimple
	.addrsig_sym "S::Init"
	.addrsig_sym StructByRef
	.addrsig_sym StructByValue
	.addrsig_sym TestRefStruct
	.addrsig_sym ReturnValueS
	.addrsig_sym ReturnRefS
	.addrsig_sym TestRefReturnStruct
	.addrsig_sym g
	.addrsig_sym s
