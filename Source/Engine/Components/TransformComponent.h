#pragma once

#include "BaseComponent.h"
#include "Engine/Helpers/Structs.h"

class TransformComponent : public BaseComponent
{
public:
	TransformComponent();
	virtual ~TransformComponent();

	void Translate(float x, float y);
	void Translate(const Vector2& pos);

	//Rotation?

	void Scale(float x, float y);
	void Scale(const Vector2& scale);

	Vector2 GetPosition() const;
	Vector2 GetScale() const;

	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;

protected:
	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;

private:
	Vector2 m_Position;
	Vector2 m_Scale;
};