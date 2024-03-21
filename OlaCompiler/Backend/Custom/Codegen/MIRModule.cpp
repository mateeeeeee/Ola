#include "MIRModule.h"
#include "MIRGlobal.h"
#include "Backend/Custom/IR/IRModule.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{

	MIRModule::MIRModule(IRModule& ir_module) 
	{
		LowerModule(ir_module);
	}

	void MIRModule::Print(std::ofstream& of)
	{

	}

	void MIRModule::LowerModule(IRModule& ir_module)
	{
		auto const& ir_globals = ir_module.Globals();

		std::unordered_map<GlobalValue*, MIRGlobal*> global_map;
		for (GlobalValue* GV : ir_globals)
		{
			if (GV->IsFunction())
			{
				Function* F = cast<Function>(GV);
				globals.emplace_back(new MIRFunction(F->GetName()), F->GetLinkage());
			}
			else
			{
				GlobalVariable* V = cast<GlobalVariable>(GV);
				IRType* type = V->GetValueType();
				uint32 size = type->GetSize();
				uint32 alignment = type->GetAlign();

				if (Value* init_value = V->GetInitValue())
				{
					OLA_ASSERT(isa<Constant>(init_value));
					Constant* C = cast<Constant>(init_value);

					bool const read_only = V->IsReadOnly();
					MIRDataStorage* data = new MIRDataStorage(V->GetName(), read_only);

					auto ExpandValue = [&](auto&& self, Value* V) -> void
						{
							if (ConstantInt* CI = dyn_cast<ConstantInt>(C))
							{
								int64 value = CI->GetValue();
								switch (CI->GetBitWidth())
								{
								case 1:
								{
									data->AppendByte((uint8)value);
									break;
								}
								case 8:
								{
									data->AppendQWord((uint64)value);
									break;
								}
								}
							}
							else if (ConstantFloat* CF = dyn_cast<ConstantFloat>(C))
							{
								double value = CF->GetValue();
								void* value_ptr = static_cast<void*>(&value);
								data->AppendQWord(*static_cast<uint64*>(value_ptr));
							}
							else if (ConstantArray* CA = dyn_cast<ConstantArray>(C))
							{
								IRArrayType const* array_type = CA->GetArrayType();
								auto const& values = CA->Values();
								for (auto sub : values) self(self, sub);

								uint32 const remaining_count = array_type->GetArraySize() - values.size();
								if (remaining_count) 
								{
									const auto rem_size = array_type->GetBaseType()->GetSize() * remaining_count;
									for (uint32 i = 0; i < remaining_count; ++i)
									{
										data->AppendByte(0);
									}
								}
							}
							else OLA_ASSERT(false);
						};
					ExpandValue(ExpandValue, init_value);

					globals.emplace_back(data, V->GetLinkage(), alignment);
				}
				else
				{
					globals.emplace_back(new MIRZeroStorage(V->GetName(), size), V->GetLinkage(), alignment);
				}
			}

			global_map[GV] = &globals.back();
		}

		for (GlobalValue* GV : ir_globals)
		{
			if (GV->IsFunction())
			{
				Function* F = cast<Function>(GV);
				MIRGlobal* mir_global = global_map[GV];
				MIRFunction* MF = dynamic_cast<MIRFunction*>(mir_global->GetRelocable());
				LowerFunction(F, MF, global_map);
			}
		}
	}

	void MIRModule::LowerFunction(Function*, MIRFunction*, std::unordered_map<GlobalValue*, MIRGlobal*>&)
	{
		std::unordered_map<BasicBlock*, MIRBasicBlock*> block_map;
		std::unordered_map<Value*, MIROperand> value_map;
		std::unordered_map<Value*, MIROperand> storage_map;
	}

}