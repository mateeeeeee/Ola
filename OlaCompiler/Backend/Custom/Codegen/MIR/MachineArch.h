#pragma once
#include <string>

namespace ola
{
	enum class MachineArch
	{
		x86,
		x64,
		Unknown
	};
	enum ByteSize
	{
		ByteSize_1,
		ByteSize_2,
		ByteSize_4,
		ByteSize_8
	};

	enum class MachineSegment : uint16
	{
		None,
		BSS,
		Const,
		Data,
		Text
	};

	struct MachineResult
	{
		std::string no_segment;
		std::string bss_segment;
		std::string rodata_segment;
		std::string data_segment;
		std::string text_segment;
	};
}