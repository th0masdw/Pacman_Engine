#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Font.h"
#include "Engine/Graphics/Texture2D.h"

TextObject::TextObject(const string& text, shared_ptr<Font> font) 
	: m_NeedsUpdate(true), m_Text(text), m_Font(font)
{ }

void TextObject::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) {
			stringstream ss; ss << "Render text failed: " << SDL_GetError();
			throw runtime_error(ss.str().c_str());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) {
			stringstream ss; ss << "Create text texture from surface failed: " << SDL_GetError();
			throw runtime_error(ss.str().c_str());
		}
		SDL_FreeSurface(surf);
		m_Texture = make_shared<Texture2D>(texture);
	}
}

void TextObject::SetText(const string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}