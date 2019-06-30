#pragma once
#include <SDL2/SDL_rect.h>

struct SDL_Texture;
struct SDL_Renderer;

class Font
{
	SDL_Texture * _ptr;
	// not allocated
	SDL_Renderer * _render;
public:
	Font (unsigned char *, unsigned int, SDL_Renderer *, int w);
	~Font();

	const int width;

	void draw_at (int x, int y, char l);
	void draw_at (SDL_Point p, char l) {draw_at (p.x, p.y, l);}
};
