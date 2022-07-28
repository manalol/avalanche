#include "esp.h"

bool esp::WorldToScreen(CVector3 pos, CVector2& screen)
{
	CVector4 projection;
	projection.x = pos.x * view_matrix[0] + pos.y * view_matrix[1] + pos.z * view_matrix[2] + view_matrix[3];
	projection.y = pos.x * view_matrix[4] + pos.y * view_matrix[5] + pos.z * view_matrix[6] + view_matrix[7];
	projection.z = pos.x * view_matrix[8] + pos.y * view_matrix[9] + pos.z * view_matrix[10] + view_matrix[11];
	projection.w = pos.x * view_matrix[12] + pos.y * view_matrix[13] + pos.z * view_matrix[14] + view_matrix[15];


	if (projection.w < 0.1f)
		return false;

	CVector2 ndc{};
	ndc.x = projection.x / projection.w;
	ndc.y = projection.y / projection.w;

	screen.x = (renderer::screen_width / 2 * ndc.x) + (ndc.x + renderer::screen_width / 2);
	screen.y = -(renderer::screen_height / 2 * ndc.y) + (ndc.y + renderer::screen_height / 2);
	return true;
}

void esp::Run()
{
	memcpy(view_matrix, (uintptr_t*)(globals::client + offsets::viewmatrix), sizeof(view_matrix));
	for (int i = 0; i < 32; ++i)
	{
		auto entity = reinterpret_cast<CEntity*>(globals::entitylist[i * 4]);
		if (!entity || entity == reinterpret_cast<CEntity*>(globals::player || entity->GetOffset<bool>("m_iDormant")))
			continue;

		auto position = entity->GetPosition();

		CVector2 screen;
		if (WorldToScreen(position, screen))
		{
			renderer::DrawLine(renderer::screen_width / 2, renderer::screen_height, screen.x, screen.y, D3DCOLOR_XRGB(255, 255, 255), 2.0f);
		}
	}
}