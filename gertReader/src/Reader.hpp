#pragma once
#include <string>
#include <list>
#include <map>
#include <iostream>

// Not supporting else-if since it's hard to do and easy to emulate

class Story
{
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
			CONDITIONAL_TEXT,	// 7
		} type;

		std::string parameters;
		bool lineBreak;

		Field() : type (BASIC_TEXT), lineBreak (false) {}
	};
	using Chapter = std::list <Field>;

	std::map <std::string, Chapter> nodes;
public:
	Story (const std::string & filename);

	void graph (const std::string & start, int indent = 0);
};
