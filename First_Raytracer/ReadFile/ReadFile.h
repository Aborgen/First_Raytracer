#pragma once
#ifndef READFILE_H
#define READFILE_H

#include <optional>
#include <string>

#include "ConfigList.h"

namespace IO
{
	class ReadFile
	{
	public:
		ReadFile(std::string filename);
		bool parse();
		ConfigList generateConfigList();

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
		bool validateFilename(std::string filename);
		bool hasBeenParsed = false;
	};
}

#endif // !READFILE_H