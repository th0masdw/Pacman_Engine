#include "MiniginPCH.h"
#include "GhostActor.h"
#include "Engine/Components/ShapeComponent.h"
#include "Engine/Components/ColliderComponent.h"
#include "Engine/Components/CharacterController.h"
#include "Game/Components/AIComponent.h"
#include "Game/Gameplay/Actors/PacmanActor.h"

GhostActor::GhostActor(PacmanActor* pPacman, float size, float speed, const Color& color, bool isPlayerControlled)
	: GameObject{ Tag::Enemy },
	m_pController(nullptr),
	m_IsPlayerControlled(isPlayerControlled)
{
	ShapeComponent* pShape = new ShapeComponent(size, size, color);
	AddComponent(pShape);

	ColliderComponent* pCollider = new ColliderComponent(size, size, false);
	AddComponent(pCollider);

	if (!isPlayerControlled) {
		AIComponent* pAI = new AIComponent(pPacman, speed);
		AddComponent(pAI);
	} else {
		m_pController = new CharacterController(speed);
		AddComponent(m_pController);

		//Add P2 input
	}
}

void GhostActor::Update(const GameTime& time)
{
	UNREFERENCED_PARAMETER(time);
}

void GhostActor::Draw() const
{
}