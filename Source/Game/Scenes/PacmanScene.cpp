#include "MiniginPCH.h"
#include "PacmanScene.h"

#include "Game/Gameplay/Actors/PacmanActor.h"
#include "Game/Gameplay/Actors/GhostActor.h"
#include "Game/Gameplay/Objects/FPSObject.h"
#include "Game/Utilities/LevelLoader.h"

PacmanScene::PacmanScene()
	: GameScene("PacmanScene"),
	m_pPlayer(nullptr),
	m_pGhost(nullptr),
	m_pFPS(nullptr),
	m_WallPool()
{
	Initialize();
}

PacmanScene::~PacmanScene()
{
	delete m_pLoader;
	m_WallPool.DestroyPool();
	FlushSceneObjects();
}

void PacmanScene::Initialize()
{
	m_pLoader = new LevelLoader("../Resources/TestLevel.txt");
	m_WallPool.Initialize(m_pLoader->GetWallAmount());

	//Player
	m_pPlayer = new PacmanActor(25, 150);
	glm::vec2 playerPos = m_pLoader->GetPlayerPosition();
	m_pPlayer->GetTransform()->Translate(playerPos);
	AddObject(m_pPlayer);

	//Walls
	Wall* pWall = nullptr;
	for (const glm::vec2& wallPos : m_pLoader->GetWallPositions()) {
		pWall = m_WallPool.GetAvailableUnit();
		pWall->SetDimensions(25, 25);
		pWall->SetColor({ 0, 0, 255, 255 });
		pWall->GetTransform()->Translate(wallPos);
		AddObject(pWall);
	}

	//Ghost
	m_pGhost = new GhostActor(m_pPlayer, 25, 150, { 255, 105, 180, 255 });
	m_pGhost->GetTransform()->Translate(87.5f, 237.5f);
	AddObject(m_pGhost);

	//FPS Counter
	m_pFPS = new FPSObject("../Resources/Lingua.otf", 20, { 0, 255, 0, 255 }, { 20, 20 });
	AddObject(m_pFPS);
}

void PacmanScene::Update(const GameTime& time) 
{
	m_pPlayer->Update(time);
	m_pGhost->Update(time);
	m_pFPS->Update(time);

	GameScene::Update(time);
}

void PacmanScene::Draw() const 
{
	GameScene::Draw();
}