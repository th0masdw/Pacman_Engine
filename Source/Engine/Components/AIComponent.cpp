#include "MiniginPCH.h"
#include "AIComponent.h"
#include "Engine/Helpers/Window.h"

AIComponent::AIComponent()
	: m_PathSolver(Window::GetGridSize())
{
}

void AIComponent::PostInitialize()
{
	m_PathSolver.GetGridRef().PostInitialize();
}

void AIComponent::Update(const GameTime& time)
{
	UNREFERENCED_PARAMETER(time);

	//update path
}

void AIComponent::Draw() const
{
	m_PathSolver.GetGridCopy().Draw();
}