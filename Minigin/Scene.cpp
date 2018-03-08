#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int Scene::idCounter = 0;

Scene::Scene(const string& name) : m_Name(name) 
{
}

Scene::~Scene()
{
	for (GameObject* pObject : m_Objects) {
		delete pObject;
	}
}

void Scene::Add(GameObject* object) {
	m_Objects.push_back(object);
}

void Scene::Update(float deltaTime) {
	for(GameObject* pObject : m_Objects) {
		pObject->Update(deltaTime);
	}
}

void Scene::Draw() const {
	for (GameObject* pObject : m_Objects) {
		pObject->Draw();
	}
}

