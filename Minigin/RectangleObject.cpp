#include "MiniginPCH.h"
#include "RectangleObject.h"
#include "Renderer.h"

RectangleObject::RectangleObject(const Vector2& pos, float width, float height, const Color& color)
	: m_Pos{ pos },
	m_Width{ width },
	m_Height{ height },
	m_Color{ color }
{
}

void RectangleObject::Update() {
	//nothing to do
}

void RectangleObject::Draw() const {
	Renderer::GetInstance().RenderRect(m_Pos, m_Width, m_Height, m_Color);
}

void RectangleObject::SetPosition(const Vector2& pos) {
	m_Pos = pos;
}

void RectangleObject::SetDimensions(float width, float height) {
	m_Width = width;
	m_Height = height;
}

void RectangleObject::SetColor(const Color& color) {
	m_Color = color;
}