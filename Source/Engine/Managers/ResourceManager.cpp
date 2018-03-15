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
		throw std::runtime_error("Failed to load support for png: " + std::string(SDL_GetError()));
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) {
		throw std::runtime_error("Failed to load support for jpg: " + std::string(SDL_GetError()));
	}

	if (TTF_Init() != 0) {
		throw std::runtime_error("Failed to load support for fonts: " + std::string(SDL_GetError()));
	}
}

std::shared_ptr<Texture2D> ResourceManager::LoadTexture(const std::string& file)
{
	if (file.empty())
		throw std::runtime_error{ "Filename cannot be empty!" };

	SDL_Texture* pTexture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), file.c_str());
	if (pTexture) {
		auto result = m_Textures.insert({ file, std::make_shared<Texture2D>(pTexture) });
		return result.first->second;
	} else {
		throw std::runtime_error{ "File could not be loaded: " + file };
	}
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	if (file.empty())
		throw std::runtime_error{ "Filename cannot be empty!" };

	auto result = m_Fonts.insert({ file, std::make_shared<Font>(file, size) });
	return result.first->second;
}