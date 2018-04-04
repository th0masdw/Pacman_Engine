#include "MiniginPCH.h"
#include "AIComponent.h"
#include "Engine/Helpers/Window.h"
#include "Engine/Managers/PhysicsManager.h"
#include "Game/Gameplay/Actors/GhostActor.h"
#include "Game/Gameplay/Actors/PacmanActor.h"
#include "Engine/Managers/EventManager.h"
#include "Engine/Graphics/Renderer.h"

AIComponent::AIComponent(GhostActor* pGhost, PacmanActor* pPacman, float speed)
	: CharacterController(speed),
	m_pGhost(pGhost),
	m_pPacman(pPacman),
	m_Speed(speed),
	m_State(State::Wandering),
	m_ChaseRadius(300.0f),
	m_PathSolver(Window::GetGridWidth(), Window::GetGridHeight()),
	m_CurrentTarget(0, 0)
{
	m_Directions = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

	//Events
	EventManager::GetInstance().StartListening("EatPower", "EatPowerAICB", [this]() { m_State = State::Scared; });
	EventManager::GetInstance().StartListening("LostPower", "LostPowerAICB", [this]() { 
		m_State = State::Wandering;
		m_Path.clear();
	});
}

void AIComponent::PostInitialize()
{
	m_PathSolver.GetGridRef().PostInitialize();
}

void AIComponent::Update(const GameTime& time)
{
	UpdateState();
	UpdatePath();

	if (HasZeroMagnitude(m_CurrentTarget)) {
		m_CurrentTarget = GetNextTarget();

		if (HasZeroMagnitude(m_CurrentTarget))
			return;
	}

	CheckCollision({});
	Move(GetDirection() * time.GetElapsedTime());
	CheckIfTargetReached();

	//Debug::Log(std::to_string(static_cast<int>(m_State)));
}

void AIComponent::Draw() const
{
	//m_PathSolver.GetGridCopy().Draw();

	//Draw chase radius
	if (Debug::IsDebugRenderingEnabled()) {
		glm::vec2 pos = m_pGameObject->GetTransform()->GetPosition();
		glm::vec2 center = { pos.x - m_ChaseRadius, pos.y - m_ChaseRadius };

		Renderer::GetInstance().RenderRect(center, m_ChaseRadius * 2, m_ChaseRadius * 2, { 255, 0, 0, 50 });
	}
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

void AIComponent::UpdateState()
{
	if (m_State != State::Scared) {
		glm::vec2 ghostPos = m_pGameObject->GetTransform()->GetPosition();
		glm::vec2 playerPos = m_pPacman->GetTransform()->GetPosition();

		if (Distance(ghostPos, playerPos) < m_ChaseRadius)
			m_State = State::Chasing;
		else
			m_State = State::Wandering;
	}
}

void AIComponent::UpdatePath()
{
	glm::vec2 startPos = GetGameObject()->GetTransform()->GetPosition();
	glm::vec2 endPos = {};
	
	switch (m_State) {
		case State::Wandering:
			endPos = GetWanderPos();
			break;

		case State::Chasing:
			m_Path.clear();
			endPos = m_pPacman->GetTransform()->GetPosition();
			break;

		case State::Scared:
			endPos = GetScaredPos();
			break;
	}
	
	m_PathSolver.GetPath(startPos, endPos, m_Path);
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

glm::vec2 AIComponent::GetWanderPos() const
{
	if (m_Path.size() > 0)
		return m_Path.back().GetPosition();

	return GetRandomPosFromDirections(m_Directions);
}

glm::vec2 AIComponent::GetScaredPos() const
{
	if (m_Path.size() > 0)
		return m_Path.front().GetPosition();

	//Determine direction ghost should avoid
	glm::vec2 pacmanPos = m_pPacman->GetTransform()->GetPosition();
	glm::vec2 ghostPos = m_pGameObject->GetTransform()->GetPosition();

	glm::vec2 pacmanDir = pacmanPos - ghostPos;
	glm::vec2 forbidDir;

	if (abs(pacmanDir.x) > abs(pacmanDir.y) || abs(pacmanDir.y) <= FLT_EPSILON)
		forbidDir = { pacmanDir.x, 0.0f };
	else if (abs(pacmanDir.x) <= abs(pacmanDir.y) || abs(pacmanDir.x) <= FLT_EPSILON)
		forbidDir = { 0.0f, pacmanDir.y };
	else
		forbidDir = { 0, 1 };	//Default

	Normalize(forbidDir);
	
	//Build allowed directions vector
	std::vector<glm::vec2> directions;
	for (UINT i = 0; i < m_Directions.size(); ++i) {
		if (!AreEqual(m_Directions[i], forbidDir))
			directions.emplace_back(m_Directions[i]);
	}

	//Debug::Log(std::to_string(directions.size()));
	return GetRandomPosFromDirections(directions);
}

void AIComponent::HandlePlayerHit()
{
	if (m_pGhost->IsScared()) {
		m_Path.clear();
		m_CurrentTarget = {};
		m_pGhost->Respawn();
	}	
}

glm::vec2 AIComponent::GetRandomPosFromDirections(const std::vector<glm::vec2>& directions) const
{
	int x, y;
	glm::vec2 currentPos = m_pGameObject->GetTransform()->GetPosition();
	Grid grid = m_PathSolver.GetGridCopy();
	grid.ToIndexPos(currentPos, x, y);
	int chaseRadius = static_cast<int>(m_ChaseRadius / grid.GetTileSize());

	glm::vec2 newPos = {};
	int randIndex = 0;
	
	while (HasZeroMagnitude(newPos)) {
		randIndex = rand() % directions.size();
		int newX = x + static_cast<int>(directions[randIndex].x) * rand() % chaseRadius + 1;
		int newY = y + static_cast<int>(directions[randIndex].y) * rand() % chaseRadius + 1;

		if (!grid.IsObstacle({ newX, newY })) {
			newPos = { newX, newY };
			break;
		}
	}

	return newPos * grid.GetTileSize();
}