#pragma once

#include "SDL.h"
#include "Structs.h"
#include <chrono>

class MainGame
{
public:
	MainGame();
	~MainGame();

	void Initialize();
	void Run();

	MainGame(const MainGame& other) = delete;
	MainGame(MainGame&& other) = delete;
	MainGame& operator=(const MainGame& other) = delete;
	MainGame& operator=(MainGame&& other) = delete;

private:
	static WindowSettings WindowSettings;
	SDL_Window* m_pWindow;
	std::chrono::high_resolution_clock::time_point m_GameTime;

	void InitWindow();
	void LoadGame();
};