#pragma once
#include <memory>
#include "MachineRelocable.h"
#include "Backend/Custom/IR/GlobalValue.h"

namespace ola
{

	class MachineGlobal 
	{
	public:
		MachineGlobal(MachineRelocable* relocable, Linkage linkage, uint32 alignment = 0)
			: relocable(relocable), linkage(linkage), alignment(alignment) {}

		Linkage GetLinkage() const { return linkage; }
		uint32  GetAlignment() const { return alignment; }
		MachineRelocable* GetRelocable() const { return relocable.get(); }

	private:
		std::unique_ptr<MachineRelocable> relocable;
		Linkage linkage;
		uint32 alignment;
	};
}