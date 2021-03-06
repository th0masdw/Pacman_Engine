#pragma once

#include "BaseComponent.h"
#include "Engine/Helpers/Structs.h"
struct vec2;

class TransformComponent : public BaseComponent
{
public:
	TransformComponent();
	virtual ~TransformComponent() = default;

	void Translate(float x, float y);
	void Translate(const glm::vec2& pos);

	void Rotate(float angle);

	void Scale(float x, float y);
	void Scale(const glm::vec2& scale);

	glm::vec2 GetPosition() const;
	float GetRotation() const;
	glm::vec2 GetScale() const;

	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;

protected:
	virtual void PostInitialize() override;
	virtual void Update(const GameTime& time) override;
	virtual void Draw() const override;

private:
	glm::vec2 m_Position;
	float m_Rotation;
	glm::vec2 m_Scale;
};