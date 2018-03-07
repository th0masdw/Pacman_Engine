#pragma once
#include "SceneManager.h"

class SceneObject;

class Scene
{
	friend Scene& SceneManager::CreateScene(const std::string& name);

public:
	~Scene();

	void Update();
	void Render() const;
	void Add(const std::shared_ptr<SceneObject>& object);

	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

private: 
	explicit Scene(const std::string& name);

	std::string m_Name{};
	std::vector < std::shared_ptr<SceneObject>> m_Objects{};

	static unsigned int idCounter; 
};