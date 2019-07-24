#ifndef FILM_H
#define FILM_H
#pragma once

#include <vector>
#include <string>

#include "../Sampler/src/Sample.h"
#include "../Utils/ColorTriad.h"

namespace IO
{
	class Film
	{
	public:
		Film() {};
		Film(int width, int height);
		void commit(const Utils::ColorTriad &color);
		bool writeImage(std::string filename = "rayTracer.png");

	private:
		int width;
		int height;
		std::vector<Utils::ColorTriad> colors;
		unsigned char toByte(float value);
	};
}

#endif // !FILM_H
