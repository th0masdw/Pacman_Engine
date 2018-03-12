#include "MiniginPCH.h"
#include "PacmanActor.h"
#include "Engine/Managers/InputManager.h"

PacmanActor::PacmanActor(float width, float height, const Color& color, float speed)
	: Actor(width, height, color, speed)
{
	Initialize();
}

void PacmanActor::Initialize()
{
	//player index member that binds different actions
	InputManager::GetInstance().AddInputAction(InputAction{ Input::P1_Up, XINPUT_GAMEPAD_DPAD_UP, 0 });
	InputManager::GetInstance().AddInputAction(InputAction{ Input::P1_Down, XINPUT_GAMEPAD_DPAD_DOWN, 0 });
	InputManager::GetInstance().AddInputAction(InputAction{ Input::P1_Left, XINPUT_GAMEPAD_DPAD_LEFT, 0 });
	InputManager::GetInstance().AddInputAction(InputAction{ Input::P1_Right, XINPUT_GAMEPAD_DPAD_RIGHT, 0 });
}

void PacmanActor::Update(float deltaTime)
{
	InputManager& input = InputManager::GetInstance();

	if (input.IsActionTriggered(Input::P1_Up))
		Move(Vector2{ 0.0f, 1.0f } * deltaTime);

	if (input.IsActionTriggered(Input::P1_Down))
		Move(Vector2{ 0.0f, -1.0f } * deltaTime);

	if (input.IsActionTriggered(Input::P1_Left))
		Move(Vector2{ -1.0f, 0.0f } * deltaTime);

	if (input.IsActionTriggered(Input::P1_Right))
		Move(Vector2{ 1.0f, 0.0f } * deltaTime);
}