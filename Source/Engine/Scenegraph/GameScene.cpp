#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"

GameScene::GameScene(const string& name) 
	: m_Name(name) 
{
}

GameScene::~GameScene()
{
	for (GameObject* pObject : m_Objects) {
		delete pObject;
	}
}

void GameScene::Update(float deltaTime)
{
	for (GameObject* pObject : m_Objects) {
		pObject->Update(deltaTime);
	}
}

void GameScene::Draw() const {
	for (GameObject* pObject : m_Objects) {
		pObject->Draw();
	}
}

void GameScene::AddObject(GameObject* pObject) {
	if (pObject)
		m_Objects.push_back(pObject);
}

void GameScene::RemoveObject(GameObject* pObject, bool deleteObject) {
	auto it = find(m_Objects.begin(), m_Objects.end(), pObject);

	if (it != m_Objects.end()) {
		m_Objects.erase(it);

		if (deleteObject) {
			delete pObject;
			pObject = nullptr;
		}
	}
}

string GameScene::GetName() const {
	return m_Name;
}