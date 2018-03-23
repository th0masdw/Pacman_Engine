#include "MiniginPCH.h"
#include "AIComponent.h"
#include "Engine/Helpers/Window.h"
#include "Game/Gameplay/Actors/PacmanActor.h"

AIComponent::AIComponent(PacmanActor* pPacman)
	: m_PathSolver(Window::GetGridWidth(), Window::GetGridHeight()),
	m_pPacman(pPacman)
{
}

void AIComponent::PostInitialize()
{
	m_PathSolver.GetGridRef().PostInitialize();
}

void AIComponent::Update(const GameTime& time)
{
	UNREFERENCED_PARAMETER(time);

	m_Path.clear();
	glm::vec2 pos = GetGameObject()->GetTransform()->GetPosition();
	m_PathSolver.GetPath(pos, m_pPacman->GetTransform()->GetPosition(), m_Path);
}

void AIComponent::Draw() const
{
	m_PathSolver.GetGridCopy().Draw();
}