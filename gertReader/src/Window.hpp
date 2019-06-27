#pragma once
class SDL_Window;
class SDL_Renderer;

class Window
{
	SDL_Window * ptr;
	SDL_Renderer * rend;
public:
	Window (const char * title);

	SDL_Window * get_ptr() {return ptr;}
	SDL_Renderer * get_render() {return rend;}
};
