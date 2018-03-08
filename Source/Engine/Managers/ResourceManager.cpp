#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Texture2D.h"
#include "Engine/Graphics/Font.h"

void ResourceManager::Init(string&& dataPath)
{
	m_DataPath = move(dataPath);

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		stringstream ss; ss << "Failed to load support for png: " << SDL_GetError();
		throw runtime_error(ss.str().c_str());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) {
		stringstream ss; ss << "Failed to load support for png: " << SDL_GetError();
		throw runtime_error(ss.str().c_str());
	}

	if (TTF_Init() != 0) {
		stringstream ss; ss << "Failed to load support for fonts: " << SDL_GetError();
		throw runtime_error(ss.str().c_str());
	}
}

shared_ptr<Texture2D> ResourceManager::LoadTexture(const string& file)
{
	string fullPath = (m_DataPath + file).c_str();
	SDL_Texture *texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) {
		stringstream ss; ss << "Failed to load texture: " << SDL_GetError();
		throw runtime_error(ss.str().c_str());
	}
	return make_shared<Texture2D>(texture);
}

shared_ptr<Font> ResourceManager::LoadFont(const string& file, unsigned int size)
{
	string fullPath = (m_DataPath + file).c_str();
	return make_shared<Font>(fullPath, size);
}
