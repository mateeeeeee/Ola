	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"WaveModule"
	.def	ReturnRef;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function ReturnRef
ReturnRef:                              # @ReturnRef
.seh_proc ReturnRef
# %bb.0:                                # %entry
	push	rax
	.seh_stackalloc 8
	.seh_endprologue
	lea	rax, [rip + g]
	mov	qword ptr [rsp], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	pop	rcx
	ret
	.seh_endproc
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
# %bb.1:                                # %exit
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
	sub	rsp, 104
	.seh_stackalloc 104
	.seh_endprologue
	call	ReturnRef
	mov	qword ptr [rsp + 96], rax
	mov	rax, qword ptr [rsp + 96]
	mov	rcx, qword ptr [rax]
	mov	rdx, qword ptr [rax]
	mov	qword ptr [rsp + 88], rdx
	add	rcx, 1
	mov	qword ptr [rax], rcx
	cmp	qword ptr [rip + g], 10
	sete	cl
	call	Assert
	call	ReturnValue
	mov	qword ptr [rsp + 80], rax
	mov	rax, qword ptr [rsp + 80]
	mov	rcx, qword ptr [rax]
	mov	rdx, qword ptr [rax]
	mov	qword ptr [rsp + 72], rdx
	add	rcx, 1
	mov	qword ptr [rax], rcx
	cmp	qword ptr [rip + g], 10
	sete	cl
	call	Assert
	call	ReturnRef
	mov	rax, qword ptr [rax]
	mov	qword ptr [rsp + 64], rax
	mov	rax, qword ptr [rsp + 64]
	mov	rcx, qword ptr [rsp + 64]
	mov	qword ptr [rsp + 56], rcx
	add	rax, 1
	mov	qword ptr [rsp + 64], rax
	cmp	qword ptr [rip + g], 10
	sete	cl
	call	Assert
	call	ReturnValue
	mov	qword ptr [rsp + 48], rax
	mov	rax, qword ptr [rsp + 48]
	mov	rcx, qword ptr [rsp + 48]
	mov	qword ptr [rsp + 40], rcx
	add	rax, 1
	mov	qword ptr [rsp + 48], rax
	cmp	qword ptr [rip + g], 10
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
	call	TestRefReturnSimple
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.data
	.p2align	3, 0x0                          # @g
g:
	.quad	9                               # 0x9

	.addrsig
	.addrsig_sym Assert
	.addrsig_sym ReturnRef
	.addrsig_sym ReturnValue
	.addrsig_sym TestRefReturnSimple
	.addrsig_sym g
