#pragma once

class GameTime;
class GameObject;

class GameScene
{
public:
	explicit GameScene(const std::string& name);
	virtual ~GameScene();

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
	std::vector<GameObject*> m_Objects{};

	void AddToPhysicsScene(GameObject* pObject);
	void RemoveFromPhysicsScene(GameObject* pObject);
};