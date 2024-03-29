#include <deque>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

#include "../ReadFile.h"
#include "InstructionList.h"
#include "../Transformations/TransformMatrix.h"
#include "../Transformations/Transformations.h"
#include "../Light/DirectionalLight.h"
#include "../Light/PointLight.h"
#include "../Utils/Mat4.h"
#include "../Utils/Operations.h"
#include "../Geometry/Icosphere.h"
#include "../Geometry/Sphere.h"
#include "../Geometry/Triangle.h"

namespace IO
{
	ReadFile::ReadFile(std::string filename)
	{
		if (!validateFilename(filename))
		{
			throw new std::exception("Filename must have a file extension of test or txt");
		}

		this->filename = filename;
	}

	std::vector<std::string> ReadFile::lineSplit(const std::string &line, std::string &command)
	{
		std::stringstream ss(line);
		std::vector<std::string> args;
		std::string fragment;
		while (std::getline(ss, fragment, ' ')) {
			if (command == "") {
				command = fragment;
				continue;
			}
			if (fragment == "") {
				continue;
			}

			args.push_back(fragment);
		}

		return args;
	}

	InstructionList ReadFile::parse()
	{
		using namespace Geometry;
		using namespace Processing;
		using namespace Utils;
		std::string line;
		std::ifstream file("scenes\\"+filename);
		if (!file.is_open()) {
			std::cout << "File with name of " << filename << " cannot be opened or does not exist\n";
			return InstructionList();
		}

		InstructionList instructions = InstructionList();
		std::deque<Vec3> vertices;
		MaterialProps material;
		Attenuation attenuation;
		TransformMatrix transforms;
		while (std::getline(file, line)) {
			lineNumber++;
			bool onlySpaces = line.find_first_not_of(' ') == std::string::npos;
			// Skips the line if it is empty or if it is a comment.
			if (onlySpaces || (line[0] == '#')) {
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
					material.setAmbient(r, g, b);
					break;
				}
				case ValidCommands::ATTENUATION:
				{
					float constant = 0.0f, linear = 0.0f, quadratic = 0.0f;
					parseVector(args, constant, linear, quadratic);
					attenuation.setAttenuation(constant, linear, quadratic);
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
						std::vector<std::string> eyeArgs   { args[0], args[1], args[2] };
						std::vector<std::string> centerArgs{ args[3], args[4], args[5] };
						std::vector<std::string> upArgs    { args[6], args[7], args[8] };
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
					Camera camera(eye, center, up, fovy, instructions.getResolution());
					instructions.setCamera(camera);
					break;
				}
				case ValidCommands::DIFFUSE:
				{
					float r = 0.0f, g = 0.0f, b = 0.0f;
					parseColor(args, r, g, b);
					material.setDiffuse(r, g, b);
					break;
				}
				case ValidCommands::DIRECTIONAL_LIGHT:
				{
					float x = 0.0f, y = 0.0f, z = 0.0f,
						  r = 0.0f, g = 0.0f, b = 0.0f;
					parseLight(args, x, y, z, r, g, b);

					DirectionalLight light(x, y, z, r, g, b);
					instructions.pushLight<DirectionalLight>(light);
					break;
				}
				case ValidCommands::EMISSION:
				{
					float r = 0.0f, g = 0.0f, b = 0.0f;
					parseColor(args, r, g, b);
					material.setEmission(r, g, b);
					break;
				}
				case ValidCommands::MAX_DEPTH:
				{
					std::optional<float> optDepth = stringToFloat(args[0]);
					int depth = (int) optDepth.has_value() ? optDepth.value() : 5;
					instructions.setMaxDepth(depth);
					break;
				}
				case ValidCommands::MAX_VERTEX_NORMALS:
					// Unused
					break;
				case ValidCommands::MAX_VERTICES:
					// Unused
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
					light.setAttenuation(attenuation);
					instructions.pushLight<PointLight>(light);
					break;
				}
				case ValidCommands::POP_TRANSFORM:
					transforms.resetToBase();
					break;
				case ValidCommands::PUSH_TRANSFORM:
					transforms.updateBase();
					break;
				case ValidCommands::ROTATE:
				{
					float x = 0.0f, y = 0.0f, z = 0.0f, degrees = 0.0f;
					parseVector(args, x, y, z);
					if (args.size() == 4) {
						std::optional<float> optDegrees = stringToFloat(args[3]);
						if (optDegrees.has_value()) {
							degrees = optDegrees.value();
						}
					}

					Vec3 axis(x, y, z);
					transforms.addRotation(degrees, axis);
					break;
				}
				case ValidCommands::SCALE:
				{
					float x = 0.0f, y = 0.0f, z = 0.0f;
					parseVector(args, x, y, z);
					transforms.addScale(x, y, z);
					break;
				}
				case ValidCommands::SHININESS:
				{
					std::optional<float> optIntensity = stringToFloat(args[0]);
					float intensity = optIntensity.has_value() ? optIntensity.value() : 0.0f;
					material.setShininess(intensity);
					break;
				}
				case ValidCommands::SIZE:
				{
					float width = 160.0f, height = 120.0f;
					std::optional<float> optWidth = stringToFloat(args[0]);
					std::optional<float> optHeight = stringToFloat(args[1]);
					if (optWidth.has_value()) {
						width = (int) optWidth.value();
					}

					if (optHeight.has_value()) {
						height = (int) optHeight.value();
					}

					instructions.setResolution(width, height);
					break;
				}
				case ValidCommands::SPECULAR:
				{
					float r = 0.0f, g = 0.0f, b = 0.0f;
					parseColor(args, r, g, b);
					material.setSpecular(r, g, b);
					break;
				}
				case ValidCommands::SPHERE:
				{
					float x = 0.0f, y = 0.0f, z = 0.0f, radius = 0.0f;
					parseSphere(args, x, y, z, radius);
					Vec3 center(x, y, z);
					if (transforms.getScaleType() == TransformMatrix::ScaleType::NON_UNIFORM || transforms.hasRotation()) {
						Icosphere sphere(center, radius, transforms.getMatrix(), material);
						instructions.pushShape<Icosphere>(sphere);
					}
					else {
						Sphere sphere(center, radius, transforms.getMatrix(), material);
						instructions.pushShape<Sphere>(sphere);
					}

					break;
				}
				case ValidCommands::TRANSLATE:
				{
					float x = 0.0f, y = 0.0f, z = 0.0f;
					parseVector(args, x, y, z);
					transforms.addTranslation(x, y, z);
					break;
				}
				case ValidCommands::TRIANGLE:
				{
					int a = 0, b = 0, c = 0;
					parseTriangle(args, a, b, c);
					Triangle triangle(vertices[a], vertices[b], vertices[c], transforms.getMatrix(), material);
					instructions.pushShape<Triangle>(triangle);
					break;
				}
				case ValidCommands::TRIANGLE_NORMAL:
					// Unused
					break;
				case ValidCommands::VERTEX:
				{
					float x = 0.0f, y = 0.0f, z = 0.0f;
					parseVector(args, x, y, z);
					Vec3 vertex(x, y, z);
					vertices.push_back(vertex);
					break;
				}
				case ValidCommands::VERTEX_NORMAL:
					// Unused
					break;
				case ValidCommands::UNKNOWN:
					// Nothing for now. Move on to the next line.
					break;
				default:
					// Default is handled in the case above.
					break;
			}
		}

		return instructions;
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

	void ReadFile::parseSphere(const std::vector<std::string>& args, float &x, float &y, float &z, float& radius)
	{
		if (args.size() < 4) {
			std::string message = "Line must be a command followed by 4 arguments (" + filename + " line " + std::to_string(lineNumber) + ")";
			throw new std::exception(message.c_str());
		}

		std::optional<float> optX = stringToFloat(args[0]);
		std::optional<float> optY = stringToFloat(args[1]);
		std::optional<float> optZ = stringToFloat(args[2]);
		std::optional<float> optRadius = stringToFloat(args[3]);
		if (optX.has_value()) {
			x = optX.value();
		}

		if (optY.has_value()) {
			y = optY.value();
		}

		if (optZ.has_value()) {
			z = optZ.value();
		}

		if (optRadius.has_value()) {
			radius = optRadius.value();
		}
	}

	void ReadFile::parseTriangle(const std::vector<std::string>& args, int &a, int &b, int &c)
	{
		if (args.size() < 3) {
			std::string message = "Line must be a command followed by 3 arguments (" + filename + " line " + std::to_string(lineNumber) + ")";
			throw new std::exception(message.c_str());
		}

		std::optional<float> optA = stringToFloat(args[0]);
		std::optional<float> optB = stringToFloat(args[1]);
		std::optional<float> optC = stringToFloat(args[2]);
		if (optA.has_value()) {
			a = (int) optA.value();
		}
		
		if (optB.has_value()) {
			b = (int) optB.value();
		}
		
		if (optC.has_value()) {
			c = (int) optC.value();
		}
	}

	std::optional<float> ReadFile::stringToFloat(std::string str)
	{
		char *endptr;
		errno = 0;
		const char *charString = str.c_str();
		float newFloat = strtof(charString, &endptr);
		if (errno == ERANGE || *endptr != '\0' || charString == endptr) {
			return std::nullopt;
		}

		return newFloat;
	}

	bool ReadFile::validateFilename(std::string str)
	{
		std::regex pattern("[A-Za-z0-9_\-]+\.(txt|test)");
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
