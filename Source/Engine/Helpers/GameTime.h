#pragma once

#include <chrono>

class GameTime
{
public:
	GameTime();
	~GameTime() = default;

	void Start();
	void Update();
	void SetMaxElapsedTime(float time);

	float GetTotalTime() const;
	float GetElapsedTime() const;
	int GetFPS() const;

	GameTime(const GameTime& other) = delete;
	GameTime(GameTime&& other) = delete;
	GameTime& operator=(const GameTime& other) = delete;
	GameTime& operator=(GameTime&& other) = delete;

private:
	float m_TotalTime;
	float m_ElapsedTime;
	int m_FPS;

	float m_FPSTimer;
	int m_FPSCount;
	float m_MaxElapsedTime;
	std::chrono::high_resolution_clock::time_point m_GameTime;
};