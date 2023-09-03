#pragma once
#include <map>
#include <string>

namespace coolercli {
	class ParseArgs
	{
	public:
		ParseArgs() = default;
		~ParseArgs() = default;

		void addArgs(int argc, char* argv[]);
		bool argExists(const std::string& arg);

		void tempPrintArgs(); // Remove, just here for debugging.
	private:
		std::map<std::string, std::string> m_Args;
	};
}