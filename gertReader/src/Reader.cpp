#include "Reader.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cstring>

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
	std::string currentChapter = "Start";
	while (c >> word)
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
			else if (function == "and")
				line.type = Field::FUNC_AND;
			else if (function == "set")
				line.type = Field::FUNC_SET;
			else if (function == "unset")
				line.type = Field::FUNC_UNSET;
			else
				throw std::runtime_error {"In chapter \"" + currentChapter + "\" Unkown function of type \"" + function + "\""};

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
					throw std::runtime_error {"In chapter \"" + currentChapter + "\" Missing last ']' in link: \"" + word + '"'};
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
		if (c.peek() == '\n' and not nodes [currentChapter].empty())
			nodes [currentChapter].back().carriageReturn = true;
	}

	// post compile checks
	for (auto & i : nodes)
	{
		for (auto & f : i.second)
		{
			if (f.type == Field::LINK_TO)
			{
				if (nodes.count (f.parameters) == 0)
					throw std::runtime_error {"Chapter \"" + i.first + "\" links to \"" + f.parameters + "\", which does not exist!"};
			}
		}
	}
}

// BAD GRAPH

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

	if (nodes.count (s) == 0)
		throw std::runtime_error {"Cannot graph chapter \"" + s + "\", since it does not exist!"};
	for (auto & i : nodes.at (s))
	{
		if (i.type == Field::LINK_TO)
		{
			graph (i.parameters, indent+1);
		}
	}
}

enum c_t
{
	TRUE,
	FALSE,
	IGNORE,
};

// CLI PLAYER
void Story::play (std::string c)
{
	c_t past {IGNORE};

	int input {1};
	while (input != 0)
	{
		if (nodes.count (c) == 0)
			throw std::runtime_error {"Cannot play chapter \"" + c + "\" since it does not exist!"};

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
				// just a heads up this is super gross syntax, but false fallthroughs are nice
				if (false) {
				[[fallthrough]];
			case Field::LINK_TO:
				if (past == FALSE)
					break;
				std::cout << '[' << linkIndex++ << ' ' << i.text << "] ";
				}
				if (i.carriageReturn)
					std::cout << std::endl;
				past = IGNORE;
				break;

			// functional non-text
			case Field::FUNC_AND:
				if (past == FALSE)
					break;
				[[fallthrough]];
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

inline void cr (SDL_Point & pos)
{
	pos.y += 33;
	pos.x = 0;
}

std::map <std::string, SDL_Rect> clickables;

void Story::draw (Font * f, std::string c, const int maxw) const
{
	if (nodes.count (c) == 0)
		throw std::runtime_error {"Couldn't draw chapter \"" + c + "\" because it does not exist!"};

	clickables.clear();

	c_t past {IGNORE};
	SDL_Point cursor {0, 0};
	auto word_break {[&] (const std::string & s)
	{
		if (cursor.x + s.length() * f->width > static_cast <unsigned> (maxw))
			cr (cursor);
	}};

	auto create_clickable {[&] (const std::string & text, const std::string & link)
	{
		const int width (text.length() * f->width);
		clickables [link] = SDL_Rect {cursor.x, cursor.y, width, 33};
	}};

	for (auto & i : nodes.at (c))
	{
		switch (i.type)
		{
		case Field::BASIC_TEXT:
			word_break (i.text);
			cursor.x = f->draw_line (cursor, i.text + ' ');
			past = IGNORE;
			if (i.carriageReturn)
				cr (cursor);
			break;

		// conditional
		case Field::CONDITIONAL_TEXT:
			if (past == FALSE)
				break;
			word_break (i.text);
			cursor.x = f->draw_line (cursor, i.text + ' ');
			// just a heads up this is super gross syntax, but false fallthroughs are nice
			if (false) {
			[[fallthrough]];
		case Field::LINK_TO:
			if (past == FALSE)
				break;
			std::string t {"[" + i.text + "] "};
			word_break (t);
			create_clickable (t, i.parameters);
			cursor.x = f->draw_line (cursor, t, color::BLUE);
			}
			if (i.carriageReturn)
				cr (cursor);
			past = IGNORE;
			break;

		// functional non-text
		case Field::FUNC_AND:
			if (past == FALSE)
				break;
			[[fallthrough]];
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
