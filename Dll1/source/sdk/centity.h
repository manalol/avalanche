#pragma once

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

#include "../utils/globals.h"
#include "cmath.h"

#define NETVAR(func_name, netvar_name, type) type& func_name()\
{ \
	static auto offset = netvar::netvars[fnv::cphash(netvar_name)]; \
	return *reinterpret_cast<type*>(std::uintptr_t(this) + offset); \
}


class CEntity
{
public:
	NETVAR(health, "CBasePlayer->m_iHealth", int)
	NETVAR(team, "CBasePlayer->m_iTeam", int)
	NETVAR(position, "CBasePlayer-m_vecOrigin", CVector3)
	NETVAR(view, "CBasePlayer->m_vecViewOrigin", CVector3)
	NETVAR(dormant, "CBasePlayer->m_bDormant", bool)

	auto GetHealth()
	{
		return health();
	}

	auto GetTeam()
	{
		return team();
	}

	auto GetPosition()
	{
		return position();
	}

	auto IsLocalPlayer()
	{
		return reinterpret_cast<CEntity*>(globals::player) == this;
	}
};