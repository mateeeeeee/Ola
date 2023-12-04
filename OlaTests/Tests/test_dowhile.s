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
	sub	rsp, 24
	.seh_stackalloc 24
	.seh_endprologue
	mov	qword ptr [rsp + 16], 1
	xor	eax, eax
                                        # kill: def $rax killed $eax
	mov	qword ptr [rsp + 8], rax        # 8-byte Spill
.LBB0_1:                                # %dowhile.body
                                        # =>This Inner Loop Header: Depth=1
	mov	rdx, qword ptr [rsp + 8]        # 8-byte Reload
	mov	rax, qword ptr [rsp + 16]
	mov	rcx, rax
	add	rcx, 1
	mov	qword ptr [rsp + 16], rcx
	add	rax, rdx
	mov	qword ptr [rsp], rax            # 8-byte Spill
	cmp	rcx, 6
	mov	qword ptr [rsp + 8], rax        # 8-byte Spill
	jl	.LBB0_1
# %bb.2:                                # %dowhile.end
	mov	rax, qword ptr [rsp]            # 8-byte Reload
	sub	rax, 15
	sete	cl
	add	rsp, 24
	jmp	Assert                          # TAILCALL
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
	sub	rsp, 16
	.seh_stackalloc 16
	.seh_endprologue
	mov	qword ptr [rsp + 8], 0
	mov	al, 1
	mov	byte ptr [rsp + 7], al          # 1-byte Spill
.LBB1_1:                                # %dowhile.body
                                        # =>This Inner Loop Header: Depth=1
	mov	cl, byte ptr [rsp + 7]          # 1-byte Reload
	mov	rax, qword ptr [rsp + 8]
	inc	rax
	mov	qword ptr [rsp + 8], rax
	sub	rax, 3
	setne	al
	and	al, cl
	test	al, 1
	mov	byte ptr [rsp + 7], al          # 1-byte Spill
	jne	.LBB1_1
# %bb.2:                                # %dowhile.end
	mov	rax, qword ptr [rsp + 8]
	sub	rax, 3
	sete	cl
	add	rsp, 16
	jmp	Assert                          # TAILCALL
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
	sub	rsp, 56
	.seh_stackalloc 56
	.seh_endprologue
	mov	qword ptr [rsp + 48], 0
	mov	qword ptr [rsp + 40], 0
.LBB2_1:                                # %dowhile.body
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB2_3 Depth 2
	jmp	.LBB2_3
.LBB2_2:                                # %dowhile.end
	mov	rax, qword ptr [rsp + 32]       # 8-byte Reload
	sub	rax, 3
	sete	cl
	call	Assert
	mov	rax, qword ptr [rsp + 40]
	sub	rax, 4
	sete	cl
	add	rsp, 56
	jmp	Assert                          # TAILCALL
.LBB2_3:                                # %dowhile.body1
                                        #   Parent Loop BB2_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	mov	rax, qword ptr [rsp + 40]
	add	rax, 1
	mov	qword ptr [rsp + 40], rax
	cmp	rax, 2
	jl	.LBB2_3
# %bb.4:                                # %dowhile.end3
                                        #   in Loop: Header=BB2_1 Depth=1
	mov	rax, qword ptr [rsp + 48]
	add	rax, 1
	mov	qword ptr [rsp + 32], rax       # 8-byte Spill
	mov	qword ptr [rsp + 48], rax
	cmp	rax, 3
	jl	.LBB2_1
	jmp	.LBB2_2
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
	sub	rsp, 24
	.seh_stackalloc 24
	.seh_endprologue
	mov	qword ptr [rsp + 16], 1
	xor	eax, eax
                                        # kill: def $rax killed $eax
	mov	qword ptr [rsp + 8], rax        # 8-byte Spill
.LBB3_1:                                # %dowhile.body
                                        # =>This Inner Loop Header: Depth=1
	mov	rdx, qword ptr [rsp + 8]        # 8-byte Reload
	mov	rcx, qword ptr [rsp + 16]
	mov	rax, rcx
	add	rax, rdx
	mov	qword ptr [rsp], rax            # 8-byte Spill
	add	rcx, 1
	mov	qword ptr [rsp + 16], rcx
	cmp	rcx, 5
	mov	qword ptr [rsp + 8], rax        # 8-byte Spill
	jle	.LBB3_1
# %bb.2:                                # %if.then
	mov	rax, qword ptr [rsp]            # 8-byte Reload
	sub	rax, 15
	sete	cl
	add	rsp, 24
	jmp	Assert                          # TAILCALL
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
	sub	rsp, 24
	.seh_stackalloc 24
	.seh_endprologue
	mov	qword ptr [rsp + 16], 0
	xor	eax, eax
                                        # kill: def $rax killed $eax
	mov	qword ptr [rsp + 8], rax        # 8-byte Spill
.LBB4_1:                                # %dowhile.body
                                        # =>This Inner Loop Header: Depth=1
	mov	rcx, qword ptr [rsp + 8]        # 8-byte Reload
	mov	rax, qword ptr [rsp + 16]
	add	rax, 1
	mov	qword ptr [rsp + 16], rax
	mov	rdx, rax
	and	rdx, 1
	add	rax, rcx
	cmp	rdx, 0
	cmove	rax, rcx
	mov	qword ptr [rsp], rax            # 8-byte Spill
	cmp	qword ptr [rsp + 16], 5
	mov	qword ptr [rsp + 8], rax        # 8-byte Spill
	jl	.LBB4_1
# %bb.2:                                # %dowhile.end
	mov	rax, qword ptr [rsp]            # 8-byte Reload
	sub	rax, 9
	sete	cl
	add	rsp, 24
	jmp	Assert                          # TAILCALL
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
	xor	eax, eax
                                        # kill: def $rax killed $eax
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
