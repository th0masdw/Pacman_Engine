#include "MiniginPCH.h"
#include "PacmanActor.h"
#include "Engine/Components/ShapeComponent.h"
#include "Engine/Components/ColliderComponent.h"
#include "Engine/Components/CharacterController.h"
#include "Engine/Managers/InputManager.h"

PacmanActor::PacmanActor(float size, float speed)
	: GameObject{ Tag::Player },
	m_Direction{ 0.0f, 0.0f }
{
	ShapeComponent* pShape = new ShapeComponent(size, size, { 255.0f, 255.0f, 0.0f, 255.0f });
	AddComponent(pShape);

	ColliderComponent* pCollider = new ColliderComponent(size, size, false);
	AddComponent(pCollider);

	m_pController = new CharacterController(speed);
	AddComponent(m_pController);

	//Input
	InputManager& input = InputManager::GetInstance();
	input.AddInputAction(InputAction{ Input::P1_Up, XINPUT_GAMEPAD_DPAD_UP, 0, true });
	input.AddInputAction(InputAction{ Input::P1_Down, XINPUT_GAMEPAD_DPAD_DOWN, 0, true });
	input.AddInputAction(InputAction{ Input::P1_Left, XINPUT_GAMEPAD_DPAD_LEFT, 0, true });
	input.AddInputAction(InputAction{ Input::P1_Right, XINPUT_GAMEPAD_DPAD_RIGHT, 0, true });
}

void PacmanActor::Update(const GameTime& time)
{	
	m_pController->CheckCollision(m_Direction * time.GetElapsedTime());

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

	m_pController->Move(m_Direction * time.GetElapsedTime());
}

void PacmanActor::Draw() const
{
}

glm::vec2 PacmanActor::GetPosition() const
{
	return GetTransform()->GetPosition();
}