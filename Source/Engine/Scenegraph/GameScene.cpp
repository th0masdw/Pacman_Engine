#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"
#include "Engine/Components/ColliderComponent.h"
#include "Engine/Managers/PhysicsManager.h"

GameScene::GameScene(const std::string& name) 
	: m_Name(name) 
{
}

GameScene::~GameScene()
{
	for (GameObject* pObject : m_Objects) {
		delete pObject;
	}
}

void GameScene::Update(const GameTime& time)
{
	for (GameObject* pObject : m_Objects) {
		pObject->Update(time);
	}
}

void GameScene::Draw() const 
{
	for (GameObject* pObject : m_Objects) {
		pObject->Draw();
	}
}

void GameScene::AddObject(GameObject* pObject) 
{
	auto it = find(m_Objects.begin(), m_Objects.end(), pObject);

	if (it == m_Objects.end() && pObject) {
		m_Objects.push_back(pObject);
		pObject->SetScene(this);
		pObject->PostInitialize();
		AddToPhysicsScene(pObject);
	} else
		Debug::LogWarning("Object already present!");
}

void GameScene::RemoveObject(GameObject* pObject, bool deleteObject) 
{
	auto it = find(m_Objects.begin(), m_Objects.end(), pObject);

	if (it != m_Objects.end()) {
		m_Objects.erase(it);
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