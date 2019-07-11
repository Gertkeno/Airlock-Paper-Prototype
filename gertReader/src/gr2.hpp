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

	using _Node = std::list <Line>;
	std::map <std::string, _Node> _chapters;
	std::string _firstChapter;

	void place_text (const Line & c) const;
	void process_text (const Line & c);
public:
	gr2 (const std::string  & filename);

	void draw (Window * w) const;
	void select_option (int i);
	void select_option (int x, int y);
};
