#pragma once

#include "GameObject.h"
#include "Engine/Helpers/Structs.h"
class GameTime;

class RectangleObject : public GameObject
{
public:
	explicit RectangleObject(float width = 1, float height = 1, const Color& color = { 255, 255, 255, 255 });
	virtual ~RectangleObject() = default;

	virtual void Update(const GameTime& time);
	virtual void Draw() const;

	void SetDimensions(float width, float height);
	void SetColor(const Color& color);

	RectangleObject(const RectangleObject& other) = delete;
	RectangleObject(RectangleObject&& other) = delete;
	RectangleObject& operator=(const RectangleObject& other) = delete;
	RectangleObject& operator=(RectangleObject&& other) = delete;

protected:
	float m_Width;
	float m_Height;
	Color m_Color;
};