#include "MiniginPCH.h"
#include "GhostActor.h"
#include "Engine/Components/ShapeComponent.h"
#include "Engine/Components/ColliderComponent.h"
#include "Engine/Components/CharacterController.h"
#include "Game/Components/AIComponent.h"
#include "Game/Gameplay/Actors/PacmanActor.h"
#include "Engine/Managers/InputManager.h"

GhostActor::GhostActor(PacmanActor* pPacman, float size, float speed, const Color& color, bool isPlayerControlled)
	: GameObject{ Tag::Enemy, Layer::Characters },
	m_IsPlayerControlled(isPlayerControlled),
	m_pController(nullptr),
	m_Direction(0, 0)
{
	ShapeComponent* pShape = new ShapeComponent(size, size, color);
	AddComponent(pShape);

	ColliderComponent* pCollider = new ColliderComponent(size, size, false);
	AddComponent(pCollider);

	SetupBehaviour(pPacman, speed);
}

void GhostActor::Update(const GameTime& time)
{
	if (m_IsPlayerControlled) {
		m_pController->CheckCollision(m_Direction * time.GetElapsedTime());

		//Input
		InputManager& input = InputManager::GetInstance();

		if (input.IsActionTriggered(Input::P2_Up))
			m_Direction = glm::vec2{ 0.0f, 1.0f };

		else if (input.IsActionTriggered(Input::P2_Down))
			m_Direction = glm::vec2{ 0.0f, -1.0f };

		else if (input.IsActionTriggered(Input::P2_Left))
			m_Direction = glm::vec2{ -1.0f, 0.0f };

		else if (input.IsActionTriggered(Input::P2_Right))
			m_Direction = glm::vec2{ 1.0f, 0.0f };

		m_pController->Move(m_Direction * time.GetElapsedTime());
	}
}

void GhostActor::Draw() const
{
}

void GhostActor::SetupBehaviour(PacmanActor* pActor, float speed)
{
	if (!m_IsPlayerControlled) {
		AIComponent* pAI = new AIComponent(pActor, speed);
		AddComponent(pAI);
	} else {
		m_pController = new CharacterController(speed);
		AddComponent(m_pController);

		//Input
		InputManager& input = InputManager::GetInstance();
		input.AddInputAction(InputAction{ Input::P2_Up, SDL_SCANCODE_W, 1, false });
		input.AddInputAction(InputAction{ Input::P2_Down, SDL_SCANCODE_S, 1, false });
		input.AddInputAction(InputAction{ Input::P2_Left, SDL_SCANCODE_A, 1, false });
		input.AddInputAction(InputAction{ Input::P2_Right, SDL_SCANCODE_D, 1, false });
	}
}