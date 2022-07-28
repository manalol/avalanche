#pragma once

#include <iostream>

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")

#include "memory.h"
#include "renderer/renderer.h"

#include "../core/settings.h"
#include "../hacks/esp/esp.h"

static void* D3DTable[119];
namespace hooks
{
	using endscene_t = HRESULT(_stdcall*)(LPDIRECT3DDEVICE9);
	inline endscene_t o_endscene;

	static HWND window;

	bool Initalize();
	void Cleanup();

	HWND GetThreadWindow();
	BOOL WINAPI EnumerateWindow(HWND handle, LPARAM lp);

	HRESULT __stdcall EndScene(LPDIRECT3DDEVICE9 device);
	
}