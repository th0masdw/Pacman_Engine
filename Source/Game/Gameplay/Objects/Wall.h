#pragma once

#include "Engine/Scenegraph/GameObject.h"
struct Color;
class ShapeComponent;
class ColliderComponent;

class Wall : public GameObject
{
public:
	explicit Wall(float width = 25.0f, float height = 25.0f, const Color& color = { 0.0f, 0.0f, 205.0f, 255.0f });
	virtual ~Wall() = default;

	void SetDimensions(float width, float height);
	void SetColor(const Color& color);

private:
	ShapeComponent* m_pShape;
	ColliderComponent* m_pCollider;
};