#pragma once

#include "Engine/Helpers/Singleton.h"
#include <map>
class ColliderComponent;
class GameTime;
struct Rect;
class GameObject;

class PhysicsManager final : public Singleton<PhysicsManager>
{
public:
	void Update(const GameTime& time);

	void AddCollider(ColliderComponent* pCollider, const std::string& sceneName);
	void RemoveCollider(ColliderComponent* pCollider, const std::string& sceneName);

private:
	std::map<std::string, std::vector<ColliderComponent*>> m_pColliders;
	std::vector<ColliderComponent*> m_pStatics;
	std::vector<ColliderComponent*> m_pDynamics;

	void FilterColliders(std::vector<ColliderComponent*>& pStatics, std::vector<ColliderComponent*>& pDynamics);
	bool DoCollide(const Rect& a, const Rect& b) const;
	void UpdatePosition(ColliderComponent* pDynamicColl, ColliderComponent* pStaticColl);
};