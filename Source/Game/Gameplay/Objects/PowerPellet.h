#pragma once

#include "Pellet.h"
class ShapeComponent;

class PowerPellet : public Pellet
{
public:
	explicit PowerPellet(float size = 15.0f, const Color& color = { 253, 191, 166, 255 }, bool isPoolable = false);
	virtual ~PowerPellet() = default;

	void Update(const GameTime& time);

private:
	bool m_IsDrawing;
	float m_DrawTimer;
	ShapeComponent* m_pShape;
};