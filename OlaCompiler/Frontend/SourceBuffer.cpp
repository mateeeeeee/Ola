#include "SourceBuffer.h"
#include <fstream>
#include <sstream>

namespace ola
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

	SourceBuffer::SourceBuffer(Char const* buffer_start, Uint64 buffer_size, std::string_view refname)
		: data_buffer(buffer_start, buffer_size), ref_name(refname)
	{}

	void SourceBuffer::Prepend(Char const* str)
	{
		data_buffer = str + data_buffer;
	}

}

