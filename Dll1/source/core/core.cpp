#include "core.h"
#include "settings.h"

void core::Run()
{
	if (GetAsyncKeyState(VK_F1) & 1)
		settings::esp::enabled = !settings::esp::enabled;

	if (GetAsyncKeyState(VK_F2) & 1)
		settings::menu::enabled = !settings::menu::enabled;

	if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		settings::esp::snapline_type = SnaplinePosition::bottom;

	if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		settings::esp::snapline_type = SnaplinePosition::top;

	if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		settings::esp::snapline_type = SnaplinePosition::crosshair;
}
