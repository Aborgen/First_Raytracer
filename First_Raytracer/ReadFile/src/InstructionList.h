#ifndef INSTRUCTIONLIST_H
#define INSTRUCTIONLIST_H
#pragma once

#include <memory>
#include <stack>

#include "../Camera/Camera.h"
#include "../Geometry/Sphere.h";
#include "../Light/Light.h"
#include "../MaterialProps/MaterialProps.h"
#include "../Screen/Screen.h"
#include "../Utils/Mat4.h"

namespace IO
{
	typedef std::shared_ptr<Geometry::Sphere> SpherePtr;
	typedef std::shared_ptr<Processing::Light> LightPtr;
	class InstructionList
	{
	public:
		InstructionList() {};
		Processing::MaterialProps& getMaterialProps();
		void setMaterialProps(const Processing::MaterialProps &material);

		std::stack<SpherePtr> getSpheres();
		void pushSphere(const Geometry::Sphere &sphere);
		SpherePtr popSphere();

		std::stack<LightPtr> getLights();
		void pushLight(const Processing::Light &light);
		LightPtr popLight();

		std::stack<Utils::Mat4>& getTransforms();
		void pushTransform(const Utils::Mat4 &transformMatrix);
		Utils::Mat4 popTransform();
		void copyTransform();

		std::stack<Processing::Attenuation> getAttenuationStack();
		void pushAttenuation(const Processing::Attenuation &attenuationStack);
		Processing::Attenuation popAttenuation();

		std::string getOutputFilename();
		void setOutputFilename(std::string outputFilename);

		Screen getResolution();
		void setResolution(int width, int height);

		Processing::Camera getCamera();
		void setCamera(Processing::Camera camera);



	private:
		std::stack<Processing::Attenuation> attenuationStack;
		std::stack<SpherePtr> sphereStack;
		std::stack<LightPtr> lightStack;
		Processing::MaterialProps material;
		std::stack<Utils::Mat4> transformStack;
		std::string outputFilename = "raytrace";
		Screen resolution = Screen(160, 120); // 160x120
		Processing::Camera camera;
	};
}

#endif // !INSTRUCTIONLIST_H
