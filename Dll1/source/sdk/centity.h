#pragma once

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

#include "../utils/globals.h"
#include "cmath.h"

class CEntity
{
public:
	template <typename type>
	type GetOffset(std::string netvar_name)
	{
		return *reinterpret_cast<type*>(std::uintptr_t(this) + globals::net->GetNetvar(netvar_name));
	}

	int GetHealth()
	{
		return GetOffset<int>(offsets::health);
	}

	int GetTeam()
	{
		return GetOffset<int>(offsets::team);
	}

	CVector3 GetPosition()
	{
		return GetOffset<CVector3>(offsets::position);
	}
};