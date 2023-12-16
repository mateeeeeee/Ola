	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	f;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function f
f:                                      # @f
.seh_proc f
# %bb.0:                                # %entry
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	mov	qword ptr [rsp + 8], rcx
	mov	rax, qword ptr [rsp + 8]
	shl	rax
	mov	qword ptr [rsp], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp]
	add	rsp, 16
	ret
	.seh_endproc
                                        # -- End function
	.def	f.1;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function f.1
f.1:                                    # @f.1
.seh_proc f.1
# %bb.0:                                # %entry
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], rcx
	lea	rcx, [rsp + 48]
	call	PrintString
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 40]
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
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	ecx, 5
	call	f
	mov	qword ptr [rsp + 40], rax
	mov	rax, qword ptr [rsp + 40]
	mov	qword ptr [rsp + 48], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym PrintString
	.addrsig_sym f
