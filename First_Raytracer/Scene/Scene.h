#ifndef SCENE_H
#define SCENE_H
#pragma once

#include "../Camera/Camera.h"
#include "../Film/Film.h"
#include "../Raytracer/Raytracer.h"
#include "../Sampler/Sampler.h"
#include "../Types/LightPtr.h"
#include "../Types/ShapePtr.h"

namespace Processing
{
	class Scene
	{
	public:
		Scene(const Camera &camera, const Film &film, const Raytracer &raytracer, const Sampler &sampler, const ShapeDeque &shapes, const LightDeque &lights);
		void render();

	private:
		Camera camera;
		Film film;
		Raytracer raytracer;
		Sampler sampler;
		ShapeDeque shapes;
		LightDeque lights;
	};
}

#endif // !SCENE_H
