#include "MiniginPCH.h"
#include "PacmanController.h"
#include "Engine/Scenegraph/GameObject.h"
#include "Engine/Managers/PhysicsManager.h"
#include "Engine/Managers/EventManager.h"

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
				EatPellet(pCollision);
				break;

			case Tag::PowerPellet:
				EatPowerPellet(pCollision);
				break;

			case Tag::Fruit:
				EatFruit(pCollision);
				break;
		}
	}
}

void PacmanController::EatPellet(GameObject* pPellet)
{
	pPellet->SetActive(false);
	EventManager::GetInstance().TriggerEvent("EatPellet");
	//Play sound
}

void PacmanController::EatPowerPellet(GameObject* pPower)
{
	pPower->SetActive(false);
	EventManager::GetInstance().TriggerEvent("EatPower");
	//Play sound
	//Power up pacman
}

void PacmanController::EatFruit(GameObject* pFruit)
{
	pFruit->SetActive(false);
	EventManager::GetInstance().TriggerEvent("EatFruit");
	//Play sound
}