#pragma once

#include "MiniginPCH.h"

enum class Input : int
{
	P1_Up		= 0,
	P1_Down		= 1,
	P1_Left		= 2,
	P1_Right	= 3,

	P2_Up		= 4,
	P2_Down		= 5,
	P2_Left		= 6,
	P2_Right	= 7,
};

struct Color
{
	float r, g, b, a;
};

struct Rect
{
	Rect() = default;

	Rect(float x, float y, float width, float height)
		: x{ x },
		y{ y },
		width{ width },
		height{ height }
	{
	}

	float x, y, width, height;
};

struct InputAction
{
	Input id;
	int bitMask;
	int playerId;
	bool useGamepad;
};

enum class Tag
{
	Empty, 
	Player, 
	Enemy, 
	Obstacle, 
	Pickup
};