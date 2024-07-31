	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_goto.ola"
	.def	TestGotoNestedLoops;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestGotoNestedLoops
TestGotoNestedLoops:                    # @TestGotoNestedLoops
.seh_proc TestGotoNestedLoops
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 48
	.seh_stackalloc 48
	lea	rbp, [rsp + 48]
	.seh_setframe rbp, 48
	.seh_endprologue
	mov	qword ptr [rbp - 8], 5
	mov	qword ptr [rbp - 16], 0
	jmp	.LBB0_3
.LBB0_1:                                # %label.Found
	mov	rax, qword ptr [rbp - 16]
	imul	rax, qword ptr [rbp - 24]
	cmp	rax, qword ptr [rbp - 8]
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB0_12
.LBB0_2:                                # %for.body
                                        #   in Loop: Header=BB0_3 Depth=1
	mov	qword ptr [rbp - 24], 0
	jmp	.LBB0_7
.LBB0_3:                                # %for.cond
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_7 Depth 2
	cmp	qword ptr [rbp - 16], 10
	jl	.LBB0_2
	jmp	.LBB0_5
.LBB0_4:                                # %for.iter
                                        #   in Loop: Header=BB0_3 Depth=1
	mov	rax, qword ptr [rbp - 16]
	mov	qword ptr [rbp - 32], rax       # 8-byte Spill
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 32]       # 8-byte Reload
	mov	rcx, rsp
	mov	rdx, qword ptr [rbp - 16]
	mov	qword ptr [rcx], rdx
	add	rax, 1
	mov	qword ptr [rbp - 16], rax
	jmp	.LBB0_3
.LBB0_5:                                # %for.end
	jmp	.LBB0_1
.LBB0_6:                                # %for.body1
                                        #   in Loop: Header=BB0_7 Depth=2
	mov	rax, qword ptr [rbp - 16]
	imul	rax, qword ptr [rbp - 24]
	cmp	rax, qword ptr [rbp - 8]
	je	.LBB0_10
	jmp	.LBB0_11
.LBB0_7:                                # %for.cond2
                                        #   Parent Loop BB0_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	cmp	qword ptr [rbp - 24], 10
	jl	.LBB0_6
	jmp	.LBB0_9
.LBB0_8:                                # %for.iter3
                                        #   in Loop: Header=BB0_7 Depth=2
	mov	rax, qword ptr [rbp - 24]
	mov	qword ptr [rbp - 40], rax       # 8-byte Spill
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 40]       # 8-byte Reload
	mov	rcx, rsp
	mov	rdx, qword ptr [rbp - 24]
	mov	qword ptr [rcx], rdx
	add	rax, 1
	mov	qword ptr [rbp - 24], rax
	jmp	.LBB0_7
.LBB0_9:                                # %for.end4
                                        #   in Loop: Header=BB0_3 Depth=1
	jmp	.LBB0_4
.LBB0_10:                               # %if.then
	jmp	.LBB0_1
.LBB0_11:                               # %if.end
                                        #   in Loop: Header=BB0_7 Depth=2
	jmp	.LBB0_8
.LBB0_12:                               # %exit
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	TestGotoErrorHandling;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestGotoErrorHandling
TestGotoErrorHandling:                  # @TestGotoErrorHandling
.seh_proc TestGotoErrorHandling
# %bb.0:                                # %entry
	sub	rsp, 24
	.seh_stackalloc 24
	.seh_endprologue
	mov	qword ptr [rsp + 8], 0
	mov	qword ptr [rsp], 1
	cmp	qword ptr [rsp], 0
	jne	.LBB1_2
	jmp	.LBB1_3
.LBB1_1:                                # %label.HandleError
	mov	qword ptr [rsp + 8], -1
	mov	rax, qword ptr [rsp + 8]
	mov	qword ptr [rsp + 16], rax
	jmp	.LBB1_4
.LBB1_2:                                # %if.then
	jmp	.LBB1_1
.LBB1_3:                                # %if.end
	mov	qword ptr [rsp + 8], 42
	mov	rax, qword ptr [rsp + 8]
	mov	qword ptr [rsp + 16], rax
.LBB1_4:                                # %exit
	mov	rax, qword ptr [rsp + 16]
	add	rsp, 24
	ret
	.seh_endproc
                                        # -- End function
	.def	TestGotoEndOfFunction;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestGotoEndOfFunction
TestGotoEndOfFunction:                  # @TestGotoEndOfFunction
.seh_proc TestGotoEndOfFunction
# %bb.0:                                # %entry
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	mov	qword ptr [rsp], 0
	cmp	qword ptr [rsp], 0
	jne	.LBB2_2
	jmp	.LBB2_3
.LBB2_1:                                # %label.CleanUpAndReturn
	mov	rax, qword ptr [rsp]
	mov	qword ptr [rsp + 8], rax
	jmp	.LBB2_4
.LBB2_2:                                # %if.then
	jmp	.LBB2_1
.LBB2_3:                                # %if.end
	jmp	.LBB2_1
.LBB2_4:                                # %exit
	mov	rax, qword ptr [rsp + 8]
	add	rsp, 16
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
	call	TestGotoNestedLoops
	call	TestGotoErrorHandling
	mov	qword ptr [rsp + 40], rax
	cmp	qword ptr [rsp + 40], -1
	sete	cl
	call	Assert
	call	TestGotoEndOfFunction
	mov	qword ptr [rsp + 32], rax
	cmp	qword ptr [rsp + 32], 0
	sete	cl
	call	Assert
	mov	qword ptr [rsp + 48], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 48]
	add	rsp, 56
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestGotoNestedLoops
	.addrsig_sym TestGotoErrorHandling
	.addrsig_sym TestGotoEndOfFunction
