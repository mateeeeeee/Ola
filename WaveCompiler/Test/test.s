	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"WaveModule"
	.def	FooByRef;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function FooByRef
FooByRef:                               # @FooByRef
.seh_proc FooByRef
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	mov	qword ptr [rsp], rcx
	mov	rax, qword ptr [rsp]
	mov	rcx, qword ptr [rax]
	add	rcx, 1
	mov	qword ptr [rax], rcx
# %bb.1:                                # %exit
	pop	rax
	ret
	.seh_endproc
                                        # -- End function
	.def	FooByValue;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function FooByValue
FooByValue:                             # @FooByValue
.seh_proc FooByValue
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	mov	qword ptr [rsp], rcx
	mov	rax, qword ptr [rsp]
	add	rax, 1
	mov	qword ptr [rsp], rax
# %bb.1:                                # %exit
	pop	rax
	ret
	.seh_endproc
                                        # -- End function
	.def	TestRefSimple;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestRefSimple
TestRefSimple:                          # @TestRefSimple
.seh_proc TestRefSimple
# %bb.0:                                # %entry
	sub	rsp, 88
	.seh_stackalloc 88
	.seh_endprologue
	mov	qword ptr [rsp + 80], 9
	lea	rcx, [rsp + 80]
	call	FooByRef
	cmp	qword ptr [rsp + 80], 10
	sete	cl
	call	Assert
	lea	rax, [rsp + 80]
	mov	qword ptr [rsp + 72], rax
	mov	rax, qword ptr [rsp + 72]
	mov	qword ptr [rsp + 40], rax       # 8-byte Spill
	mov	rcx, qword ptr [rax]
	add	rcx, 1
	mov	qword ptr [rax], rcx
	cmp	qword ptr [rsp + 80], 11
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 40]       # 8-byte Reload
	mov	rax, qword ptr [rax]
	mov	qword ptr [rsp + 64], rax
	mov	rax, qword ptr [rsp + 64]
	add	rax, 1
	mov	qword ptr [rsp + 64], rax
	cmp	qword ptr [rsp + 64], 12
	sete	cl
	call	Assert
	cmp	qword ptr [rsp + 80], 11
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 40]       # 8-byte Reload
	mov	qword ptr [rsp + 56], rax
	mov	rax, qword ptr [rsp + 56]
	mov	qword ptr [rsp + 48], rax       # 8-byte Spill
	mov	rcx, qword ptr [rax]
	add	rcx, 1
	mov	qword ptr [rax], rcx
	cmp	qword ptr [rsp + 80], 12
	sete	cl
	call	Assert
	mov	rcx, qword ptr [rsp + 48]       # 8-byte Reload
	call	FooByRef
	cmp	qword ptr [rsp + 80], 13
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 48]       # 8-byte Reload
	mov	rcx, qword ptr [rax]
	call	FooByValue
	cmp	qword ptr [rsp + 80], 13
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 88
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
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym FooByRef
	.addrsig_sym FooByValue
	.addrsig_sym TestRefSimple
