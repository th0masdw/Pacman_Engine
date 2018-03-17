#include "MiniginPCH.h"
#include "PhysicsManager.h"
#include <sstream>
#include "Engine/Components/ColliderComponent.h"
#include "Engine/Managers/SceneManager.h"
#include "Engine/Scenegraph/GameScene.h"

void PhysicsManager::Update(const GameTime& time)
{
	UNREFERENCED_PARAMETER(time);

	GameScene* pActiveScene = SceneManager::GetInstance().GetActiveScene();

	if (pActiveScene) {
		std::string name = pActiveScene->GetName();
		auto pColliders = m_pColliders.find(name);

		if (pColliders != m_pColliders.end())
			Debug::Log(name + ": " + std::to_string(pColliders->second.size()));
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