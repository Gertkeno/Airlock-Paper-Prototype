#pragma once
#include <SDL2/SDL_rect.h>
#include <string>

struct SDL_Texture;
struct SDL_Renderer;

namespace color
{
	constexpr SDL_Color BLUE = {0, 0, 0xff, 0xff};
	constexpr SDL_Color WHITE = {0xff, 0xff, 0xff, 0xff};
}

class Font
{
	SDL_Texture * _ptr;
	// not allocated
	SDL_Renderer * _render;
public:
	Font (unsigned char *, unsigned int, SDL_Renderer *, int w);
	~Font();

	const int width;

	void draw_at (int x, int y, char l, SDL_Color = color::WHITE);
	void draw_at (SDL_Point p, char l, SDL_Color c = color::WHITE) {draw_at (p.x, p.y, l, c);}

	int draw_line (SDL_Point p, const std::string &, SDL_Color c = color::WHITE);
};
