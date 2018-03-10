#include "MiniginPCH.h"
#include "RectangleObject.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Managers/EventManager.h"

RectangleObject::RectangleObject(const Vector2& pos, float width, float height, const Color& color)
	: GameObject(pos),
	m_Width{ width },
	m_Height{ height },
	m_Color{ color }
{
}

void RectangleObject::Update(float deltaTime) {
	UNREFERENCED_PARAMETER(deltaTime);
}

void RectangleObject::Draw() const {
	Renderer::GetInstance().RenderRect(m_Position, m_Width, m_Height, m_Color);
}

void RectangleObject::SetDimensions(float width, float height) {
	m_Width = width;
	m_Height = height;
}

void RectangleObject::SetColor(const Color& color) {
	m_Color = color;
}