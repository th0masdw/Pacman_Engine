#pragma once

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
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;

	void Add(GameObject* pObject);
	//Remove

	std::string m_Name{};

private:
	std::vector<GameObject*> m_Objects{};
};