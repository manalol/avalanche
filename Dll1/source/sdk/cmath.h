#pragma once
#include <chrono>

using namespace std::chrono_literals;
using ms = std::chrono::milliseconds;
using msf = std::chrono::duration<double, std::milli>;

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

