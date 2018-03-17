#pragma once

#include <cstdlib>
#include <cstdint>
#include <type_traits>
#include <algorithm>

namespace gli{
	/**
	 * Swap bytes of trivial object
	 * @tparam T Type of object
	 * @param x Object to swap bytes
	 * @return Reversed object
	 *
	 * Note: This can be constexpr in C++14 and later.
	 */
	template <typename T>
	T byteswap(T x)
	{
		static_assert(std::is_trivial<T>::value, "T must be trivial");

		char *begin = reinterpret_cast<char *>(&x);
		char *end = begin + sizeof(T);
		std::reverse(begin, end);

		return x;
	}

	/**
	 * Swap bytes of uint16_t
	 * @param x uint16_t to swap
	 * @return Swapped uint16_t
	 */
	template <>
	constexpr uint16_t byteswap(uint16_t const x)
	{
		return static_cast<uint16_t>(
				((x >> 8) & 0x00ff) |
				((x & 0x00ff) << 8)
		);
	}

	/**
	 * Swap bytes of uint32_t
	 * @param x uint32_t to swap
	 * @return Swapped uint32_t
	 */
	template <>
	constexpr uint32_t byteswap(uint32_t const x)
	{
		return ((x & 0xff000000) >> 24) | // 3 -> 0
			   ((x & 0x00ff0000) >> 8) |  // 2 -> 1
			   ((x & 0x0000ff00) << 8) |  // 1 -> 2
			   ((x & 0x000000ff) << 24);  // 0 -> 3
	}

	/**
	 * Swap bytes of uint64_t
	 * @param x uint64_t to swap
	 * @return Swapped uint64_t
	 */
	template <>
	constexpr uint64_t byteswap(uint64_t const x)
	{
		return ((x & 0xff00000000000000) >> 56) | // 7 -> 0
			   ((x & 0x00ff000000000000) >> 40) | // 6 -> 1
			   ((x & 0x0000ff0000000000) >> 24) | // 5 -> 2
			   ((x & 0x000000ff00000000) >>  8) | // 4 -> 3
			   ((x & 0x00000000ff000000) <<  8) | // 3 -> 4
			   ((x & 0x0000000000ff0000) << 24) | // 2 -> 5
			   ((x & 0x000000000000ff00) << 40) | // 1 -> 6
			   ((x & 0x00000000000000ff) << 56);  // 0 -> 7
	}

	/**
	 * Check if platform is big endian.
	 *
	 * The check is performed during runtime,
	 * might want to find a way to do this during compile time.
	 * @return True if platform is big endian, false otherwise
	 *
	 * Note: This can be constexpr in C++14 and later.
	 */
	bool is_big_endian()
	{
		uint32_t const num = 0x1;
		return *reinterpret_cast<uint8_t const *>(&num) != 0x1;
	}

}//namespace gli
