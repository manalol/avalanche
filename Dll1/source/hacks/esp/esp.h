#pragma once

#include <iostream>

#include "../../sdk/centity.h"

#include "../../utils/renderer/renderer.h"
#include "../../utils/globals.h"

#include "../../core/settings.h"



namespace esp
{
	
	inline float view_matrix[16];

	void Update();
	void Run();
	bool WorldToScreen(CVector3 pos, CVector2& screen);
	CVector3 GetBonePosition(CEntity* entity, int bone);

	void DrawSnapline(CVector3 position, D3DCOLOR color, float thickness, SnaplinePosition snap_position);
	void DrawBox(CEntity* entity, D3DCOLOR color, float thickness);

}

