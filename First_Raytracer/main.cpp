
#include <iostream>

#include "Camera/Camera.h"
#include "Configuration/Configuration.h"
#include "Film/Film.h"
#include "Raytracer/Raytracer.h"
#include "Scene/Scene.h"
#include "Sampler/Sampler.h"

bool main(int argc, char *argv)
{
	using namespace Processing;
	if (argc < 2)
	{
		std::cout << "Missing filename: [filename \"file.txt\"]";
		return false;
	}

	Configuration configuration(argc, argv);
	bool result = configuration.init();
	if (!result) {
		std::cout << "Summin' bad happened.";
		return false;
	}

	Camera camera();
	Film film();
	Raytracer raytracer();
	Sampler sampler();
	Scene scene(Camera camera, Film film, Raytracer raytracer, Sampler sampler);


	return true;
}