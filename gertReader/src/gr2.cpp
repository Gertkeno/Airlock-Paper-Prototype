#include "gr2.hpp"

#include <iostream>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <fstream>

#include "stringfuncs.hpp"
#include "Window.hpp"
#include "Font.hpp"

extern Font * gfont;

gr2::gr2 (const std::string & filename)
	: _chapterProgress {0}
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
		trunc_front (word);
		if (word [0] == '#')
		{
			 currentChapter = trunc_whitespacer (word.substr (1));
			 if (_firstChapter.empty())
				_firstChapter = currentChapter;

			 #ifndef NDEBUG
			 std::cout << "CHAPTER: \"" << currentChapter << "\"\n";
			 #endif
		}
		else if (word.find ("//") == 0)
		{
			std::getline (c, word);
			continue;
		}
		else if (word [0] == '~')
		{
			std::cout << "Function start\n";
			const auto breakfind {word.find (':')};
			if (breakfind == std::string::npos)
				throw std::runtime_error {"Missing ending : in function declaration " + std::to_string (line)};
			std::string function {trunc_whitespacer (word.substr (1, breakfind-1))};

			std::transform (function.begin(), function.end(), function.begin(), tolower);

			Line::Attrib lf;
			if (function == "if")
				lf.type = Line::Attrib::CONDITIONAL;
			else if (function == "set")
				lf.type = Line::Attrib::SET;
			else if (function == "unset")
				lf.type = Line::Attrib::UNSET;
			else if (function == "raise")
				lf.type = Line::Attrib::RAISE;
			else if (function == "lower")
				lf.type = Line::Attrib::LOWER;
			else if (function == "link")
				lf.type = Line::Attrib::LINK_TO;
			else if (function == "name")
				lf.type = Line::Attrib::NAME;
			else
				throw std::runtime_error {"In chapter \"" + currentChapter + "\" Unkown function of type \"" + function + "\"" + " at line: " + std::to_string (line)};

			lf.parameters = trunc_whitespacer (word.substr (breakfind+1));

			#ifndef NDEBUG
			std::cout << "FUNCTION:\n\ttype: " << lf.type << "\n\tparameter: \"" << lf.parameters << "\"\n";
			#endif

			_chapters [currentChapter].back().attributes.push_back (lf);
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
			Line line {word, inChoiceBlock};

			_chapters [currentChapter].push_back (line);
		}

		++line;
	}

	// POST COMPILE CHECKS
	for (auto & i : _chapters)
	{
		for (auto & f : i.second)
		{
			for (auto & c : f.attributes)
			{
				if (c.type == Line::Attrib::LINK_TO)
				{
					if (_chapters.count (c.parameters) == 0)
						throw std::runtime_error {"Chapter \"" + i.first + "\" links to \"" + c.parameters + "\", which does not exist!"};
				}
			}
		}
	}

	#ifndef NDEBUG
	std::cout << "=== DONE READING ===\n";
	#endif

	_currentChapter = _firstChapter;
}

static std::map <std::string, bool> variables;
static int paranoia;

void gr2::process_text (const Line & c)
{
	bool conditionalMatch = true;
	for (auto & i : c.attributes)
	{
		if (i.type == Line::Attrib::CONDITIONAL)
			conditionalMatch = variables [i.parameters];
		else
			continue;
		break;
	}

	if (not conditionalMatch)
		return;
	for (auto & i : c.attributes)
	{
		switch (i.type)
		{
		case Line::Attrib::LINK_TO:
			_currentChapter = i.parameters;
			_chapterProgress = 0;
			break;
		case Line::Attrib::SET:
			variables [i.parameters] = true;
			break;
		case Line::Attrib::UNSET:
			variables [i.parameters] = false;
			break;
		case Line::Attrib::RAISE:
			paranoia += std::stoi (i.parameters);
			break;
		case Line::Attrib::LOWER:
			paranoia -= std::stoi (i.parameters);
			break;
		case Line::Attrib::CONDITIONAL:
		case Line::Attrib::NAME:
			break;
		}
	}
}

void gr2::draw() const
{
}

void gr2::draw (Window * w) const
{
}

bool gr2::select_option (int i)
{
}

bool gr2::select_option (int x, int y)
{
}
