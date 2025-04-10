#pragma once
#include <unordered_map>
#include <format>
#include "Compiler/CompilerMacros.h"
#include "SourceLocation.h"


namespace ola
{
	enum DiagCode : Uint32
	{
		#define DIAG(diag_code, diag_kind, diag_msg) diag_code,
		#include "Diagnostics.def"
	};

	class Diagnostics
	{
		enum class DiagKind : Uint32
		{
			info,
			warning,
			error
		};
		static std::unordered_map<DiagCode, std::string_view> diag_msgs;
		static std::unordered_map<DiagCode, DiagKind> diag_kinds;
		static std::string ToString(DiagKind c);
		static void PrintMessage(DiagKind diag_kind, std::string const& msg);

	public:
		explicit Diagnostics(Bool warnings_as_errors = false, Bool exit_on_error = true);

		void SetDefaultLocation(SourceLocation const& loc);
		void Report(DiagCode code);
		void Report(SourceLocation const& loc, DiagCode code);
		template<typename... Args>
		void Report(SourceLocation const& loc, DiagCode code, Args&&... args)
		{
			DiagKind diag_kind = diag_kinds[code];
			std::string_view fmt = diag_msgs[code];
			std::string diag_msg = std::vformat(fmt, std::make_format_args(args...));
			std::string output = std::format("[Diagnostics][{}]: {} in file {} at line: {}, col: {}\n",
											  ToString(diag_kind), diag_msg, loc.filename, loc.line, loc.column);
			output += "\n";

			PrintMessage(diag_kind, output);
			if (exit_on_error && diag_kind == DiagKind::error) std::exit(OLA_INVALID_SOURCE_CODE);
		}

	private:
		Bool warnings_as_errors = false;
		Bool exit_on_error = false;
		SourceLocation loc;
		Bool error_reported = false;
	};
}