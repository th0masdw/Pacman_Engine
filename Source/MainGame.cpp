#include "MiniginPCH.h"
#include "MainGame.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Managers/SceneManager.h"
#include "Engine/Managers/ResourceManager.h"
#include "Engine/Managers/InputManager.h"
#include "Engine/Managers/EventManager.h"

#include "Game/Scenes/PacmanScene.h"

MainGame::MainGame()
	: m_pWindow{},
	m_WindowSettings{},
	m_GameTime{}
{
}

MainGame::~MainGame()
{
	Renderer::GetInstance().Destroy();
	SceneManager::GetInstance().Destroy();
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void MainGame::Initialize() 
{
	InitWindow();

	Renderer::GetInstance().Init(m_pWindow);
	ResourceManager::GetInstance().Init();
	EventManager::GetInstance().Init();
	Debug::Initialize();
}

void MainGame::Run() 
{
	LoadGame();
	m_GameTime.Start();

	Renderer& renderer = Renderer::GetInstance();
	SceneManager& sceneManager = SceneManager::GetInstance();
	InputManager& input = InputManager::GetInstance();
	bool doContinue = true;

	while(doContinue)  {
		m_GameTime.Update();
		doContinue = input.Update();
		sceneManager.Update(m_GameTime);

		renderer.Draw();
	}
}

void MainGame::InitWindow() 
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));

	m_pWindow = SDL_CreateWindow(
		m_WindowSettings.Name.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_WindowSettings.Width,                    
		m_WindowSettings.Height,                    
		SDL_WINDOW_OPENGL       
	);

	if (m_pWindow == nullptr)
		throw std::runtime_error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
}

void MainGame::LoadGame() 
{
	SceneManager::GetInstance().CreateScene(new PacmanScene());
}