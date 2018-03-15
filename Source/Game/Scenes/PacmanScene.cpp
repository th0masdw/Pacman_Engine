#include "MiniginPCH.h"
#include "PacmanScene.h"

//TESTING
#include "Engine/Scenegraph/GameObject.h"
#include "Engine/Components/Components.h"
#include "Game/Gameplay/Actors/PacmanActor.h"

PacmanScene::PacmanScene()
	: GameScene("PacmanScene"),
	m_pTextureObject(nullptr),
	m_pTextObject(nullptr),
	m_pFPSCounter(nullptr),
	m_pPlayer(nullptr)
{
	Initialize();
}

PacmanScene::~PacmanScene()
{
}

void PacmanScene::Initialize()
{
	m_pTextureObject = new GameObject();
	m_pTextureObject->GetTransform()->Translate(100.0f, 100.0f);
	m_pTextureObject->GetTransform()->Rotate(45.0f);
	m_pTextureObject->GetTransform()->Scale(0.5f, 0.5f);
	SpriteComponent* pSprite = new SpriteComponent("../Resources/logo.png");
	m_pTextureObject->AddComponent(pSprite);
	AddObject(m_pTextureObject);

	m_pTextObject = new GameObject();
	m_pTextObject->GetTransform()->Translate(300.0f, 300.0f);
	m_pTextObject->GetTransform()->Scale(2.0f, 2.0f);
	TextComponent* pText = new TextComponent();
	pText->SetText("TextComponent test", { 255.0f, 0.0f, 0.0f, 255.0f });
	pText->SetFont("../Resources/Lingua.otf", 20);
	m_pTextObject->AddComponent(pText);
	AddObject(m_pTextObject);

	//FPS Counter
	GameObject* pFPS = new GameObject();
	m_pFPSCounter = new TextComponent("FPS", { 0.0f, 255.0f, 0.0f, 255.0f }, "../Resources/Lingua.otf", 12);
	pFPS->AddComponent(m_pFPSCounter);
	pFPS->GetTransform()->Translate(20.0f, 20.0f);
	AddObject(pFPS);

	//Player
	m_pPlayer = new PacmanActor(25.0f, 200.0f);
	m_pPlayer->GetTransform()->Translate(200.0f, 200.0f);
	AddObject(m_pPlayer);
}

void PacmanScene::Update(const GameTime& time) 
{
	GameScene::Update(time);

	m_pPlayer->Update(time);
	m_pFPSCounter->SetText(to_string(time.GetFPS()), { 0.0f, 255.0f, 0.0f, 255.0f });
}

void PacmanScene::Draw() const 
{
	GameScene::Draw();
}