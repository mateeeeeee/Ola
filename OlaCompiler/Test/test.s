	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test.ola"
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 32
	.seh_stackalloc 32
	lea	rbp, [rsp + 32]
	.seh_setframe rbp, 32
	.seh_endprologue
	mov	qword ptr [rbp - 16], 5
	mov	rax, qword ptr [rbp - 16]
	add	rax, 6
	mov	qword ptr [rbp - 24], rax
	cmp	qword ptr [rbp - 24], 10
	jle	.LBB0_2
# %bb.1:                                # %if.then
	mov	rax, qword ptr [rbp - 16]
	mov	qword ptr [rbp - 32], rax       # 8-byte Spill
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 32]       # 8-byte Reload
	mov	rcx, rsp
	mov	qword ptr [rcx], rax
	add	rax, 1
	mov	qword ptr [rbp - 16], rax
	jmp	.LBB0_3
.LBB0_2:                                # %if.else
	mov	qword ptr [rbp - 8], 2
	jmp	.LBB0_4
.LBB0_3:                                # %if.end
	mov	rax, qword ptr [rbp - 16]
	mov	qword ptr [rbp - 8], rax
.LBB0_4:                                # %exit
	mov	rax, qword ptr [rbp - 8]
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
