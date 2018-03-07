#pragma once

#include "SDL.h"

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
	SDL_Window* m_pWindow;

	void InitWindow();
	void LoadGame();
};