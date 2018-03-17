#pragma once

#include "Engine/Scenegraph/GameObject.h"
struct Color;

class Wall : public GameObject
{
public:
	explicit Wall(float width = 50.0f, float height = 50.0f, const Color& color = { 255.0f, 255.0f, 255.0f, 255.0f });
	virtual ~Wall() = default;

	void SetDimensions(float width, float height);
	void SetColor(const Color& color);
};