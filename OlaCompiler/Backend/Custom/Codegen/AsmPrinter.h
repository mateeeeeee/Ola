#pragma once
#include <fstream>
#include <format>
#include <string>
#include <map>

namespace ola
{
	using SectionId = uint32;
	class AsmPrinter
	{
	public:
		explicit AsmPrinter(char const* asm_file) : asm_stream(asm_file) {}
		~AsmPrinter() = default;

		void Finalize()
		{
			for (auto const& [section, buffer] : section_map)
			{
				std::string section_label = GetSectionLabel(section);
				if (!section_label.empty()) asm_stream << section_label << "\n";
				asm_stream << buffer;
			}
			asm_stream.close();
		}
		virtual std::string GetSectionLabel(SectionId) const = 0;

	protected:
		std::ofstream asm_stream;
		std::map<SectionId, std::string> section_map;

	protected:
		template<SectionId Section, typename... Args>
		void Emit(char const* fmt, Args&&... args)
		{
			std::string output = std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
			output += "\n";
			section_map[Section] += output;
		}
	};
}