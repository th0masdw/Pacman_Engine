#include "MiniginPCH.h"
#include "GhostActor.h"
#include "Engine/Components/ShapeComponent.h"
#include "Engine/Components/ColliderComponent.h"
#include "Engine/Components/AIComponent.h"

GhostActor::GhostActor(float size, float speed, const Color& color)
	: GameObject{ Tag::Enemy },
	m_Speed{ speed }
{
	ShapeComponent* pShape = new ShapeComponent(size, size, color);
	AddComponent(pShape);

	ColliderComponent* pCollider = new ColliderComponent(size, size, false);
	AddComponent(pCollider);

	AIComponent* pAI = new AIComponent();
	AddComponent(pAI);
}

void GhostActor::Update(const GameTime& time)
{
	UNREFERENCED_PARAMETER(time);
}

void GhostActor::Draw() const
{
}

void GhostActor::Move(const glm::vec2& displacement)
{
	UNREFERENCED_PARAMETER(displacement);
}