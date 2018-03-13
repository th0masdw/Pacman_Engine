#pragma once

#include "BaseComponent.h"
#include "Engine/Helpers/Structs.h"
class Texture2D;
class Font;

class TextComponent : public BaseComponent
{
public:
	TextComponent();
	explicit TextComponent(const std::string& text, const Color& color, const std::string& fontFile, unsigned int size);
	virtual ~TextComponent();

	void SetText(const std::string& text, const Color& color);
	void SetFont(const std::string& file, unsigned int size);

	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;

protected:
	virtual void Update(float deltaTime) override;
	virtual void Draw() const;

private:
	std::string m_Text;
	std::shared_ptr<Font> m_pFont;
	Texture2D* m_pTexture;
	Color m_Color;
	bool m_NeedsUpdate;
};

