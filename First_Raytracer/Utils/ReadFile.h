#ifndef READFILE_H
#define READFILE_H
#pragma once

#include <fstream>
#include <map>
#include <stack>
#include <string>

#include "Mat4.h"

namespace Utils
{
	class ReadFile
	{
	public:
		ReadFile(std::string filename);
		void parse();

	private:
		std::string filename;
		bool hasBeenParsed = false;
		std::ifstream file;
		std::stack<Mat4> transformations;

		bool validateFilename(std::string filename);
	};
}

#endif // !READFILE_H
