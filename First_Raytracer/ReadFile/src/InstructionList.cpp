#include "InstructionList.h"

namespace IO
{
	std::stack<Processing::MaterialProps> InstructionList::getMaterialProps()
	{
		return materialPropStack;
	}

	void InstructionList::setMaterialProps(std::stack<Processing::MaterialProps> materialPropStack)
	{
		this->materialPropStack = materialPropStack;
	}

	void InstructionList::pushMaterialProps(Processing::MaterialProps materialProps)
	{
		materialPropStack.push(materialProps);
	}

	Processing::MaterialProps InstructionList::popMaterialProps()
	{
		using namespace Processing;
		MaterialProps materialProps = materialPropStack.top();
		materialPropStack.pop();
		return materialProps;
	}

	Processing::MaterialProps InstructionList::topMaterialProps()
	{
		using namespace Processing;
		MaterialProps materialProps = materialPropStack.top();
		return materialProps;
	}

	std::stack<SpherePtr> InstructionList::getSpheres()
	{
		return sphereStack;
	}

	void InstructionList::pushSphere(const Geometry::Sphere &sphere)
	{
		using namespace Geometry;
		sphereStack.push(std::make_shared<Sphere>(sphere));
	}

	SpherePtr InstructionList::popSphere()
	{
		SpherePtr sphere = sphereStack.top();
		sphereStack.pop();
		return sphere;
	}

	std::stack<LightPtr> InstructionList::getLights()
	{
		return lightStack;
	}

	void InstructionList::pushLight(const Processing::Light &light)
	{
		using namespace Processing;
		lightStack.push(std::make_shared<Light>(light));
	}

	LightPtr InstructionList::popLight()
	{
		LightPtr light = lightStack.top();
		lightStack.pop();
		return light;
	}

	std::stack<Utils::Mat4>& InstructionList::getTransforms()
	{
		return transformStack;
	}

	void InstructionList::pushTransform(const Utils::Mat4 &transformMatrix)
	{
		transformStack.push(transformMatrix);
	}

	Utils::Mat4 InstructionList::popTransform()
	{
		Utils::Mat4 transformMatrix = transformStack.top();
		transformStack.pop();
		return transformMatrix;
	}

	void InstructionList::copyTransform()
	{
		transformStack.push(transformStack.top());
	}

	std::stack<Processing::Attenuation> InstructionList::getAttenuationStack()
	{
		return attenuationStack;
	}

	void InstructionList::pushAttenuation(const Processing::Attenuation &attenuation)
	{
		attenuationStack.push(attenuation);
	}

	Processing::Attenuation InstructionList::popAttenuation()
	{
		using namespace Processing;
		Attenuation attenuation = attenuationStack.top();
		attenuationStack.pop();
		return attenuation;
	}

	std::string InstructionList::getOutputFilename()
	{
		return outputFilename;
	}

	void InstructionList::setOutputFilename(std::string outputFilename)
	{
		this->outputFilename = outputFilename;
	}

	Screen InstructionList::getResolution()
	{
		return resolution;
	}

	void InstructionList::setResolution(int width, int height)
	{
		Screen resolution(width, height);
		this->resolution = resolution;
	}

	Processing::Camera InstructionList::getCamera()
	{
		return camera;
	}

	void InstructionList::setCamera(Processing::Camera camera)
	{
		this->camera = camera;
	}
}