#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "Engine/Scenegraph/GameObject.h"

BaseComponent::BaseComponent()
	: m_pGameObject(nullptr)
{
}

BaseComponent::~BaseComponent()
{
}

void BaseComponent::SetGameObject(GameObject* pObject) 
{
	if (pObject)
		m_pGameObject = pObject;
}

GameObject* BaseComponent::GetGameObject() const 
{
	return m_pGameObject;
}