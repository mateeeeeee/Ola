option(ENABLE_LLVM "Enable LLVM backend" ON)

if(ENABLE_LLVM)
    message(STATUS "LLVM backend is enabled.")
    find_package(LLVM 17 QUIET CONFIG)
    if(LLVM_FOUND)
        message(STATUS "LLVM 17.0 found.")
    else()
        message(STATUS "LLVM backend was enabled, but LLVM 17.0 was not found! Disabling LLVM backend...")
    endif()
else()
    message(STATUS "LLVM backend is disabled.")
endif()

configure_file(${CMAKE_SOURCE_DIR}/ola_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/autogen/OlaConfig.h)



set(CORE_FILES
  Core/Types.h
  Core/Macros.h
  Core/Log.h
  Core/Log.cpp
)

set(UTILITY_FILES
  Utility/DebugVisitor.h
  Utility/DebugVisitor.cpp
  Utility/EnumOperators.h
  Utility/IntrusiveList.h
  Utility/IteratorRange.h
  Utility/IteratorFacade.h
  Utility/Hash.h
  Utility/Attribute.h
  Utility/CLIParser.h
  Utility/CLIParser.cpp
  Utility/TreeIterator.h
  Utility/Command.h
  Utility/Command.cpp
)


set(FRONTEND_FILES
  Frontend/Diagnostics.cpp
  Frontend/Diagnostics.def
  Frontend/Diagnostics.h
  Frontend/FrontendContext.h
  Frontend/FrontendContext.cpp
  Frontend/ImportProcessor.cpp
  Frontend/ImportProcessor.h
  Frontend/Lexer.cpp
  Frontend/Lexer.h
  Frontend/Parser.cpp
  Frontend/Parser.h
  Frontend/Scope.h
  Frontend/Sema.cpp
  Frontend/Sema.h
  Frontend/SourceBuffer.cpp
  Frontend/SourceBuffer.h
  Frontend/SourceLocation.h
  Frontend/Token.h
  Frontend/Tokens.def
  Frontend/TokenKind.cpp
  Frontend/TokenKind.h
  Frontend/AST/Type.h
  Frontend/AST/Type.cpp
  Frontend/AST/AST.cpp
  Frontend/AST/AST.h
  Frontend/AST/ASTNode.h
  Frontend/AST/ASTFwd.h
  Frontend/AST/ASTAliases.h
  Frontend/AST/ASTVisitor.h
  Frontend/AST/Decl.h
  Frontend/AST/Decl.cpp
  Frontend/AST/Stmt.h
  Frontend/AST/Stmt.cpp
  Frontend/AST/Expr.h
  Frontend/AST/Expr.cpp
)


