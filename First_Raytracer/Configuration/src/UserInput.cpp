#include <iostream>
#include <regex>

#include "UserInput.h"

namespace Controll
{
	bool UserInput::parse(std::vector<std::string> input)
	{
		if (hasBeenParsed)
		{
			hasBeenParsed = false;
		}

		size_t length = input.size();
		if (length > maxInputLength) {
			throw std::exception("Parse requires input vector's size to not be more than maxInputLength property");
		}

		size_t additionalArgs = 0;
		std::string currentCommand;
		for (size_t i = 0; i < length; i++) {
			std::string token = input.at(i);
			std::map<std::string, int>::const_iterator iter = validCommands.find(token);
			// The input is not a command. Options include junk and an argument.
			// Junk is ignored.
			if (iter == validCommands.end()) {
				// In this case, the input is considered an argument of a command.
				// Note: if the command does not exist as a key in the map,
				// the [] acessor will automatically add it.
				if (additionalArgs > 0) {
					commandToArgs[currentCommand].push_back(token);
					additionalArgs--;
				}


				continue;
			}
			else {
				// In this case, the previously added command is still expecting at least one argument.
				if (additionalArgs > 0) {
					std::cout << currentCommand + " is still expecting " << std::to_string(additionalArgs) << " additional arguments";
					return false;
				}
			}


			currentCommand = iter->first;
			additionalArgs = iter->second;
			// If this is true, a valid command is being considered, but the expected
			// arguments are missing.
			if (i + additionalArgs > length - 1) {
				std::cout << currentCommand + " is still expecting " << std::to_string(additionalArgs) << " additional arguments";
				return false;
			}

			// Without a filename, we're not gonna get anywhere.
			if (currentCommand == "filename")
			{
				std::string filename = input.at(i + 1);
				if (!validateFilename(filename)) {
					std::cout << "Invalid file: " << filename << ".";
					return false;
				}

				essentialInputPresent = true;
			}
		}

		if (!essentialInputPresent)
		{
			std::cout << "Program requires, at minimum, the name of a file [filename title] when initialized from the command line";
			return false;
		}

		hasBeenParsed = true;
		return true;
	}

	ConfigList UserInput::generateConfigList()
	{
		if (!hasBeenParsed)
		{
			throw std::exception("Hey. Caller needs to note the result of parse before it can use this method.");
		}

		ConfigList configList = ConfigList();
		// c++17 feature: structured bindings
		for (auto const&[command, args] : commandToArgs) {
			if (command == "size") {
				std::optional<float> height = stringToFloat(args.at(0));
				std::optional<float> width = stringToFloat(args.at(1));
				if (!(height.has_value() || width.has_value()))
				{
					continue;
				}

				configList.setSize(height.value(), width.value());
			}
			else if (command == "maxdepth") {
				std::optional<float> depth = stringToFloat(args.at(0));
				if (!depth.has_value())
				{
					continue;
				}

				configList.setDepth(depth.value());
			}
			else if (command == "filename") {
				std::string filename = args.at(0);
				configList.setFilename(filename);
			}
		}

		return configList;
	}

	std::optional<float> UserInput::stringToFloat(std::string str)
	{
		char *endptr;
		errno = 0;
		const char *charString = str.c_str();
		float newFloat = (float)strtol(charString, &endptr, 0);
		//   out of range   , extra junk at end,  no conversion at all   
		if (errno == ERANGE || *endptr != '\0' || charString == endptr) {
			return std::nullopt;
		}

		return newFloat;
	}

	bool UserInput::validateFilename(std::string str)
	{
		std::regex pattern("[A-Za-z0-9_-]+[.](txt|json)");
		return std::regex_match(str, pattern);
	}
}