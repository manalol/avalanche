#pragma once
#include <chrono>

using namespace std::chrono_literals;
using ms = std::chrono::milliseconds;
using msf = std::chrono::duration<double, std::milli>;

using Vector2 = CVector2;
using Vector3 = CVector3;

using Vec3 = CVector3;
using Vec2 = CVector2;

class CVector2
{
public:
	float x, y;
};

class CVector3
{
public:
	float x, y, z;
};

class CVector4
{
public:
	float x, y, z, w;
};

