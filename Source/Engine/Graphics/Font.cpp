#include "MiniginPCH.h"
#include "Font.h"

Font::Font(const string& fullPath, unsigned int size) : m_Font(nullptr), m_Size(size)
{
	m_Font = TTF_OpenFont(fullPath.c_str(), size);

	if (m_Font == nullptr) {
		throw runtime_error("Failed to load font: " + string(SDL_GetError()));
	}
}

Font::~Font()
{
	TTF_CloseFont(m_Font);
}

TTF_Font* Font::GetFont() const {
	return m_Font;
}