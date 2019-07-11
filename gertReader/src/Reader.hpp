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

		struct Attrib
		{
			enum type_t
			{
				CHOICE,
				LINK_TO,
				CONDITIONAL,
				SET,
				UNSET,
				RAISE,
				LOWER,
			} type;

			std::string parameters;
		};
		std::list <Attrib> func;
	};
private:
	using Chapter = std::list <Field>;

	std::map <std::string, Chapter> nodes;
	std::string firstChapter;
	int chapterProgress;

	std::list <Field *> choices;

	using writer_f = std::function <void (const Field &)>;
	void engine (const std::string & chapter, writer_f) const;
public:
	Story (const std::string & filename);

	void play (std::string start) const;
	void play() const {play (firstChapter);}

	std::string get_first_chapter() const {return firstChapter;}
	void draw (std::string chapter, const int maxw) const;

	std::string get_clicked (int x, int y) const;
};
