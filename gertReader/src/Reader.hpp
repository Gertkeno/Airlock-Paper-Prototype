#pragma once
#include <string>
#include <list>
#include <map>
#include <iostream>

class Story
{
	struct Field
	{
		std::string text;
		enum type_t
		{
			BASIC_TEXT   = 0x1,
			LINK_TO      = 0x2,
			VARIABLE_IF  = 0x4,
			VARIABLE_SET = 0x8,
		} type;

		std::string parameters;
		bool lineBreak;

		Field() : type (BASIC_TEXT), lineBreak (false) {}
	};
	using Chapter = std::list <Field>;

	std::map <std::string, Chapter> nodes;
public:
	Story (const std::string & filename);
};
