#pragma once

inline void trunc_front (std::string & r)
{
	if (r.empty())
		return;
	while (std::isspace (r.front()))
		r.erase(r.begin());
}

inline void trunc_back (std::string & r)
{
	if (r.empty())
		return;
	while (std::isspace (r.back()))
		r.pop_back();
}

inline void trunc_whitespace (std::string & r)
{
	trunc_front (r);
	trunc_back (r);
}

inline std::string trunc_whitespacer (std::string r)
{
	trunc_whitespace (r);
	return r;
}
