#include "pch.h"
#include "ParseArgs.h"
#include <iostream>
#include <regex>

// To start, try to store count of every arg and be able to access count through API.

using namespace coolercli;

const std::regex arg_regex("(\-[a-z])");

void ParseArgs::addArgs(int argc, char* argv[])
{
	std::cout << "You have entered " << argc << " arguments." << std::endl;

	for (int i = 0; i < argc; i++)
	{
		std::string s = argv[i];

		auto words_begin = std::sregex_iterator(s.begin(), s.end(), arg_regex);
		auto words_end = std::sregex_iterator();

		for (std::sregex_iterator i = words_begin; i != words_end; i++)
		{
			std::smatch match = *i;
			std::string match_str = match.str();
			m_Args[match_str] = match_str; // TODO: Value should be next arg if no hypen.
		}
	}
}

void ParseArgs::tempPrintArgs()
{
	for (auto const& x : m_Args)
	{
		std::cout << x.first // string (key)
			<< ":"
			<< x.second // string (value)
			<< std::endl;
	}
}