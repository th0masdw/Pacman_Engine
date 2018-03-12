#pragma once

class GameObject;

class BaseComponent
{
public:
	BaseComponent();
	virtual ~BaseComponent();

	void SetGameObject(GameObject* pObject);
	GameObject* GetGameObject() const;

	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

protected:
	friend class GameObject;

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;

	GameObject* m_pGameObject;
};