#include <list>
#include <unordered_map>
#include "GlobalAttributeInferPass.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{
	Bool GlobalAttributeInferPass::RunOn(IRModule& Module, IRModuleAnalysisManager& MAM)
	{
		std::list<GlobalVariable*> Worklist;
		for (GlobalValue* G : Module.Globals())
		{
			if (GlobalVariable* GV = dyn_cast<GlobalVariable>(G))
			{
				if (!GV->IsReadOnly() && GV->GetLinkage() == Linkage::Internal)
				{
					Worklist.push_back(GV);
				}
			}
		}

		if (Worklist.empty())
		{
			return false;
		}

		for (GlobalValue* G : Module.Globals())
		{
			if (Function* F = dyn_cast<Function>(G))
			{
				std::unordered_map<Value*, GlobalVariable*> AddressHolder;
				for (GlobalValue* GV : Module.Globals())
				{
					if (GlobalVariable* GVar = dyn_cast<GlobalVariable>(GV))
					{
						AddressHolder[GVar] = GVar;
					}
				}

				// Pass 1: Find direct stores to globals
				for (BasicBlock& BB : *F)
				{
					for (Instruction const& I : BB)
					{
						if (StoreInst const* SI = dyn_cast<StoreInst>(&I))
						{
							Value* AddressOp = SI->GetAddressOp();
							if (GlobalVariable* GV = dyn_cast<GlobalVariable>(AddressOp))
							{
								Worklist.remove_if([&](GlobalVariable* GV2) { return GV2 == GV; });
							}
						}
					}
				}

				Bool changed = true;
				while (changed)
				{
					changed = false;
					for (BasicBlock& BB : *F)
					{
						for (Instruction& I : BB)
						{
							if (LoadInst* LI = dyn_cast<LoadInst>(&I))
							{
								Value* LoadAddr = LI->GetAddressOp();
								if (LI->GetType()->IsPointer())
								{
									for (BasicBlock& BB2 : *F)
									{
										for (Instruction& I2 : BB2)
										{
											if (StoreInst* SI = dyn_cast<StoreInst>(&I2))
											{
												if (SI->GetAddressOp() == LoadAddr)
												{
													Value* StoredValue = SI->GetValueOp();
													if (auto it = AddressHolder.find(StoredValue); it != AddressHolder.end())
													{
														if (AddressHolder.find(LI) == AddressHolder.end())
														{
															AddressHolder[LI] = it->second;
															changed = true;
														}
													}
												}
											}
										}
									}
								}
							}
							else if (StoreInst* SI = dyn_cast<StoreInst>(&I))
							{
								Value* StoreAddr = SI->GetAddressOp();
								if (auto it = AddressHolder.find(StoreAddr); it != AddressHolder.end())
								{
									Worklist.remove_if([&](GlobalVariable* GV2) { return GV2 == it->second; });
								}
							}
						}
					}
				}
			}
		}

		for (GlobalVariable* GV : Worklist)
		{
			GV->SetReadOnly();
		}
		return !Worklist.empty();
	}
}

