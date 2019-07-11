#include "Reader.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

#include <SDL2/SDL.h>

#include "stringfuncs.hpp"
#include "Font.hpp"

static std::map <std::string, bool> variables;

Story::Story (const std::string & filename)
{
	std::ifstream c (filename);
	if (not c.is_open())
		throw std::runtime_error {"Couldn't open file: " + filename};

	std::string word;
	std::string currentChapter {"Start"};
	bool inChoiceBlock {false};
	int line {1};
	while (std::getline (c, word))
	{
		if (word [0] == '#')
		{
			 std::string line;
			 std::getline (c, line);
			 currentChapter = trunc_whitespacer (word.substr (1) + line);
			 if (firstChapter.empty())
				firstChapter = currentChapter;

			 #ifndef NDEBUG
			 std::cout << "CHAPTER: \"" << currentChapter << "\"\n";
			 #endif
		}
		else if (word.find ("//") == 0)
		{
			std::getline (c, word);
			continue;
		}
		else if (word[0] == '~')
		{
			const auto breakfind {word.find (':')};
			if (breakfind == std::string::npos)
				throw std::runtime_error {"Missing ending : in function declaration " + std::to_string (line)};
			std::string function {trunc_whitespacer (word.substr (1, breakfind-1))};

			std::transform (function.begin(), function.end(), function.begin(), tolower);

			Field::Attrib line;
			if (function == "if")
				line.type = Field::Attrib::CONDITIONAL;
			else if (function == "set")
				line.type = Field::Attrib::FUNC_SET;
			else if (function == "unset")
				line.type = Field::Attrib::FUNC_UNSET;
			else
				throw std::runtime_error {"In chapter \"" + currentChapter + "\" Unkown function of type \"" + function + "\""};

			line.parameters = trunc_whitespacer (word.substr (breakfind));

			#ifndef NDEBUG
			std::cout << "FUNCTION:\n\ttype: " << line.type << "\n\tparameter: \"" << line.parameters << "\"\n";
			#endif

			nodes [currentChapter].back().func.push_back (line);
		}
		else if (word [0] == '{')
		{
			if (inChoiceBlock)
				throw std::runtime_error {"Unexpected { inside of choice block: " + std::to_string (line)};
			inChoiceBlock = true;
		}
		else if (word [0] == '}')
		{
			if (not inChoiceBlock)
				throw std::runtime_error {"Unexpected } before choice block start " + std::to_string (line)};
			inChoiceBlock = false;
		}
		else
		{
			Field line;
			line.text = word;

			nodes [currentChapter].push_back (line);
		}

		++line;
	}

	// post compile checks
	for (auto & i : nodes)
	{
		for (auto & f : i.second)
		{
			for (auto & c : f.func)
			{
				if (c.type == Field::Attrib::LINK_TO)
				{
					if (nodes.count (c.parameters) == 0)
						throw std::runtime_error {"Chapter \"" + i.first + "\" links to \"" + c.parameters + "\", which does not exist!"};
				}
			}
		}
	}

	#ifndef NDEBUG
	std::cout << "=== DONE READING ===\n";
	#endif
}

bool Story::Field::parse_functional() const
{
	bool conditionalMet = true;
	for (auto & f : func)
	{
		if (f.type != Attrib::CONDITIONAL)
			continue;
		conditionalMet = variables [f.parameters];
		break;
	}

	if (not conditionalMet)
		return conditionalMet;
	
	for (auto & f : func)
	{
		switch (f.type)
		{
		case Attrib::FUNC_SET:
			variables [f.parameters] = true;
			break;
		case Attrib::FUNC_UNSET:
			variables [f.parameters] = false;
			break;
		}
	}

	return true;
}

void Story::engine (const std::string & chapter, writer_f f) const
{
	for (auto & i : nodes.at (chapter))
	{
		if (i.parse_functional())
			f (i);
	}
}

// CLI PLAYER
static std::vector <std::string> cli_link_to;

void text_adventure (const Story::Field & f)
{
	// if (f.type == Story::Field::LINK_TO)
	// {
		// cli_link_to.push_back (f.parameters);
		// std::cout << '[' << cli_link_to.size() << ' ' << f.text << "] ";
	// }
	// else
	// {
		std::cout << f.text << ' ';
	// }
}

void Story::play (std::string c) const
{
	int input {1};
	while (input != 0)
	{
		if (nodes.count (c) == 0)
			throw std::runtime_error {"Cannot play chapter \"" + c + "\" since it does not exist!"};

		cli_link_to.clear();
		engine (c, text_adventure);

		std::cout << "\n:";
		std::cin >> input;
		
		if (cli_link_to.size() > static_cast <unsigned> (input-1))
		{
			c = cli_link_to [input-1];
		}

		std::cout << std::endl;
	}
}

// GUI PLAYER
inline void cr (SDL_Point & pos)
{
	pos.y += 33;
	pos.x = 0;
}

extern Font * gfont;
static std::map <std::string, SDL_Rect> clickables;
static SDL_Point cursor;

void gui_adventure (const Story::Field & f, unsigned maxw)
{
	auto word_break {[&] (const std::string & s)
	{
		if (cursor.x + s.length() * gfont->width > maxw)
			cr (cursor);
	}};

	auto create_clickable {[&] (const std::string & text, const std::string & link)
	{
		const int width (text.length() * gfont->width);
		clickables [link] = SDL_Rect {cursor.x, cursor.y, width, 33};
	}};

	// if (f.type == Story::Field::LINK_TO)
	// {
		// const std::string t {"[" + f.text + "] "};
		// word_break (t);
		// create_clickable (t, f.parameters);
		// cursor.x = gfont->draw_line (cursor, t, color::BLUE);
	// }
	// else
	// {
		word_break (f.text);
		cursor.x = gfont->draw_line (cursor, f.text + ' ');
	// }
}

void Story::draw (std::string c, const int maxw) const
{
	if (nodes.count (c) == 0)
		throw std::runtime_error {"Couldn't draw chapter \"" + c + "\" because it does not exist!"};

	clickables.clear();
	cursor = {0, 0};

	using namespace std::placeholders;
	engine (c, std::bind (gui_adventure, _1, maxw));
}

std::string Story::get_clicked (int x, int y) const
{
	for (auto & i : clickables)
	{
		if (x < i.second.x)
			continue;
		if (x > i.second.x + i.second.w)
			continue;
		if (y < i.second.y)
			continue;
		if (y > i.second.y + i.second.h)
			continue;
		return i.first;
	}

	return std::string();
}
