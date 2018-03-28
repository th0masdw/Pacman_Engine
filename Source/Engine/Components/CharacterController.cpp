#include "MiniginPCH.h"
#include "CharacterController.h"
#include "Engine/Scenegraph/GameObject.h"

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