#pragma once

#include "Engine/Scenegraph/GameObject.h"
struct Color;
class ShapeComponent;
class ColliderComponent;

class Pellet : public GameObject
{
public:
	explicit Pellet(float size = 5.0f, const Color& color = { 253, 191, 166, 255 }, const Tag tag = Tag::Pellet, bool isPoolable = true);
	virtual ~Pellet() = default;

	void SetSize(float size);
	void SetColor(const Color& color);

	Color GetColor() const;

private:
	ShapeComponent* m_pShape;
	ColliderComponent* m_pCollider;
};