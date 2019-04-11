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
#include "../Utils/Mat4.h"
#include "../Utils/Operations.h"

namespace IO
{
	ReadFile::ReadFile(std::string filename)
	{
		if (!validateFilename(filename))
		{
			throw new std::exception("Filename must have a file extension of .test");
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
		using namespace Utils;
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
				{
					float r = 0.0f, g = 0.0f, b = 0.0f;
					parseColor(args, r, g, b);

					MaterialProps newProps = instructions.popMaterialProps();
					newProps.setAmbient(r, g, b);
					instructions.pushMaterialProps(newProps);
					break;
				}
				case ValidCommands::ATTENUATION:
				{
					float constant = 0.0f, linear = 0.0f, quadratic = 0.0f;
					parseVector(args, constant, linear, quadratic);

					Attenuation attenuation(constant, linear, quadratic);
					instructions.pushAttenuation(attenuation);
					break;
				}
				case ValidCommands::CAMERA:
				{
					float eyeX = 0.0f, eyeY = 0.0f, eyeZ = 0.0f;
					float centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f;
					float upX = 0.0f, upY = 0.0f, upZ = 0.0f;
					float fovy = 0.0f;
					// If the line doesn't have the required number of arguments, just use the defaults.
					if (args.size() >= 10)
					{
						std::vector<std::string> eyeArgs(args.begin(), args.end() + 2);
						std::vector<std::string> centerArgs(args.begin() + 2, args.end() + 4);
						std::vector<std::string> upArgs(args.begin() + 4, args.end() + 6);
						parseVector(eyeArgs, eyeX, eyeY, eyeZ);
						parseVector(centerArgs, centerX, centerY, centerZ);
						parseVector(upArgs, upX, upY, upZ);

						std::optional<float> optFovy = stringToFloat(args[9]);
						if (optFovy.has_value()) {
							fovy = optFovy.value();
						}
					}

					Vec3 eye(eyeX, eyeY, eyeZ);
					Vec3 center(centerX, centerY, centerZ);
					Vec3 up(upX, upY, upZ);
					Camera camera(eye, center, up, fovy);
					instructions.setCamera(camera);
					break;
				}
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
					instructions.setOutputFilename(args[0]);
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
					// This is usually called after transforming an object relative to the camera position.
					// Will "reset" the transformation stack to the original camera position, ready to transform the next object.
					instructions.popTransform();
					break;
				case ValidCommands::PUSH_TRANSFORM:
					// Add a copy of the top transformation matrix to the stack, which will be manipulated in some way.
					instructions.copyTransform();
					break;
				case ValidCommands::ROTATE:
				{
					float x = 0.0f, float y = 0.0f, float z = 0.0f, float degrees = 0.0f;
					parseVector(args, x, y, z);
					if (args.size() == 4) {
						std::optional<float> optDegrees = stringToFloat(args[3]);
						if (optDegrees.has_value()) {
							degrees = optDegrees.value();
						}
					}

					Vec3 axis(x, y, z);
					Mat3 matrix = Transformations::rotate(degrees, axis);
					Mat4 rotationMatrix(
						matrix[0][0], matrix[0][1], matrix[0][2], 0.0f,
						matrix[1][0], matrix[1][1], matrix[1][2], 0.0f,
						matrix[2][0], matrix[2][1], matrix[2][2], 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f
					);

					std::stack<Mat4> &transformStack = instructions.getTransforms();
					rightMultiply(rotationMatrix, transformStack);
					break;
				}
				case ValidCommands::SCALE:
				{
					float x = 0.0f, float y = 0.0f, float z = 0.0f;
					parseVector(args, x, y, z);
					Mat4 scaleMatrix = Transformations::scale(x, y, z);
					std::stack<Mat4> &transformStack = instructions.getTransforms();
					rightMultiply(scaleMatrix, transformStack);
					break;
				}
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
				{
					float width = 160.0f, height = 120.0f;
					std::optional<float> optWidth = stringToFloat(args[0]);
					std::optional<float> optHeight = stringToFloat(args[1]);
					if (optWidth.has_value()) {
						width = optWidth.value();
					}

					if (optHeight.has_value()) {
						height = optHeight.value();
					}

					instructions.setResolution(width, height);
					break;
				}
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
				{
					float x = 0.0f, float y = 0.0f, float z = 0.0f;
					parseVector(args, x, y, z);
					Mat4 translationMatrix = Transformations::translate(x, y, z);
					std::stack<Mat4> &transformStack = instructions.getTransforms();
					rightMultiply(translationMatrix, transformStack);
					break;
				}
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
	
	void ReadFile::parseColor(const std::vector<std::string> &args, float &r, float &g, float &b)
	{
		if (args.size() < 3) {
			std::string message = "Line must be a command followed by 3 arguments (" + filename + " line " + std::to_string(lineNumber) + ")";
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
		if (args.size() < 6) {
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

	void ReadFile::parseVector(const std::vector<std::string> &args, float &x, float &y, float &z)
	{
		parseColor(args, x, y, z);
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

	void ReadFile::rightMultiply(const Utils::Mat4 &M, std::stack<Utils::Mat4> &transformStack)
	{
		Utils::Mat4 &T = transformStack.top();
		T = T * M;
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
