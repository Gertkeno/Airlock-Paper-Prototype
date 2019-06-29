#include "Reader.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cstring>
#include "stringfuncs.hpp"

extern std::map <std::string, bool> variables;

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
			 #ifndef NDEBUG
			 std::cout << "CHAPTER: \"" << currentChapter << "\"\n";
			 #endif
		}
		else if (word.find ("//") == 0)
		{
			std::getline (c, word);
			continue;
		}
		else if (word[0] == '(')
		{
			std::string function {[&] ()
			{
				const auto endfind {word.find (':')};
				if (endfind != std::string::npos)
					return trunc_whitespacer (word.substr (1, endfind-1));

				std::string f;
				std::getline (c, f, ':');
				return trunc_whitespacer (word.substr (1) + f);
			}()};

			std::transform (function.begin(), function.end(), function.begin(), tolower);

			Field line;
			if (function == "if")
				line.type = Field::FUNC_IF;
			else if (function == "else-if")
				line.type = Field::FUNC_ELSE_IF;
			else if (function == "else")
				line.type = Field::FUNC_ELSE;
			else if (function == "set")
				line.type = Field::FUNC_SET;
			else if (function == "unset")
				line.type = Field::FUNC_UNSET;
			else
				throw std::runtime_error {"Unkown function of type \"" + function + "\""};

			c >> line.parameters;
			#ifndef NDEBUG
			std::cout << "FUNCTION:\n\ttype: " << line.type << "\n\tparameter: \"" << line.parameters << "\"\n";
			#endif

			nodes [currentChapter].push_back (line);
		}
		else if (word.find ("[[") == 0)
		{
			#ifndef NDEBUG
			std::cout << "LINK: \"" << word << "\"\n";
			#endif
			Field line;
			line.type = Field::LINK_TO;
			const auto endfind {word.find ("]]")};
			if (endfind == std::string::npos)
			{
				std::string endAppender;
				std::getline (c, endAppender, ']');
				word += endAppender;
				if (c.get() != ']')
					throw std::runtime_error {"Missing last ']' in link: \"" + word + '"'};
			}
			else
				word = word.substr (0, endfind);

			const auto breakfind {word.find ('|')};
			if (breakfind == std::string::npos)
			{
				line.text = trunc_whitespacer (word.substr (2));
				line.parameters	= line.text;
			}
			else
			{
				line.text = trunc_whitespacer (word.substr (2, breakfind-2));
				line.parameters = trunc_whitespacer (word.substr (breakfind+1));
			}

			#ifndef NDEBUG
			std::cout << "\ttext: \"" << line.text << "\"\n\tlink: \"" << line.parameters << "\"\n";
			#endif
			nodes [currentChapter].push_back (line);
		}
		else if (word[0] == '[')
		{
			Field line;
			line.type = Field::CONDITIONAL_TEXT;
			const auto breakfind {word.find ("]")};
			if (breakfind == std::string::npos)
			{
				std::string addr;
				std::getline (c, addr, ']');
				line.text = trunc_whitespacer (word.substr (1) + addr);
			}
			else
				line.text = trunc_whitespacer (word.substr(1, breakfind-1));

			nodes [currentChapter].push_back (line);
		}
		else
		{
			Field line;
			line.text = word;

			nodes [currentChapter].push_back (line);
		}
	}
}

void Story::graph (const std::string & s, int indent)
{
	static std::map <std::string, bool> ips;
	if (indent == 0)
		ips.clear();

	std::cout << std::string (indent, '\t');
	std::cout << "#" << s << '\n';
	if (ips [s])
		return;
	else
		ips [s] = true;

	for (auto & i : nodes [s])
	{
		if (i.type == Field::LINK_TO)
		{
			graph (i.parameters, indent+1);
		}
	}
}
