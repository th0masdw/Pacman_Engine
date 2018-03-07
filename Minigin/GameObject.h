#pragma once
#include <memory>

#include "Transform.h"
#include "Texture2D.h"
#include "SceneObject.h"

class GameObject : public SceneObject
{
public:
	GameObject() = default;
	virtual ~GameObject();

	void Update() override;
	void Render() const override;

	void SetTexture(const std::string& filename);
	void SetPosition(float x, float y);

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

private:
	Transform m_Transform;
	std::shared_ptr<Texture2D> m_Texture;
};