#include "MiniginPCH.h"
#include "PacmanScene.h"

#include "Engine/Managers/SoundManager.h"
#include "Engine/Managers/EventManager.h"
#include "Engine/Components/TextComponent.h"
#include "Game/Gameplay/Actors/PacmanActor.h"
#include "Game/Gameplay/Actors/GhostActor.h"
#include "Game/Gameplay/Objects/FPSObject.h"
#include "Game/Gameplay/Objects/PowerPellet.h"
#include "Game/Gameplay/Objects/Fruit.h"
#include "Game/Utilities/LevelLoader.h"
#include "Game/Gameplay/UI/ScoreWidget.h"
#include "Game/Gameplay/UI/LivesWidget.h"

PacmanScene::PacmanScene()
	: GameScene("PacmanScene"),
	m_pPlayer(nullptr),
	m_pGhosts{},
	m_pPowerPellets{},
	m_pFruit(nullptr),
	m_pFPS(nullptr),
	m_PauseGame(false),
	m_PelletCounter(0),
	m_WallPool(),
	m_PelletPool(),
	m_pLoader(nullptr)
{	
	LoadSounds();
	RegisterEvents();
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
	m_PelletCounter = m_pLoader->GetPelletAmount();

	//Player
	m_pPlayer = new PacmanActor(25, 100);
	glm::vec2 playerPos = m_pLoader->GetPlayerPosition();
	m_pPlayer->GetTransform()->Translate(playerPos);
	AddObject(m_pPlayer);

	//Ghosts
	GhostActor* pGhost = nullptr;
	std::vector<glm::vec2> ghostPositions = m_pLoader->GetGhostPositions();
	for (UINT i = 0; i < ghostPositions.size(); ++i) {
		pGhost = new GhostActor(m_pPlayer, i, 25, 100, { 255, 255, 255, 255 }, ghostPositions[i]);
		pGhost->GetTransform()->Translate(ghostPositions[i]);
		m_pGhosts.emplace_back(pGhost);
		AddObject(pGhost);
	}

	//Set ghost colors
	m_pGhosts[0]->SetColor({ 255, 0, 0, 255 });
	m_pGhosts[1]->SetColor({ 255, 153, 204, 255 });
	m_pGhosts[2]->SetColor({ 102, 255, 255, 255 });
	m_pGhosts[3]->SetColor({ 255, 153, 51, 255 });

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
	m_pFruit = new Fruit();
	m_pFruit->GetTransform()->Translate(m_pLoader->GetFruitPosition());
	m_pFruit->GetTransform()->Scale(0.2f, 0.2f);
	AddObject(m_pFruit);

	//FPS Counter
	m_pFPS = new FPSObject("../Resources/Lingua.otf", 20, { 0, 255, 0, 255 });
	m_pFPS->GetTransform()->Translate({ 15.0f, 15.0f });
	AddObject(m_pFPS);

	//Scores
	ScoreWidget* pScores = new ScoreWidget();
	pScores->GetTransform()->Translate(35.0f, 350.0f);
	AddObject(pScores);

	//Lives
	LivesWidget* pLives = new LivesWidget();
	pLives->GetTransform()->Translate(735.0f, 400.0f);
	AddObject(pLives);

	//Play sound
	PlaySound(SoundId::Background);
}

void PacmanScene::Update(const GameTime& time) 
{
	if (!m_PauseGame) {
		m_pPlayer->Update(time);	

		for (GhostActor* pActor : m_pGhosts) {
			pActor->Update(time);
		}

		for (PowerPellet* pPower : m_pPowerPellets) {
			pPower->Update(time);
		}

		m_pFruit->Update(time);
		m_pFPS->Update(time);

		GameScene::Update(time);
	}
}

void PacmanScene::Draw() const 
{
	GameScene::Draw();
}

void PacmanScene::ResetLevel()
{
	m_pPlayer->GetTransform()->Translate(m_pLoader->GetPlayerPosition());

	for (UINT i = 0; i < m_pLoader->GetGhostAmount(); ++i) {
		m_pGhosts[i]->Respawn();
	}

	Debug::Log("Reset level");
}

void PacmanScene::GameOver()
{
	m_PauseGame = true;

	GameObject* pGameOver = new GameObject(Tag::Empty, Layer::UI);
	TextComponent* pText = new TextComponent("Game Over!", { 255, 0, 0, 255 }, "../Resources/Lingua.otf", 30);
	pGameOver->AddComponent(pText);
	pGameOver->GetTransform()->Translate(387.5f, 275.0f);
	AddObject(pGameOver);

	StopSound(SoundId::Background);
	PlaySound(SoundId::GameOver);
}

void PacmanScene::CheckIfGameWon()
{
	--m_PelletCounter;

	if (m_PelletCounter <= 0) {
		m_PauseGame = true;

		GameObject* pWin = new GameObject(Tag::Empty, Layer::UI);
		TextComponent* pText = new TextComponent("You win!", { 0, 255, 0, 255 }, "../Resources/Lingua.otf", 30);
		pWin->AddComponent(pText);
		pWin->GetTransform()->Translate(387.5f, 275.0f);
		AddObject(pWin);

		StopSound(SoundId::Background);
		PlaySound(SoundId::Win);
	}
}

void PacmanScene::LoadSounds()
{
	SoundManager& soundManager = SoundManager::GetInstance();

	soundManager.CreateSound(static_cast<int>(SoundId::Background), "../Resources/sounds/background.wav", FMOD_LOOP_NORMAL, true);
	soundManager.CreateSound(static_cast<int>(SoundId::Chomp), "../Resources/sounds/chomp.wav");
	soundManager.CreateSound(static_cast<int>(SoundId::Fruit), "../Resources/sounds/eatfruit.wav");
	soundManager.CreateSound(static_cast<int>(SoundId::Ghost), "../Resources/sounds/eatghost.wav");
	soundManager.CreateSound(static_cast<int>(SoundId::GameOver), "../Resources/sounds/gameover.wav");
	soundManager.CreateSound(static_cast<int>(SoundId::Win), "../Resources/sounds/win.wav");
}

void PacmanScene::RegisterEvents()
{
	EventManager& eventManager = EventManager::GetInstance();

	//Gameplay events
	eventManager.StartListening(Event::Die(), "DieSceneCB", [this]() { ResetLevel(); });
	eventManager.StartListening(Event::GameOver(), "GameOverSceneCB", [this]() { GameOver(); });
	eventManager.StartListening(Event::EatPellet(), "EatPelletGameCB", [this]() { CheckIfGameWon(); });

	//Sound events
	eventManager.StartListening(Event::EatPower(), "EatPowerGameCB", [this]() { PlaySound(SoundId::Chomp); });
	eventManager.StartListening(Event::EatFruit(), "EatFruitGameCB", [this]() { PlaySound(SoundId::Fruit); });
	eventManager.StartListening(Event::EatGhost(), "EatGhostGameCB", [this]() { PlaySound(SoundId::Ghost); });
}

void PacmanScene::PlaySound(const SoundId id)
{
	int playId = static_cast<int>(id);
	SoundManager::GetInstance().PlaySoundOnChannel(playId, playId);
}

void PacmanScene::StopSound(const SoundId id)
{
	int playId = static_cast<int>(id);
	SoundManager::GetInstance().StopChannel(playId);
}