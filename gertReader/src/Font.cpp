#include "Font.hpp"

#include <SDL2/SDL.h>
#include <stdexcept>

Font::Font (unsigned char * sc, unsigned int sl, SDL_Renderer * r, int w)
	: _render (r)
	, width (w)
{
	auto surf {SDL_LoadBMP_RW (SDL_RWFromConstMem (sc, sl), true)};
	if (surf == nullptr)
		throw std::runtime_error {"Big mess up making font, probably SDL init issue or race"};
	SDL_SetColorKey (surf, true, SDL_MapRGB (surf->format, 0xFF, 0, 0xFF));
	_ptr = SDL_CreateTextureFromSurface (_render, surf);
	if (_ptr == nullptr)
		throw std::runtime_error {"Font Texture failed creation " + std::string (SDL_GetError())};
	SDL_FreeSurface (surf);
}

Font::~Font()
{
	SDL_DestroyTexture (_ptr);
}

void Font::draw_at (int x, int y, char l)
{
	SDL_Rect src {(l%16)*32, (l/16)*32, width, 32}, dst {x, y, width, 32};
	SDL_RenderCopy (_render, _ptr, &src, &dst);
}
