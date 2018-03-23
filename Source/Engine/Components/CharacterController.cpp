#include "MiniginPCH.h"
#include "CharacterController.h"
#include "Engine/Scenegraph/GameObject.h"
#include "Engine/Managers/PhysicsManager.h"

CharacterController::CharacterController(float speed)
	: m_Speed(speed)
{
}

void CharacterController::PostInitialize()
{
}

void CharacterController::Update(const GameTime&)
{
}

void CharacterController::Draw() const
{
}

void CharacterController::Move(const glm::vec2& direction)
{
	glm::vec2 displacement = direction * m_Speed;
	displacement.y *= -1.0f;

	glm::vec2 pos = m_pGameObject->GetTransform()->GetPosition();
	pos += displacement;
	m_pGameObject->GetTransform()->Translate(pos);
}

void CharacterController::CheckCollision(const glm::vec2& direction)
{
	GameObject* pCollision = PhysicsManager::GetInstance().DoesCollide(m_pGameObject);
	
	if (pCollision) {
		if (pCollision->GetTag() == Tag::Obstacle)
			Move(-direction);
		
		//other collision cases...
	}
}