#include "MiniginPCH.h"
#include "GameObject.h"
#include "Engine/Components/BaseComponent.h"
#include "Engine/Scenegraph/GameScene.h"

GameObject::GameObject(const Tag tag, const Layer layer)
	: m_Tag{ tag },
	m_Layer{ layer },
	m_pParent(nullptr),
	m_pScene(nullptr),
	m_pTransform(nullptr),
	m_pChildren{},
	m_pComponents{}
{
	m_pTransform = new TransformComponent();
	m_pTransform->SetGameObject(this);
	m_pComponents.push_back(m_pTransform);
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

void GameObject::PostInitialize()
{
	for (BaseComponent* pComp : m_pComponents) {
		pComp->PostInitialize();
	}

	for (GameObject* pObject : m_pChildren) {
		pObject->PostInitialize();
	}
}

void GameObject::Update(const GameTime& time)
{
	for (BaseComponent* pComp : m_pComponents) {
		pComp->Update(time);
	}

	for (GameObject* pObject : m_pChildren) {
		pObject->Update(time);
	}
}

void GameObject::Draw() const 
{
	for (BaseComponent* pComp : m_pComponents) {
		pComp->Draw();
	}

	for (GameObject* pObject : m_pChildren) {
		pObject->Draw();
	}
}

void GameObject::AddChild(GameObject* pObject) 
{
	auto it = find(m_pChildren.begin(), m_pChildren.end(), pObject);

	if (it == m_pChildren.end() && pObject) {
		pObject->m_pParent = this;
		m_pChildren.push_back(pObject);
	} else {
		Debug::LogWarning("Child already present!");
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

void GameObject::AddComponent(BaseComponent* pComp) 
{
	if (typeid(*pComp) == typeid(TransformComponent)) {
		Debug::LogWarning("Can't add component: GameObject already has a TransformComponent");
		return;
	}

	auto it = find(m_pComponents.begin(), m_pComponents.end(), pComp);

	if (it == m_pComponents.end() && pComp) {
		pComp->SetGameObject(this);
		m_pComponents.push_back(pComp);
	} else {
		Debug::LogWarning("Component already present!");
	}
}

void GameObject::RemoveComponent(BaseComponent* pComp, bool deleteComp) 
{
	if (typeid(*pComp) == typeid(TransformComponent)) {
		Debug::LogError("Can't remove TransformComponent!");
		return;
	}

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

TransformComponent* GameObject::GetTransform() const 
{
	return m_pTransform;
}

GameObject* GameObject::GetParent() const
{
	return m_pParent;
}

Tag GameObject::GetTag() const
{
	return m_Tag;
}

Layer GameObject::GetLayer() const
{
	return m_Layer;
}

void GameObject::SetScene(GameScene* pScene)
{
	m_pScene = pScene;
}

GameScene* GameObject::GetScene() const
{
	return m_pScene;
}