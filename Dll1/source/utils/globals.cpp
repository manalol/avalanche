#include "globals.h"

#include "../sdk/centity.h"

// Initalizes all global variables
bool globals::Initalize()
{
	client = reinterpret_cast<uintptr_t>(GetModuleHandle(L"client.dll"));
	if (!client)
		return false;

	engine = reinterpret_cast<uintptr_t>(GetModuleHandle(L"engine.dll"));
	if (!engine)
		return false;

	globals::entitylist = interfaces::GetInterface<IClientEntityList>(L"client.dll", "VClientEntityList003");

	globals::player = reinterpret_cast<CEntity*>(entitylist->GetClientEntity(0));
	globals::net = new CNetvars;

	globals::net->Dump();
	return true;
}
