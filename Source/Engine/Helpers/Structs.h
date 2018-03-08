#pragma once

#include "MiniginPCH.h"

//TODO: rename Structs.h file!

enum class Input : int
{
	P1_Up, P1_Down, P1_Left, P1_Right,
	P2_Up, P2_Down, P2_Left, P2_Right
};

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

struct InputAction
{
	Input id;
	int bitMask;
	int playerId;
};