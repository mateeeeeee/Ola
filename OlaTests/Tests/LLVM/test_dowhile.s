	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_dowhile.ola"
	.def	TestDoWhileLoopInt;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestDoWhileLoopInt
TestDoWhileLoopInt:                     # @TestDoWhileLoopInt
.seh_proc TestDoWhileLoopInt
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
.LBB0_1:                                # %dowhile.body
                                        # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbp - 8]
	mov	rcx, qword ptr [rbp - 16]
	add	rax, rcx
	mov	qword ptr [rbp - 8], rax
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
# %bb.2:                                # %dowhile.cond
                                        #   in Loop: Header=BB0_1 Depth=1
	cmp	qword ptr [rbp - 16], 5
	jle	.LBB0_1
# %bb.3:                                # %dowhile.end
	cmp	qword ptr [rbp - 8], 15
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
# %bb.4:                                # %exit
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	TestDoWhileLoopBool;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestDoWhileLoopBool
TestDoWhileLoopBool:                    # @TestDoWhileLoopBool
.seh_proc TestDoWhileLoopBool
# %bb.0:                                # %entry
	push	rbp
	.seh_pushreg rbp
	sub	rsp, 32
	.seh_stackalloc 32
	lea	rbp, [rsp + 32]
	.seh_setframe rbp, 32
	.seh_endprologue
	mov	byte ptr [rbp - 1], 1
	mov	qword ptr [rbp - 16], 0
.LBB1_1:                                # %dowhile.body
                                        # =>This Inner Loop Header: Depth=1
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
	cmp	qword ptr [rbp - 16], 3
	je	.LBB1_4
	jmp	.LBB1_5
.LBB1_2:                                # %dowhile.cond
                                        #   in Loop: Header=BB1_1 Depth=1
	test	byte ptr [rbp - 1], 1
	jne	.LBB1_1
# %bb.3:                                # %dowhile.end
	cmp	qword ptr [rbp - 16], 3
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB1_6
.LBB1_4:                                # %if.then
                                        #   in Loop: Header=BB1_1 Depth=1
	mov	byte ptr [rbp - 1], 0
.LBB1_5:                                # %if.end
                                        #   in Loop: Header=BB1_1 Depth=1
	jmp	.LBB1_2
.LBB1_6:                                # %exit
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	TestNestedDoWhileLoops;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestNestedDoWhileLoops
TestNestedDoWhileLoops:                 # @TestNestedDoWhileLoops
.seh_proc TestNestedDoWhileLoops
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
.LBB2_1:                                # %dowhile.body
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB2_4 Depth 2
	jmp	.LBB2_4
.LBB2_2:                                # %dowhile.cond
                                        #   in Loop: Header=BB2_1 Depth=1
	cmp	qword ptr [rbp - 8], 3
	jl	.LBB2_1
# %bb.3:                                # %dowhile.end
	cmp	qword ptr [rbp - 8], 3
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	cmp	qword ptr [rbp - 16], 4
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB2_7
.LBB2_4:                                # %dowhile.body1
                                        #   Parent Loop BB2_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
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
# %bb.5:                                # %dowhile.cond2
                                        #   in Loop: Header=BB2_4 Depth=2
	cmp	qword ptr [rbp - 16], 2
	jl	.LBB2_4
# %bb.6:                                # %dowhile.end3
                                        #   in Loop: Header=BB2_1 Depth=1
	mov	rax, qword ptr [rbp - 8]
	mov	qword ptr [rbp - 32], rax       # 8-byte Spill
	mov	eax, 16
	call	__chkstk
	sub	rsp, rax
	mov	rax, qword ptr [rbp - 32]       # 8-byte Reload
	mov	rcx, rsp
	mov	rdx, qword ptr [rbp - 8]
	mov	qword ptr [rcx], rdx
	add	rax, 1
	mov	qword ptr [rbp - 8], rax
	jmp	.LBB2_2
.LBB2_7:                                # %exit
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	TestDoWhileLoopWithBreak;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestDoWhileLoopWithBreak
TestDoWhileLoopWithBreak:               # @TestDoWhileLoopWithBreak
.seh_proc TestDoWhileLoopWithBreak
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
.LBB3_1:                                # %dowhile.body
                                        # =>This Inner Loop Header: Depth=1
	mov	rax, qword ptr [rbp - 8]
	mov	rcx, qword ptr [rbp - 16]
	add	rax, rcx
	mov	qword ptr [rbp - 8], rax
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
	cmp	qword ptr [rbp - 16], 5
	jg	.LBB3_4
	jmp	.LBB3_5
.LBB3_2:                                # %dowhile.cond
                                        #   in Loop: Header=BB3_1 Depth=1
	mov	al, 1
	test	al, 1
	jne	.LBB3_1
	jmp	.LBB3_3
.LBB3_3:                                # %dowhile.end
	cmp	qword ptr [rbp - 8], 15
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB3_6
.LBB3_4:                                # %if.then
	jmp	.LBB3_3
.LBB3_5:                                # %if.end
                                        #   in Loop: Header=BB3_1 Depth=1
	jmp	.LBB3_2
.LBB3_6:                                # %exit
	mov	rsp, rbp
	pop	rbp
	ret
	.seh_endproc
                                        # -- End function
	.def	TestDoWhileLoopWithContinue;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function TestDoWhileLoopWithContinue
TestDoWhileLoopWithContinue:            # @TestDoWhileLoopWithContinue
.seh_proc TestDoWhileLoopWithContinue
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
.LBB4_1:                                # %dowhile.body
                                        # =>This Inner Loop Header: Depth=1
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
	mov	rax, qword ptr [rbp - 16]
	mov	ecx, 2
	cqo
	idiv	rcx
	cmp	rdx, 0
	je	.LBB4_4
	jmp	.LBB4_5
.LBB4_2:                                # %dowhile.cond
                                        #   in Loop: Header=BB4_1 Depth=1
	cmp	qword ptr [rbp - 16], 5
	jl	.LBB4_1
# %bb.3:                                # %dowhile.end
	cmp	qword ptr [rbp - 8], 9
	sete	cl
	sub	rsp, 32
	call	Assert
	add	rsp, 32
	jmp	.LBB4_6
.LBB4_4:                                # %if.then
                                        #   in Loop: Header=BB4_1 Depth=1
	jmp	.LBB4_2
.LBB4_5:                                # %if.end
                                        #   in Loop: Header=BB4_1 Depth=1
	mov	rax, qword ptr [rbp - 8]
	add	rax, qword ptr [rbp - 16]
	mov	qword ptr [rbp - 8], rax
	jmp	.LBB4_2
.LBB4_6:                                # %exit
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
	call	TestDoWhileLoopInt
	call	TestDoWhileLoopBool
	call	TestNestedDoWhileLoops
	call	TestDoWhileLoopWithBreak
	call	TestDoWhileLoopWithContinue
	mov	qword ptr [rsp + 32], 0
# %bb.1:                                # %exit
	mov	rax, qword ptr [rsp + 32]
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestDoWhileLoopInt
	.addrsig_sym TestDoWhileLoopBool
	.addrsig_sym TestNestedDoWhileLoops
	.addrsig_sym TestDoWhileLoopWithBreak
	.addrsig_sym TestDoWhileLoopWithContinue
