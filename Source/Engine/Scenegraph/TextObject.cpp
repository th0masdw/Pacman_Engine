#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Font.h"
#include "Engine/Graphics/Texture2D.h"

TextObject::TextObject(const string& text, shared_ptr<Font> font) 
	: m_NeedsUpdate(true), m_Text(text), m_Font(font)
{ 
}

void TextObject::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 };
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
			throw runtime_error("Render text failed: " + string(SDL_GetError()));

		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
			throw runtime_error("Create text texture from surface failed: " + string(SDL_GetError()));

		SDL_FreeSurface(surf);
		m_Texture = make_shared<Texture2D>(texture);
	}
}

void TextObject::SetText(const string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}