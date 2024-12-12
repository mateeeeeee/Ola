#include "LLVMIRPassManager.h"
#include "LLVMUtils.h"
#include "Passes/TestPass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/IPO.h"
#include "llvm/Transforms/Utils/Mem2Reg.h"
#include "llvm/Transforms/Scalar/InstSimplifyPass.h"       
#include "llvm/Transforms/Scalar/SimplifyCFG.h"            
#include "llvm/Transforms/Scalar/DCE.h"                    
#include "llvm/Transforms/Scalar/Reassociate.h"            
#include "llvm/Transforms/Scalar/SROA.h"                   
#include "llvm/Transforms/Scalar/ADCE.h"    
#include "llvm/Analysis/DominanceFrontier.h"

namespace ola
{
	LLVMIRPassManager::LLVMIRPassManager(llvm::Module& module) : module(module) {}

	void LLVMIRPassManager::Run(OptimizationLevel level, LLVMIRPassOptions const& opts)
	{
		llvm::PassBuilder PB;

		llvm::LoopAnalysisManager LAM;
		llvm::FunctionAnalysisManager FAM;
		llvm::CGSCCAnalysisManager CGAM;
		llvm::ModuleAnalysisManager MAM;

		PB.registerModuleAnalyses(MAM);
		PB.registerCGSCCAnalyses(CGAM);
		PB.registerFunctionAnalyses(FAM);
		PB.registerLoopAnalyses(LAM);
		PB.crossRegisterProxies(LAM, FAM, CGAM, MAM);

		llvm::ModulePassManager MPM;
		llvm::FunctionPassManager FPM;
		switch (level)
		{
		case OptimizationLevel::O3:
			MPM.addPass(PB.buildPerModuleDefaultPipeline(llvm::OptimizationLevel::O3));
			break;
		case OptimizationLevel::O2:
			MPM.addPass(PB.buildPerModuleDefaultPipeline(llvm::OptimizationLevel::O2));
			break;
		case OptimizationLevel::O1:
			FPM.addPass(llvm::PromotePass());
			FPM.addPass(llvm::InstSimplifyPass());
			FPM.addPass(llvm::SimplifyCFGPass());           
			FPM.addPass(llvm::DCEPass());                   
			FPM.addPass(llvm::ReassociatePass());           
			FPM.addPass(llvm::SROAPass(llvm::SROAOptions::PreserveCFG));                  
			FPM.addPass(llvm::ADCEPass());          
			break;
		case OptimizationLevel::O0:
		default:
			break;
		}
		if(opts.domfrontier_print) FPM.addPass(llvm::DominanceFrontierPrinterPass(llvm::errs()));

		MPM.addPass(llvm::createModuleToFunctionPassAdaptor(std::move(FPM)));
		MPM.run(module, MAM);
		if (!VerifyLLVMModule(module))
		{
			llvm::errs() << "LLVM Module verification failed!\n";
		}
	}
}