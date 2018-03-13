#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "Engine/Managers/SceneManager.h"
#include "Engine/Helpers/Structs.h"
#include "Texture2D.h"

void Renderer::Init(SDL_Window* window)
{
	m_pRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (m_pRenderer == nullptr) {
		throw runtime_error("SDL_CreateRenderer Error: " + string(SDL_GetError()));
	}
}

void Renderer::Draw()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
	SDL_RenderClear(m_pRenderer);
	SceneManager::GetInstance().Draw();
	SDL_RenderPresent(m_pRenderer);
}

void Renderer::Destroy()
{
	if (m_pRenderer != nullptr) {
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}
}

void Renderer::RenderTexture(const Texture2D& texture, const Vector2& pos) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(pos.x);
	dst.y = static_cast<int>(pos.y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const Texture2D& texture, const Vector2& pos, float angle, const Vector2& scales) const
{
	SDL_Rect dst;
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	dst.w = static_cast<int>(dst.w * scales.x);
	dst.h = static_cast<int>(dst.h * scales.y);
	dst.x = static_cast<int>(pos.x - dst.w / 2);
	dst.y = static_cast<int>(pos.y - dst.h / 2);

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, double(angle), nullptr, SDL_FLIP_NONE);
}

void Renderer::RenderRect(const Vector2& pos, float width, float height, const Color& color) const {
	SDL_Rect rect{ int(pos.x), int(pos.y), int(width), int(height) };
	RenderRect(rect, color);
}

void Renderer::RenderRect(const SDL_Rect& rect, const Color& color) const {
	SDL_SetRenderDrawColor(m_pRenderer, Uint8(color.r), Uint8(color.g), Uint8(color.b), Uint8(color.a));
	SDL_RenderFillRect(m_pRenderer, &rect);
}