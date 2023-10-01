#include "SourceBuffer.h"
#include <fstream>
#include <sstream>

namespace wave
{
	SourceBuffer::SourceBuffer(std::string_view source_file)
		: ref_name(source_file)
	{
		std::string path(source_file);
		std::ifstream input_stream(path);
		auto good = input_stream.good();
		std::ostringstream buf;
		buf << input_stream.rdbuf();
		data_buffer = buf.str();
		data_buffer.push_back('\0');
	}

	SourceBuffer::SourceBuffer(char const* buffer_start, size_t buffer_size, std::string_view refname)
		: ref_name(refname), data_buffer(buffer_start, buffer_size)
	{}

	void SourceBuffer::Prepend(char const* str)
	{
		data_buffer = str + data_buffer;
	}

}

