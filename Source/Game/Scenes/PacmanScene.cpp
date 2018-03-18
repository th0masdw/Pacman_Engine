#include "MiniginPCH.h"
#include "PacmanScene.h"

#include "Engine/Scenegraph/GameObject.h"
#include "Engine/Components/Components.h"
#include "Game/Gameplay/Actors/PacmanActor.h"
#include "Game/Gameplay/Objects/Wall.h"

PacmanScene::PacmanScene()
	: GameScene("PacmanScene"),
	m_pFPSCounter(nullptr),
	m_pPlayer(nullptr),
	m_pWall(nullptr)
{
	Initialize();
}

PacmanScene::~PacmanScene()
{
}

void PacmanScene::Initialize()
{
	//FPS Counter
	GameObject* pFPS = new GameObject();
	m_pFPSCounter = new TextComponent("FPS", { 0.0f, 255.0f, 0.0f, 255.0f }, "../Resources/Lingua.otf", 20);
	pFPS->AddComponent(m_pFPSCounter);
	pFPS->GetTransform()->Translate(20.0f, 20.0f);
	AddObject(pFPS);

	//Player
	m_pPlayer = new PacmanActor(25.0f, 200.0f);
	m_pPlayer->GetTransform()->Translate(400.0f, 200.0f);
	AddObject(m_pPlayer);

	//Walls
	m_pWall = new Wall(30.0f, 200.0f, { 0.0f, 0.0f, 255.0f, 255.0f });
	m_pWall->GetTransform()->Translate(200.0f, 200.0f);
	AddObject(m_pWall);

	m_pWall = new Wall(200.0f, 30.0f, { 0.0f, 0.0f, 255.0f, 255.0f });
	m_pWall->GetTransform()->Translate(300.0f, 300.0f);
	AddObject(m_pWall);
}

void PacmanScene::Update(const GameTime& time) 
{
	m_pPlayer->Update(time);
	m_pFPSCounter->SetText(std::to_string(time.GetFPS()), { 0.0f, 255.0f, 0.0f, 255.0f });

	GameScene::Update(time);
}

void PacmanScene::Draw() const 
{
	GameScene::Draw();
}