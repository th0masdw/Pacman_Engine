#include "MiniginPCH.h"
#include "MainGame.h"

#include "Engine/Managers/SceneManager.h"
#include "Engine/Managers/ResourceManager.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Managers/InputManager.h"
#include "Engine/Managers/EventManager.h"

#include "Game/Scenes/PacmanScene.h"

#define MAX_ELAPSED_TIME 0.1f
WindowSettings MainGame::WindowSettings{};

MainGame::MainGame()
	: m_pWindow{}
{
}

MainGame::~MainGame()
{
	Renderer::GetInstance().Destroy();
	SceneManager::GetInstance().Destroy();
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void MainGame::Initialize() {
	InitWindow();

	Renderer::GetInstance().Init(m_pWindow);
	ResourceManager::GetInstance().Init();
	EventManager::GetInstance().Init();
	Debug::Initialize();
}

void MainGame::Run() {
	LoadGame();

	m_GameTime = chrono::high_resolution_clock::now();
	Renderer& renderer = Renderer::GetInstance();
	SceneManager& sceneManager = SceneManager::GetInstance();
	InputManager& input = InputManager::GetInstance();
	bool doContinue = true;

	while(doContinue)  {
		auto now = chrono::high_resolution_clock::now();
		auto timeSpan = chrono::duration_cast<std::chrono::duration<float>>(now - m_GameTime);
		float elapsedTime = timeSpan.count();
		m_GameTime = now;

		// Prevent jumps in time caused by break points
		elapsedTime = Min(elapsedTime, MAX_ELAPSED_TIME);

		doContinue = input.Update();

		sceneManager.Update(elapsedTime);
		renderer.Draw();
	}
}

void MainGame::InitWindow() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw runtime_error("SDL_Init Error: " + string(SDL_GetError()));

	m_pWindow = SDL_CreateWindow(
		WindowSettings.Name.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WindowSettings.Width,                    
		WindowSettings.Height,                    
		SDL_WINDOW_OPENGL       
	);

	if (m_pWindow == nullptr)
		throw runtime_error("SDL_CreateWindow Error: " + string(SDL_GetError()));
}

void MainGame::LoadGame() {
	SceneManager::GetInstance().CreateScene(new PacmanScene());
}