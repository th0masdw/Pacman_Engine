#include "MiniginPCH.h"
#include "Fruit.h"
#include "Engine/Components/SpriteComponent.h"
#include "Engine/Components/ColliderComponent.h"

Fruit::Fruit()
	: GameObject(Tag::Fruit, Layer::Pickups)
{
	SpriteComponent* pSprite = new SpriteComponent("../Resources/fruit.png");
	AddComponent(pSprite);

	ColliderComponent* pCollider = new ColliderComponent(34.0f, 34.0f);
	AddComponent(pCollider);
}