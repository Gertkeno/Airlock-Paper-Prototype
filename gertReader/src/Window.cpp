#include "Window.hpp"
#include <SDL2/SDL.h>

Window::Window (const char * title)
{
	SDL_CreateWindowAndRenderer (800, 600, SDL_WINDOW_RESIZABLE, &ptr, &rend);
	SDL_SetWindowTitle (ptr, title);
}
