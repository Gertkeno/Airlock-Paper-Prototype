#include <SDL2/SDL.h>
#include <stdexcept>
#include <iostream>
#include "gr2.hpp"
#include "Window.hpp"
#include "Font.hpp"

// bad
Font * gfont;

//inline bool loop_gui (SDL_Event * e, Window * w)
//{
	//static std::string guichapter;
	//while (SDL_PollEvent (e))
	//{
		//switch (e->type)
		//{
		//case SDL_QUIT:
			//return false;
		//case SDL_DROPFILE:
			//if (guistory != nullptr)
				//delete guistory;
			//std::cout << "Loading story file " << e->drop.file << std::endl;
			//guistory = new Story (e->drop.file);
			//guichapter = guistory->get_first_chapter();
			//break;
		//case SDL_MOUSEBUTTONUP:
			//const auto clicked {guistory->get_clicked (e->button.x, e->button.y)};
			//if (clicked.empty())
				//break;
			//guichapter = clicked;
			//break;
		//}
	//}
//
	//SDL_RenderClear (w->get_render());
	//if (guistory != nullptr)
	//{
		//int width, height;
		//SDL_GetWindowSize (w->get_ptr(), &width, &height);
		//guistory->draw (guichapter, width);
	//}
	////f->draw_at (0, 0, 'a');
//
	//SDL_RenderPresent (w->get_render());
//
	//SDL_Delay (32);
	//return true;
//}

int main (int argc, char * argv [])
{
	if (SDL_Init (SDL_INIT_VIDEO) != 0)
		throw std::runtime_error {"Couldn't init SDL" + std::string (SDL_GetError())};

	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			try
			{
				gr2 test (argv [i]);
				//test.play();
			}
			catch (const std::runtime_error & e)
			{
				std::cerr << argv [i] << '\t' << "runtime error:\t" << e.what() << std::endl;
				SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, ">:(", e.what(), nullptr);
			}
			catch (const std::exception & e)
			{
				std::cerr << argv [i] << '\t' << e.what() << std::endl;
				SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "Oops!", "This is probably my fault", nullptr);
			}
		}
	}
	else
	{
		std::cout << "No input files" << std::endl;
		//SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "Hey, Listen", "This is a command line application, you must drag a file onto the executable, or open it in cmd", nullptr);

		Window win("gert reader");

		extern unsigned char font_bmp;
		extern unsigned int font_bmp_len;
		gfont = new Font (&font_bmp, font_bmp_len, win.get_render(), 16);

		//SDL_Event e;
		try
		{
			//while (loop_gui (&e, &win));
		}
		catch (const std::runtime_error & e)
		{
			std::cerr << "runtime error: " << e.what() << std::endl;
			SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, ">:(", e.what(), nullptr);
		}

		delete gfont;
	}

	SDL_Quit();
}
