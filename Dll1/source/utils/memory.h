#pragma once

#include <vector>
#include <Windows.h>

class PatchInfo
{
public:
	size_t m_size;
	BYTE* m_address;
	BYTE* m_original{ nullptr };

public:
	PatchInfo(size_t size, BYTE* address);
};

namespace memory
{
	bool Patch(BYTE* src, BYTE* dst, size_t size, bool save = false);
	bool Detour(BYTE* src, BYTE* dst, size_t size, bool save = false);
	BYTE* Tramphook(BYTE* src, BYTE* dst, size_t size, bool save = false);

	inline std::vector<PatchInfo> patches;
}
