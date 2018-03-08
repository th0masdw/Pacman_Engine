#include "MiniginPCH.h"
#include "MainGame.h"

#include "ResourceManager.h"
#include "Renderer.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"

#include "Scene.h"
#include "TextureObject.h"
#include "TextObject.h"

#define MS_PER_FRAME 16		//16: 60 FPS, 33: 30 FPS
WindowSettings MainGame::WindowSettings{};

MainGame::MainGame()
	: m_pWindow{}
{
}

MainGame::~MainGame()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void MainGame::Initialize() {
	InitWindow();

	Renderer::GetInstance().Init(m_pWindow);
	ResourceManager::GetInstance().Init("../Resources/");
}

void MainGame::Run() {
	LoadGame();

	auto t = std::chrono::high_resolution_clock::now();
	Renderer& renderer = Renderer::GetInstance();
	SceneManager& sceneManager = SceneManager::GetInstance();
	InputManager& input = InputManager::GetInstance();
	bool doContinue = true;

	while(doContinue)  {
		doContinue = input.ProcessInput();

		sceneManager.Update();
		renderer.Draw();

		t += std::chrono::milliseconds(MS_PER_FRAME);
		std::this_thread::sleep_until(t);
	}
}

void MainGame::InitWindow() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::stringstream ss; ss << "SDL_Init Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	m_pWindow = SDL_CreateWindow(
		WindowSettings.Name.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WindowSettings.Width,                    
		WindowSettings.Height,                    
		SDL_WINDOW_OPENGL       
	);

	if (m_pWindow == nullptr) {
		std::stringstream ss; ss << "SDL_CreateWindow Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}
}

void MainGame::LoadGame() {
	Scene& scene = SceneManager::GetInstance().CreateScene("Demo");
	
	std::shared_ptr<TextureObject> pTextureObject = std::make_shared<TextureObject>();
	pTextureObject->SetTexture("background.jpg");
	scene.Add(pTextureObject);

	pTextureObject = std::make_shared<TextureObject>();
	pTextureObject->SetTexture("logo.png");
	pTextureObject->SetPosition(216, 180);
	scene.Add(pTextureObject);

	std::shared_ptr<Font> pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	std::shared_ptr<TextObject> pTextObject = std::make_shared<TextObject>("Programming 4 Assignment", pFont);
	pTextObject->SetPosition(80, 20);
	scene.Add(pTextObject);
}