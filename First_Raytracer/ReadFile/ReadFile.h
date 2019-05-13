#pragma once
#ifndef READFILE_H
#define READFILE_H

#include <optional>
#include <string>

#include "src/InstructionList.h"
#include "../Utils/Mat4.h"

namespace IO
{
	class ReadFile
	{
	public:
		ReadFile(std::string filename);
		InstructionList parse();

	private:
		std::string filename;
		enum ValidCommands
		{
			AMBIENT,
			ATTENUATION,
			CAMERA,
			DIFFUSE,
			DIRECTIONAL_LIGHT,
			EMISSION,
			MAX_DEPTH,
			MAX_VERTEX_NORMALS,
			MAX_VERTICES,
			OUTPUT,
			POINT_LIGHT,
			POP_TRANSFORM,
			PUSH_TRANSFORM,
			ROTATE,
			SCALE,
			SHININESS,
			SIZE,
			SPECULAR,
			SPHERE,
			TRANSLATE,
			TRIANGLE,
			TRIANGLE_NORMAL,
			VERTEX,
			VERTEX_NORMAL,
			UNKNOWN
		};

		ValidCommands commandMapping(std::string str);
		std::optional<float> stringToFloat(std::string str);
		std::vector<std::string> lineSplit(const std::string &line, std::string &command);
		bool validateFilename(std::string filename);
		void rightMultiply(const Utils::Mat4 &M, Utils::Mat4 &T);
		void parseColor(const std::vector<std::string>& args, float &r, float &g, float &b);
		void parseLight(const std::vector<std::string>& args, float &x, float &y, float &z, float &r, float &g, float &b);
		void parseVector(const std::vector<std::string>& args, float &x, float &y, float &z);
		void parseSphere(const std::vector<std::string>& args, float &x, float &y, float &z, float& radius);
		void parseTriangle(const std::vector<std::string>& args, int &a, int &b, int &c);
		bool hasBeenParsed = false;
		int lineNumber = 0;
		bool inTransaction = false;
	};
}

#endif // !READFILE_H