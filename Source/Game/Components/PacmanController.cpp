#include "MiniginPCH.h"
#include "PacmanController.h"
#include "Engine/Scenegraph/GameObject.h"
#include "Engine/Managers/PhysicsManager.h"
#include "Engine/Managers/EventManager.h"
#include "Game/Gameplay/Actors/PacmanActor.h"

PacmanController::PacmanController(PacmanActor* pActor, float speed)
	: CharacterController(speed),
	m_pPlayer(pActor)
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
				GetHit();
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

void PacmanController::GetHit()
{
	if (!m_pPlayer->IsPowered())
		m_pPlayer->LoseLife();
}

void PacmanController::EatPellet(GameObject* pPellet)
{
	pPellet->SetActive(false);
	EventManager::GetInstance().TriggerEvent(Event::EatPellet());
	//Play sound
}

void PacmanController::EatPowerPellet(GameObject* pPower)
{
	pPower->SetActive(false);
	m_pPlayer->PowerUp();
	EventManager::GetInstance().TriggerEvent(Event::EatPower());
	//Play sound
}

void PacmanController::EatFruit(GameObject* pFruit)
{
	pFruit->SetActive(false);
	EventManager::GetInstance().TriggerEvent(Event::EatFruit());
	//Play sound
}