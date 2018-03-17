#include "MiniginPCH.h"
#include "PhysicsManager.h"
#include <sstream>
#include "Engine/Helpers/Structs.h"
#include "Engine/Components/ColliderComponent.h"
#include "Engine/Managers/SceneManager.h"
#include "Engine/Scenegraph/GameScene.h"
#include "Engine/Scenegraph/GameObject.h"

void PhysicsManager::Update(const GameTime& time)
{
	UNREFERENCED_PARAMETER(time);

	FilterColliders(m_pStatics, m_pDynamics);

	for (ColliderComponent* pDynamic : m_pDynamics) {
		Rect collA = pDynamic->GetShape();

		for (ColliderComponent* pStatic : m_pStatics) {
			Rect collB = pStatic->GetShape();

			if (DoCollide(collA, collB)) {
				UpdatePosition(pDynamic, pStatic);
			}
		}
	}
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

void PhysicsManager::FilterColliders(std::vector<ColliderComponent*>& pStatics, std::vector<ColliderComponent*>& pDynamics)
{
	pStatics.clear();
	pDynamics.clear();
	GameScene* pActiveScene = SceneManager::GetInstance().GetActiveScene();

	if (pActiveScene) {
		std::string name = pActiveScene->GetName();
		auto pColliders = m_pColliders.find(name);

		if (pColliders != m_pColliders.end()) {
			std::vector<ColliderComponent*>& colliders = pColliders->second;

			for (ColliderComponent* pColl : colliders) {
				if (pColl->IsStatic())
					pStatics.push_back(pColl);
				else
					pDynamics.push_back(pColl);
			}
		}
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

void PhysicsManager::UpdatePosition(ColliderComponent* pDynamicColl, ColliderComponent* pStaticColl) 
{
	glm::vec2 newPos = { pStaticColl->GetShape().x - pStaticColl->GetShape().width / 2 - pDynamicColl->GetShape().width / 2,
						 pDynamicColl->GetShape().y};

	pDynamicColl->GetGameObject()->GetTransform()->Translate(newPos);
}