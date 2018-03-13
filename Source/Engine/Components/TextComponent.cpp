#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Engine/Graphics/Font.h"
#include "Engine/Graphics/Texture2D.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Managers/ResourceManager.h"
#include "Engine/Scenegraph/GameObject.h"

TextComponent::TextComponent()
	: m_Text{},
	m_Color{ 255.0f, 255.0f, 255.0f, 255.0f },
	m_NeedsUpdate{ false }
{
}

TextComponent::TextComponent(const string& text, const Color& color, const string& fontFile, unsigned int size)
	: m_Text{ text },
	m_Color{ color },
	m_pFont{ ResourceManager::GetInstance().LoadFont(fontFile, size) },
	m_NeedsUpdate(true)
{
}

TextComponent::~TextComponent()
{
	delete m_pTexture;
}

void TextComponent::Update(float deltaTime) {
	UNREFERENCED_PARAMETER(deltaTime);

	if (m_NeedsUpdate && m_pFont) {
		SDL_Color color = { Uint8(m_Color.r), Uint8(m_Color.g), Uint8(m_Color.b) };
		SDL_Surface* pSurf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);

		if (pSurf == nullptr)
			throw runtime_error("Could not create SDL Surface: " + string(SDL_GetError()));

		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), pSurf);

		if (pTexture == nullptr)
			throw runtime_error("Could not create SDL Texture: " + string(SDL_GetError()));

		SDL_FreeSurface(pSurf);

		delete m_pTexture;
		m_pTexture = new Texture2D(pTexture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::Draw() const {
	if (m_pTexture) {
		GameObject* pObject = GetGameObject();
		Vector2 pos = pObject->GetTransform()->GetPosition();

		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	} else {
		Debug::LogError("TextComponent::Draw() - Texture not loaded!");
	}
}

void TextComponent::SetText(const string& text, const Color& color) {
	m_Text = text;
	m_Color = color;
	m_NeedsUpdate = true;
}

void TextComponent::SetFont(const string& file, unsigned int size) {
	m_pFont = ResourceManager::GetInstance().LoadFont(file, size);
	m_NeedsUpdate = true;
}