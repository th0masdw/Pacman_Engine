#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int Scene::idCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{
	for(auto gameObject : m_Objects)
	{
		gameObject->Update();
	}
}

void Scene::Draw() const
{
	for (const auto gameObject : m_Objects)
	{
		gameObject->Draw();
	}
}

