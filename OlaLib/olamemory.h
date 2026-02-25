#include <stdlib.h>
#include <string.h>

extern "C"
{
	void* __ola_alloc(long long size)
	{
		void* ptr = malloc((size_t)size);
		if (ptr) memset(ptr, 0, (size_t)size);
		return ptr;
	}
	void __ola_free(void* ptr)
	{
		free(ptr);
	}
}
