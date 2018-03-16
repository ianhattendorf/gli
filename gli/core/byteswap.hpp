#pragma once

#include <cstdlib>
#include <cstdint>

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
				auto swapped = static_cast<uint32_t>(x);
				swapped = ((swapped & 0xff000000) >> 24) | // 3 -> 0
						 ((swapped & 0x00ff0000) >>  8) | // 2 -> 1
						 ((swapped & 0x0000ff00) <<  8) | // 1 -> 2
						 ((swapped & 0x000000ff) << 24);  // 0 -> 3
				return static_cast<T>(swapped);
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
