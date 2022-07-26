
#include <iostream>
#include <thread>

#include <Windows.h>

#include "utils/hook.h"
#include "core/core.h"

using ms = std::chrono::duration<double, std::milli>;

FILE* Startup()
{
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);

	return fp;
}

bool Cleanup(FILE* fp, HMODULE hModule)
{
	fclose(fp);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);

	if (globals::net)
		delete globals::net;
	return 0;
}

DWORD WINAPI Handler(HMODULE hModule)
{
	auto output = Startup();

	if (!hooks::Initalize())
		return Cleanup(output, hModule);

	if (!globals::Initalize())
		return Cleanup(output, hModule);

	while (!GetAsyncKeyState(VK_END) & 1)
	{
		core::Run();
		std::this_thread::sleep_for(ms(100));
	}
		
	hooks::Cleanup();
	Cleanup(output, hModule);

	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD reason, LPVOID lpreserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		HANDLE thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Handler), hModule, 0, nullptr);
		if (thread != INVALID_HANDLE_VALUE)
		{
			CloseHandle(thread);
		}
	}

	return TRUE;
}