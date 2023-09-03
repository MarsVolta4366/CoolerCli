#include "pch.h"
#include "ParseArgs.h"
#include <iostream>
#include <regex>

using namespace coolercli;

const std::regex arg_regex("(\-[a-z])");

void ParseArgs::addArgs(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
	{
		std::string s = argv[i];

		auto words_begin = std::sregex_iterator(s.begin(), s.end(), arg_regex);
		auto words_end = std::sregex_iterator();

		for (std::sregex_iterator j = words_begin; j != words_end; j++)
		{
			std::smatch match = *j;
			std::string match_str = match.str();

			if (i + 1 == argc)
			{
				m_Args[match_str] = "";
			}
			else
			{
				// If next arg doesn't contain "-", use arg as value in m_Args map.
				std::string sV = argv[i + 1];
				if (sV.find("-") == -1)
				{
					m_Args[match_str] = sV;
				}
				else
				{
					m_Args[match_str] = "";
				}
			}
		}
	}
}

bool ParseArgs::argKeyExists(const std::string& arg)
{
	return m_Args.find(arg) != m_Args.end();
}

std::string ParseArgs::getArgValue(const std::string& argKey)
{
	return m_Args[argKey];
}

void ParseArgs::tempPrintArgs() // Remove, just here for debugging.
{
	for (auto const& x : m_Args)
	{
		std::cout << x.first // string (key)
			<< ":"
			<< x.second // string (value)
			<< std::endl;
	}
}