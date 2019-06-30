#include "Window.hpp"
#include <SDL2/SDL.h>

Window::Window (const char * title)
{
	SDL_CreateWindowAndRenderer (800, 600, SDL_WINDOW_RESIZABLE, &_ptr, &_rend);
	SDL_SetWindowTitle (_ptr, title);
}

Window::~Window()
{
	SDL_DestroyRenderer (_rend);
	SDL_DestroyWindow (_ptr);
}
