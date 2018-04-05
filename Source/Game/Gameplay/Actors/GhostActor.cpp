#include "MiniginPCH.h"
#include "GhostActor.h"
#include "Engine/Components/ShapeComponent.h"
#include "Engine/Components/ColliderComponent.h"
#include "Game/Components/AIComponent.h"
#include "Game/Gameplay/Actors/PacmanActor.h"
#include "Engine/Managers/InputManager.h"
#include "Game/Components/GhostController.h"
#include "Engine/Managers/EventManager.h"

GhostActor::GhostActor(PacmanActor* pPacman, float size, float speed, const Color& color, const glm::vec2& ghostHouse, bool isPlayerControlled)
	: GameObject{ Tag::Enemy, Layer::Characters },
	m_Color(color),
	m_IsPlayerControlled(isPlayerControlled),
	m_pAI(nullptr),
	m_pController(nullptr),
	m_Direction(0, 0),
	m_GhostHouse(ghostHouse),
	m_IsScared(false)
{
	m_pShape = new ShapeComponent(size, size, color);
	AddComponent(m_pShape);

	ColliderComponent* pCollider = new ColliderComponent(size, size, false);
	AddComponent(pCollider);

	SetupBehaviour(pPacman, speed);

	//Events
	EventManager::GetInstance().StartListening(Event::EatPower(), "EatPowerActorCB", [this]() { GetScared(true); });
	EventManager::GetInstance().StartListening(Event::LostPower(), "LostPowerActorCB", [this]() { GetScared(false); });
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

void GhostActor::Respawn()
{
	GetTransform()->Translate(m_GhostHouse);

	if (m_pAI)
		m_pAI->Reset();
}

bool GhostActor::IsScared() const
{
	return m_IsScared;
}

void GhostActor::SetupBehaviour(PacmanActor* pActor, float speed)
{
	if (!m_IsPlayerControlled) {
		m_pAI = new AIComponent(this, pActor, speed);
		AddComponent(m_pAI);
	} else {
		m_pController = new GhostController(this, speed);
		AddComponent(m_pController);

		//Input
		InputManager& input = InputManager::GetInstance();
		input.AddInputAction(InputAction{ Input::P2_Up, SDL_SCANCODE_W, 1, false });
		input.AddInputAction(InputAction{ Input::P2_Down, SDL_SCANCODE_S, 1, false });
		input.AddInputAction(InputAction{ Input::P2_Left, SDL_SCANCODE_A, 1, false });
		input.AddInputAction(InputAction{ Input::P2_Right, SDL_SCANCODE_D, 1, false });
	}
}

void GhostActor::GetScared(bool value)
{
	m_IsScared = value;

	Color newColor = (m_IsScared) ? Color{ 255, 255, 255, 255 } : m_Color;
	m_pShape->SetColor(newColor);
}