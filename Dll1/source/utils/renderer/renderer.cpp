#include "renderer.h"

extern const wchar_t* renderer::font_name = L"Tahoma";
extern const int renderer::font_size;

void renderer::DrawLine(int x, int y, int x2, int y2, D3DCOLOR color, float thickness)
{
	if (!renderer::device)
		return;

	if (!renderer::line)
	{
		auto result = D3DXCreateLine(renderer::device, &renderer::line);
		if (result != S_OK)
			return;
	}
	
	renderer::line->SetWidth(thickness);

	D3DXVECTOR2 lines[2] = { D3DXVECTOR2(x, y), D3DXVECTOR2(x2, y2) };
	renderer::line->Draw(lines, 2, color);
}

void renderer::DrawRect(int x, int y, int width, int height, D3DCOLOR color, float thickness)
{
}

/*
void renderer::DrawRect(D3DXVECTOR2 start, D3DXVECTOR2 size, D3DCOLOR color, float thickness)
{
	if (!renderer::device)
		return;

	// Draw our lines clockwise
	DrawLine(start, { end.x, start.y }, color, thickness); // First line from top left to top right
	DrawLine({end.x, start.y}, end, color, thickness); // Second line from top right to bottom right
	DrawLine(end, {start.x, end.y}, color, thickness); // Third line from bottom right to bottom left
	DrawLine({start.x, end.y}, start, color, thickness); // Final from bottom left to top left
}
*/

void renderer::DrawFilledRect(int x, int y, int width, int height, D3DCOLOR color)
{
	if (!renderer::device)
		return;

	D3DRECT rect{ x, y, x + width, y + height };
	renderer::device->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void renderer::DrawText(const wchar_t* text, int x, int y, D3DCOLOR color)
{
	if (!renderer::device)
		return;

	if (!renderer::font)
	{
		D3DXCreateFont(
			renderer::device,
			20,
			0,
			FW_NORMAL,
			1,
			FALSE,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			PROOF_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			L"Tahoma",
			&renderer::font
		);
	}

	RECT position{ x, y, x, y};
	renderer::font->DrawTextW(NULL, text, -1, &position, DT_NOCLIP, color);
}
