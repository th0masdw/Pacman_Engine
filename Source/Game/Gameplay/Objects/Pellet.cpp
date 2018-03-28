#include "MiniginPCH.h"
#include "Pellet.h"
#include "Engine/Helpers/Structs.h"
#include "Engine/Components/ShapeComponent.h"
#include "Engine/Components/ColliderComponent.h"

Pellet::Pellet(float size, const Color& color)
	: GameObject(Tag::Pellet, Layer::Pickups, true)
{
	ShapeComponent* pShape = new ShapeComponent(size, size, color);
	AddComponent(pShape);

	ColliderComponent* pCollider = new ColliderComponent(size, size);
	AddComponent(pCollider);
}

void Pellet::SetSize(float size)
{
	ShapeComponent* pShape = GetComponent<ShapeComponent>();
	if (pShape)
		pShape->SetDimensions(size, size);

	ColliderComponent* pColl = GetComponent<ColliderComponent>();
	if (pColl)
		pColl->SetDimensions(size, size);
}

void Pellet::SetColor(const Color& color)
{
	ShapeComponent* pShape = GetComponent<ShapeComponent>();

	if (pShape)
		pShape->SetColor(color);
}