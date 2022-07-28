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

CVector3 esp::GetBonePosition(CEntity* entity, int bone)
{
	return CVector3();
}

void esp::DrawSnapline(CVector3 position, D3DCOLOR color, float thickness, SnaplinePosition snap_position)
{
	CVector2 screen;
	if (!WorldToScreen(position, screen))
		return;

	int x, y;
	switch (snap_position)
	{
	case SnaplinePosition::bottom:
		y = renderer::screen_height;
		x = renderer::screen_width / 2;
		break;
	case SnaplinePosition::top:
		y = 0;
		x = renderer::screen_width / 2;
		break;
	case SnaplinePosition::crosshair:
		x = renderer::screen_width / 2;
		y = renderer::screen_height / 2;
		break;
	default:
		x = renderer::screen_width;
		y = 0;
	}

	renderer::DrawLine(x, y, screen.x, screen.y, color, thickness);
}

void esp::DrawBox(CEntity* entity, D3DCOLOR color, float thickness)
{
	;;
}

void esp::Update()
{
	// Do any important updating and other shit
	memcpy(view_matrix, (uintptr_t*)(globals::client + offsets::viewmatrix), sizeof(view_matrix));
}

void esp::Run()
{
	esp::Update();

	for (int i = 0; i < 32; ++i)
	{
		auto entity = reinterpret_cast<CEntity*>(globals::entitylist[i * 4]);
		if (!entity)
			continue;

		if (entity->IsLocalPlayer())
			continue;

		if (!entity->dormant())
			continue;

		if (!entity->GetHealth())
			continue;

		auto position = entity->GetPosition();

		CVector2 screen{};
		// DrawSnapline(position, D3DCOLOR_XRGB(0, 255, 0), 2.0f, settings::esp::snapline_type);
		DrawBox(entity, D3DCOLOR_XRGB(255, 255, 255), 3.0f);
	}
}