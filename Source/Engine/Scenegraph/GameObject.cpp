#include "MiniginPCH.h"
#include "GameObject.h"
#include "Engine/Components/BaseComponent.h"

GameObject::GameObject()
	: m_pParent(nullptr),
	m_pTransform(nullptr),
	m_pChildren{},
	m_pComponents{}
{
	m_pTransform = new TransformComponent();
	AddComponent(m_pTransform);
}

GameObject::~GameObject()
{
	for (BaseComponent* pComp : m_pComponents) {
		delete pComp;
	}

	for (GameObject* pObject : m_pChildren) {
		delete pObject;
	}
}

void GameObject::RootUpdate(float deltaTime)
{
	Update(deltaTime);

	for (BaseComponent* pComp : m_pComponents) {
		pComp->Update(deltaTime);
	}

	for (GameObject* pObject : m_pChildren) {
		pObject->RootUpdate(deltaTime);
	}
}

void GameObject::RootDraw() const 
{
	Draw();

	for (BaseComponent* pComp : m_pComponents) {
		pComp->Draw();
	}

	for (GameObject* pObject : m_pChildren) {
		pObject->RootDraw();
	}
}

void GameObject::AddChild(GameObject* pObject) 
{
	if (pObject) {
		pObject->m_pParent = this;
		m_pChildren.push_back(pObject);
	}
}

void GameObject::RemoveChild(GameObject* pObject, bool deleteObject)
{
	auto it = find(m_pChildren.begin(), m_pChildren.end(), pObject);

	if (it != m_pChildren.end()) {
		m_pChildren.erase(it);

		if (deleteObject) {
			delete pObject;
			pObject = nullptr;
		} else {
			pObject->m_pParent = nullptr;
		}
	}
}

void GameObject::AddComponent(BaseComponent* pComp) {
	if (pComp) {
		pComp->SetGameObject(this);
		m_pComponents.push_back(pComp);
	}
}

void GameObject::RemoveComponent(BaseComponent* pComp, bool deleteComp) {
	auto it = find(m_pComponents.begin(), m_pComponents.end(), pComp);

	if (it != m_pComponents.end()) {
		m_pComponents.erase(it);

		if (deleteComp) {
			delete pComp;
			pComp = nullptr;
		} else {
			pComp->SetGameObject(nullptr);
		}
	}
}

TransformComponent* GameObject::GetTransform() const {
	return m_pTransform;
}