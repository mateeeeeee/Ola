#pragma once
#include <iosfwd>
#include <format>
#include <string>
#include <map>

namespace ola
{
	using SectionId = Uint32;
	class MachineModule;

	class AsmPrinter
	{
	public:
		explicit AsmPrinter(std::ostream& os) : os(os) {}
		~AsmPrinter() = default;
		virtual void PrintModule(MachineModule const& M) = 0;

	protected:
		std::ostream& os;
		std::map<SectionId, std::string> section_map;

	protected:
		virtual std::string GetSectionLabel(SectionId) const = 0;

		template<SectionId Section, typename... Args>
		void Emit(Char const* fmt, Args&&... args)
		{
			std::string output = std::vformat(fmt, std::make_format_args(args...));
			output += "\n";
			section_map[Section] += output;
		}
		void Finalize();
	};
}