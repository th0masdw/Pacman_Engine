#pragma once

#include "BaseComponent.h"
class Texture2D;

class SpriteComponent : public BaseComponent
{
public:
	SpriteComponent() = default;
	SpriteComponent(const std::string& file);
	virtual ~SpriteComponent() = default;

	void SetTexture(const std::string& file);

	SpriteComponent(const SpriteComponent& other) = delete;
	SpriteComponent(SpriteComponent&& other) = delete;
	SpriteComponent& operator=(const SpriteComponent& other) = delete;
	SpriteComponent& operator=(SpriteComponent&& other) = delete;

protected:
	virtual void PostInitialize() override;
	virtual void Update(const GameTime& time) override;
	virtual void Draw() const override;

private:
	std::shared_ptr<Texture2D> m_pTexture;
};

