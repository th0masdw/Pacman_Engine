#pragma once

#include "GameObject.h"
#include "../Helpers/Structs.h"

class RectangleObject : public GameObject
{
public:
	explicit RectangleObject(const Vector2& pos = {}, float width = 1, float height = 1, const Color& color = { 255, 255, 255, 255 });
	virtual ~RectangleObject() = default;

	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;

	void SetPosition(const Vector2& pos);
	void SetDimensions(float width, float height);
	void SetColor(const Color& color);

	RectangleObject(const RectangleObject& other) = delete;
	RectangleObject(RectangleObject&& other) = delete;
	RectangleObject& operator=(const RectangleObject& other) = delete;
	RectangleObject& operator=(RectangleObject&& other) = delete;

private:
	float m_Width;
	float m_Height;
	Vector2 m_Pos;
	Color m_Color;
};