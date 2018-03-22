#pragma once

#include "Engine/Scenegraph/GameObject.h"
#include "Engine/Helpers/Structs.h"
class GameTime;
struct vec2;
class TextComponent;

class FPSObject : public GameObject
{
public:
	explicit FPSObject(const std::string& fontFile, unsigned int fontSize, const Color& color, const glm::vec2& pos);
	virtual ~FPSObject() = default;

	void Update(const GameTime& time);

	void SetColor(const Color& color);
	void SetPosition(const glm::vec2& pos);

private:
	TextComponent* m_pTextComponent;
	Color m_Color;
};