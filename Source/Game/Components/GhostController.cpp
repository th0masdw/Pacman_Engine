#include "MiniginPCH.h"
#include "GhostController.h"
#include "Engine/Scenegraph/GameObject.h"
#include "Engine/Managers/PhysicsManager.h"
#include "Game/Gameplay/Actors/GhostActor.h"

GhostController::GhostController(GhostActor* pGhost, float speed)
	: CharacterController(speed),
	m_pGhost(pGhost)
{
}

void GhostController::CheckCollision(const glm::vec2& direction)
{
	GameObject* pCollision = PhysicsManager::GetInstance().DoesCollide(m_pGameObject);
	
	if (pCollision) {
		switch (pCollision->GetTag()) {
			case Tag::Obstacle:
				Move(-direction);
				break;

			case Tag::Player:
				GetHit();
				break;
		}
	}
}

void GhostController::GetHit()
{
	if (m_pGhost->IsScared())
		m_pGhost->Respawn();
}