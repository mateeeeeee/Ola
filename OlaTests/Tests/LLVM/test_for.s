	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_for.ola"
	.def	TestForLoopInt;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestForLoopInt
TestForLoopInt:                         # @TestForLoopInt
.seh_proc TestForLoopInt
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 32
	.seh_stackalloc 32
	lea	rbp, [rsp + 32]
	.seh_setframe rbp, 32
	.seh_endprologue
	mov	qword ptr [rbp - 8], 0
	mov	qword ptr [rbp - 16], 1
	jmp	.LBB0_2
.LBB0_1:                                # %for.body
                                        #   in Loop: Header=BB0_2 Depth=1
	mov	rax, qword ptr [rbp - 8]
	add	rax, qword ptr [rbp - 16]
	mov	qword ptr [rbp - 8], rax
	jmp	.LBB0_3
.LBB0_2:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	cmp	qword ptr [rbp - 16], 5
	jle	.LBB0_1
	jmp	.LBB0_4
.LBB0_3:                                # %for.iter
                                        #   in Loop: Header=BB0_2 Depth=1
	mov	rax, qword ptr [rbp - 16]
	mov	qword ptr [rbp - 24], rax       # 8-byte Spill
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 24]       # 8-byte Reload
	mov	rcx, rsp
	mov	rdx, qword ptr [rbp - 16]
	mov	qword ptr [rcx], rdx
	add	rax, 1
	mov	qword ptr [rbp - 16], rax
	jmp	.LBB0_2
.LBB0_4:                                # %for.end
	cmp	qword ptr [rbp - 8], 15
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
# %bb.5:                                # %exit
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	TestForLoopBoolCondition;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestForLoopBoolCondition
TestForLoopBoolCondition:               # @TestForLoopBoolCondition
.seh_proc TestForLoopBoolCondition
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 16
	.seh_stackalloc 16
	lea	rbp, [rsp + 16]
	.seh_setframe rbp, 16
	.seh_endprologue
	mov	qword ptr [rbp - 8], 0
	jmp	.LBB1_2
.LBB1_1:                                # %for.body
                                        #   in Loop: Header=BB1_2 Depth=1
	mov	rax, qword ptr [rbp - 8]
	mov	qword ptr [rbp - 16], rax       # 8-byte Spill
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 16]       # 8-byte Reload
	mov	rcx, rsp
	mov	rdx, qword ptr [rbp - 8]
	mov	qword ptr [rcx], rdx
	add	rax, 1
	mov	qword ptr [rbp - 8], rax
	jmp	.LBB1_3
.LBB1_2:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	cmp	qword ptr [rbp - 8], 3
	jl	.LBB1_1
	jmp	.LBB1_4
.LBB1_3:                                # %for.iter
                                        #   in Loop: Header=BB1_2 Depth=1
	jmp	.LBB1_2
.LBB1_4:                                # %for.end
	cmp	qword ptr [rbp - 8], 3
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
# %bb.5:                                # %exit
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	TestForLoopMultipleExpressions;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestForLoopMultipleExpressions
TestForLoopMultipleExpressions:         # @TestForLoopMultipleExpressions
.seh_proc TestForLoopMultipleExpressions
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 48
	.seh_stackalloc 48
	lea	rbp, [rsp + 48]
	.seh_setframe rbp, 48
	.seh_endprologue
	mov	qword ptr [rbp - 8], 0
	mov	qword ptr [rbp - 16], 1
	mov	qword ptr [rbp - 24], 5
	jmp	.LBB2_2
.LBB2_1:                                # %for.body
                                        #   in Loop: Header=BB2_2 Depth=1
	mov	rax, qword ptr [rbp - 16]
	add	rax, qword ptr [rbp - 24]
	add	rax, qword ptr [rbp - 8]
	mov	qword ptr [rbp - 8], rax
	jmp	.LBB2_3
.LBB2_2:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	cmp	qword ptr [rbp - 16], 3
	jle	.LBB2_1
	jmp	.LBB2_4
.LBB2_3:                                # %for.iter
                                        #   in Loop: Header=BB2_2 Depth=1
	mov	rcx, qword ptr [rbp - 16]
	mov	eax, 16
	mov	qword ptr [rbp - 40], rax       # 8-byte Spill
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 40]       # 8-byte Reload
	mov	rdx, rsp
	mov	r8, qword ptr [rbp - 16]
	mov	qword ptr [rdx], r8
	inc	rcx
	mov	qword ptr [rbp - 16], rcx
	mov	rcx, qword ptr [rbp - 24]
	mov	qword ptr [rbp - 32], rcx       # 8-byte Spill
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 32]       # 8-byte Reload
	mov	rcx, rsp
	mov	rdx, qword ptr [rbp - 24]
	mov	qword ptr [rcx], rdx
	sub	rax, 1
	mov	qword ptr [rbp - 24], rax
	jmp	.LBB2_2
.LBB2_4:                                # %for.end
	cmp	qword ptr [rbp - 8], 18
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
# %bb.5:                                # %exit
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	TestNestedForLoops;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestNestedForLoops
TestNestedForLoops:                     # @TestNestedForLoops
.seh_proc TestNestedForLoops
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 32
	.seh_stackalloc 32
	lea	rbp, [rsp + 32]
	.seh_setframe rbp, 32
	.seh_endprologue
	mov	qword ptr [rbp - 8], 0
	mov	qword ptr [rbp - 16], 0
	jmp	.LBB3_2
.LBB3_1:                                # %for.body
                                        #   in Loop: Header=BB3_2 Depth=1
	jmp	.LBB3_6
.LBB3_2:                                # %for.cond
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB3_6 Depth 2
	cmp	qword ptr [rbp - 8], 3
	jl	.LBB3_1
	jmp	.LBB3_4
