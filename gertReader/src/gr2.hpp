#pragma once
#include <string>
#include <list>
#include <map>

struct Line
{
	std::string text;
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
			EMOTE,
			LOOK_AT,
			WAIT,
		} type;

		std::string parameters;

		static type_t str_to_type (const std::string &);
	};

	std::list <Attrib> attributes;
	std::list <Line> choices;

	Line() {}
	Line (std::string t)
		: text (t)
	{}
};

class Window;

class gr2
{
	// PROGRESSION DATA
	std::string _currentChapter;
	unsigned _chapterProgress;

	// STORAGE
	using _Node = std::list <Line>;
	std::map <std::string, _Node> _chapters;
	std::string _firstChapter;

	// PLAY DATA
	std::string _dialogue, _nameplate;

	const Line * get_current_line() const;
	// true if text is to be displayed / not ignored
	bool process_text (const Line * c);
	bool process_text() {return process_text (get_current_line());}
	bool condition_test_text (const Line * c);
	bool condition_test_text() {return condition_test_text (get_current_line());};
public:
	gr2 (const std::string  & filename);

	void cli_play();
	bool select_option (const Line * c, unsigned i);
	bool select_option (unsigned i) {return select_option (get_current_line(), i);}
};
