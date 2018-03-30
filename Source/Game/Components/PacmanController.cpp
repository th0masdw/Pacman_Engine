#include "MiniginPCH.h"
#include "PacmanController.h"
#include "Engine/Scenegraph/GameObject.h"
#include "Engine/Managers/PhysicsManager.h"

PacmanController::PacmanController(float speed)
	: CharacterController(speed)
{
}

void PacmanController::CheckCollision(const glm::vec2& direction)
{
	GameObject* pCollision = PhysicsManager::GetInstance().DoesCollide(m_pGameObject);
	
	if (pCollision) {
		switch (pCollision->GetTag()) {
			case Tag::Obstacle:
				Move(-direction);
				break;

			case Tag::Enemy:
				Debug::Log("Dead");
				break;

			case Tag::Pellet:
				Debug::Log("Got pellet!");
				break;

			case Tag::PowerPellet:
				Debug::Log("POWER");
				break;

			case Tag::Fruit:
				Debug::Log("Fruit!");
				break;
		}
	}
}