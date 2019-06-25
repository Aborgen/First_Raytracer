#include <string>
#include <iostream>

#include "Camera/Camera.h"
#include "Film/Film.h"
#include "Raytracer/Raytracer.h"
#include "ReadFile/ReadFile.h"
#include "ReadFile/src/InstructionList.h"
#include "Scene/Scene.h"
#include "Screen/Screen.h"
#include "Sampler/Sampler.h"

bool main(int argc, char *argv[])
{
	using namespace Processing;
	using namespace IO;
	if (argc < 2)
	{
		std::cout << "Missing filename: [filename \"file.txt\"]";
		return false;
	}

	std::string filename = argv[1];
	ReadFile file(filename);
	InstructionList instructions = file.parse();
	Screen screen = instructions.getResolution();
	Sampler sampler(screen.getWidth(), screen.getHeight());
	Film film(screen.getWidth(), screen.getHeight());

	Camera camera = instructions.getCamera();
	Raytracer raytracer(instructions.getLights(), instructions.getShapes(), screen.getBackgroundColor());
	Scene scene(camera, film, raytracer, sampler);
	bool result = scene.render(instructions.getOutputFilename());
	return result;
}