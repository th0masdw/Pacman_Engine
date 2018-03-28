#include "MiniginPCH.h"
#include "GhostController.h"
#include "Engine/Scenegraph/GameObject.h"
#include "Engine/Managers/PhysicsManager.h"

GhostController::GhostController(float speed)
	: CharacterController(speed)
{
}

void GhostController::CheckCollision(const glm::vec2& direction)
{
	GameObject* pCollision = PhysicsManager::GetInstance().DoesCollide(m_pGameObject);
	
	if (pCollision) {
		if (pCollision->GetTag() == Tag::Obstacle)
			Move(-direction);
	}
}