#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

#pragma warning( push )
#pragma warning( disable : 6031 )

extern "C"
{
	typedef FILE* FileHandle;

	static const char* MODE_READ = "r";
	static const char* MODE_WRITE = "w";
	static const char* MODE_APPEND = "a";
	static const char* MODE_READ_WRITE = "r+";
	static const char* MODE_WRITE_READ = "w+";
	static const char* MODE_APPEND_READ = "a+";
	static const char* MODE_READ_BINARY = "rb";
	static const char* MODE_WRITE_BINARY = "wb";
	static const char* MODE_APPEND_BINARY = "ab";

	FileHandle FileOpen(char* filename, char* mode)
	{
		return fopen(filename, mode);
	}

	bool FileClose(FileHandle file)
	{
		if (file == NULL) return false;
		return fclose(file) == 0;
	}

	bool FileIsOpen(FileHandle file)
	{
		return file != NULL;
	}

	int64_t FileReadInt(FileHandle file)
	{
		if (file == NULL) return 0;
		int64_t value;
		fscanf(file, "%" SCNd64, &value);
		return value;
	}

	double FileReadFloat(FileHandle file)
	{
		if (file == NULL) return 0.0;
		double value;
		fscanf(file, "%lf", &value);
		return value;
	}

	char FileReadChar(FileHandle file)
	{
		if (file == NULL) return '\0';
		return (char)fgetc(file);
	}

	bool FileReadLine(FileHandle file, char* buffer, int64_t buffer_size)
	{
		if (file == NULL || buffer == NULL || buffer_size <= 0) return false;
		return fgets(buffer, (int)buffer_size, file) != NULL;
	}

	int64_t FileRead(FileHandle file, char* buffer, int64_t count)
	{
		if (file == NULL || buffer == NULL || count <= 0) return 0;
		return (int64_t)fread(buffer, 1, (size_t)count, file);
	}

	bool FileWriteInt(FileHandle file, int64_t value)
	{
		if (file == NULL) return false;
		return fprintf(file, "%" PRId64, value) >= 0;
	}

	bool FileWriteFloat(FileHandle file, double value)
	{
		if (file == NULL) return false;
		return fprintf(file, "%lf", value) >= 0;
	}

	bool FileWriteChar(FileHandle file, char ch)
	{
		if (file == NULL) return false;
		return fputc(ch, file) != EOF;
	}

	bool FileWriteString(FileHandle file, char* str)
	{
		if (file == NULL || str == NULL) return false;
		return fputs(str, file) >= 0;
	}

	bool FileWriteLine(FileHandle file, char* str)
	{
		if (file == NULL || str == NULL) return false;
		if (fputs(str, file) < 0) return false;
		return fputc('\n', file) != EOF;
	}

	int64_t FileWrite(FileHandle file, char* buffer, int64_t count)
	{
		if (file == NULL || buffer == NULL || count <= 0) return 0;
		return (int64_t)fwrite(buffer, 1, (size_t)count, file);
	}

	int64_t FileTell(FileHandle file)
	{
		if (file == NULL) return -1;
		return (int64_t)ftell(file);
	}

	bool FileSeek(FileHandle file, int64_t offset, int64_t origin)
	{
		if (file == NULL) return false;
		return fseek(file, (long)offset, (int)origin) == 0;
	}

	void FileRewind(FileHandle file)
	{
		if (file == NULL) return;
		rewind(file);
	}

	bool FileEOF(FileHandle file)
	{
		if (file == NULL) return true;
		return feof(file) != 0;
	}

	bool FileError(FileHandle file)
	{
		if (file == NULL) return true;
		return ferror(file) != 0;
	}

	void FileClearError(FileHandle file)
	{
		if (file == NULL) return;
		clearerr(file);
	}

	bool FileFlush(FileHandle file)
	{
		if (file == NULL) return false;
		return fflush(file) == 0;
	}

	bool FileExists(char* filename)
	{
		if (filename == NULL) return false;
		FILE* file = fopen(filename, "r");
		if (file != NULL)
		{
			fclose(file);
			return true;
		}
		return false;
	}

	bool FileDelete(char* filename)
	{
		if (filename == NULL) return false;
		return remove(filename) == 0;
	}

	bool FileRename(char* old_name, char* new_name)
	{
		if (old_name == NULL || new_name == NULL) return false;
		return rename(old_name, new_name) == 0;
	}

	int64_t FileSize(char* filename)
	{
		if (filename == NULL) return -1;
		FILE* file = fopen(filename, "rb");
		if (file == NULL) return -1;

		fseek(file, 0, SEEK_END);
		int64_t size = (int64_t)ftell(file);
		fclose(file);

		return size;
	}

	static const int64_t SEEK_SET_VALUE = SEEK_SET;
	static const int64_t SEEK_CUR_VALUE = SEEK_CUR;
	static const int64_t SEEK_END_VALUE = SEEK_END;
}

#pragma warning( pop )