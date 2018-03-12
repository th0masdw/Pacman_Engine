#pragma once
#include "Engine/Helpers/Singleton.h"
#include <unordered_map>

class Texture2D;
class Font;

class ResourceManager final : public Singleton<ResourceManager>
{
public:
	ResourceManager() = default;

	void Init();

	std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
	std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size);

private:
	std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_Textures;
	std::unordered_map<std::string, std::shared_ptr<Font>> m_Fonts;
};