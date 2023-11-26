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
	.def	ReturnValueS;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function ReturnValueS
ReturnValueS:                           # @ReturnValueS
# %bb.0:                                # %entry
	lea	rax, [rip + s]
	mov	qword ptr [rcx], rax
# %bb.1:                                # %exit
	ret
                                        # -- End function
	.def	ReturnRefS;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function ReturnRefS
ReturnRefS:                             # @ReturnRefS
.seh_proc ReturnRefS
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	lea	rax, [rip + s]
	mov	qword ptr [rsp], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	pop	rcx
	ret
	.seh_endproc
                                        # -- End function
	.def	TestRefReturnStruct;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestRefReturnStruct
TestRefReturnStruct:                    # @TestRefReturnStruct
.seh_proc TestRefReturnStruct
# %bb.0:                                # %entry
	sub	rsp, 136
	.seh_stackalloc 136
	.seh_endprologue
	lea	rcx, [rip + s]
	mov	r8d, 9
	mov	rdx, r8
	call	"S::Init"
	call	ReturnRefS
	mov	qword ptr [rsp + 128], rax
	mov	rax, qword ptr [rsp + 128]
	mov	rcx, qword ptr [rax]
	mov	rdx, qword ptr [rax]
	mov	qword ptr [rsp + 120], rdx
	add	rcx, 1
	mov	qword ptr [rax], rcx
	mov	rcx, qword ptr [rax + 8]
	mov	rdx, qword ptr [rax + 8]
	mov	qword ptr [rsp + 112], rdx
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
	mov	qword ptr [rsp + 96], rcx
	mov	rax, qword ptr [rax + 8]
	mov	qword ptr [rsp + 104], rax
	mov	rax, qword ptr [rsp + 96]
	mov	rcx, qword ptr [rsp + 96]
	mov	qword ptr [rsp + 88], rcx
	add	rax, 1
	mov	qword ptr [rsp + 96], rax
	mov	rax, qword ptr [rsp + 96]
	mov	rcx, qword ptr [rsp + 96]
	mov	qword ptr [rsp + 80], rcx
	add	rax, 1
	mov	qword ptr [rsp + 96], rax
	cmp	qword ptr [rip + s], 10
	sete	cl
	call	Assert
	cmp	qword ptr [rip + s+8], 10
	sete	cl
	call	Assert
	lea	rcx, [rsp + 72]
	call	ReturnValueS
	mov	rax, qword ptr [rsp + 72]
	mov	qword ptr [rsp + 56], rax
	mov	rax, qword ptr [rsp + 80]
	mov	qword ptr [rsp + 64], rax
	mov	rax, qword ptr [rsp + 56]
	mov	rcx, qword ptr [rsp + 56]
	mov	qword ptr [rsp + 48], rcx
	add	rax, 1
	mov	qword ptr [rsp + 56], rax
	mov	rax, qword ptr [rsp + 56]
	mov	rcx, qword ptr [rsp + 56]
	mov	qword ptr [rsp + 40], rcx
	add	rax, 1
	mov	qword ptr [rsp + 56], rax
	cmp	qword ptr [rip + s], 10
	sete	cl
	call	Assert
	cmp	qword ptr [rip + s+8], 10
	sete	cl
	call	Assert
# %bb.1:                                # %exit
	nop
	add	rsp, 136
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
	call	TestRefReturnStruct
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.bss
	.globl	s                               # @s
	.p2align	3, 0x0
s:
	.zero	16

	.addrsig
	.addrsig_sym Assert
	.addrsig_sym "S::Init"
	.addrsig_sym ReturnValueS
	.addrsig_sym ReturnRefS
	.addrsig_sym TestRefReturnStruct
	.addrsig_sym s
