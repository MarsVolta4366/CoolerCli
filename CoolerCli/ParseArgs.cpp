#include "pch.h"
#include "ParseArgs.h"
#include <iostream>
#include <regex>
#include<sstream>

using namespace coolercli;

const std::regex arg_regex("(\-[a-z])");

void ParseArgs::addArgs(int argc, char* argv[])
{
	// Skip first arg which is run command.
	argc--;
	argv++;

	for (int i = 0; i < argc; i++)
	{
		std::string s = argv[i];

		auto words_begin = std::sregex_iterator(s.begin(), s.end(), arg_regex);
		auto words_end = std::sregex_iterator();

		if (words_begin == words_end)
		{
			throw std::invalid_argument("Arg " + s + " needs a preceeding key, i.e. (\-[a-z])");
			exit(EXIT_FAILURE);
		}

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
				// If next arg doesn't contain "-", use next arg as value in m_Args map.
				std::string sV = argv[i + 1];
				if (sV.find("-") == -1)
				{
					m_Args[match_str] = sV;
					// Skip next arg because it was used already for the value above.
					argc--;
					argv++;
				}
				else
				{
					// If no value is provided for arg key, default value to empty string.
					m_Args[match_str] = "";
				}
			}
		}
	}
}

void ParseArgs::addArgs(std::string str)
{
	std::stringstream ss(str);
	std::string item;
	std::vector<std::string> args;
	while (std::getline(ss, item, ' '))
	{
		if (item.length() > 0) {
			args.push_back(item);
		}
	}

	char* argv[200];
	for (int i = 0; i < args.size(); i++)
	{
		argv[i] = args[i].data();
	}
	addArgs(args.size(), argv);
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