set(BACKEND_FILES
  Backend/Custom/IR/IRBuilder.h
  Backend/Custom/IR/IRBuilder.cpp
  Backend/Custom/IR/ConstantFold.h
  Backend/Custom/IR/ConstantFold.cpp
  Backend/Custom/IR/IRContext.h
  Backend/Custom/IR/IRContext.cpp
  Backend/Custom/IR/IRGenContext.h
  Backend/Custom/IR/IRGenContext.cpp
  Backend/Custom/IR/IRModule.h
  Backend/Custom/IR/IRModule.cpp
  Backend/Custom/IR/IRPassManager.h
  Backend/Custom/IR/IRPassManager.cpp
  Backend/Custom/IR/IRPrinter.h
  Backend/Custom/IR/IRPrinter.cpp
  Backend/Custom/IR/PrinterBase.h
  Backend/Custom/IR/PrinterBase.cpp
  Backend/Custom/IR/CFG.h
  Backend/Custom/IR/CFG.cpp
  Backend/Custom/IR/CFGPrinter.h
  Backend/Custom/IR/CFGPrinter.cpp
  Backend/Custom/IR/IRType.h
  Backend/Custom/IR/IRType.cpp
  Backend/Custom/IR/IRVisitor.h
  Backend/Custom/IR/IRVisitor.cpp
  Backend/Custom/IR/PatternMatch.h

  Backend/Custom/IR/Value.h
  Backend/Custom/IR/Value.cpp
  Backend/Custom/IR/Instruction.h
  Backend/Custom/IR/Instruction.cpp
  Backend/Custom/IR/GlobalValue.h
  Backend/Custom/IR/GlobalValue.cpp
  Backend/Custom/IR/BasicBlock.h
  Backend/Custom/IR/BasicBlock.cpp
  Backend/Custom/IR/Constant.h
  Backend/Custom/IR/Constant.cpp
  Backend/Custom/IR/FunctionPass.h
  Backend/Custom/IR/IRModulePass.h
  Backend/Custom/IR/Loop.h
  Backend/Custom/IR/Loop.cpp
  Backend/Custom/IR/DominatorTree.h
  Backend/Custom/IR/DominatorTree.cpp
  Backend/Custom/IR/DominanceFrontier.h
  Backend/Custom/IR/DominanceFrontier.cpp
  
  Backend/Custom/IR/Passes/DominatorTreeAnalysisPass.h
  Backend/Custom/IR/Passes/DominatorTreeAnalysisPass.cpp
  Backend/Custom/IR/Passes/DominanceFrontierAnalysisPass.h
  Backend/Custom/IR/Passes/DominanceFrontierAnalysisPass.cpp
  Backend/Custom/IR/Passes/CFGAnalysisPass.h
  Backend/Custom/IR/Passes/CFGAnalysisPass.cpp
  Backend/Custom/IR/Passes/DeadCodeEliminationPass.h
  Backend/Custom/IR/Passes/DeadCodeEliminationPass.cpp
  Backend/Custom/IR/Passes/CommonSubexpressionEliminationPass.h
  Backend/Custom/IR/Passes/CommonSubexpressionEliminationPass.cpp
  Backend/Custom/IR/Passes/ArithmeticReductionPass.h
  Backend/Custom/IR/Passes/ArithmeticReductionPass.cpp
  Backend/Custom/IR/Passes/GlobalAttributeInferPass.h
  Backend/Custom/IR/Passes/GlobalAttributeInferPass.cpp
  Backend/Custom/IR/Passes/Mem2RegPass.h
  Backend/Custom/IR/Passes/Mem2RegPass.cpp
  Backend/Custom/IR/Passes/ConstantPropagationPass.h
  Backend/Custom/IR/Passes/ConstantPropagationPass.cpp
  Backend/Custom/IR/Passes/FunctionPassManagerModuleAdaptor.h
  Backend/Custom/IR/Passes/FunctionPassManagerModuleAdaptor.cpp

  Backend/Custom/Codegen/MachineOperand.h
  Backend/Custom/Codegen/MachineOperand.cpp
  Backend/Custom/Codegen/MachineInstruction.h
  Backend/Custom/Codegen/MachineInstruction.cpp
  Backend/Custom/Codegen/MachineBasicBlock.h
  Backend/Custom/Codegen/MachineRelocable.h
  Backend/Custom/Codegen/MachineStorage.h
  Backend/Custom/Codegen/MachineFunction.h
  Backend/Custom/Codegen/MachineFunction.cpp
  Backend/Custom/Codegen/MachineGlobal.h
  Backend/Custom/Codegen/MachineModule.h
  Backend/Custom/Codegen/MachineModule.cpp
  Backend/Custom/Codegen/MachineIRPrinter.h
  Backend/Custom/Codegen/MachineIRPrinter.cpp
  Backend/Custom/Codegen/Target.h
  Backend/Custom/Codegen/Target.cpp
  Backend/Custom/Codegen/MachineContext.h
  Backend/Custom/Codegen/MachineContext.cpp
  Backend/Custom/Codegen/MachineModulePass.h
  Backend/Custom/Codegen/MachineFunctionPass.h
  Backend/Custom/Codegen/LivenessAnalysis.h
  Backend/Custom/Codegen/LivenessAnalysis.cpp
  Backend/Custom/Codegen/RegisterAllocator.h
  Backend/Custom/Codegen/LinearScanRegisterAllocator.h
  Backend/Custom/Codegen/LinearScanRegisterAllocator.cpp
  Backend/Custom/Codegen/AsmPrinter.h
  Backend/Custom/Codegen/AsmPrinter.cpp

  Backend/Custom/Codegen/x64/x64.h
  Backend/Custom/Codegen/x64/x64Target.h
  Backend/Custom/Codegen/x64/x64Target.cpp
  Backend/Custom/Codegen/x64/x64TargetFrameInfo.h
  Backend/Custom/Codegen/x64/x64TargetFrameInfo.cpp
  Backend/Custom/Codegen/x64/x64TargetInstInfo.h
  Backend/Custom/Codegen/x64/x64TargetInstInfo.cpp
  Backend/Custom/Codegen/x64/x64AsmPrinter.h
  Backend/Custom/Codegen/x64/x64AsmPrinter.cpp


  Backend/Custom/Pass.h
  Backend/Custom/Pass.cpp
  Backend/Custom/PassManager.h
  Backend/Custom/PassRegistry.h
  Backend/Custom/AnalysisManager.h
)

if(LLVM_FOUND)
    list(APPEND BACKEND_FILES 
	  Backend/LLVM/LLVMIRGenContext.h
	  Backend/LLVM/LLVMIRGenContext.cpp
	  Backend/LLVM/LLVMIRVisitor.h
	  Backend/LLVM/LLVMIRVisitor.cpp
	  Backend/LLVM/LLVMIRPassManager.h
	  Backend/LLVM/LLVMIRPassManager.cpp
	  Backend/LLVM/LLVMUtils.h
	  Backend/LLVM/LLVMUtils.cpp
	  Backend/LLVM/Passes/TestPass.h
)
endif()

set(COMPILER_FILES
  Compiler/Compiler.h
  Compiler/Compiler.cpp
  Compiler/CompileRequest.h
  Compiler/CompilerMacros.h
  Compiler/CompileRequest.cpp
  Compiler/CompilerOptions.h
  Compiler/RTTI.h
)

