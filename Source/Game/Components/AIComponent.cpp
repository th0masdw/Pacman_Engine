#include "MiniginPCH.h"
#include "AIComponent.h"
#include "Engine/Helpers/Window.h"
#include "Engine/Managers/PhysicsManager.h"
#include "Game/Gameplay/Actors/GhostActor.h"
#include "Game/Gameplay/Actors/PacmanActor.h"

AIComponent::AIComponent(GhostActor* pGhost, PacmanActor* pPacman, float speed)
	: CharacterController(speed),
	m_pGhost(pGhost),
	m_pPacman(pPacman),
	m_Speed(speed),
	m_PathSolver(Window::GetGridWidth(), Window::GetGridHeight()),
	m_CurrentTarget(0, 0)
{
}

void AIComponent::PostInitialize()
{
	m_PathSolver.GetGridRef().PostInitialize();
}

void AIComponent::Update(const GameTime& time)
{
	UpdatePath();

	if (HasZeroMagnitude(m_CurrentTarget.x, m_CurrentTarget.y)) {
		m_CurrentTarget = GetNextTarget();

		if (HasZeroMagnitude(m_CurrentTarget.x, m_CurrentTarget.y))
			return;
	}

	CheckCollision({});
	Move(GetDirection() * time.GetElapsedTime());
	CheckIfTargetReached();
}

void AIComponent::Draw() const
{
	m_PathSolver.GetGridCopy().Draw();
}

void AIComponent::CheckCollision(const glm::vec2& direction)
{
	UNREFERENCED_PARAMETER(direction);

	GameObject* pCollision = PhysicsManager::GetInstance().DoesCollide(m_pGameObject);
	
	if (pCollision) {
		switch (pCollision->GetTag()) {
			case Tag::Player:
				HandlePlayerHit();
				break;
		}
	}
}

void AIComponent::UpdatePath()
{
	m_Path.clear();
	glm::vec2 pos = GetGameObject()->GetTransform()->GetPosition();
	m_PathSolver.GetPath(pos, m_pPacman->GetTransform()->GetPosition(), m_Path);
}

void AIComponent::CheckIfTargetReached()
{
	glm::vec2 pos = m_pGameObject->GetTransform()->GetPosition();
	float tileSize = m_PathSolver.GetGridCopy().GetTileSize();

	if (abs(pos.x - m_CurrentTarget.x) <= tileSize * 0.25f &&
		abs(pos.y - m_CurrentTarget.y) <= tileSize * 0.25f) {
		m_CurrentTarget = {};
	}
}

glm::vec2 AIComponent::GetNextTarget()
{
	glm::vec2 pos = {};

	if (!m_Path.empty()) {
		float tileSize = m_PathSolver.GetGridCopy().GetTileSize();
		pos = m_Path.front().GetPosition();
		pos.x = tileSize * 0.5f + (pos.x * tileSize);
		pos.y = tileSize * 0.5f + (pos.y * tileSize);

		m_Path.pop_front();
	}
	return pos;
}

glm::vec2 AIComponent::GetDirection() const
{
	glm::vec2 dir = m_CurrentTarget - m_pGameObject->GetTransform()->GetPosition();
	float magnitude = std::sqrt(std::pow(dir.x, 2) + std::pow(dir.y, 2));
	dir.x /= magnitude;
	dir.y /= magnitude;
	dir.y *= -1.0f;

	return dir;
}

void AIComponent::HandlePlayerHit()
{
	if (m_pGhost->IsScared()) {
		m_Path.clear();
		m_CurrentTarget = {};
		m_pGhost->Respawn();
	}	
}