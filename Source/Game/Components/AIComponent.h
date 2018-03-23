#pragma once

#include "Engine/Components/BaseComponent.h"
#include "Engine/Algorithms/Astar/Solver.h"
class PacmanActor;

class AIComponent : public BaseComponent
{
public:
	AIComponent(PacmanActor* pPacman);
	virtual ~AIComponent() = default;

	AIComponent(const AIComponent& other) = delete;
	AIComponent(AIComponent&& other) = delete;
	AIComponent& operator=(const AIComponent& other) = delete;
	AIComponent& operator=(AIComponent&& other) = delete;

protected:
	virtual void PostInitialize() override;
	virtual void Update(const GameTime& time) override;
	virtual void Draw() const override;

private:
	std::list<Node> m_Path;
	Solver m_PathSolver;

	PacmanActor* m_pPacman;
};