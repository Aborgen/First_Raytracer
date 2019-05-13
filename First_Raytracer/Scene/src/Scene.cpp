#include <optional>

#include "../Scene.h"
#include "../Utils/ColorTriad.h"

namespace Processing
{
	Scene::Scene(const Camera &camera, const IO::Film &film, const Raytracer &raytracer, const Sampler &sampler)
	{
		this->camera = camera;
		this->film = film;
		this->raytracer = raytracer;
		this->sampler = sampler;
	}

	bool Scene::render(std::string filename)
	{
		using namespace Utils;
		while (sampler.hasSample()) {
			Sample sample = sampler.getSample();
			Ray ray = camera.castRay(sample.getX(), sample.getY());
			ColorTriad color = raytracer.trace(ray);
			film.commit(color);
		}

		return film.writeImage(filename);
	}
}