
find_package(LLVM 17.0 REQUIRED CONFIG)

configure_file(${CMAKE_SOURCE_DIR}/wave_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/autogen/WaveConfig.h)

set(CORE_FILES
  Core/CoreTypes.h
  Core/Defines.h
  Core/Logger.h
)

set(UTILITY_FILES
  Utility/DebugVisitor.h
  Utility/DebugVisitor.cpp
  Utility/Enums.h
)


set(FRONTEND_FILES
  Frontend/AST.cpp
  Frontend/AST.h
  Frontend/ASTForwardDeclarations.h
  Frontend/ASTTypeAliases.h
  Frontend/ASTVisitor.h
  Frontend/Diagnostics.cpp
  Frontend/Diagnostics.def
  Frontend/Diagnostics.h
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
  Frontend/TokenTypes.cpp
  Frontend/TokenTypes.h
  Frontend/Type.h
)


set(BACKEND_FILES
  Backend/LLVMVisitor.h
  Backend/LLVMVisitor.cpp
  Backend/LLVMOptimizer.h
  Backend/LLVMOptimizer.cpp
  Backend/LLVMIRGenerator.h
  Backend/LLVMIRGenerator.cpp
)

set(COMPILER_FILES
  Compiler/Compiler.h
  Compiler/Compiler.cpp
)

set(TEST_FILES
	Test/test.wv
	Test/test.ll
)

add_executable(WaveCompiler main.cpp autogen/WaveConfig.h ${CORE_FILES} ${UTILITY_FILES} ${FRONTEND_FILES} ${BACKEND_FILES} ${COMPILER_FILES} ${TEST_FILES})

set_target_properties(WaveCompiler PROPERTIES OUTPUT_NAME Wave)

source_group(" " 		FILES main.cpp)
source_group("Core"     FILES ${CORE_FILES})
source_group("Utility"  FILES ${UTILITY_FILES})
source_group("Frontend" FILES ${FRONTEND_FILES})
source_group("Backend"  FILES ${BACKEND_FILES})
source_group("Compiler" FILES ${COMPILER_FILES})
source_group("Test" 	FILES ${TEST_FILES})

target_include_directories(WaveCompiler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(WaveCompiler PRIVATE ${CMAKE_SOURCE_DIR}/Libraries/spdlog/include)
target_include_directories(WaveCompiler PRIVATE ${CMAKE_SOURCE_DIR}/Libraries/CLI11/include)
target_include_directories(WaveCompiler PRIVATE ${LLVM_INCLUDE_DIRS})
target_compile_definitions(WaveCompiler PRIVATE ${LLVM_DEFINITIONS})

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

target_link_directories(WaveCompiler PRIVATE ${LLVM_LIBRARY_DIRS})
target_link_libraries(WaveCompiler PRIVATE ${LLVM_LIBRARIES})

target_link_directories(WaveCompiler PRIVATE ${CMAKE_SOURCE_DIR}/Libraries/spdlog/lib/Release/)
target_link_libraries(WaveCompiler PRIVATE spdlog)

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

target_compile_options(WaveCompiler PRIVATE ${DISABLED_WARNINGS})

if(MSVC)
    add_definitions(/FI"Core/CoreTypes.h" /FI"Core/Defines.h")
else()                                                   
    add_definitions(-include Core/CoreTypes.h -include Core/Defines.h)
endif()

install(TARGETS WaveCompiler DESTINATION bin)
