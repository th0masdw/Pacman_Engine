#pragma once

#include "SDL.h"
#include "Engine/Helpers/Structs.h"
#include "Engine/Helpers/GameTime.h"

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
	WindowSettings m_WindowSettings;
	GameTime m_GameTime;

	void InitWindow();
	void LoadGame();
};