#include "MiniginPCH.h"
#include "Fruit.h"
#include "Engine/Components/SpriteComponent.h"
#include "Engine/Components/ColliderComponent.h"

Fruit::Fruit()
	: GameObject(Tag::Fruit, Layer::Pickups),
	m_HasAppeared(false)
{
	SpriteComponent* pSprite = new SpriteComponent("Resources/Images/fruit.png");
	AddComponent(pSprite);

	ColliderComponent* pCollider = new ColliderComponent(34.0f, 34.0f);
	AddComponent(pCollider);

	m_Timer = static_cast<float>(rand() % 41 + 20);
	SetActive(false);
}

void Fruit::Update(const GameTime& time)
{
	if (!m_HasAppeared) {
		m_Timer -= time.GetElapsedTime();

		if (m_Timer <= 0.0f) {
			SetActive(true);
			m_HasAppeared = true;
		}			
	}
}