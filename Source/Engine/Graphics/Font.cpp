#include "MiniginPCH.h"
#include "Font.h"

Font::Font(const string& fullPath, unsigned int size) : m_Font(nullptr), m_Size(size)
{
	m_Font = TTF_OpenFont(fullPath.c_str(), size);

	if (m_Font == nullptr) {
		stringstream ss; ss << "Failed to load font: " << SDL_GetError();
		throw runtime_error(ss.str().c_str());
	}
}

Font::~Font()
{
	TTF_CloseFont(m_Font);
}

TTF_Font* Font::GetFont() const {
	return m_Font;
}