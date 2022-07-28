#pragma once

#include <string>
#include <Windows.h>


#include "../sdk/netvar/manager.h"

namespace offsets
{
	inline constexpr const char* health = "m_iHealth";
	inline constexpr const char* position = "m_vecOrigin";
	inline constexpr const char* team = "m_iTeam";

	inline constexpr uintptr_t entitylist = 0x4DDB8FC;
	inline constexpr uintptr_t viewmatrix = 0x4DCD214;
}

namespace globals
{
	bool Initalize();

	inline CNetvars* net;
	inline uintptr_t client;
	inline uintptr_t engine;

	inline uintptr_t* player;
	inline uintptr_t* entitylist;
}

