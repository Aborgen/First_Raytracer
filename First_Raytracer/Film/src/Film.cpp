#include <iostream>

#include "../Film.h"
#include "lodepng.h"

namespace IO
{
	Film::Film(int width, int height)
	{
		this->width = width;
		this->height = height;
	}

	void Film::commit(const Utils::ColorTriad &color)
	{
		colors.push_back(color);
	}

	bool Film::writeImage(std::string filename)
	{
		using namespace Processing;
		using namespace Utils;
		std::vector<unsigned char> image;
		for (ColorTriad &color : colors) {
			float r = color.getR();
			float g = color.getG();
			float b = color.getB();
			image.push_back(toByte(r));
			image.push_back(toByte(g));
			image.push_back(toByte(b));
			image.push_back(255); // Unused alpha
		}

		std::vector<unsigned char> png;
		unsigned error = lodepng::encode(png, image, width, height);
		if (error) {
			std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
			return false;
		}

		lodepng::save_file(png, filename);
		return true;
	}

	unsigned char Film::toByte(float value)
	{
		if (value >= 1.0) {
			return 255;
		}
		else if (value < 0) {
			return 0;
		}

		return (unsigned char) value * 256.0;
	}
}