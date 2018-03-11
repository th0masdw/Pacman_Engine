#include "MiniginPCH.h"
#include "TestScene3.h"
#include "Engine/Scenegraph/RectangleObject.h"

TestScene3::TestScene3()
	: GameScene("TestScene3"),
	m_pRect(nullptr)
{
	Initialize();
}

TestScene3::~TestScene3()
{
}

void TestScene3::Initialize() 
{
	m_pRect = new RectangleObject();
	m_pRect->SetPosition({ 300.0f, 300.0f });
	m_pRect->SetDimensions(50.0f, 50.0f);
	m_pRect->SetColor({ 0.0f, 0.0f, 255.0f, 255.0f });

	AddObject(m_pRect);
}

void TestScene3::Update(float deltaTime) 
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void TestScene3::Draw() const 
{
	GameScene::Draw();
}