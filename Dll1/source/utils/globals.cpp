#include "globals.h"



// Initalizes all global variables
bool globals::Initalize()
{
	client = reinterpret_cast<uintptr_t>(GetModuleHandle(L"client.dll"));
	if (!client)
		return false;

	engine = reinterpret_cast<uintptr_t>(GetModuleHandle(L"engine.dll"));
	if (!engine)
		return false;

	interfaces::entitylist = interfaces::GetInterface<EntityListInterface>(L"client.dll", "VClientEntityList003");
	interfaces::engine = interfaces::GetInterface<EngineClientInterface>(L"engine.dll", "VEngineClient014");
	interfaces::client = interfaces::GetInterface<ClientInterface>(L"client.dll", "VClient018");

	globals::player = reinterpret_cast<uintptr_t*>(interfaces::entitylist->GetClientEntity(interfaces::engine->GetLocalPlayer()));
	globals::net = new CNetvars;
	globals::entitylist = reinterpret_cast<uintptr_t*>(client + offsets::entitylist);

	globals::net->Dump();


	return true;
}
