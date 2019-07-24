#include <iostream>
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
		std::cout << "Output: " << filename << "\n";
		std::cout << "Beginning render\n---------\n";
		while (sampler.hasSample()) {
			Sample sample = sampler.getSample();
			Ray ray = camera.castRay(sample.getX(), sample.getY());
			ColorTriad color = raytracer.trace(ray);
			film.commit(color);
			writeProgress();
		}

		return film.writeImage(filename);
	}

	void Scene::writeProgress()
	{
		using std::cout;
		switch (sampler.getProgress()) {
			case Sampler::Progress::FOURTH:
				cout << "\t25% complete...\n";
				break;
			case Sampler::Progress::HALF:
				cout << "\t50% complete...\n";
				break;
			case Sampler::Progress::THREE_FOURTHS:
				cout << "\t75% complete...\n";
				break;
			case Sampler::Progress::FINISH:
				cout << "--------\nScene rendered!\n";
				break;
			default:
				break;
			}
	}
}