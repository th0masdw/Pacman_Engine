#include "MiniginPCH.h"
#include "TestScene2.h"
#include "Engine/Scenegraph/RectangleObject.h"

TestScene2::TestScene2()
	: GameScene("TestScene2"),
	m_pRect(nullptr)
{
	Initialize();
}

TestScene2::~TestScene2()
{
}

void TestScene2::Initialize() 
{
	m_pRect = new RectangleObject();
	m_pRect->SetPosition({ 200.0f, 200.0f });
	m_pRect->SetDimensions(50.0f, 50.0f);
	m_pRect->SetColor({ 0.0f, 255.0f, 0.0f, 255.0f });

	Add(m_pRect);
}

void TestScene2::Update(float deltaTime) 
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void TestScene2::Draw() const 
{
	GameScene::Draw();
}