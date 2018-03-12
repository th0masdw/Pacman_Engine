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

enum class Input : int
{
	//Player 1
	P1_Up		= 0,
	P1_Down		= 1,
	P1_Left		= 2,
	P1_Right	= 3,

	//Player 2
	P2_Up		= 4,
	P2_Down		= 5,
	P2_Left		= 6,
	P2_Right	= 7,
};

struct Vector2
{
	float x, y;

	Vector2& operator+=(const Vector2& right) {
		x += right.x;
		y += right.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& right) {
		x -= right.x;
		y -= right.y;
		return *this;
	}

	Vector2& operator*=(float right) {
		x *= right;
		y *= right;
		return *this;
	}

	friend Vector2 operator+(const Vector2& left, const Vector2& right) {
		return { left.x + right.x, left.y + right.y };
	}

	friend Vector2 operator-(const Vector2& left, const Vector2& right) {
		return { left.x - right.x, left.y - right.y };
	}

	friend Vector2 operator*(const Vector2& left, float right) {
		return { left.x * right, left.y * right };
	}

	friend Vector2 operator*(float left, const Vector2& right) {
		return { right.x * left, right.y * left };
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