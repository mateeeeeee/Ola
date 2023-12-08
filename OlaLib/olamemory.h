#include <malloc.h>
#include <stdint.h>

extern "C"
{
	int64_t* AllocateInts(int64_t count)
	{
		return (int64_t*)malloc(sizeof(int64_t) * count);
	}
	void FreeInts(int64_t* arr)
	{
		free(arr);
	}

	double* AllocateFloats(int64_t count)
	{
		return (double*)malloc(sizeof(double) * count);
	}
	void FreeFloats(double* arr)
	{
		free(arr);
	}

	char* AllocateChars(int64_t count)
	{
		return (char*)malloc(sizeof(char) * count);
	}
	void FreeChars(char* arr)
	{
		free(arr);
	}

	bool* AllocateBools(int64_t count)
	{
		return (bool*)malloc(sizeof(bool) * count);
	}
	void FreeBools(bool* arr)
	{
		free(arr);
	}
}