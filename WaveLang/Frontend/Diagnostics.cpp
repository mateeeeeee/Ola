#include <string_view>
#include <iostream>
#include <format>
#include "Diagnostics.h"
#include "SourceLocation.h"
#include "Core/Logger.h"

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
			#define DIAG(diag_code, diag_kind, diag_msg) {DiagCode::##diag_code, diag_msg},
			#include "Diagnostics.def"
		};
		std::unordered_map<DiagCode, DiagKind> diag_kinds =
		{
			#define DIAG(diag_code, diag_kind, diag_msg) {DiagCode::##diag_code, DiagKind::##diag_kind},
			#include "Diagnostics.def"
		};

		bool warnings_as_errors = false;
		bool exit_on_error = false;
		SourceLocation loc;
		bool error_reported = false;
	}

	void Initialize(bool _warnings_as_errors, bool _exit_on_error)
	{
		warnings_as_errors = _warnings_as_errors;
		exit_on_error = _exit_on_error;
	}

	void Report(DiagCode code, SourceLocation const& loc)
	{
		DiagKind diag_kind = diag_kinds[code];
		std::string output = std::format("[Diagnostics][{}]: {} in file {} at line: {}, col: {}\n",
										 ToString(diag_kind), diag_msgs[code], loc.filename, loc.line, loc.column);
		
		switch (diag_kind)
		{
		case DiagKind::info:
			LU_INFO(output);
			break;
		case DiagKind::warning:
			LU_WARN(output);
			break;
		case DiagKind::error:
			LU_ERROR(output);
			break;
		}
		if (exit_on_error && diag_kind == DiagKind::error) std::exit(EXIT_CODE_COMPILATION_FAILED);
	}

	void Report(DiagCode code)
	{
		Report(code, loc);
	}

	void SetLocation(SourceLocation const& _loc)
	{
		loc = _loc;
	}

}

