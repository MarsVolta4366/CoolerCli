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
		void tempPrintArgs();
	private:
		std::map<std::string, std::string> m_Args;
	};
}