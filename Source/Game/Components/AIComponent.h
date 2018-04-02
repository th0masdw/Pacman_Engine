#pragma once

#include "Engine/Components/CharacterController.h"
#include "Engine/Algorithms/Astar/Solver.h"
class GhostActor;
class PacmanActor;

class AIComponent : public CharacterController
{
public:
	AIComponent(GhostActor* pGhost, PacmanActor* pPacman, float speed = 50.0f);
	virtual ~AIComponent() = default;

	virtual void CheckCollision(const glm::vec2& direction) override;

	AIComponent(const AIComponent& other) = delete;
	AIComponent(AIComponent&& other) = delete;
	AIComponent& operator=(const AIComponent& other) = delete;
	AIComponent& operator=(AIComponent&& other) = delete;

protected:
	virtual void PostInitialize() override;
	virtual void Update(const GameTime& time) override;
	virtual void Draw() const override;

private:
	GhostActor* m_pGhost;
	PacmanActor* m_pPacman;
	float m_Speed;

	std::list<Node> m_Path;
	Solver m_PathSolver;
	glm::vec2 m_CurrentTarget;

	void UpdatePath();
	void CheckIfTargetReached();
	glm::vec2 GetNextTarget();
	glm::vec2 GetDirection() const;
	void HandlePlayerHit();
};