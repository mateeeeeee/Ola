#include <ostream>
#include "AsmPrinter.h"

namespace ola
{

	void AsmPrinter::Finalize()
	{
		for (auto const& [section, buffer] : section_map)
		{
			std::string section_label = GetSectionLabel(section);
			if (!section_label.empty()) os << section_label << "\n";
			os << buffer;
		}
	}

}

