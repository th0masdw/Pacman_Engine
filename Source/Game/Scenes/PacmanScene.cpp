#include "MiniginPCH.h"
#include "PacmanScene.h"
#include "Game/Gameplay/Actors/PacmanActor.h"

PacmanScene::PacmanScene()
	: GameScene("PacmanScene"),
	m_pPlayer(nullptr)
{
	Initialize();
}

PacmanScene::~PacmanScene()
{
}

void PacmanScene::Initialize()
{
	m_pPlayer = new PacmanActor();
	m_pPlayer->SetPosition({ 100.0f, 100.0f });
	m_pPlayer->SetDimensions(30.0f, 30.0f);
	m_pPlayer->SetColor({ 255.0f, 255.0f, 0.0f, 255.0f });
	m_pPlayer->SetSpeed(100.0f);

	AddObject(m_pPlayer);
}

void PacmanScene::Update(float deltaTime) 
{
	GameScene::Update(deltaTime);
}

void PacmanScene::Draw() const 
{
	GameScene::Draw();
}