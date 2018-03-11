#include "MiniginPCH.h"
#include "PacmanScene.h"

PacmanScene::PacmanScene()
	: GameScene("PacmanScene")
{
	Initialize();
}

PacmanScene::~PacmanScene()
{
}

void PacmanScene::Initialize()
{
}

void PacmanScene::Update(float deltaTime) 
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void PacmanScene::Draw() const 
{
	GameScene::Draw();
}