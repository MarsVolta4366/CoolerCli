#pragma once
#include <map>
#include <string>

namespace coolercli {

	class ParseArgs
	{
	public:
		ParseArgs() = default;
		~ParseArgs() = default;

		enum ParseArgsResult { Ok, Unexpected_Argument };

		void addArgs(int argc, char* argv[]); // Remove eventually.

		ParseArgsResult addArgs(std::string str);
		static const std::string ParseArgsResultToString(ParseArgsResult parseArgsResult);
		bool argKeyExists(const std::string& arg);
		std::string getArgValue(const std::string& argKey);

		void tempPrintArgs(); // Remove, just here for debugging.
	private:
		std::map<std::string, std::string> m_Args;
	};
}