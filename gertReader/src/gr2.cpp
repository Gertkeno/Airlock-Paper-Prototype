#include "gr2.hpp"

#include <iostream>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <fstream>

#include "stringfuncs.hpp"

static constexpr auto IGNORE_TXT {"IGNORE ME"};
static constexpr auto CHOICE_TXT {"CHOICE BLOCK"};

Line::Attrib::type_t Line::Attrib::str_to_type (const std::string & c)
{
	struct
	{
		type_t t;
		const char * name;
	} static constexpr vars []
	{
		{LINK_TO, "link"},
		{CONDITIONAL, "if"},
		{SET, "set"},
		{UNSET, "unset"},
		{RAISE, "raise"},
		{LOWER, "lower"},
		{NAME, "name"},
		{EMOTE, "emote"},
		{LOOK_AT, "lookat"},
		{WAIT, "wait"},
	};

	for (auto & i : vars)
	{
		if (i.name == c)
			return i.t;
	}
	throw std::runtime_error {"Unknown Line Attribute type of " + c};
}

gr2::gr2 (const std::string & filename)
	: _chapterProgress {0}
{
	std::ifstream c (filename);
	if (not c.is_open())
		throw std::runtime_error {"Couldn't open file: " + filename};

	std::string word;
	std::string currentChapter;
	bool inChoiceBlock {false};
	int line {1};
	_Node * operatingList = nullptr;
	while (std::getline (c, word))
	{
		if (word.empty())
		{
			++line;
			continue;
		}

		//std::cout << word [0] << std::endl;
		//std::cout << std::endl;
		trunc_front (word);
		if (word [0] == '#')
		{
			 currentChapter = trunc_whitespacer (word.substr (1));
			 strlower (currentChapter);
			 if (_firstChapter.empty())
				_firstChapter = currentChapter;

			 #ifndef NDEBUG
			 std::cout << "CHAPTER: \"" << currentChapter << "\"\n";
			 #endif
			 operatingList = &_chapters [currentChapter];
		}
		else if (word.find ("//") == 0)
		{
			++line;
			continue;
		}
		else if (operatingList == nullptr)
		{
			throw std::runtime_error {"First line must be a node declaration via #"};
		}
		else if (word [0] == '~')
		{
			const auto breakfind {word.find (':')};
			if (breakfind == std::string::npos)
				throw std::runtime_error {std::to_string (line) + ": Missing ending colon : in function declaration!"};
			std::string function {trunc_whitespacer (word.substr (1, breakfind-1))};
			strlower (function);

			Line::Attrib lf;
			lf.parameters = trunc_whitespacer (word.substr (breakfind+1));
			strlower (lf.parameters);

			try
			{
				lf.type = Line::Attrib::str_to_type (function);
			}
			catch (const std::runtime_error & e)
			{
				throw std::runtime_error {std::to_string (line) + ": \"" + currentChapter + "\"" + e.what()};
			}

			#ifndef NDEBUG
			std::cout << "FUNCTION:\n\ttype: " << lf.type << "\n\tparameter: \"" << lf.parameters << "\"\n";
			#endif

			operatingList->back().attributes.push_back (lf);
		}
		else if (word [0] == '{')
		{
			if (inChoiceBlock)
				throw std::runtime_error {std::to_string (line) + ": Unexpected { inside of choice block!"};
			_chapters [currentChapter].push_back (Line (CHOICE_TXT));
			operatingList = &_chapters [currentChapter].back().choices;
			inChoiceBlock = true;
		}
		else if (word [0] == '}')
		{
			if (not inChoiceBlock)
				throw std::runtime_error {std::to_string (line) + ": Unexpected } before choice block start!"};
			operatingList = &_chapters [currentChapter];
			inChoiceBlock = false;
		}
		else
		{
			Line tmp {word};
			operatingList->push_back (tmp);
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
		std::cout << std::endl;
	}

	#ifndef NDEBUG
	std::cout << "=== DONE READING ===\n";
	#endif

	_currentChapter = _firstChapter;
}

static std::map <std::string, bool> variables;
static int paranoia;

bool gr2::condition_test_text (const Line * c)
{
	bool conditionalMatch = true;
	for (auto & i : c->attributes)
	{
		if (i.type == Line::Attrib::CONDITIONAL)
			conditionalMatch = variables [i.parameters];
		else
			continue;
		break;
	}

	return conditionalMatch;
}

bool gr2::process_text (const Line * c)
{
	bool shownDialogue = true;
	if (c->text == IGNORE_TXT)
		shownDialogue = false;
	else if (c->text == CHOICE_TXT)
		;
	else
		_dialogue = c->text;

	for (auto & i : c->attributes)
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
		case Line::Attrib::NAME:
			_nameplate = i.parameters;
			break;
		// need unreal implementation
		case Line::Attrib::WAIT:
		case Line::Attrib::EMOTE:
		case Line::Attrib::LOOK_AT:

		// don't use
		case Line::Attrib::CONDITIONAL:
			break;
		}
	}
	return shownDialogue;
}

const Line * gr2::get_current_line() const
{
	const _Node & currentChapter {_chapters.at (_currentChapter)};
	if (_chapterProgress >= currentChapter.size())
		return nullptr;

	auto chapterLine {currentChapter.begin()};
	std::advance (chapterLine, _chapterProgress);
	return &*chapterLine;
}

bool gr2::select_option (const Line * c, unsigned i)
{
	if (c->choices.empty())
	{
			++_chapterProgress;
			return true;
	}

	int index = i;
	for (auto & choice : c->choices)
	{
		if (condition_test_text (&choice) and --index == 0)
		{
			++_chapterProgress;
			process_text (&choice);
			return true;
		}
	}

	std::cout << index << std::endl;
	return false;
}

// for testing
void gr2::cli_play()
{
	const Line * cl {get_current_line()};
	while (cl != nullptr)
	{
		// so much garbage gets altered with process_text (), thus the issue with OOP
		if (condition_test_text (cl) and process_text (cl))
		{
			cl = get_current_line();
			std::cout << _nameplate << ":\n" << _dialogue;
			if (not cl->choices.empty())
			{
				std::cout << "\n\n";
				int choicesIndex {0};
				for (auto & i : cl->choices)
				{
					if (condition_test_text (&i))
						std::cout << ++choicesIndex << ") " << i.text << '\n';
				}
			}
			std::cout << "\n//";

			int userChoice;
			std::cin >> userChoice;
			if (userChoice == 0)
				break;

			select_option (cl, userChoice);

		}
		else
			++_chapterProgress;
		cl = get_current_line();
	}
}
