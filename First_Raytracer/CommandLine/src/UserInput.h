#pragma once

#include <array>
#include <iostream>
#include <map>
#include <optional>
#include <regex>
#include <stack>
#include <string>
#include <vector>

#include "CommandList.h"

class UserInput
{
public:
	int maxInputLength = 30;
	bool parse(std::vector<std::string> args);
	CommandList generateCommandList();
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
