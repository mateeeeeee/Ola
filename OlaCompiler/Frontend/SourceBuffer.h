#pragma once
#include <string>

namespace ola
{
	class SourceBuffer
	{
	public:

		explicit SourceBuffer(std::string_view source_file);
		SourceBuffer(Char const* buffer_start, Uint64 buffer_size, std::string_view refname = "");
		OLA_NONCOPYABLE(SourceBuffer)
		OLA_DEFAULT_MOVABLE(SourceBuffer)
		~SourceBuffer() = default;

		void Prepend(Char const* str);

		Char const* GetBufferStart() const { return data_buffer.c_str(); }
		Char const* GetBufferEnd() const { return GetBufferStart() + data_buffer.size(); }
		Uint64		GetBufferSize() const {	return data_buffer.size(); }
		std::string_view GetBuffer() const
		{
			return std::string_view{ data_buffer };
		}
		std::string_view GetRefName() const
		{
			return ref_name;
		}

	private:
		std::string data_buffer;
		std::string ref_name;
	};
}