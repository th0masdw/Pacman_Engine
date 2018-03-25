#pragma once

#include <set>
#include "GameObject.h"
class GameTime;

class GameScene
{
public:
	explicit GameScene(const std::string& name);
	virtual ~GameScene();

	void FlushSceneObjects();

	std::string GetName() const;

	GameScene(const GameScene& other) = delete;
	GameScene(GameScene&& other) = delete;
	GameScene& operator=(const GameScene& other) = delete;
	GameScene& operator=(GameScene&& other) = delete;

protected:
	friend class SceneManager;

	virtual void Initialize() = 0;
	virtual void PostInitialize();
	virtual void Update(const GameTime& time);
	virtual void Draw() const;

	void AddObject(GameObject* pObject);
	void RemoveObject(GameObject* pObject, bool deleteObject = true);

	std::string m_Name{};

private:
	struct ObjectCompare
	{
		bool operator()(GameObject* pLeft, GameObject* pRight) {
			return pLeft->GetLayer() < pRight->GetLayer();
		}
	};

	std::multiset<GameObject*, ObjectCompare> m_Objects{};
	std::vector<std::multiset<GameObject*, ObjectCompare>::iterator> m_Poolables;

	void AddToPhysicsScene(GameObject* pObject);
	void RemoveFromPhysicsScene(GameObject* pObject);
};