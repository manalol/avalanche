#include "core.h"
#include "settings.h"

void core::Run()
{
	if (GetAsyncKeyState(VK_F1) & 1)
		settings::esp::enabled = !settings::esp::enabled;

	if (GetAsyncKeyState(VK_F2) & 1)
		settings::menu::enabled = !settings::menu::enabled;

}
