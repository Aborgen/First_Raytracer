#ifndef SCENE_H
#define SCENE_H
#pragma once

#include <string>

#include "../Camera/Camera.h"
#include "../Film/Film.h"
#include "../Raytracer/Raytracer.h"
#include "../Sampler/Sampler.h"

namespace Processing
{
	class Scene
	{
	public:
		Scene(const Camera &camera, const IO::Film &film, const Raytracer &raytracer, const Sampler &sampler);
		bool render(std::string filename);

	private:
		Camera camera;
		IO::Film film;
		Raytracer raytracer;
		Sampler sampler;
		void writeProgress();
	};
}

#endif // !SCENE_H
