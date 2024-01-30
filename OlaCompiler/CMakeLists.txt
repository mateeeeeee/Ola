
find_package(LLVM 17.0 REQUIRED CONFIG)

configure_file(${CMAKE_SOURCE_DIR}/ola_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/autogen/OlaConfig.h)

set(CORE_FILES
  Core/CoreTypes.h
  Core/Defines.h
  Core/Logger.h
)

set(UTILITY_FILES
  Utility/DebugVisitor.h
  Utility/DebugVisitor.cpp
  Utility/Enums.h
  Utility/IntrusiveList.h
  Utility/IteratorRange.h
  Utility/IteratorFacade.h
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
  Backend/LLVM/LLVMIRGen.h
  Backend/LLVM/LLVMIRGen.cpp
  Backend/LLVM/LLVMIRVisitor.h
  Backend/LLVM/LLVMIRVisitor.cpp
  Backend/LLVM/LLVMOptimizer.h
  Backend/LLVM/LLVMOptimizer.cpp
  Backend/LLVM/LLVMCodeGen.h
  Backend/LLVM/LLVMCodeGen.cpp
  Backend/Custom/IR.h
  Backend/Custom/IRBuilder.h
  Backend/Custom/IRBuilder.cpp
  Backend/Custom/IRType.h
  Backend/Custom/IRType.cpp
  Backend/Custom/IRGen.h
  Backend/Custom/IRGen.cpp
  Backend/Custom/IRVisitor.h
  Backend/Custom/IRVisitor.cpp
  Backend/Custom/IRContext.h
  Backend/Custom/IRContext.cpp
  Backend/Custom/IRModule.h
  Backend/Custom/IRModule.cpp
  Backend/Custom/IR/Values.def
  Backend/Custom/IR/IRFwd.h
  Backend/Custom/IR/Value.h
  Backend/Custom/IR/Value.cpp
  Backend/Custom/IR/Use.h
  Backend/Custom/IR/User.h
  Backend/Custom/IR/User.cpp
  Backend/Custom/IR/Instruction.h
  Backend/Custom/IR/Instruction.cpp
  Backend/Custom/IR/Constant.h
  Backend/Custom/IR/GlobalValue.h
  Backend/Custom/IR/GlobalValue.cpp
  Backend/Custom/IR/BasicBlock.h
  Backend/Custom/IR/BasicBlock.cpp
  Backend/Custom/IR/UnaryInstruction.h
  Backend/Custom/IR/UnaryInstruction.cpp
  Backend/Custom/IR/BinaryInstruction.h
  Backend/Custom/IR/BinaryInstruction.cpp
  Backend/Custom/IR/Instructions.h
  Backend/Custom/IR/Instructions.cpp
)

set(COMPILER_FILES
  Compiler/Compiler.h
  Compiler/Compiler.cpp
  Compiler/RTTI.h
)

set(TEST_FILES
	Test/test.ola
	Test/test.ll
	Test/Test2/test2.ola
	Test/Test2/test2.ll
)

add_executable(OlaCompiler main.cpp autogen/OlaConfig.h ${CORE_FILES} ${UTILITY_FILES} ${FRONTEND_FILES} ${BACKEND_FILES} ${COMPILER_FILES} ${TEST_FILES})

set_target_properties(OlaCompiler PROPERTIES OUTPUT_NAME Ola)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES  main.cpp autogen/OlaConfig.h ${CORE_FILES} ${UTILITY_FILES} ${FRONTEND_FILES} ${BACKEND_FILES} ${COMPILER_FILES} ${TEST_FILES})

target_include_directories(OlaCompiler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(OlaCompiler PRIVATE ${CMAKE_SOURCE_DIR}/Libraries/spdlog/include)
target_include_directories(OlaCompiler PRIVATE ${CMAKE_SOURCE_DIR}/Libraries/CLI11/include)
target_include_directories(OlaCompiler PRIVATE ${LLVM_INCLUDE_DIRS})
#target_compile_definitions(OlaCompiler PRIVATE ${LLVM_DEFINITIONS})

set(LLVM_LIBRARIES
LLVMAnalysis.lib
LLVMCore.lib
LLVMExecutionEngine.lib
LLVMInstCombine.lib
LLVMObject.lib
LLVMOrcJIT.lib
LLVMRuntimeDyld.lib
LLVMScalarOpts.lib
LLVMSupport.lib
LLVMX86CodeGen.lib
LLVMX86AsmParser.lib
LLVMX86Desc.lib
LLVMX86Disassembler.lib
LLVMX86Info.lib
LLVMAArch64AsmParser.lib
LLVMAArch64CodeGen.lib
LLVMAArch64Desc.lib
LLVMAArch64Disassembler.lib
LLVMAArch64Info.lib
LLVMAArch64Utils.lib
LLVMARMAsmParser.lib
LLVMARMCodeGen.lib
LLVMARMDesc.lib
LLVMARMDisassembler.lib
LLVMARMInfo.lib
LLVMARMUtils.lib
LLVMWebAssemblyAsmParser.lib
LLVMWebAssemblyCodeGen.lib
LLVMWebAssemblyDesc.lib
LLVMWebAssemblyDisassembler.lib
LLVMWebAssemblyInfo.lib
LLVMWebAssemblyUtils.lib
LLVMPasses.lib
LLVMCoroutines.lib
LLVMipo.lib
LLVMFrontendOpenMP.lib
LLVMLinker.lib
LLVMIRPrinter.lib
LLVMVectorize.lib
LLVMJITLink.lib
LLVMOrcTargetProcess.lib
LLVMOrcShared.lib
LLVMWindowsDriver.lib
LLVMOption.lib
LLVMAsmPrinter.lib
LLVMCFGuard.lib
LLVMGlobalISel.lib
LLVMInstrumentation.lib
LLVMSelectionDAG.lib
LLVMCodeGen.lib
LLVMAggressiveInstCombine.lib
LLVMTarget.lib
LLVMBitWriter.lib
LLVMObjCARCOpts.lib
LLVMTransformUtils.lib
LLVMProfileData.lib
LLVMSymbolize.lib
LLVMDebugInfoPDB.lib
LLVMDebugInfoMSF.lib
LLVMDebugInfoBTF.lib
LLVMDebugInfoDWARF.lib
LLVMIRReader.lib
LLVMBitReader.lib
LLVMAsmParser.lib
LLVMTextAPI.lib
LLVMRemarks.lib
LLVMBitstreamReader.lib
LLVMCodeGenTypes.lib
LLVMMCParser.lib
LLVMMCDisassembler.lib
LLVMMC.lib
LLVMBinaryFormat.lib
LLVMTargetParser.lib
LLVMDebugInfoCodeView.lib
LLVMDemangle.lib
)

target_link_directories(OlaCompiler PRIVATE ${LLVM_LIBRARY_DIRS})
target_link_libraries(OlaCompiler PRIVATE ${LLVM_LIBRARIES})

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

if(MSVC)
    add_definitions(/FI"Core/CoreTypes.h" /FI"Core/Defines.h")
else()                                                   
    add_definitions(-include Core/CoreTypes.h -include Core/Defines.h)
endif()

install(TARGETS OlaCompiler DESTINATION bin)
