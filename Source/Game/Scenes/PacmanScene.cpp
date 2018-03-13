#include "MiniginPCH.h"
#include "PacmanScene.h"
#include "Game/Gameplay/Actors/PacmanActor.h"
#include "Engine/Scenegraph/RectangleObject.h"

//TESTING
#include "Engine/Scenegraph/GameObject.h"
#include "Engine/Components/SpriteComponent.h"
#include "Engine/Components/TextComponent.h"

PacmanScene::PacmanScene()
	: GameScene("PacmanScene"),
	m_pPlayer(nullptr),
	m_pWall(nullptr),
	m_pTextureObject(nullptr),
	m_pTextObject(nullptr)
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

	m_pTextureObject = new GameObject();
	m_pTextureObject->GetTransform()->Translate(100.0f, 100.0f);
	SpriteComponent* pSprite = new SpriteComponent("../Resources/logo.png");
	m_pTextureObject->AddComponent(pSprite);
	AddObject(m_pTextureObject);

	m_pTextObject = new GameObject();
	m_pTextObject->GetTransform()->Translate(200.0f, 200.0f);
	TextComponent* pText = new TextComponent();
	pText->SetText("TextComponent test", { 255.0f, 0.0f, 0.0f, 255.0f });
	pText->SetFont("../Resources/Lingua.otf", 20);
	m_pTextObject->AddComponent(pText);
	AddObject(m_pTextObject);
}

void PacmanScene::Update(float deltaTime) 
{
	GameScene::Update(deltaTime);
}

void PacmanScene::Draw() const 
{
	GameScene::Draw();
}