#pragma once

#include "Engine/Scenegraph/GameObject.h"
struct Color;

class Pellet : public GameObject
{
public:
	explicit Pellet(float size = 10.0f, const Color& color = { 255, 253, 218, 255 });
	virtual ~Pellet() = default;

	void SetSize(float size);
	void SetColor(const Color& color);
};