.LBB3_3:                                # %for.iter
                                        #   in Loop: Header=BB3_2 Depth=1
	mov	rax, qword ptr [rbp - 8]
	mov	qword ptr [rbp - 24], rax       # 8-byte Spill
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 24]       # 8-byte Reload
	mov	rcx, rsp
	mov	rdx, qword ptr [rbp - 8]
	mov	qword ptr [rcx], rdx
	add	rax, 1
	mov	qword ptr [rbp - 8], rax
	jmp	.LBB3_2
.LBB3_4:                                # %for.end
	cmp	qword ptr [rbp - 8], 3
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	cmp	qword ptr [rbp - 16], 2
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB3_9
.LBB3_5:                                # %for.body1
                                        #   in Loop: Header=BB3_6 Depth=2
	jmp	.LBB3_7
.LBB3_6:                                # %for.cond2
                                        #   Parent Loop BB3_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	cmp	qword ptr [rbp - 16], 2
	jl	.LBB3_5
	jmp	.LBB3_8
.LBB3_7:                                # %for.iter3
                                        #   in Loop: Header=BB3_6 Depth=2
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
	jmp	.LBB3_6
.LBB3_8:                                # %for.end4
                                        #   in Loop: Header=BB3_2 Depth=1
	jmp	.LBB3_3
.LBB3_9:                                # %exit
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	TestForLoopWithBreak;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestForLoopWithBreak
TestForLoopWithBreak:                   # @TestForLoopWithBreak
.seh_proc TestForLoopWithBreak
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 32
	.seh_stackalloc 32
	lea	rbp, [rsp + 32]
	.seh_setframe rbp, 32
	.seh_endprologue
	mov	qword ptr [rbp - 8], 0
	mov	qword ptr [rbp - 16], 1
	jmp	.LBB4_2
.LBB4_1:                                # %for.body
                                        #   in Loop: Header=BB4_2 Depth=1
	mov	rax, qword ptr [rbp - 8]
	add	rax, qword ptr [rbp - 16]
	mov	qword ptr [rbp - 8], rax
	cmp	qword ptr [rbp - 16], 3
	je	.LBB4_5
	jmp	.LBB4_6
.LBB4_2:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	cmp	qword ptr [rbp - 16], 5
	jle	.LBB4_1
	jmp	.LBB4_4
.LBB4_3:                                # %for.iter
                                        #   in Loop: Header=BB4_2 Depth=1
	mov	rax, qword ptr [rbp - 16]
	mov	qword ptr [rbp - 24], rax       # 8-byte Spill
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 24]       # 8-byte Reload
	mov	rcx, rsp
	mov	rdx, qword ptr [rbp - 16]
	mov	qword ptr [rcx], rdx
	add	rax, 1
	mov	qword ptr [rbp - 16], rax
	jmp	.LBB4_2
.LBB4_4:                                # %for.end
	cmp	qword ptr [rbp - 8], 6
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB4_7
.LBB4_5:                                # %if.then
	jmp	.LBB4_4
.LBB4_6:                                # %if.end
                                        #   in Loop: Header=BB4_2 Depth=1
	jmp	.LBB4_3
.LBB4_7:                                # %exit
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	TestForLoopWithContinue;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestForLoopWithContinue
TestForLoopWithContinue:                # @TestForLoopWithContinue
.seh_proc TestForLoopWithContinue
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 32
	.seh_stackalloc 32
	lea	rbp, [rsp + 32]
	.seh_setframe rbp, 32
	.seh_endprologue
	mov	qword ptr [rbp - 8], 0
	mov	qword ptr [rbp - 16], 1
	jmp	.LBB5_2
.LBB5_1:                                # %for.body
                                        #   in Loop: Header=BB5_2 Depth=1
	cmp	qword ptr [rbp - 16], 3
	je	.LBB5_5
	jmp	.LBB5_6
.LBB5_2:                                # %for.cond
                                        # =>This Inner Loop Header: Depth=1
	cmp	qword ptr [rbp - 16], 5
	jle	.LBB5_1
	jmp	.LBB5_4
.LBB5_3:                                # %for.iter
                                        #   in Loop: Header=BB5_2 Depth=1
	mov	rax, qword ptr [rbp - 16]
	mov	qword ptr [rbp - 24], rax       # 8-byte Spill
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 24]       # 8-byte Reload
	mov	rcx, rsp
	mov	rdx, qword ptr [rbp - 16]
	mov	qword ptr [rcx], rdx
	add	rax, 1
	mov	qword ptr [rbp - 16], rax
	jmp	.LBB5_2
.LBB5_4:                                # %for.end
	cmp	qword ptr [rbp - 8], 12
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB5_7
.LBB5_5:                                # %if.then
                                        #   in Loop: Header=BB5_2 Depth=1
	jmp	.LBB5_3
.LBB5_6:                                # %if.end
                                        #   in Loop: Header=BB5_2 Depth=1
	mov	rax, qword ptr [rbp - 8]
	add	rax, qword ptr [rbp - 16]
	mov	qword ptr [rbp - 8], rax
	jmp	.LBB5_3
.LBB5_7:                                # %exit
	mov	rsp, rbp
	pop	rbp
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
	call	TestForLoopInt
	call	TestForLoopBoolCondition
	call	TestForLoopMultipleExpressions
	call	TestNestedForLoops
	call	TestForLoopWithBreak
	call	TestForLoopWithContinue
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestForLoopInt
	.addrsig_sym TestForLoopBoolCondition
	.addrsig_sym TestForLoopMultipleExpressions
	.addrsig_sym TestNestedForLoops
	.addrsig_sym TestForLoopWithBreak
	.addrsig_sym TestForLoopWithContinue
