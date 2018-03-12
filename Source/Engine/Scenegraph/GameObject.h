#pragma once

#include "Engine/Components/TransformComponent.h"
class BaseComponent;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void RootUpdate(float deltaTime);
	void RootDraw() const;

	void AddChild(GameObject* pChild);
	void RemoveChild(GameObject* pChild, bool deleteObject = true);

	void AddComponent(BaseComponent* pComp);
	void RemoveComponent(BaseComponent* pComp, bool deleteComp = true);

	TransformComponent* GetTransform() const;

#pragma region Template Functions
	template<class T> T* GetChild() {
		for (GameObject* pChild : m_pChildren) {
			if (pChild && typeid(*pChild) == typeid(T))
				return static_cast<T*>(pChild);
		}
		return nullptr;
	}

	template<class T> vector<T*> GetChildren() {
		vector<T*> children;

		for (GameObject* pChild : m_pChildren) {
			if (pChild && typeid(*pChild) == typeid(T))
				children.push_back(static_cast<T*>(pChild));
		}
		return children;
	}

	template<class T> T* GetComponent() {
		for (BaseComponent* pComp : m_pComponents) {
			if (pComp && typeid(*pComp) == typeid(T))
				return static_cast<T*>(pComp);
		}
		return nullptr;
	}

	template<class T> vector<T*> GetComponents() {
		vector<T*> components;

		for (BaseComponent* pComp : m_pComponents) {
			if (pComp && typeid(*pComp) == typeid(T))
				components.push_back(static_cast<T*>(pComp));
		}
		return components;
	}
#pragma endregion

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

protected:
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;

private:
	TransformComponent* m_pTransform;
	GameObject* m_pParent;
	std::vector<GameObject*> m_pChildren;
	std::vector<BaseComponent*> m_pComponents;
};