#include "MiniginPCH.h"
#include "ShapeComponent.h"
#include "Engine/Scenegraph/GameObject.h"
#include "Engine/Graphics/Renderer.h"

ShapeComponent::ShapeComponent(float width, float height, const Color& color)
	: m_Width{ width },
	m_Height{ height },
	m_Color{ color }
{
}

void ShapeComponent::Update(const GameTime& time) 
{
	UNREFERENCED_PARAMETER(time);
}

void ShapeComponent::Draw() const 
{
	TransformComponent* pComp = m_pGameObject->GetTransform();
	Vector2 pos = pComp->GetPosition();
	Vector2 scale = pComp->GetScale();
	Vector2 center = { pos.x - m_Width / 2, pos.y - m_Height / 2 };

	Renderer::GetInstance().RenderRect(center, m_Width * scale.x, m_Height * scale.y, m_Color);
}

void ShapeComponent::SetDimensions(float width, float height) {
	m_Width = width;
	m_Height = height;
}

void ShapeComponent::SetDimensions(const Vector2& size) {
	m_Width = size.x;
	m_Height = size.y;
}

void ShapeComponent::SetColor(const Color& color) {
	m_Color = color;
}