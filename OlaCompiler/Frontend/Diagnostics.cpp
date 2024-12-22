#include <string_view>
#include "Diagnostics.h"
#include "Core/Log.h"

namespace ola
{
	std::unordered_map<DiagCode, std::string_view> Diagnostics::diag_msgs =
	{
		#define DIAG(diag_code, diag_kind, diag_msg) {DiagCode::diag_code, diag_msg},
		#include "Diagnostics.def"
	};
	std::unordered_map<DiagCode, Diagnostics::DiagKind> Diagnostics::diag_kinds =
	{
		#define DIAG(diag_code, diag_kind, diag_msg) {DiagCode::diag_code, DiagKind::diag_kind},
		#include "Diagnostics.def"
	};

	std::string Diagnostics::ToString(DiagKind c)
	{
		switch (c)
		{
		case DiagKind::error: return "Error";
		case DiagKind::warning: return "Warning";
		case DiagKind::info: return "Info";
		}
		return "";
	}

	void Diagnostics::PrintMessage(DiagKind diag_kind, std::string const& msg)
	{
		switch (diag_kind)
		{
		case DiagKind::info:
			OLA_INFO("{}", msg);
			break;
		case DiagKind::warning:
			OLA_WARN("{}", msg);
			break;
		case DiagKind::error:
			OLA_ERROR("{}", msg);
			break;
		}
	}

	Diagnostics::Diagnostics(Bool _warnings_as_errors, Bool _exit_on_error)
	{
		warnings_as_errors = _warnings_as_errors;
		exit_on_error = _exit_on_error;
	}

	void Diagnostics::SetDefaultLocation(SourceLocation const& _loc)
	{
		loc = _loc;
	}
	void Diagnostics::Report(DiagCode code)
	{
		Report(loc, code);
	}
	void Diagnostics::Report(SourceLocation const& loc, DiagCode code)
	{
		DiagKind diag_kind = diag_kinds[code];
		std::string output = std::format("[Diagnostics][{}]: {} in file {} at line: {}, col: {}\n",
			ToString(diag_kind), diag_msgs[code], loc.filename, loc.line, loc.column);
		PrintMessage(diag_kind, output);
		if (exit_on_error && diag_kind == DiagKind::error) 
			std::exit(OLA_INVALID_SOURCE_CODE);
	}
}
