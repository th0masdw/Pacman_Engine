#pragma once

#include "Engine/Scenegraph/GameObject.h"
#include "Engine/Helpers/Structs.h"
class GameTime;
struct vec2;
class TextComponent;

class FPSObject : public GameObject
{
public:
	explicit FPSObject(const std::string& fontFile, unsigned int fontSize, const Color& color);
	virtual ~FPSObject() = default;

	void Update(const GameTime& time);
	void SetColor(const Color& color);

private:
	TextComponent* m_pTextComponent;
	Color m_Color;
};