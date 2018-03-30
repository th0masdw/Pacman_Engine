#include "MiniginPCH.h"
#include "GameScene.h"
#include "Engine/Components/ColliderComponent.h"
#include "Engine/Managers/PhysicsManager.h"

GameScene::GameScene(const std::string& name) 
	: m_Name(name) 
{
}

GameScene::~GameScene()
{
	for (GameObject* pObject : m_pObjects) {
		delete pObject;
	}
}

void GameScene::FlushSceneObjects()
{
	for (auto poolIt : m_Poolables) {
		m_pObjects.erase(poolIt);
	}
}

void GameScene::PostInitialize()
{
	for (GameObject* pObject : m_pObjects) {
		pObject->PostInitialize();
	}
}

void GameScene::Update(const GameTime& time)
{
	for (GameObject* pObject : m_pObjects) {
		if (pObject->IsActive()) 
			pObject->Update(time);
	}
}

void GameScene::Draw() const 
{
	for (GameObject* pObject : m_pObjects) {
		if (pObject->IsActive())
			pObject->Draw();
	}
}

void GameScene::AddObject(GameObject* pObject)
{
	auto it = find(m_pObjects.begin(), m_pObjects.end(), pObject);

	if (it == m_pObjects.end() && pObject) {
		auto addIt = m_pObjects.insert(pObject);
		pObject->SetScene(this);
		AddToPhysicsScene(pObject);

		if (pObject->IsPoolable())
			m_Poolables.emplace_back(addIt);
	} else
		Debug::LogWarning("Object already present!");
}

void GameScene::RemoveObject(GameObject* pObject, bool deleteObject) 
{
	auto it = find(m_pObjects.begin(), m_pObjects.end(), pObject);

	if (it != m_pObjects.end()) {
		m_pObjects.erase(it);
		pObject->SetScene(nullptr);
		RemoveFromPhysicsScene(pObject);

		if (deleteObject) {
			delete pObject;
			pObject = nullptr;
		}
	}
}

void GameScene::AddToPhysicsScene(GameObject* pObject)
{
	auto pColliders = pObject->GetComponents<ColliderComponent>();

	if (!pColliders.empty()) {
		for (ColliderComponent* pComp : pColliders) {
			PhysicsManager::GetInstance().AddCollider(pComp, m_Name);
		}
	}
}

void GameScene::RemoveFromPhysicsScene(GameObject* pObject)
{
	auto pColliders = pObject->GetComponents<ColliderComponent>();

	if (!pColliders.empty()) {
		for (ColliderComponent* pComp : pColliders) {
			PhysicsManager::GetInstance().RemoveCollider(pComp, m_Name);
		}
	}
}

std::string GameScene::GetName() const 
{
	return m_Name;
}