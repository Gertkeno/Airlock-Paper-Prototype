#pragma once
#include <string>
#include <list>
#include <map>

struct Line
{
	std::string text;
	bool choice;
	struct Attrib
	{
		enum type_t
		{
			LINK_TO,
			CONDITIONAL,
			SET,
			UNSET,
			RAISE,
			LOWER,
			NAME,
		} type;

		std::string parameters;
	};

	std::list <Attrib> attributes;

	Line() : choice (false) {}
	Line (std::string t, bool c)
		: text (t)
		, choice (c)
	{}
};

class Window;

class gr2
{
	// PROGRESSION DATA
	std::string _currentChapter;
	int _chapterProgress;

	// STORAGE
	using _Node = std::list <Line>;
	std::map <std::string, _Node> _chapters;
	std::string _firstChapter;

	// PLAY DATA
	std::string _dialogue, _nameplate;
	std::list <std::string *> _choices;

	// true if text is to be displayed / not ignored
	bool process_text (const Line & c);
public:
	gr2 (const std::string  & filename);

	void cli_play();
	void draw (Window * w) const;
	void draw() const;
	bool select_option (int i);
	bool select_option (int x, int y);
};
