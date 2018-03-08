#pragma once
#include "SceneManager.h"

class GameObject;

class Scene
{
	friend Scene& SceneManager::CreateScene(const std::string& name);

public:
	~Scene();

	void Update(float deltaTime);
	void Draw() const;
	void Add(GameObject* object);

	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

private: 
	explicit Scene(const std::string& name);

	std::string m_Name{};
	std::vector<GameObject*> m_Objects{};

	static unsigned int idCounter; 
};