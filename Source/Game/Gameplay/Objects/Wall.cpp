#include "MiniginPCH.h"
#include "Wall.h"
#include "Engine/Helpers/Structs.h"
#include "Engine/Components/ShapeComponent.h"
#include "Engine/Components/ColliderComponent.h"

Wall::Wall(float width, float height, const Color& color)
	: GameObject{ Tag::Obstacle, Layer::Walls, true }
{
	ShapeComponent* pShape = new ShapeComponent(width, height, color);
	AddComponent(pShape);

	ColliderComponent* pCollider = new ColliderComponent(width, height);
	AddComponent(pCollider);
}

void Wall::SetDimensions(float width, float height)
{
	ShapeComponent* pShape = GetComponent<ShapeComponent>();
	if (pShape)
		pShape->SetDimensions(width, height);

	ColliderComponent* pColl = GetComponent<ColliderComponent>();
	if (pColl)
		pColl->SetDimensions(width, height);
}

void Wall::SetColor(const Color& color)
{
	ShapeComponent* pShape = GetComponent<ShapeComponent>();

	if (pShape)
		pShape->SetColor(color);
}