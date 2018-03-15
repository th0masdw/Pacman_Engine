#include "MiniginPCH.h"
#include "PacmanActor.h"
#include "Engine/Components/ShapeComponent.h"
#include "Engine/Managers/InputManager.h"

PacmanActor::PacmanActor(float size, float speed)
	: GameObject{},
	m_Speed{ speed }
{
	ShapeComponent* pShape = new ShapeComponent(size, size, { 255.0f, 255.0f, 0.0f, 255.0f });
	AddComponent(pShape);

	//Input
	InputManager& input = InputManager::GetInstance();
	input.AddInputAction(InputAction{ Input::P1_Up, XINPUT_GAMEPAD_DPAD_UP, 0 });
	input.AddInputAction(InputAction{ Input::P1_Down, XINPUT_GAMEPAD_DPAD_DOWN, 0 });
	input.AddInputAction(InputAction{ Input::P1_Left, XINPUT_GAMEPAD_DPAD_LEFT, 0 });
	input.AddInputAction(InputAction{ Input::P1_Right, XINPUT_GAMEPAD_DPAD_RIGHT, 0 });
}

void PacmanActor::Update(const GameTime& time)
{
	InputManager& input = InputManager::GetInstance();

	if (input.IsActionTriggered(Input::P1_Up))
		Move(Vector2{ 0.0f, 1.0f } * time.GetElapsedTime() * m_Speed);

	else if (input.IsActionTriggered(Input::P1_Down))
		Move(Vector2{ 0.0f, -1.0f } * time.GetElapsedTime() * m_Speed);

	else if (input.IsActionTriggered(Input::P1_Left))
		Move(Vector2{ -1.0f, 0.0f } * time.GetElapsedTime() * m_Speed);

	else if (input.IsActionTriggered(Input::P1_Right))
		Move(Vector2{ 1.0f, 0.0f } * time.GetElapsedTime() * m_Speed);
}

void PacmanActor::Draw() const
{
}

void PacmanActor::SetSize(float size)
{
	ShapeComponent* pShape = GetComponent<ShapeComponent>();

	if (pShape)
		pShape->SetDimensions(size, size);
}

void PacmanActor::SetSpeed(float speed)
{
	m_Speed = speed;
}

void PacmanActor::Move(const Vector2& displacement)
{
	Vector2 flipped = { displacement.x, displacement.y * -1.0f };
	Vector2 pos = GetTransform()->GetPosition();
	pos += flipped;
	GetTransform()->Translate(pos);
}