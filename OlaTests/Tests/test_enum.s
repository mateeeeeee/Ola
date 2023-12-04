	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.intel_syntax noprefix
	.file	"test_enum.ola"
	.def	TestEnumValues;
	.scl	2;
	.type	32;
	.endef
	.globl	TestEnumValues                  # -- Begin function TestEnumValues
	.p2align	4, 0x90
TestEnumValues:                         # @TestEnumValues
.seh_proc TestEnumValues
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	ecx, 1
	call	Assert
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.def	TestEnumValuesAfterModification;
	.scl	2;
	.type	32;
	.endef
	.globl	TestEnumValuesAfterModification # -- Begin function TestEnumValuesAfterModification
	.p2align	4, 0x90
TestEnumValuesAfterModification:        # @TestEnumValuesAfterModification
.seh_proc TestEnumValuesAfterModification
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	ecx, 1
	call	Assert
	mov	ecx, 1
	call	Assert
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.def	TestEnumSwitch;
	.scl	2;
	.type	32;
	.endef
	.globl	TestEnumSwitch                  # -- Begin function TestEnumSwitch
	.p2align	4, 0x90
TestEnumSwitch:                         # @TestEnumSwitch
.seh_proc TestEnumSwitch
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	ecx, 1
	call	Assert
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.def	TestLocalEnumDeclaration;
	.scl	2;
	.type	32;
	.endef
	.globl	TestLocalEnumDeclaration        # -- Begin function TestLocalEnumDeclaration
	.p2align	4, 0x90
TestLocalEnumDeclaration:               # @TestLocalEnumDeclaration
.seh_proc TestLocalEnumDeclaration
# %bb.0:                                # %entry
	sub	rsp, 40
	.seh_stackalloc 40
	.seh_endprologue
	mov	ecx, 1
	call	Assert
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
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
	cmp	qword ptr [rip + globalColor], 0
	sete	cl
	call	Assert
	call	TestLocalEnumDeclaration
	call	TestEnumValues
	call	TestEnumValuesAfterModification
	call	TestEnumSwitch
	xor	eax, eax
                                        # kill: def $rax killed $eax
	add	rsp, 40
	ret
	.seh_endproc
                                        # -- End function
	.lcomm	globalColor,8,8                 # @globalColor
	.addrsig
	.addrsig_sym Assert
	.addrsig_sym TestEnumValues
	.addrsig_sym TestEnumValuesAfterModification
	.addrsig_sym TestEnumSwitch
	.addrsig_sym TestLocalEnumDeclaration
	.addrsig_sym globalColor
