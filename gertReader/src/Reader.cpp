#include "Reader.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include "stringfuncs.hpp"

Story::Story (const std::string & filename)
{
	std::ifstream c (filename);
	if (not c.is_open())
		throw std::runtime_error {"Couldn't open file: " + filename};

	std::string word;
	std::string currentChapter = "Start";
	while (c >> word)
	{
		if (word [0] == '#')
		{
			 std::string line;
			 std::getline (c, line);
			 currentChapter = trunc_whitespacer (word.substr (1) + line);
			 std::cout << "Found chapter \"" << currentChapter << "\"\n";
		}
		else if (word.find ("//") == 0)
		{
			std::getline (c, word);
			continue;
		}
		else if (word[0] == '(')
		{
			nodes [currentChapter];
		}
		else if (word.find ("[[") == 0)
		{
			nodes [currentChapter];
		}
		//if (titleParser [0] == '#')
		//{
			//const std::string currentChapter {titleParser.substr (1)};
			//std::cout << "Found chapter \"" << trunc_whitespacer (currentChapter) << "\"\n";
			//std::string word;
			//while (c >> word)
			//{
				//if (word [0] == '(')
				//{
				//}
				//else if (word.find ("[[") == 0)
				//{
				//}
			//}
		//}
	}
}
