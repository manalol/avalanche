#include "memory.h"

bool memory::Patch(BYTE* src, BYTE* dst, size_t size, bool save)
{
    DWORD old;
    VirtualProtect(src, size, PAGE_EXECUTE_READWRITE, &old);

    if (save)
        patches.push_back(PatchInfo(size, dst));
 
    memcpy(src, dst, size);

    VirtualProtect(src, size, old, &old);
    return true;
}

bool memory::Detour(BYTE* src, BYTE* dst, size_t size, bool save)
{
    if (size < 5)
        return false; // Too short for a near jmp

    DWORD old;
    VirtualProtect(src, size, PAGE_EXECUTE_READWRITE, &old);

    if (save)
        memory::patches.push_back(PatchInfo(size, src));

    memset(src, 0x90, size);
    *static_cast<BYTE*>(src) = 0xE9;
    *reinterpret_cast<uintptr_t*>(src + 1) = dst - src - 5;

    VirtualProtect(src, size, old, &old);
    return true;
}

// Allocates room for our stolen bytes to be executed and returns the function address
BYTE* memory::Tramphook(BYTE* src, BYTE* dst, size_t size, bool save)
{
    if (size < 5)
        return nullptr; // Detour function will fail

    BYTE* gateway = reinterpret_cast<BYTE*>(VirtualAlloc(0x0, size + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE)); // 5 extra bytes for our jump instr at the end
    if (!gateway)
        return nullptr;

    DWORD old;
    VirtualProtect(src, size, PAGE_EXECUTE_READWRITE, &old);

    // Copy our bytes from source destination to our gateway, then have the source detour to the gateway
    memcpy(gateway, src, size); 

    *(gateway + size) = 0xE9;
    *reinterpret_cast<uintptr_t*>(gateway + size + 1) = src - gateway - 5;

    Detour(src, dst, size, save);
    return gateway;
}

PatchInfo::PatchInfo(size_t size, BYTE* address) : m_size{ size }, m_address{ address }
{
    m_original = new BYTE[m_size];
    memcpy(m_original, address, size); // Will fail if we dont have memory access or some shit
}