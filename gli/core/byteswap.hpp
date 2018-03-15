#pragma once

#include <cstdlib>
#include <cstdint>

#ifdef __linux__
#include <byteswap.h>
#endif

namespace gli{
	namespace detail
	{
		template <typename T, size_t n>
		struct ByteswapImpl;

		template <typename T>
		struct ByteswapImpl<T, 4>
		{
			T operator()(T const& x) const
			{
				auto x_cast = static_cast<uint32_t>(x);
#ifdef __linux__
				x_cast = bswap_32(x_cast);
#else
				x_cast = ((x_cast & 0xff000000) >> 24) | // 3 -> 0
						 ((x_cast & 0x00ff0000) >>  8) | // 2 -> 1
						 ((x_cast & 0x0000ff00) <<  8) | // 1 -> 2
						 ((x_cast & 0x000000ff) << 24);  // 0 -> 3
#endif
				return static_cast<T>(x_cast);
			}
		};

		template <typename T>
		T byteswap(T const& x)
		{
			return ByteswapImpl<T, sizeof(T)>()(x);
		}

		bool is_big_endian()
		{
			uint32_t const num = 0x1;
			return *reinterpret_cast<uint8_t const *>(&num) != 0x1;
		}

	}//namespace detail
}//namespace gli
