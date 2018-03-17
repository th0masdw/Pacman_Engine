#pragma once

#include "BaseComponent.h"
#include "Engine/Helpers/Structs.h"
struct vec2;
class GameTime;

//Rectangle shape -> no other shapes supported because of SDL
class ShapeComponent : public BaseComponent
{
public:
	explicit ShapeComponent(float width = 1.0f, float height = 1.0f, const Color& color = { 255.0f, 255.0f, 255.0f, 255.0f });
	virtual ~ShapeComponent() = default;

	void SetDimensions(float width, float height);
	void SetDimensions(const glm::vec2& size);
	void SetColor(const Color& color);

	ShapeComponent(const ShapeComponent& other) = delete;
	ShapeComponent(ShapeComponent&& other) = delete;
	ShapeComponent& operator=(const ShapeComponent& other) = delete;
	ShapeComponent& operator=(ShapeComponent&& other) = delete;

protected:
	virtual void PostInitialize() override;
	virtual void Update(const GameTime& time) override;
	virtual void Draw() const override;

private:
	float m_Width;
	float m_Height;
	Color m_Color;
};