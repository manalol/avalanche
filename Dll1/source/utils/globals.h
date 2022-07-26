#pragma once
#include <Windows.h>


#include "../sdk/netvar/manager.h"

class CEntity;
namespace globals
{
	bool Initalize();

	inline CNetvars* net;
	static uintptr_t client;
	static uintptr_t engine;

	inline CEntity* player;
	inline IClientEntityList* entitylist;
}

