#include "MiniginPCH.h"
#include "RectangleObject.h"
#include "Engine/Graphics/Renderer.h"

RectangleObject::RectangleObject(float width, float height, const Color& color)
	: m_Width{ width },
	m_Height{ height },
	m_Color{ color }
{
}

void RectangleObject::Update(const GameTime& time) {
	UNREFERENCED_PARAMETER(time);
}

void RectangleObject::Draw() const {
	Vector2 pos = GetTransform()->GetPosition();
	Vector2 scale = GetTransform()->GetScale();
	Vector2 center = { pos.x - m_Width / 2, pos.y - m_Height / 2 };
	Renderer::GetInstance().RenderRect(center, m_Width * scale.x, m_Height * scale.y, m_Color);
}

void RectangleObject::SetDimensions(float width, float height) {
	m_Width = width;
	m_Height = height;
}

void RectangleObject::SetColor(const Color& color) {
	m_Color = color;
}