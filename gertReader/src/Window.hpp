#pragma once
class SDL_Window;
class SDL_Renderer;

class Window
{
	SDL_Window * _ptr;
	SDL_Renderer * _rend;
public:
	Window (const char * title);
	~Window();

	SDL_Window * get_ptr() {return _ptr;}
	SDL_Renderer * get_render() {return _rend;}
};
