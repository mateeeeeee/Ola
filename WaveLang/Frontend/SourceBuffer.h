#pragma once
#include <string>

namespace wave
{
	class SourceBuffer
	{
	public:
		explicit SourceBuffer(std::string_view source_file);
		SourceBuffer(char const* buffer_start, size_t buffer_size, std::string_view refname = "");

		SourceBuffer(SourceBuffer const&) = delete;
		SourceBuffer(SourceBuffer&&) = default;
		SourceBuffer& operator=(SourceBuffer const&) = delete;
		SourceBuffer& operator=(SourceBuffer&&) = default;
		~SourceBuffer() = default;

		void Prepend(char const* str);

		char const* GetBufferStart() const { return data_buffer.c_str(); }
		char const* GetBufferEnd() const { return GetBufferStart() + data_buffer.size(); }
		size_t		GetBufferSize() const { return data_buffer.size(); }
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