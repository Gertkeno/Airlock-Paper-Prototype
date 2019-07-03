#pragma once
#include <string>
#include <list>
#include <map>
#include <iostream>
#include <functional>

class Window;
class Font;

class Story
{
public:
	struct Field
	{
		std::string text;
		enum type_t
		{
			BASIC_TEXT,		// 0
			LINK_TO,		// 1
			FUNC_IF,		// 2
			FUNC_ELSE_IF,	// 3
			FUNC_ELSE,		// 4
			FUNC_SET,		// 5
			FUNC_UNSET,		// 6
			FUNC_AND,		// 7
			CONDITIONAL_TEXT,	// 8
		} type;

		std::string parameters;
		bool carriageReturn;

		Field() : type (BASIC_TEXT), carriageReturn (false) {}
	};
private:
	using Chapter = std::list <Field>;

	std::map <std::string, Chapter> nodes;
	std::string firstChapter;

	void graph (const std::string & s, int indent);

	using writer_f = std::function <void (const Field &)>;
	void engine (const std::string & chapter, writer_f) const;
public:
	Story (const std::string & filename);

	void graph (const std::string & start) {graph (start, 0);}
	void graph() {graph (firstChapter);}

	void play (std::string start) const;
	void play() const {play (firstChapter);}

	std::string get_first_chapter() const {return firstChapter;}
	void draw (std::string chapter, const int maxw) const;

	std::string get_clicked (int x, int y) const;
};
