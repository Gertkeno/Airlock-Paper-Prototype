#include "Reader.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cstring>
#include "stringfuncs.hpp"

static std::map <std::string, bool> variables;

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
			const auto breakfind {word.find (':')};
			std::string function {[&] ()
			{
				if (breakfind != std::string::npos)
					return trunc_whitespacer (word.substr (1, breakfind-1));

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

			const auto endfind {word.find (')')};
			if (endfind == std::string::npos)
			{
				std::string t;
				std::getline (c, t, ')');
				line.parameters = trunc_whitespacer (t);
			}
			else
				line.parameters = trunc_whitespacer (word.substr (breakfind, endfind-breakfind));

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

		// user formatting ;)
		if (c.peek() == '\n')
			nodes [currentChapter].back().carriageReturn = true;
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

	for (auto & i : nodes.at (s))
	{
		if (i.type == Field::LINK_TO)
		{
			graph (i.parameters, indent+1);
		}
	}
}

void Story::play (std::string c)
{
	enum c_t
	{
		TRUE,
		FALSE,
		IGNORE,
	} past {IGNORE};

	int input {1};
	while (input != 0)
	{
		int linkIndex {1};
		for (auto & i : nodes.at (c))
		{
			switch (i.type)
			{
			case Field::BASIC_TEXT:
				std::cout << i.text << ' ';
				past = IGNORE;
				if (i.carriageReturn)
					std::cout << std::endl;
				break;

			// conditional
			case Field::CONDITIONAL_TEXT:
				if (past == FALSE)
					break;
				std::cout << i.text << ' ';
				if (i.carriageReturn)
					std::cout << std::endl;
				break;
			case Field::LINK_TO:
				if (past == FALSE)
					break;
				std::cout << linkIndex++ << ") " << i.text << ' ';
				if (i.carriageReturn)
					std::cout << std::endl;
				break;

			// functional non-text
			case Field::FUNC_IF:
				if (variables [i.parameters])
					past = TRUE;
				else
					past = FALSE;
				break;
			case Field::FUNC_ELSE_IF:
				if (past == FALSE and variables [i.parameters])
					past = TRUE;
				break;
			case Field::FUNC_ELSE:
				if (past == TRUE)
					past = FALSE;
				else if (past == FALSE)
					past = TRUE;
				break;
			case Field::FUNC_SET:
				variables [i.parameters] = true;
				break;
			case Field::FUNC_UNSET:
				variables [i.parameters] = false;
				break;
			}
		}

		std::cout << "\n:";
		std::cin >> input;
		
		int copy {input};
		for (auto & i : nodes.at (c))
		{
			if (i.type != Field::LINK_TO)
				continue;
			if (copy-- <= 1)
			{
				c = i.parameters;
				break;
			}
		}
		std::cout << std::endl;
	}
}
