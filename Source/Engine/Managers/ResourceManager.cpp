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
	string fullPath = file.c_str();
	SDL_Texture *texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) {
		throw runtime_error("Failed to load texture: " + string(SDL_GetError()));
	}
	return make_shared<Texture2D>(texture);
}

shared_ptr<Font> ResourceManager::LoadFont(const string& file, unsigned int size)
{
	string fullPath = file.c_str();
	return make_shared<Font>(fullPath, size);
}