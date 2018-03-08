#include "MiniginPCH.h"
#include "MainGame.h"

#include "Engine/Managers/ResourceManager.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Managers/InputManager.h"
#include "Engine/Managers/EventManager.h"

#include "Engine/Scenegraph/Scene.h"
#include "Engine/Scenegraph/TextureObject.h"
#include "Engine/Scenegraph/TextObject.h"
#include "Engine/Scenegraph/RectangleObject.h"
#include "Engine/Helpers/Structs.h"

#define MS_PER_FRAME 16		//16: 60 FPS, 33: 30 FPS
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
		auto t = chrono::high_resolution_clock::now();
		auto timeSpan = chrono::duration_cast<std::chrono::duration<float>>(t - m_GameTime);
		float elapsedTime = timeSpan.count();
		m_GameTime = t;

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
	Scene& scene = SceneManager::GetInstance().CreateScene("Test");

	RectangleObject* pRect = new RectangleObject{};
	pRect->SetPosition({ 100, 100 });
	pRect->SetDimensions(50, 50);
	pRect->SetColor({ 0, 255, 255, 255 });
	scene.Add(pRect);
	
	/*TextureObject* pTextureObject = new TextureObject();
	pTextureObject->SetTexture("../Resources/background.jpg");
	scene.Add(pTextureObject);

	pTextureObject = new TextureObject();
	pTextureObject->SetTexture("../Resources/logo.png");
	pTextureObject->SetPosition(216, 180);
	scene.Add(pTextureObject);

	shared_ptr<Font> pFont = ResourceManager::GetInstance().LoadFont("../Resources/Lingua.otf", 36);
	TextObject* pTextObject = new TextObject("Programming 4 Assignment", pFont);
	pTextObject->SetPosition(80, 20);
	scene.Add(pTextObject);*/
}