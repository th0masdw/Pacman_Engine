#pragma once

#include "Engine/Components/CharacterController.h"
#include "Engine/Algorithms/Astar/Solver.h"
#include "Engine/Helpers/Thread.h"
class GhostActor;
class PacmanActor;

class AIComponent : public CharacterController
{
public:
	AIComponent(GhostActor* pGhost, PacmanActor* pPacman, float speed = 50.0f);
	virtual ~AIComponent();

	void Reset();
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
	enum class State
	{
		Wandering,
		Chasing,
		Scared
	};

	//Thread m_NavigationThread;

	GhostActor* m_pGhost;
	PacmanActor* m_pPacman;
	float m_Speed;

	State m_State;
	float m_ChaseRadius;
	std::vector<glm::vec2> m_Directions;

	std::list<Node> m_Path;
	Solver m_PathSolver;
	glm::vec2 m_CurrentTarget;

	void UpdateState();
	void UpdatePath();
	void CheckIfTargetReached();
	void HandlePlayerHit();

	glm::vec2 GetNextTarget();
	glm::vec2 GetDirection() const;
	glm::vec2 GetWanderPos() const;
	glm::vec2 GetScaredPos() const;
	glm::vec2 GetRandomPosFromDirections(const std::vector<glm::vec2>& directions) const;
};