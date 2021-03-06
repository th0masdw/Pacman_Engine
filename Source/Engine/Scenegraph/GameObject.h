#pragma once

#include "Engine/Components/TransformComponent.h"
class GameTime;
class BaseComponent;
class GameScene;

class GameObject
{
public:
	explicit GameObject(const Tag tag = Tag::Empty, const Layer layer = Layer::Default, bool isActive = true, bool isPoolable = false);
	virtual ~GameObject();

	void PostInitialize();
	void Update(const GameTime& time);
	void Draw() const;

	void AddChild(GameObject* pChild);
	void RemoveChild(GameObject* pChild, bool deleteObject = true);

	void AddComponent(BaseComponent* pComp);
	void RemoveComponent(BaseComponent* pComp, bool deleteComp = true);

	TransformComponent* GetTransform() const;
	GameObject* GetParent() const;
	GameScene* GetScene() const;
	Tag GetTag() const;
	Layer GetLayer() const;
	bool IsActive() const;
	bool IsPoolable() const;

	void SetScene(GameScene* pScene);
	void SetActive(bool value);

#pragma region Template Functions
	template<class T> T* GetChild() {
		for (GameObject* pChild : m_pChildren) {
			if (pChild && dynamic_cast<T*>(pChild))
				return static_cast<T*>(pChild);
		}
		return nullptr;
	}

	template<class T> std::vector<T*> GetChildren() {
		std::vector<T*> children;

		for (GameObject* pChild : m_pChildren) {
			if (pChild && dynamic_cast<T*>(pChild))
				children.emplace_back(static_cast<T*>(pChild));
		}
		return children;
	}

	template<class T> T* GetComponent() {
		for (BaseComponent* pComp : m_pComponents) {
			if (pComp && dynamic_cast<T*>(pComp))
				return static_cast<T*>(pComp);
		}
		return nullptr;
	}

	template<class T> std::vector<T*> GetComponents() {
		std::vector<T*> components;

		for (BaseComponent* pComp : m_pComponents) {
			if (pComp && dynamic_cast<T*>(pComp))
				components.emplace_back(static_cast<T*>(pComp));
		}
		return components;
	}
#pragma endregion

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

protected:
	Tag m_Tag;
	Layer m_Layer;
	GameObject* m_pParent;
	GameScene* m_pScene;
	bool m_IsActive;
	bool m_IsPoolable;

	TransformComponent* m_pTransform;
	std::vector<GameObject*> m_pChildren;
	std::vector<BaseComponent*> m_pComponents;
};