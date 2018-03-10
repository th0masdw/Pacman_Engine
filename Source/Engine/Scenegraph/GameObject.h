#pragma once

#include "Engine/Helpers/Structs.h"

class GameObject
{
public:
	GameObject(const Vector2& pos = { 0.0f, 0.0f });
	virtual ~GameObject() = default;

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;

	void SetPosition(const Vector2& pos);

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

protected:
	Vector2 m_Position;
};