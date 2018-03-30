#include "MiniginPCH.h"
#include "PowerPellet.h"
#include "Engine/Helpers/Structs.h"
#include "Engine/Components/ShapeComponent.h"

PowerPellet::PowerPellet(float size, const Color& color)
	: Pellet(size, color, Tag::PowerPellet, false),
	m_IsDrawing(true),
	m_DrawTimer(0.25f)
{
	m_pShape = GetComponent<ShapeComponent>();
}

void PowerPellet::Update(const GameTime& time)
{
	m_DrawTimer -= time.GetElapsedTime();

	if (m_DrawTimer <= 0.0f) {
		m_IsDrawing = !m_IsDrawing;
		m_DrawTimer = 0.25f;

		Color color = m_pShape->GetColor();
		float alpha = (m_IsDrawing) ? 255.0f : 0.0f;
		m_pShape->SetColor({ color.r, color.g, color.b, alpha });
	}
}