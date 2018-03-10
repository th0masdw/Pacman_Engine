#include "MiniginPCH.h"
#include "TestScene.h"
#include "Engine/Scenegraph/RectangleObject.h"

TestScene::TestScene()
	: GameScene("TestScene"),
	m_pRect(nullptr)
{
	Initialize();
}

TestScene::~TestScene()
{
}

void TestScene::Initialize() 
{
	m_pRect = new RectangleObject();
	m_pRect->SetPosition({ 100.0f, 100.0f });
	m_pRect->SetDimensions(50.0f, 50.0f);
	m_pRect->SetColor({ 255.0f, 0.0f, 0.0f, 255.0f });

	Add(m_pRect);
}

void TestScene::Update(float deltaTime) 
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void TestScene::Draw() const 
{
	GameScene::Draw();
}