#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

#include "ConfigList.h"
#include "../../Transformations/Transformations.h"
#include "../ReadFile.h"

namespace IO
{
	ReadFile::ReadFile(std::string filename)
	{
		if (!validateFilename(filename))
		{
			throw new std::exception("Filename must have an exception of .test");
		}

		this->filename = filename;
	}

	std::vector<std::string> lineSplit(std::string &line, std::string &command)
	{
		std::stringstream ss(line);
		std::vector<std::string> args;
		std::string fragment;
		while (std::getline(ss, fragment)) {
			if (command == "") {
				command = fragment;
				continue;
			}

			args.push_back(fragment);
		}

		return args;
	}

	bool ReadFile::parse()
	{
		std::string line;
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cout << "File with name of" << filename << "cannot be opened or does not exist";
		}

		ConfigList configList();
		while (std::getline(file, line)) {
			bool hasSpace = std::find_if(line.begin(), line.end(), ::isspace) != line.end();
			// Skips the line if it is empty or if it is a comment.
			if (hasSpace || (line[0] == '#')) {
				continue;
			}

			std::string command = "";
			std::vector<std::string> args;
			lineSplit(line, command);
			ValidCommands enumCommand = commandMapping(command);
			switch (enumCommand) {
				case ValidCommands::AMBIENT:
					break;
				case ValidCommands::ATTENUATION:
					break;
				case ValidCommands::CAMERA:
					break;
				case ValidCommands::DIFFUSE:
					break;
				case ValidCommands::DIRECTIONAL_LIGHT:
					break;
				case ValidCommands::EMISSION:
					break;
				case ValidCommands::MAX_DEPTH:
					break;
				case ValidCommands::MAX_VERTEX_NORMALS:
					break;
				case ValidCommands::MAX_VERTICES:
					break;
				case ValidCommands::OUTPUT:
					break;
				case ValidCommands::POINT_LIGHT:
					break;
				case ValidCommands::POP_TRANSFORM:
					break;
				case ValidCommands::PUSH_TRANSFORM:
					break;
				case ValidCommands::ROTATE:
					break;
				case ValidCommands::SCALE:
					break;
				case ValidCommands::SHININESS:
					break;
				case ValidCommands::SIZE:
					break;
				case ValidCommands::SPECULAR:
					break;
				case ValidCommands::SPHERE:
					break;
				case ValidCommands::TRANSLATE:
					break;
				case ValidCommands::TRIANGLE:
					break;
				case ValidCommands::TRIANGLE_NORMAL:
					break;
				case ValidCommands::VERTEX:
					break;
				case ValidCommands::VERTEX_NORMAL:
					break;
				case ValidCommands::UNKNOWN:
					break;
				default:
					// Default is handled in the case above.
			}
		}

		return true;
	}

	ConfigList ReadFile::generateConfigList()
	{
		return ConfigList();
	}

	std::optional<float> ReadFile::stringToFloat(std::string str)
	{
		char *endptr;
		errno = 0;
		const char *charString = str.c_str();
		float newFloat = (float)strtol(charString, &endptr, 0);
		if (errno == ERANGE || *endptr != '\0' || charString == endptr) {
			return std::nullopt;
		}

		return newFloat;
	}

	bool ReadFile::validateFilename(std::string str)
	{
		std::regex pattern("[A-Za-z0-9_- ]+.test");
		return std::regex_match(str, pattern);
	}

	ReadFile::ValidCommands ReadFile::commandMapping(std::string str)
	{
		if (str == "ambient") {
			return ValidCommands::AMBIENT;
		}
		else if (str == "attenuation") 
			return ValidCommands::ATTENUATION;
		else if (str == "camera") 
			return ValidCommands::CAMERA;
		else if (str == "diffuse") 
			return ValidCommands::DIFFUSE;
		else if (str == "directional") 
			return ValidCommands::DIRECTIONAL_LIGHT;
		else if (str == "emission") 
			return ValidCommands::EMISSION;
		else if (str == "maxdepth") 
			return ValidCommands::MAX_DEPTH;
		else if (str == "maxvertnorms") 
			return ValidCommands::MAX_VERTEX_NORMALS;
		else if (str == "maxverts") 
			return ValidCommands::MAX_VERTICES;
		else if (str == "output") 
			return ValidCommands::OUTPUT;
		else if (str == "point") 
			return ValidCommands::POINT_LIGHT;
		else if (str == "popTransform") 
			return ValidCommands::POP_TRANSFORM;
		else if (str == "pushTransform") 
			return ValidCommands::PUSH_TRANSFORM;
		else if (str == "rotate") 
			return ValidCommands::ROTATE;
		else if (str == "scale") 
			return ValidCommands::SCALE;
		else if (str == "shininess") 
			return ValidCommands::SHININESS;
		else if (str == "size") 
			return ValidCommands::SIZE;
		else if (str == "specular") 
			return ValidCommands::SPECULAR;
		else if (str == "sphere") 
			return ValidCommands::SPHERE;
		else if (str == "translate") 
			return ValidCommands::TRANSLATE;
		else if (str == "tri") 
			return ValidCommands::TRIANGLE;
		else if (str == "trinormal") 
			return ValidCommands::TRIANGLE_NORMAL;
		else if (str == "vertex") 
			return ValidCommands::VERTEX;
		else if (str == "vertexnormal") 
			return ValidCommands::VERTEX_NORMAL;
		else
			return ValidCommands::UNKNOWN;
	}
}
