#include <stdexcept>
#include <iostream>
#include "gr2.hpp"

int main (int argc, char * argv [])
{
	if (argc <= 1)
		return EXIT_FAILURE;
	for (int i = 1; i < argc; ++i)
	{
		try
		{
			gr2 test (argv [i]);
			test.cli_play();
		}
		catch (const std::runtime_error & e)
		{
			std::cerr << argv [i] << '\t' << "runtime error:\t" << e.what() << std::endl;
		}
		catch (const std::exception & e)
		{
			std::cerr << argv [i] << '\t' << e.what() << std::endl;
		}
	}
	return EXIT_SUCCESS;
}
