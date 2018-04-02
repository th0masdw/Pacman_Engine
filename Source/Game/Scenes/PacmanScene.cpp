#include "MiniginPCH.h"
#include "PacmanScene.h"

#include "Game/Gameplay/Actors/PacmanActor.h"
#include "Game/Gameplay/Actors/GhostActor.h"
#include "Game/Gameplay/Objects/FPSObject.h"
#include "Game/Gameplay/Objects/PowerPellet.h"
#include "Game/Gameplay/Objects/Fruit.h"
#include "Game/Utilities/LevelLoader.h"
#include "Game/Gameplay/UI/ScoreManager.h"

PacmanScene::PacmanScene()
	: GameScene("PacmanScene"),
	m_pPlayer(nullptr),
	m_pGhosts{},
	m_pPowerPellets{},
	m_pFPS(nullptr),
	m_WallPool(),
	m_PelletPool(),
	m_pLoader(nullptr)
{
	Initialize();
}

PacmanScene::~PacmanScene()
{
	delete m_pLoader;
	m_WallPool.DestroyPool();
	m_PelletPool.DestroyPool();
	FlushSceneObjects();
}

void PacmanScene::Initialize()
{
	m_pLoader = new LevelLoader("../Resources/TestLevel.txt");
	m_WallPool.Initialize(m_pLoader->GetWallAmount());
	m_PelletPool.Initialize(m_pLoader->GetPelletAmount());

	//Player
	m_pPlayer = new PacmanActor(25, 150);
	glm::vec2 playerPos = m_pLoader->GetPlayerPosition();
	m_pPlayer->GetTransform()->Translate(playerPos);
	AddObject(m_pPlayer);

	//Ghosts
	GhostActor* pGhost = nullptr;
	for (const glm::vec2& ghostPos : m_pLoader->GetGhostPositions()) {
		pGhost = new GhostActor(m_pPlayer, 25, 150, { 255, 105, 180, 255 });
		pGhost->GetTransform()->Translate(ghostPos);
		m_pGhosts.emplace_back(pGhost);
		AddObject(pGhost);
	}

	//Walls
	Wall* pWall = nullptr;
	for (const glm::vec2& wallPos : m_pLoader->GetWallPositions()) {
		pWall = m_WallPool.GetAvailableUnit();
		pWall->GetTransform()->Translate(wallPos);
		AddObject(pWall);
	}

	//Pellets
	Pellet* pPellet = nullptr;
	for (const glm::vec2& pelletPos : m_pLoader->GetPelletPositions()) {
		pPellet = m_PelletPool.GetAvailableUnit();
		pPellet->GetTransform()->Translate(pelletPos);
		AddObject(pPellet);
	}

	//PowerPellets
	PowerPellet* pPower = nullptr;
	for (const glm::vec2& powerPos : m_pLoader->GetPowerPelletPositions()) {
		pPower = new PowerPellet();
		pPower->GetTransform()->Translate(powerPos);
		m_pPowerPellets.emplace_back(pPower);
		AddObject(pPower);
	}

	//Fruit
	Fruit* pFruit = new Fruit();
	pFruit->GetTransform()->Translate(m_pLoader->GetFruitPosition());
	pFruit->GetTransform()->Scale(0.2f, 0.2f);
	AddObject(pFruit);

	//FPS Counter
	m_pFPS = new FPSObject("../Resources/Lingua.otf", 20, { 0, 255, 0, 255 });
	m_pFPS->GetTransform()->Translate({ 15.0f, 15.0f });
	AddObject(m_pFPS);

	//Scores
	ScoreManager* pScoreManager = new ScoreManager();
	pScoreManager->GetTransform()->Translate(35.0f, 350.0f);
	AddObject(pScoreManager);
}

void PacmanScene::Update(const GameTime& time) 
{
	m_pPlayer->Update(time);	
	for (GhostActor* pActor : m_pGhosts) {
		pActor->Update(time);
	}
	for (PowerPellet* pPower : m_pPowerPellets) {
		pPower->Update(time);
	}
	m_pFPS->Update(time);

	GameScene::Update(time);
}

void PacmanScene::Draw() const 
{
	GameScene::Draw();
}