#include "MiniginPCH.h"
#include "Pellet.h"
#include "Engine/Helpers/Structs.h"
#include "Engine/Components/ShapeComponent.h"
#include "Engine/Components/ColliderComponent.h"

Pellet::Pellet(float size, const Color& color, const Tag tag, bool isPoolable)
	: GameObject(tag, Layer::Pickups, isPoolable)
{
	m_pShape = new ShapeComponent(size, size, color);
	AddComponent(m_pShape);

	m_pCollider = new ColliderComponent(size, size);
	AddComponent(m_pCollider);
}

void Pellet::SetSize(float size)
{
	m_pShape->SetDimensions(size, size);
	m_pCollider->SetDimensions(size, size);
}

void Pellet::SetColor(const Color& color)
{
	m_pShape->SetColor(color);
}

Color Pellet::GetColor() const
{
	return m_pShape->GetColor();
}