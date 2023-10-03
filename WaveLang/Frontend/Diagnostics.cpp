#include <unordered_map>
#include <string>
#include "Diagnostics.h"
#include "SourceLocation.h"

namespace wave::diag
{
	namespace
	{
		enum class DiagKind : uint32
		{
			info,
			warning,
			error
		};
		std::string ToString(DiagKind c)
		{
			switch (c)
			{
			case DiagKind::error: return "Error";
			case DiagKind::warning: return "Warning";
			case DiagKind::info: return "Info";
			}
			return "";
		}

		std::unordered_map<DiagCode, std::string_view> diag_msgs =
		{
			#define DIAG(diag_code, diag_class, diag_msg) {DiagCode::##diag_code, diag_msg},
			#include "Diagnostics.def"
		};
		std::unordered_map<DiagCode, DiagKind> diag_kinds =
		{
			#define DIAG(diag_code, diag_class, diag_msg) {DiagCode::##diag_code, DiagKind::##diag_class},
			#include "Diagnostics.def"
		};
	}

	void Initialize()
	{

	}

	void Report(SourceLocation const& loc, DiagCode code)
	{

	}

}

