#include "MiniginPCH.h"
#include "PacmanScene.h"
#include "Game/Gameplay/Actors/PacmanActor.h"
#include "Engine/Scenegraph/RectangleObject.h"

PacmanScene::PacmanScene()
	: GameScene("PacmanScene"),
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
	m_pPlayer = new PacmanActor();
	m_pPlayer->GetTransform()->Translate(400.0f, 200.0f);
	m_pPlayer->SetDimensions(30.0f, 30.0f);
	m_pPlayer->SetColor({ 255.0f, 255.0f, 0.0f, 255.0f });
	m_pPlayer->SetSpeed(200.0f);
	AddObject(m_pPlayer);

	m_pWall = new RectangleObject();
	m_pWall->GetTransform()->Translate(200.0f, 200.0f);
	m_pWall->SetDimensions(20.0f, 200.0f);
	m_pWall->SetColor({ 0.0f, 0.0f, 255.0f, 255.0f });
	AddObject(m_pWall);
}

void PacmanScene::Update(float deltaTime) 
{
	GameScene::Update(deltaTime);
}

void PacmanScene::Draw() const 
{
	GameScene::Draw();
}