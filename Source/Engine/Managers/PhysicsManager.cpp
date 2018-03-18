#include "MiniginPCH.h"
#include "PhysicsManager.h"
#include <sstream>
#include "Engine/Helpers/Structs.h"
#include "Engine/Components/ColliderComponent.h"
#include "Engine/Managers/SceneManager.h"
#include "Engine/Scenegraph/GameScene.h"
#include "Engine/Scenegraph/GameObject.h"

GameObject* PhysicsManager::DoesCollide(GameObject* pTarget) const
{
	GameObject* pResult = nullptr;
	ColliderComponent* pColl = pTarget->GetComponent<ColliderComponent>();

	if (pColl) {	
		if (!pColl->IsStatic()) {
			std::vector<ColliderComponent*> pColliders;
			GetSceneColliders(pColliders);

			for (ColliderComponent* pComp : pColliders) {
				if (DoCollide(pComp->GetShape(), pColl->GetShape())) {
					pResult = (pComp->GetGameObject() != pTarget) ? pComp->GetGameObject() : nullptr;

					if (pResult) break;
				}
			}
		}
	} else {
		Debug::LogWarning("PhysicsManager::DoesCollide(): Object does not have a collider attached!");
	}

	return pResult;
}

void PhysicsManager::AddCollider(ColliderComponent* pCollider, const std::string& sceneName)
{
	auto sceneIt = (m_pColliders.insert({ sceneName, {} })).first;
	auto collIt = find(sceneIt->second.begin(), sceneIt->second.end(), pCollider);

	if (collIt == sceneIt->second.end())
		sceneIt->second.push_back(pCollider);
	else
		Debug::LogWarning("PhysicsManager::AddCollider(): Object already present");
}

void PhysicsManager::RemoveCollider(ColliderComponent* pCollider, const std::string& sceneName)
{
	auto sceneIt = m_pColliders.find(sceneName);

	if (sceneIt != m_pColliders.end()) {		
		auto collIt = find(sceneIt->second.begin(), sceneIt->second.end(), pCollider);

		if (collIt != sceneIt->second.end())
			sceneIt->second.erase(collIt);
	} else {
		std::stringstream ss;
		ss << "PhysicsManager::RemoveCollider(): Scene with name " << sceneName << " could not be found";
		Debug::LogWarning(ss.str());
	}
}

void PhysicsManager::GetSceneColliders(std::vector<ColliderComponent*>& pSceneColliders) const
{
	GameScene* pActiveScene = SceneManager::GetInstance().GetActiveScene();

	if (pActiveScene) {
		std::string name = pActiveScene->GetName();
		auto pColliders = m_pColliders.find(name);

		if (pColliders != m_pColliders.end())
			pSceneColliders = pColliders->second;
	}
}

bool PhysicsManager::DoCollide(const Rect& a, const Rect& b) const
{
	float aX1 = a.x - a.width * 0.5f;
	float aX2 = aX1 + a.width;
	float aY1 = a.y - a.height * 0.5f;
	float aY2 = aY1 + a.height;

	float bX1 = b.x - b.width * 0.5f;
	float bX2 = bX1 + b.width;
	float bY1 = b.y - b.height * 0.5f;
	float bY2 = bY1 + b.height;

	bool overlap = aX1 > bX2 ||
                   bX1 > aX2 ||
                   aY1 > bY2 ||
                   bY1 > aY2;

	return !overlap;
}