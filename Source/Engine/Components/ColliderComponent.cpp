#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "Engine/Scenegraph/GameObject.h"
#include "Engine/Graphics/Renderer.h"

ColliderComponent::ColliderComponent(float width, float height, bool isStatic)
	: m_IsStatic{ isStatic }
{
	m_Box.width = width;
	m_Box.height = height;
}

void ColliderComponent::PostInitialize()
{
	if (m_IsStatic) {
		glm::vec2 pos = m_pGameObject->GetTransform()->GetPosition();
		m_Box.x = pos.x;
		m_Box.y = pos.y;
	}
}

void ColliderComponent::Update(const GameTime& time) 
{
	UNREFERENCED_PARAMETER(time);

	if (!m_IsStatic) {
		glm::vec2 pos = m_pGameObject->GetTransform()->GetPosition();
		m_Box.x = pos.x;
		m_Box.y = pos.y;
	}
}

void ColliderComponent::Draw() const 
{
	if (Debug::IsDebugRenderingEnabled()) {
		TransformComponent* pComp = m_pGameObject->GetTransform();
		glm::vec2 scale = pComp->GetScale();
		glm::vec2 center = { m_Box.x - m_Box.width / 2, m_Box.y - m_Box.height / 2 };

		Renderer::GetInstance().RenderRect(center, m_Box.width * scale.x, m_Box.height * scale.y, { 255.0f, 0.0f, 0.0f, 255.0f }, false);
	}
}

void ColliderComponent::SetDimensions(float width, float height)
{
	m_Box.width = width;
	m_Box.height = height;
}

Rect ColliderComponent::GetShape() const
{
	return m_Box;
}

bool ColliderComponent::IsStatic() const
{
	return m_IsStatic;
}