#pragma once
#include <chrono>

using namespace std::chrono_literals;
using ms = std::chrono::milliseconds;
using msf = std::chrono::duration<double, std::milli>;

class CVector2;
class CVector3;
class CVector4;

using Vector2 = CVector2;
using Vector3 = CVector3;
using Vector4 = CVector4;

using Vec3 = CVector3;
using Vec2 = CVector2;
using Vec4 = CVector4;

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

