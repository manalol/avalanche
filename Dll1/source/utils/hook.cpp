#include "hook.h"



// Sets up our endscene hook by using an endscene hook
bool hooks::Initalize()
{	
	auto d3d{ Direct3DCreate9(D3D_SDK_VERSION) };
	if (!d3d)
		return false;

	LPDIRECT3DDEVICE9 dummy{ nullptr };

	D3DPRESENT_PARAMETERS params{};
	params.Windowed = false; // Try to first hook in fullscreen mode
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.hDeviceWindow = GetThreadWindow();

	// Try to create our device
	if (SUCCEEDED(d3d->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL, params.hDeviceWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &params, &dummy)))
		hooks::window = params.hDeviceWindow;
	else
	{
		// Try again in windowed mode
		params.Windowed = true;
		if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, params.hDeviceWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &params, &dummy)))
		{
			d3d->Release();
			return false;
		}
	}

	memcpy(D3DTable, *reinterpret_cast<void***>(dummy), sizeof(D3DTable));
	

	// Setup our trampoline hook (we hook the 42nd entry because the EndScene VTable is shared by all Direct3d Objects
	o_endscene = reinterpret_cast<endscene_t>(memory::Tramphook(static_cast<BYTE*>(D3DTable[42]), reinterpret_cast<BYTE*>(hooks::EndScene), 7, true));
	

	d3d->Release();
	dummy->Release();
	return true;
}

void hooks::Cleanup()
{
	memory::Patch(static_cast<BYTE*>(D3DTable[42]), memory::patches[0].m_original, 7);
}

BOOL WINAPI hooks::EnumerateWindow(HWND handle, LPARAM lp)
{
	DWORD pid = GetWindowThreadProcessId(handle, NULL);

	if (GetCurrentThreadId() != pid)
		return TRUE;

	hooks::window = handle;
	return FALSE;
}

HWND hooks::GetThreadWindow()
{
	EnumWindows(hooks::EnumerateWindow, NULL);
	if (!hooks::window) // Window wasn't found
		return NULL;

	return hooks::window;
}

// Do all the drawing in endscene
HRESULT __stdcall hooks::EndScene(LPDIRECT3DDEVICE9 device)
{
	if (!renderer::device)
		renderer::device = device;
	
	D3DVIEWPORT9 viewport{ NULL };
	renderer::device->GetViewport(&viewport);

	renderer::screen_height = viewport.Height;
	renderer::screen_width = viewport.Width;

	//renderer::DrawFilledRect({ 200, 200 }, { 300, 300 }, D3DCOLOR_XRGB(255, 0, 0));
	//renderer::DrawRect({ 200, 200 }, { 300, 300 }, D3DCOLOR_XRGB(0, 255, 0), 4.0f);

	if (settings::esp::enabled)
		esp::Run();

	return o_endscene(device);
}
