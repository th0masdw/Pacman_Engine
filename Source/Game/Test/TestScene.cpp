#include "MiniginPCH.h"
#include "TestScene.h"
#include "Engine/Scenegraph/RectangleObject.h"
#include "Engine/Managers/InputManager.h"

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
	AddObject(m_pRect);

	m_pChild = new RectangleObject();
	m_pChild->SetDimensions(10.0f, 10.0f);
	m_pChild->SetColor({ 255.0f, 255.0f, 255.0f, 255.0f });
	m_pRect->AddChild(m_pChild);

	InputManager::GetInstance().AddInputAction(InputAction{ Input::P1_Right, XINPUT_GAMEPAD_DPAD_RIGHT, 0 });
}

void TestScene::Update(float deltaTime) 
{
	//UNREFERENCED_PARAMETER(deltaTime);

	if (InputManager::GetInstance().IsActionTriggered(Input::P1_Right)) {
		Vector2 pos = m_pRect->GetPosition();
		pos.x += 100.0f * deltaTime;
		m_pRect->SetPosition(pos);
	}
}

void TestScene::Draw() const 
{
	GameScene::Draw();
}