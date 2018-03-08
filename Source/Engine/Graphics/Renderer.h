#pragma once
#include "Engine/Helpers/Singleton.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Rect;
class Texture2D;
struct Vector2;
struct Color;

class Renderer final : public Singleton<Renderer>
{
public:
	void Init(SDL_Window* window);
	void Draw();
	void Destroy();

	void RenderTexture(const Texture2D& texture, float x, float y) const;
	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

	void RenderRect(const Vector2& pos, float width, float height, const Color& color) const;
	void RenderRect(const SDL_Rect& rect, const Color& color) const;

	SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }

private:
	SDL_Renderer* m_pRenderer = nullptr;
};