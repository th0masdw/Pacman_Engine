#include "MiniginPCH.h"
#include "Font.h"

TTF_Font* Font::GetFont() const {
	return m_Font;
}

Font::Font(const std::string& fullPath, unsigned size) : m_Font(nullptr), m_Size(size)
{
	m_Font = TTF_OpenFont(fullPath.c_str(), size);

	if (m_Font == nullptr) {
		std::stringstream ss; ss << "Failed to load font: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}
}

Font::~Font()
{
	TTF_CloseFont(m_Font);
}
