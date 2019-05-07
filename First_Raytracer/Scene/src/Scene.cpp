#include "../Scene.h"

namespace Processing
{
	Scene::Scene(const Camera &camera, const Film &film, const Raytracer &raytracer, const Sampler &sampler, const ShapeDeque &shapes, const LightDeque &lights)
	{
		this->camera = camera;
		this->film = film;
		this->raytracer = raytracer;
		this->sampler = sampler;
		this->shapes = shapes;
		this->lights = lights;
	}

	void Scene::render()
	{
		using namespace Utils;
		while (sampler.hasSample()) {
			Sample sample = sampler.getSample();
			Ray ray = camera.castRay(sample.getX(), sample.getY());
			return;
		}
	}
}