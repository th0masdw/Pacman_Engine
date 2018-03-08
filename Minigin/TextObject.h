#pragma once

#include "TextureObject.h"

class Font;

class TextObject : public TextureObject
{
public:
	explicit TextObject(const std::string& text, std::shared_ptr<Font> font);
	virtual ~TextObject() = default;

	virtual void Update() override;

	void SetText(const std::string& text);

	TextObject(const TextObject& other) = delete;
	TextObject(TextObject&& other) = delete;
	TextObject& operator=(const TextObject& other) = delete;
	TextObject& operator=(TextObject&& other) = delete;

private:
	bool m_NeedsUpdate;
	std::string m_Text;
	std::shared_ptr<Font> m_Font;
};