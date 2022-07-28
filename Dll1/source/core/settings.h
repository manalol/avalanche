#pragma once

enum class SnaplinePosition
{
	top,
	bottom,
	crosshair,
};

namespace settings
{
	namespace aim
	{
		inline bool enabled = false;
	}

	namespace esp
	{
		inline bool enabled = false;
		inline bool health = false;
		inline SnaplinePosition snapline_type;
	}

	namespace menu
	{
		inline bool enabled = false;
	}
}