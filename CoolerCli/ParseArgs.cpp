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

ParseArgs::ParseArgsResult ParseArgs::addArgs(std::string command)
{
	std::stringstream ss(command);
	std::string arg;
	std::vector<std::string> args;

	while (std::getline(ss, arg, ' '))
	{
		if (arg.length() > 0) {
			args.push_back(arg);
		}
	}

	for (int i = 0; i < args.size(); i++)
	{
		m_Args[args[i]] = "";

		if (args[i].at(0) == '-') // If arg is a valid command (command must start with a hyphen).
		{
			if (i + 1 != args.size() && args[i + 1].at(0) != '-') // If there's a next arg and it's a value (values can't start with a hyphen).
			{
				m_Args[args[i]] = args[i + 1];
				i++; // Skip next arg because it was a value.
			}
			else
			{
				m_Args[args[i]] = ""; // Default arg value to empty string.
			}
		}
		else
		{
			return ParseArgsResult::Unexpected_Argument;
		}
	}
	return ParseArgsResult::Ok;
}

const std::string ParseArgs::ParseArgsResultToString(ParseArgsResult parseArgsResult)
{
	switch (parseArgsResult)
	{
	case ParseArgsResult::Ok: return "Ok";
	case ParseArgsResult::Unexpected_Argument: return "Unexpected Argument";
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