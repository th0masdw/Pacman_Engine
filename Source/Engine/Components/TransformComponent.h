#pragma once

#include "BaseComponent.h"
#include "Engine/Helpers/Structs.h"
class GameTime;

class TransformComponent : public BaseComponent
{
public:
	TransformComponent();
	virtual ~TransformComponent() = default;

	void Translate(float x, float y);
	void Translate(const Vector2& pos);

	void Rotate(float angle);

	void Scale(float x, float y);
	void Scale(const Vector2& scale);

	Vector2 GetPosition() const;
	float GetRotation() const;
	Vector2 GetScale() const;

	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;

protected:
	virtual void Update(const GameTime& time) override;
	virtual void Draw() const override;

private:
	Vector2 m_Position;
	float m_Rotation;
	Vector2 m_Scale;
};