add_library(OlaCompiler STATIC
  ${CORE_FILES}
  ${UTILITY_FILES}
  ${FRONTEND_FILES}
  ${BACKEND_FILES}
  ${COMPILER_FILES}
)
target_include_directories(OlaCompiler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(LLVM_FOUND)
	target_include_directories(OlaCompiler PRIVATE ${LLVM_INCLUDE_DIRS})
	set(LLVM_LIBRARIES
		LLVMAnalysis
		LLVMCore
		LLVMExecutionEngine
		LLVMInstCombine
		LLVMObject
		LLVMSupport
		LLVMOrcJIT
		LLVMRuntimeDyld
		LLVMScalarOpts
		LLVMX86CodeGen
		LLVMX86AsmParser
		LLVMX86Desc
		LLVMX86Disassembler
		LLVMX86Info
		LLVMAArch64AsmParser
		LLVMAArch64CodeGen
		LLVMAArch64Desc
		LLVMAArch64Disassembler
		LLVMAArch64Info
		LLVMAArch64Utils
		LLVMARMAsmParser
		LLVMARMCodeGen
		LLVMARMDesc
		LLVMARMDisassembler
		LLVMARMInfo
		LLVMARMUtils
		LLVMWebAssemblyAsmParser
		LLVMWebAssemblyCodeGen
		LLVMWebAssemblyDesc
		LLVMWebAssemblyDisassembler
		LLVMWebAssemblyInfo
		LLVMWebAssemblyUtils
		LLVMPasses
		LLVMCoroutines
		LLVMipo
		LLVMFrontendOpenMP
		LLVMLinker
		LLVMIRPrinter
		LLVMVectorize
		LLVMJITLink
		LLVMOrcTargetProcess
		LLVMOrcShared
		LLVMWindowsDriver
		LLVMOption
		LLVMAsmPrinter
		LLVMCFGuard
		LLVMGlobalISel
		LLVMInstrumentation
		LLVMSelectionDAG
		LLVMCodeGen
		LLVMAggressiveInstCombine
		LLVMTarget
		LLVMBitWriter
		LLVMObjCARCOpts
		LLVMTransformUtils
		LLVMProfileData
		LLVMSymbolize
		LLVMDebugInfoPDB
		LLVMDebugInfoMSF
		LLVMDebugInfoBTF
		LLVMDebugInfoDWARF
		LLVMIRReader
		LLVMBitReader
		LLVMAsmParser
		LLVMTextAPI
		LLVMRemarks
		LLVMBitstreamReader
		LLVMCodeGenTypes
		LLVMMCParser
		LLVMMCDisassembler
		LLVMMC
		LLVMBinaryFormat
		LLVMTargetParser
		LLVMDebugInfoCodeView
		LLVMDemangle
	)
	target_link_directories(OlaCompiler PRIVATE ${LLVM_LIBRARY_DIRS})
	target_link_libraries(OlaCompiler PRIVATE ${LLVM_LIBRARIES})
endif()

if(MSVC)
	set(DISABLED_WARNINGS
		/wd4141
		/wd4146
		/wd4244
		/wd4267
		/wd4291
		/wd4351
		/wd4456
		/wd4457
		/wd4458
		/wd4459
		/wd4503
		/wd4624
		/wd4722
		/wd4100
		/wd4127
		/wd4512
		/wd4505
		/wd4610
		/wd4510
		/wd4702
		/wd4245
		/wd4706
		/wd4310
		/wd4701
		/wd4703
		/wd4389
		/wd4611
		/wd4804
		/wd4805
		/wd4204
		/wd4577
		/wd4091
		/wd4592
		/wd4319
		/wd4709
		/wd5105
		/wd4324
	)
	target_compile_options(OlaCompiler PRIVATE ${DISABLED_WARNINGS})
    add_definitions(/FI"Core/Types.h" /FI"Core/Macros.h")
else()                                                   
    add_definitions(-include Core/Types.h -include Core/Macros.h)
endif()

add_executable(OlaDriver main.cpp autogen/OlaConfig.h)
target_link_libraries(OlaDriver PRIVATE OlaCompiler)
set_target_properties(OlaDriver PROPERTIES OUTPUT_NAME Ola)


if(LLVM_FOUND)
    target_compile_definitions(OlaCompiler PRIVATE HAS_LLVM=1)
    target_compile_definitions(OlaDriver PRIVATE HAS_LLVM=1)
else()
    target_compile_definitions(OlaCompiler PRIVATE HAS_LLVM=0)
    target_compile_definitions(OlaDriver PRIVATE HAS_LLVM=0)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES main.cpp autogen/OlaConfig.h ${CORE_FILES} ${UTILITY_FILES} ${FRONTEND_FILES} ${BACKEND_FILES} ${COMPILER_FILES})
install(TARGETS OlaDriver DESTINATION bin)
