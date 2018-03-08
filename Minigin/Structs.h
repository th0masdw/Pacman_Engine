#pragma once

#include "MiniginPCH.h"

struct WindowSettings
{
	WindowSettings()
		: Width(640),
		Height(480),
		Name("Programming IV Assignment")
	{
	}

	int Width;
	int Height;
	std::string Name;
};

struct Vector2
{
	float x, y;

	Vector2& operator+=(const Vector2& right) {
		x += right.x;
		y += right.y;
		return *this;
	}

	friend Vector2 operator+(const Vector2& left, const Vector2& right) {
		return { left.x + right.x, left.y + right.y };
	}
};

struct Color
{
	float r, g, b, a;
};