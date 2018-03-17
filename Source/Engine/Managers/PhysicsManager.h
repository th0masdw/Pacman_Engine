#pragma once

#include "Engine/Helpers/Singleton.h"
#include <map>
class ColliderComponent;
class GameTime;

class PhysicsManager final : public Singleton<PhysicsManager>
{
public:
	void Update(const GameTime& time);

	void AddCollider(ColliderComponent* pCollider, const std::string& sceneName);
	void RemoveCollider(ColliderComponent* pCollider, const std::string& sceneName);

private:
	std::map<std::string, std::vector<ColliderComponent*>> m_pColliders;
};