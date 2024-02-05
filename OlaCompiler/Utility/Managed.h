#pragma once
#include <vector>

namespace ola
{
	template<typename T>
	class Managed;

	class ManagedRegistry
	{
		template<typename T>
		friend class Managed;
		using CleanupFn = void(*)();
	public:
		static void Register(CleanupFn cleanup_fn)
		{
			cleanup_functions.push_back(cleanup_fn);
		}
		static void Cleanup() 
		{
			for (CleanupFn cleanup_fn : cleanup_functions) cleanup_fn();
		}
	private:
		inline static std::vector<CleanupFn> cleanup_functions = {};
	};

	template<typename T>
	class Managed
	{
	public:

		template<typename... Args> requires std::is_constructible_v<T, Args...>
		static T* Create(Args&&... args)
		{
			managed_objects.push_back(new T(std::forward<Args>(args)...));
			return managed_objects.back();
		}

		static void Destroy()
		{
			for (T* obj : managed_objects) delete obj;
			managed_objects.clear();
		}

	private:
		inline static std::vector<T*> managed_objects = {};

	private:
		void* operator new(uint64 size)
		{
			return ::operator new(size);
		}
	};

#define REGISTER_CLEANUP_FOR(T) \
    namespace  \
	{ \
        struct T##Cleanup \
		{ \
            T##Cleanup() \
			{ \
                ManagedRegistry::Register(Managed<T>::Destroy); \
            } \
        } T##CleanupInstance; \
    }
}