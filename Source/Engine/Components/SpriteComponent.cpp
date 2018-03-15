#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Engine/Helpers/Structs.h"
#include "Engine/Scenegraph/GameObject.h"
#include "Engine/Managers/ResourceManager.h"
#include "Engine/Graphics/Renderer.h"

SpriteComponent::SpriteComponent(const string& file)
	: m_pTexture{ ResourceManager::GetInstance().LoadTexture(file) }
{
}

void SpriteComponent::Update(const GameTime& time) {
	UNREFERENCED_PARAMETER(time);
}

void SpriteComponent::Draw() const {
	if (m_pTexture) {
		TransformComponent* pComp = m_pGameObject->GetTransform();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pComp->GetPosition(), pComp->GetRotation(), pComp->GetScale());
	} else {
		Debug::LogError("SpriteComponent::Draw() - Texture not loaded!");
	}
}

void SpriteComponent::SetTexture(const string& file) {
	m_pTexture = ResourceManager::GetInstance().LoadTexture(file);
}