#pragma once

#include <iostream>
#include "../sdk/centity.h"

#include "../utils/renderer/renderer.h"
#include "../utils/globals.h"

namespace esp
{
	inline float view_matrix[16];

	void Run();
	bool WorldToScreen(CVector3 pos, CVector2& screen);
}

