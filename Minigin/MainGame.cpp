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
#include "RectangleObject.h"
#include "Structs.h"

#define MS_PER_FRAME 16		//16: 60 FPS, 33: 30 FPS
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
	ResourceManager::GetInstance().Init("../Resources/");
	Debug::Initialize();
}

void MainGame::Run() {
	LoadGame();

	auto t = chrono::high_resolution_clock::now();
	Renderer& renderer = Renderer::GetInstance();
	SceneManager& sceneManager = SceneManager::GetInstance();
	InputManager& input = InputManager::GetInstance();
	bool doContinue = true;

	while(doContinue)  {
		doContinue = input.ProcessInput();

		sceneManager.Update();
		renderer.Draw();

		t += chrono::milliseconds(MS_PER_FRAME);
		this_thread::sleep_until(t);
	}
}

void MainGame::InitWindow() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		stringstream ss; ss << "SDL_Init Error: " << SDL_GetError();
		throw runtime_error(ss.str().c_str());
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
		stringstream ss; ss << "SDL_CreateWindow Error: " << SDL_GetError();
		throw runtime_error(ss.str().c_str());
	}
}

void MainGame::LoadGame() {
	Scene& scene = SceneManager::GetInstance().CreateScene("Test");

	RectangleObject* pRect = new RectangleObject{};
	pRect->SetPosition({ 100, 100 });
	pRect->SetDimensions(50, 50);
	pRect->SetColor({ 0, 255, 255, 255 });
	scene.Add(pRect);
	
	/*shared_ptr<TextureObject> pTextureObject = make_shared<TextureObject>();
	pTextureObject->SetTexture("background.jpg");
	scene.Add(pTextureObject);

	pTextureObject = make_shared<TextureObject>();
	pTextureObject->SetTexture("logo.png");
	pTextureObject->SetPosition(216, 180);
	scene.Add(pTextureObject);

	shared_ptr<Font> pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	shared_ptr<TextObject> pTextObject = make_shared<TextObject>("Programming 4 Assignment", pFont);
	pTextObject->SetPosition(80, 20);
	scene.Add(pTextObject);*/
}