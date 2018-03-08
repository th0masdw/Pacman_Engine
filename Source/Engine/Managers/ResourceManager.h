#pragma once
#include "Engine/Helpers/Singleton.h"

class Texture2D;
class Font;

class ResourceManager final : public Singleton<ResourceManager>
{
public:
	ResourceManager() = default;

	void Init(std::string&& data);

	std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
	std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size);

private:
	std::string m_DataPath;
};