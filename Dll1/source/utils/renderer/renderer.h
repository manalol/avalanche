#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


namespace renderer
{
	extern const wchar_t* font_name;
	extern const int font_size;

	inline IDirect3DDevice9* device;
	inline ID3DXLine* line;
	inline ID3DXFont* font;

	inline int screen_width;
	inline int screen_height;

	void DrawLine(int x, int y, int x2, int y2, D3DCOLOR color, float thickness);
	void DrawRect(int x, int y, int width, int height, D3DCOLOR color, float thickness);
	void DrawFilledRect(int x, int y, int width, int height, D3DCOLOR color);
	void DrawText(const wchar_t* text, int x, int y, D3DCOLOR);

}

