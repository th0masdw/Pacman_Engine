#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Texture2D.h"
#include "Engine/Graphics/Font.h"

void ResourceManager::Init()
{
	// load support for png and jpg, this takes a while!
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		throw runtime_error("Failed to load support for png: " + string(SDL_GetError()));
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) {
		throw runtime_error("Failed to load support for jpg: " + string(SDL_GetError()));
	}

	if (TTF_Init() != 0) {
		throw runtime_error("Failed to load support for fonts: " + string(SDL_GetError()));
	}
}

shared_ptr<Texture2D> ResourceManager::LoadTexture(const string& file)
{
	if (file.empty())
		throw runtime_error{ "Filename cannot be empty!" };

	SDL_Texture* pTexture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), file.c_str());
	if (pTexture) {
		auto result = m_Textures.insert({ file, make_shared<Texture2D>(pTexture) });
		return result.first->second;
	} else {
		throw runtime_error{ "File could not be loaded: " + file };
	}
}

shared_ptr<Font> ResourceManager::LoadFont(const string& file, unsigned int size)
{
	if (file.empty())
		throw runtime_error{ "Filename cannot be empty!" };

	auto result = m_Fonts.insert({ file, make_shared<Font>(file, size) });
	return result.first->second;
}