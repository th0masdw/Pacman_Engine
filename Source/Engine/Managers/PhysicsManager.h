#pragma once

#include "Engine/Helpers/Singleton.h"
#include <map>
class ColliderComponent;
struct Rect;
class GameObject;

class PhysicsManager final : public Singleton<PhysicsManager>
{
public:
	GameObject* DoesCollide(GameObject* pTarget) const;

	void AddCollider(ColliderComponent* pCollider, const std::string& sceneName);
	void RemoveCollider(ColliderComponent* pCollider, const std::string& sceneName);

	void GetStaticSceneColliders(std::vector<glm::vec2>& positions) const;

private:
	std::map<std::string, std::vector<ColliderComponent*>> m_pColliders;

	void GetSceneColliders(std::vector<ColliderComponent*>& pSceneColliders) const;
	bool DoCollide(const Rect& a, const Rect& b) const;
};