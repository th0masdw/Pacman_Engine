#include "MiniginPCH.h"
#include "Wall.h"
#include "Engine/Helpers/Structs.h"
#include "Engine/Components/ShapeComponent.h"
#include "Engine/Components/ColliderComponent.h"

Wall::Wall(float width, float height, const Color& color)
	: GameObject{ Tag::Obstacle, Layer::Walls, true }
{
	m_pShape = new ShapeComponent(width, height, color);
	AddComponent(m_pShape);

	m_pCollider = new ColliderComponent(width, height);
	AddComponent(m_pCollider);
}

void Wall::SetDimensions(float width, float height)
{
	m_pShape->SetDimensions(width, height);
	m_pCollider->SetDimensions(width, height);
}

void Wall::SetColor(const Color& color)
{
	m_pShape->SetColor(color);
}