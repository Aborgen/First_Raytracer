#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

#include "InstructionList.h"
#include "../../Transformations/Transformations.h"
#include "../Light/DirectionalLight.h"
#include "../Light/PointLight.h"
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

	std::vector<std::string> lineSplit(const std::string &line, std::string &command)
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
		using namespace Processing;
		std::string line;
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cout << "File with name of" << filename << "cannot be opened or does not exist";
		}

		InstructionList instructions = InstructionList();
		while (std::getline(file, line)) {
			lineNumber++;
			bool hasSpace = std::find_if(line.begin(), line.end(), ::isspace) != line.end();
			// Skips the line if it is empty or if it is a comment.
			if (hasSpace || (line[0] == '#')) {
				continue;
			}

			std::string command = "";
			std::vector<std::string> args = lineSplit(line, command);
			ValidCommands enumCommand = commandMapping(command);
			switch (enumCommand) {
				case ValidCommands::AMBIENT:
					break;
				case ValidCommands::ATTENUATION:
					break;
				case ValidCommands::CAMERA:
					break;
				case ValidCommands::DIFFUSE:
				{
					float r = 0.0f, g = 0.0f, b = 0.0f;
					parseColor(args, r, g, b);

					MaterialProps newProps = instructions.popMaterialProps();
					newProps.setDiffuse(r, g, b);
					instructions.pushMaterialProps(newProps);
					break;
				}
				case ValidCommands::DIRECTIONAL_LIGHT:
				{
					float x = 0.0f, y = 0.0f, z = 0.0f,
						  r = 0.0f, g = 0.0f, b = 0.0f;
					parseLight(args, x, y, z, r, g, b);

					DirectionalLight light(x, y, z, r, g, b);
					instructions.pushLight(light);
					break;
				}
				case ValidCommands::EMISSION:
				{
					float r = 0.0f, g = 0.0f, b = 0.0f;
					parseColor(args, r, g, b);

					MaterialProps newProps = instructions.popMaterialProps();
					newProps.setEmission(r, g, b);
					instructions.pushMaterialProps(newProps);
					break;
				}
				case ValidCommands::MAX_DEPTH:
					break;
				case ValidCommands::MAX_VERTEX_NORMALS:
					break;
				case ValidCommands::MAX_VERTICES:
					break;
				case ValidCommands::OUTPUT:
					break;
				case ValidCommands::POINT_LIGHT:
				{
					float x = 0.0f, y = 0.0f, z = 0.0f,
						  r = 0.0f, g = 0.0f, b = 0.0f;
					parseLight(args, x, y, z, r, g, b);

					PointLight light(x, y, z, r, g, b);
					instructions.pushLight(light);
					break;
				}
				case ValidCommands::POP_TRANSFORM:
					break;
				case ValidCommands::PUSH_TRANSFORM:
					break;
				case ValidCommands::ROTATE:
					break;
				case ValidCommands::SCALE:
					break;
				case ValidCommands::SHININESS:
				{
					std::optional<float> optIntensity = stringToFloat(args[0]);
					float intensity = optIntensity.has_value() ? optIntensity.value() : 0.0f;

					MaterialProps newProps = instructions.popMaterialProps();
					newProps.setShininess(intensity);
					instructions.pushMaterialProps(newProps);
					break;
				}
				case ValidCommands::SIZE:
					break;
				case ValidCommands::SPECULAR:
				{
					float r = 0.0f, g = 0.0f, b = 0.0f;
					parseColor(args, r, g, b);

					MaterialProps newProps = instructions.popMaterialProps();
					newProps.setSpecular(r, g, b);
					instructions.pushMaterialProps(newProps);
					break;
				}
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

	void ReadFile::parseColor(const std::vector<std::string> &args, float &r, float &g, float &b)
	{
		if (args.size() != 3) {
			std::string message = "parseColor currently only works for rgb (" + filename + " line " + std::to_string(lineNumber) + ")";
			throw new std::exception(message.c_str());
		}

		std::optional<float> optR = stringToFloat(args[0]);
		std::optional<float> optG = stringToFloat(args[1]);
		std::optional<float> optB = stringToFloat(args[2]);
		if (optR.has_value()) {
			r = optR.value();
		}

		if (optG.has_value()) {
			g = optG.value();
		}

		if (optB.has_value()) {
			b = optB.value();
		}
	}

	void ReadFile::parseLight(const std::vector<std::string> &args,
							  float &x, float &y, float &z, float &r, float &g, float &b)
	{
		if (args.size() != 6) {
			std::string message = "Line is incorrectly formatted (" + filename + " line " + std::to_string(lineNumber) + ")";;
			throw new std::exception(message.c_str());
		}

		std::optional<float> optX = stringToFloat(args[0]);
		std::optional<float> optY = stringToFloat(args[1]);
		std::optional<float> optZ = stringToFloat(args[2]);

		std::optional<float> optR = stringToFloat(args[3]);
		std::optional<float> optG = stringToFloat(args[4]);
		std::optional<float> optB = stringToFloat(args[5]);
		if (optX.has_value()) {
			x = optX.value();
		}

		if (optY.has_value()) {
			y = optY.value();
		}

		if (optZ.has_value()) {
			z = optZ.value();
		}

		if (optR.has_value()) {
			r = optR.value();
		}

		if (optG.has_value()) {
			g = optG.value();
		}

		if (optB.has_value()) {
			b = optB.value();
		}
	}

	Processing::InstructionList ReadFile::generateInstructions()
	{
		return Processing::InstructionList();
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
