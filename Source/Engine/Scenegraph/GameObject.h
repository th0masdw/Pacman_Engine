#pragma once

#include "Engine/Helpers/Structs.h"

class GameObject
{
public:
	GameObject(const Vector2& pos = { 0.0f, 0.0f });
	virtual ~GameObject();

	void RootUpdate(float deltaTime);
	void RootDraw() const;

	void AddChild(GameObject* pChild);
	void RemoveChild(GameObject* pChild, bool deleteObject = true);

	void SetPosition(const Vector2& pos);
	Vector2 GetPosition() const;

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

protected:
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;

private:
	Vector2 m_Position;
	GameObject* m_pParent;
	std::vector<GameObject*> m_pChildren;
};