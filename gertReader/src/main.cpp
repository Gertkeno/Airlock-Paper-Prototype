#include <SDL2/SDL.h>
#include <stdexcept>
#include <iostream>
#include "Reader.hpp"

int main (int argc, char ** argv)
{
	if (SDL_Init (SDL_INIT_VIDEO) != 0)
		throw std::runtime_error {"Couldn't init SDL" + std::string (SDL_GetError())};

	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			try
			{
				Story test (argv [i]);
				test.graph ("Chapter 2");
				test.play ("Chapter 2");
			}
			catch (const std::runtime_error & e)
			{
				std::cerr << "runtime error: " << e.what() << std::endl;
				SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, ">:(", e.what(), nullptr);
			}
			catch (const std::exception & e)
			{
				std::cerr << e.what() << std::endl;
				SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "Oops!", "This is probably my fault", nullptr);
			}
		}
	}
	else
	{
		std::cout << "No input files" << std::endl;
	}

	SDL_Quit();
}
