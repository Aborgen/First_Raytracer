#pragma once
#ifndef USERINPUT_H
#define USERINPUT_H

#include <array>
#include <map>
#include <optional>
#include <string>
#include <vector>

#include "ConfigList.h"

namespace Controll
{
	class UserInput
	{
	public:
		int maxInputLength = 30;
		bool parse(std::vector<std::string> args);
		ConfigList generateConfigList();
	private:
		bool hasBeenParsed = false;
		bool essentialInputPresent = false;
		// Maps from command to number of arguments
		const std::map<std::string, int> validCommands = {
				{"size", 2},
				{"maxdepth", 1},
				{"filename", 1},
		};

		std::map<std::string, std::vector<std::string>> commandToArgs;
		std::optional<float> stringToFloat(std::string str);
		bool validateFilename(std::string filename);
	};
}

#endif // !USERINPUT_H