#include "MiniginPCH.h"
#include "GameObject.h"
#include "Engine/Helpers/Structs.h"

GameObject::GameObject(const Vector2& pos)
	: m_Position{ pos },
	m_pParent(nullptr)
{
}

GameObject::~GameObject()
{
	for (GameObject* pObject : m_pChildren) {
		delete pObject;
	}
}

void GameObject::RootUpdate(float deltaTime)
{
	Update(deltaTime);

	for (GameObject* pObject : m_pChildren) {
		pObject->RootUpdate(deltaTime);
	}
}

void GameObject::RootDraw() const 
{
	Draw();

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

void GameObject::SetPosition(const Vector2& pos) 
{
	m_Position = pos;
}

Vector2 GameObject::GetPosition() const 
{
	if (m_pParent)
		return m_pParent->m_Position + m_Position;
	else
		return m_Position;
}