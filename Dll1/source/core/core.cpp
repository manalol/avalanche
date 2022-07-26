#include "core.h"

void core::Run()
{


	for (int i = 0; i < 64; ++i)
	{
		auto entity = reinterpret_cast<CEntity*>(globals::entitylist->GetClientEntity(i));

		if (!entity)
			continue;

		std::cout << entity->GetOffset<int>("m_iHealth") << "\n";
	}
	std::cout << "=============\n";
}
