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
	m_NeedsUpdate{ false },
	m_pTexture(nullptr)
{
}

TextComponent::TextComponent(const std::string& text, const Color& color, const std::string& fontFile, unsigned int size)
	: m_Text{ text },
	m_Color{ color },
	m_pFont{ ResourceManager::GetInstance().LoadFont(fontFile, size) },
	m_NeedsUpdate(true),
	m_pTexture(nullptr)
{
}

TextComponent::~TextComponent()
{
	delete m_pTexture;
}

void TextComponent::PostInitialize()
{
}

void TextComponent::Update(const GameTime& time) 
{
	UNREFERENCED_PARAMETER(time);

	if (m_NeedsUpdate && m_pFont) {
		SDL_Color color = { Uint8(m_Color.r), Uint8(m_Color.g), Uint8(m_Color.b) };
		SDL_Surface* pSurf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);

		if (pSurf == nullptr)
			throw std::runtime_error("Could not create SDL Surface: " + std::string(SDL_GetError()));

		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), pSurf);

		if (pTexture == nullptr)
			throw std::runtime_error("Could not create SDL Texture: " + std::string(SDL_GetError()));

		SDL_FreeSurface(pSurf);

		delete m_pTexture;
		m_pTexture = new Texture2D(pTexture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::Draw() const 
{
	if (m_pTexture) {
		TransformComponent* pComp = GetGameObject()->GetTransform();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pComp->GetPosition(), pComp->GetRotation(), pComp->GetScale());
	} else {
		Debug::LogError("TextComponent::Draw() - Texture not loaded!");
	}
}

void TextComponent::SetText(const std::string& text, const Color& color) 
{
	if (m_Text != text) {
		m_Text = text;
		m_Color = color;
		m_NeedsUpdate = true;
	}
}

void TextComponent::SetFont(const std::string& file, unsigned int size) 
{
	m_pFont = ResourceManager::GetInstance().LoadFont(file, size);
	m_NeedsUpdate = true;
}