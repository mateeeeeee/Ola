
find_package(LLVM 17.0 REQUIRED CONFIG)

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
  Utility/Attribute.h
  Utility/CLIParser.h
  Utility/CLIParser.cpp
)


set(FRONTEND_FILES
  Frontend/Diagnostics.cpp
  Frontend/Diagnostics.def
  Frontend/Diagnostics.h
  Frontend/Context.h
  Frontend/Context.cpp
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
  Backend/LLVM/LLVMIRGenContext.h
  Backend/LLVM/LLVMIRGenContext.cpp
  Backend/LLVM/LLVMIRVisitor.h
  Backend/LLVM/LLVMIRVisitor.cpp
  Backend/LLVM/LLVMOptimizer.h
  Backend/LLVM/LLVMOptimizer.cpp
  Backend/LLVM/Passes/TestPass.h

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
  Backend/Custom/IR/IROptimizer.h
  Backend/Custom/IR/IROptimizer.cpp
  Backend/Custom/IR/IRPrinter.h
  Backend/Custom/IR/IRPrinter.cpp
  Backend/Custom/IR/IRModulePrinter.h
  Backend/Custom/IR/IRModulePrinter.cpp
  Backend/Custom/IR/CFGPrinter.h
  Backend/Custom/IR/CFGPrinter.cpp
  Backend/Custom/IR/IRType.h
  Backend/Custom/IR/IRType.cpp
  Backend/Custom/IR/IRVisitor.h
  Backend/Custom/IR/IRVisitor.cpp

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
  
  Backend/Custom/IR/Passes/DominatorTreeAnalysisPass.h
  Backend/Custom/IR/Passes/DominatorTreeAnalysisPass.cpp
  Backend/Custom/IR/Passes/CFGAnalysisPass.h
  Backend/Custom/IR/Passes/CFGAnalysisPass.cpp
  Backend/Custom/IR/Passes/DeadCodeEliminationPass.h
  Backend/Custom/IR/Passes/DeadCodeEliminationPass.cpp
  Backend/Custom/IR/Passes/ArithmeticReductionPass.h
  Backend/Custom/IR/Passes/ArithmeticReductionPass.cpp
  Backend/Custom/IR/Passes/GlobalAttributeInferPass.h
  Backend/Custom/IR/Passes/GlobalAttributeInferPass.cpp
  Backend/Custom/IR/Passes/Mem2RegPass.h
  Backend/Custom/IR/Passes/Mem2RegPass.cpp

  Backend/Custom/Codegen/MachineOperand.h
  Backend/Custom/Codegen/MachineOperand.cpp
  Backend/Custom/Codegen/MachineInstruction.h
  Backend/Custom/Codegen/MachineBasicBlock.h
  Backend/Custom/Codegen/MachineRelocable.h
  Backend/Custom/Codegen/MachineStorage.h
  Backend/Custom/Codegen/MachineFunction.h
  Backend/Custom/Codegen/MachineFunction.cpp
  Backend/Custom/Codegen/MachineGlobal.h
  Backend/Custom/Codegen/MachineModule.h
  Backend/Custom/Codegen/MachineModule.cpp
  Backend/Custom/Codegen/Target.h
  Backend/Custom/Codegen/Target.cpp
  Backend/Custom/Codegen/LoweringContext.h
  Backend/Custom/Codegen/LoweringContext.cpp
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

set(COMPILER_FILES
  Compiler/Compiler.h
  Compiler/Compiler.cpp
  Compiler/CompileRequest.h
  Compiler/CompileRequest.cpp
  Compiler/CompilerOptions.h
  Compiler/RTTI.h
)

set(TEST_FILES
	Test/test.ola
	Test/test.ll
	Test/test.s
	Test/test.oll
	Test/Test2/test2.ola
	Test/Test2/test2.ll
)

add_executable(OlaCompiler main.cpp autogen/OlaConfig.h ${CORE_FILES} ${UTILITY_FILES} ${FRONTEND_FILES} ${BACKEND_FILES} ${COMPILER_FILES} ${TEST_FILES})

set_target_properties(OlaCompiler PROPERTIES OUTPUT_NAME Ola)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES  main.cpp autogen/OlaConfig.h ${CORE_FILES} ${UTILITY_FILES} ${FRONTEND_FILES} ${BACKEND_FILES} ${COMPILER_FILES} ${TEST_FILES})

target_include_directories(OlaCompiler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(OlaCompiler PRIVATE ${LLVM_INCLUDE_DIRS})
#target_compile_definitions(OlaCompiler PRIVATE ${LLVM_DEFINITIONS})

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

install(TARGETS OlaCompiler DESTINATION bin)
