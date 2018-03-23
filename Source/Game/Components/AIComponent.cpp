#include "MiniginPCH.h"
#include "AIComponent.h"
#include "Engine/Helpers/Window.h"
#include "Game/Gameplay/Actors/PacmanActor.h"

AIComponent::AIComponent(PacmanActor* pPacman, float speed)
	: m_pPacman(pPacman),
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

	MoveToTarget(time.GetElapsedTime());
	CheckIfTargetReached();
}

void AIComponent::Draw() const
{
	m_PathSolver.GetGridCopy().Draw();
}

void AIComponent::UpdatePath()
{
	m_Path.clear();
	glm::vec2 pos = GetGameObject()->GetTransform()->GetPosition();
	m_PathSolver.GetPath(pos, m_pPacman->GetTransform()->GetPosition(), m_Path);
}

void AIComponent::MoveToTarget(float deltaTime)
{
	glm::vec2 direction = GetDirection() * deltaTime * m_Speed;

	glm::vec2 pos = m_pGameObject->GetTransform()->GetPosition();
	pos += direction;
	m_pGameObject->GetTransform()->Translate(pos);
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

	return dir;
}