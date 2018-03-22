#include "MiniginPCH.h"
#include "PacmanActor.h"
#include "Engine/Components/ShapeComponent.h"
#include "Engine/Components/ColliderComponent.h"
#include "Engine/Managers/InputManager.h"
#include "Engine/Managers/PhysicsManager.h"

PacmanActor::PacmanActor(float size, float speed)
	: GameObject{ Tag::Player },
	m_CurrentSpeed{ speed },
	m_MovementSpeed{ speed },
	m_Direction{ 0.0f, 0.0f },
	m_CollisionOffset{ 4.0f }
{
	ShapeComponent* pShape = new ShapeComponent(size, size, { 255.0f, 255.0f, 0.0f, 255.0f });
	AddComponent(pShape);

	ColliderComponent* pCollider = new ColliderComponent(size, size, false);
	AddComponent(pCollider);

	//Input
	InputManager& input = InputManager::GetInstance();
	input.AddInputAction(InputAction{ Input::P1_Up, XINPUT_GAMEPAD_DPAD_UP, 0 });
	input.AddInputAction(InputAction{ Input::P1_Down, XINPUT_GAMEPAD_DPAD_DOWN, 0 });
	input.AddInputAction(InputAction{ Input::P1_Left, XINPUT_GAMEPAD_DPAD_LEFT, 0 });
	input.AddInputAction(InputAction{ Input::P1_Right, XINPUT_GAMEPAD_DPAD_RIGHT, 0 });
}

void PacmanActor::Update(const GameTime& time)
{
	//Collision
	GameObject* pCollision = PhysicsManager::GetInstance().DoesCollide(this);

	//Check on tag!
	if (pCollision) {
		m_CurrentSpeed = 0.0f;
		Move(m_Direction * -m_CollisionOffset);
	} else {
		m_CurrentSpeed = m_MovementSpeed;
	}

	//Input
	InputManager& input = InputManager::GetInstance();

	if (input.IsActionTriggered(Input::P1_Up))
		m_Direction = glm::vec2{ 0.0f, 1.0f };

	else if (input.IsActionTriggered(Input::P1_Down))
		m_Direction = glm::vec2{ 0.0f, -1.0f };

	else if (input.IsActionTriggered(Input::P1_Left))
		m_Direction = glm::vec2{ -1.0f, 0.0f };

	else if (input.IsActionTriggered(Input::P1_Right))
		m_Direction = glm::vec2{ 1.0f, 0.0f };

	Move(m_Direction * time.GetElapsedTime() * m_CurrentSpeed);
}

void PacmanActor::Draw() const
{
}

glm::vec2 PacmanActor::GetPosition() const
{
	return GetTransform()->GetPosition();
}

void PacmanActor::Move(const glm::vec2& displacement)
{
	glm::vec2 flipped = { displacement.x, displacement.y * -1.0f };
	glm::vec2 pos = GetTransform()->GetPosition();
	pos += flipped;
	GetTransform()->Translate(pos);
}