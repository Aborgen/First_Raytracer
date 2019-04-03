#include "../Scene.h"

namespace Processing
{
	Scene::Scene(Camera camera, Film film, Raytracer raytracer, Sampler sampler)
	{
		this->camera = camera;
		this->film = film;
		this->raytracer = raytracer;
		this->sampler = sampler;
	}

	void Scene::render()
	{
		while (true)
		{
			return;
		}
	}
}