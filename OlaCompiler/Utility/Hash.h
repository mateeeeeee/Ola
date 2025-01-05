#pragma once
#include <functional>

namespace ola
{
	class HashState
	{
	public:
		HashState() : value(0) {}

		void Combine(Uint64 hash)
		{
			value ^= hash + 0x9e3779b9 + (value << 6) + (value >> 2);
		}

		template<typename T>
		void Combine(T const& v)
		{
			Combine(std::hash<T>{}(v));
		}

		operator Uint64() const
		{
			return value;
		}

	private:
		Uint64 value;
	};

	namespace crc
	{
		//https://stackoverflow.com/questions/28675727/using-crc32-algorithm-to-hash-string-at-compile-time 
		template <Uint64 c, Uint32 k = 8>
		struct CrcInternal : CrcInternal<((c & 1) ? 0xd800000000000000L : 0) ^ (c >> 1), k - 1>
		{};

		template <Uint64 c> struct CrcInternal<c, 0>
		{
			static constexpr Uint64 value = c;
		};

		template<Uint64 c>
		constexpr Uint64 CrcInternalValue = CrcInternal<c>::value;

#define CRC64_TABLE_0(x) CRC64_TABLE_1(x) CRC64_TABLE_1(x + 128)
#define CRC64_TABLE_1(x) CRC64_TABLE_2(x) CRC64_TABLE_2(x +  64)
#define CRC64_TABLE_2(x) CRC64_TABLE_3(x) CRC64_TABLE_3(x +  32)
#define CRC64_TABLE_3(x) CRC64_TABLE_4(x) CRC64_TABLE_4(x +  16)
#define CRC64_TABLE_4(x) CRC64_TABLE_5(x) CRC64_TABLE_5(x +   8)
#define CRC64_TABLE_5(x) CRC64_TABLE_6(x) CRC64_TABLE_6(x +   4)
#define CRC64_TABLE_6(x) CRC64_TABLE_7(x) CRC64_TABLE_7(x +   2)
#define CRC64_TABLE_7(x) CRC64_TABLE_8(x) CRC64_TABLE_8(x +   1)
#define CRC64_TABLE_8(x) CrcInternalValue<x>,

		static constexpr Uint64 CRC_TABLE[] = { CRC64_TABLE_0(0) };

		constexpr Uint64 crc64_impl(const Char* str, Uint64 N)
		{
			Uint64 val = 0xFFFFFFFFFFFFFFFFL;
			for (Uint64 idx = 0; idx < N; ++idx)
			{
				val = (val >> 8) ^ CRC_TABLE[(val ^ str[idx]) & 0xFF];
			}

			return val;
		}
	}

	template<Uint64 N>
	consteval Uint64 crc64(Char const (&_str)[N])
	{
		return crc::crc64_impl(_str, N - 1);
	}

	inline Uint64 crc64(Char const* _str, Uint64 N)
	{
		return crc::crc64_impl(_str, N);
	}
}