#pragma once
#include <memory>

#include "Engine/Graphics/Texture2D.h"
#include "GameObject.h"

class TextureObject : public GameObject
{
public:
	TextureObject() = default;
	virtual ~TextureObject();

	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;

	void SetTexture(const std::string& filename);

	TextureObject(const TextureObject& other) = delete;
	TextureObject(TextureObject&& other) = delete;
	TextureObject& operator=(const TextureObject& other) = delete;
	TextureObject& operator=(TextureObject&& other) = delete;

protected:
	std::shared_ptr<Texture2D> m_Texture;
};