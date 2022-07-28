#pragma once
#include <cstring>
#include <cstdint>

// credit to unknowncheats/cazz, no clue what this does but it fucking hashes
namespace fnv
{
	inline constexpr std::uint32_t base = 0x811C9DC5;
	inline constexpr std::uint32_t prime = 0x1000193;

	constexpr std::uint32_t cphash(const char* data, const std::uint32_t value = base)
	{
		return (data[0] == '\0') ? value : cphash(&data[1], (value ^ std::uint32_t(data[0])) * prime);
	}

	inline std::uint32_t hash(const char* data)
	{
		std::uint32_t hashed = base;
		for (size_t i = 0U; i < strlen(data); ++i)
		{
			hashed ^= data[i];
			hashed *= prime;
		}

		return hashed;
	}
}