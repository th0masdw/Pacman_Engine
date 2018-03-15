#include "MiniginPCH.h"
#include "GameTime.h"

GameTime::GameTime()
	: m_TotalTime(0.0f),
	m_ElapsedTime(0.0f),
	m_FPS(0),
	m_FPSTimer(0.0f),
	m_FPSCount(0),
	m_MaxElapsedTime(0.1f)
{
}

void GameTime::Start() 
{
	m_GameTime = std::chrono::high_resolution_clock::now();
}

void GameTime::Update() 
{
	auto now = std::chrono::high_resolution_clock::now();
	auto timeSpan = std::chrono::duration_cast<std::chrono::duration<float>>(now - m_GameTime);
	
	m_ElapsedTime = timeSpan.count();
	m_ElapsedTime = Min(m_ElapsedTime, m_MaxElapsedTime);

	m_TotalTime += m_ElapsedTime;
	m_GameTime = now;

	//FPS
	m_FPSTimer += m_ElapsedTime;
	++m_FPSCount;

	if (m_FPSTimer >= 1.0f) {
		m_FPS = m_FPSCount;
		m_FPSCount = 0;
		m_FPSTimer -= 1.0f;
	}
}

void GameTime::SetMaxElapsedTime(float time) 
{
	m_MaxElapsedTime = time;
}

float GameTime::GetTotalTime() const 
{
	return m_TotalTime;
}

float GameTime::GetElapsedTime() const 
{
	return m_ElapsedTime;
}

int GameTime::GetFPS() const 
{
	return m_FPS;
}
