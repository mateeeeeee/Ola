	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	f__I;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function f__I
f__I:                                   # @f__I
.seh_proc f__I
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
	.def	f__C0;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function f__C0
f__C0:                                  # @f__C0
.seh_proc f__C0
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
	call	f__I
	mov	qword ptr [rsp + 40], rax
	lea	rcx, [rip + __StringLiteral0]
	call	f__C0
	mov	rax, qword ptr [rsp + 40]
	mov	qword ptr [rsp + 48], rax
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr"
__StringLiteral0:                       # @__StringLiteral0
	.asciz	"Mate"

	.addrsig
	.addrsig_sym PrintString
	.addrsig_sym f__I
	.addrsig_sym f__C0
	.addrsig_sym __StringLiteral0
