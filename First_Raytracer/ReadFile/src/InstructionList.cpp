#include "InstructionList.h"

namespace IO
{
	Processing::MaterialProps& InstructionList::getMaterialProps()
	{
		return material;
	}

	void InstructionList::setMaterialProps(const Processing::MaterialProps &material)
	{
		this->material = material;
	}

	std::deque<ShapePtr> InstructionList::getShapes()
	{
		return shapeStack;
	}

	void InstructionList::pushShape(const Geometry::Shape &shape)
	{
		using namespace Geometry;
		shapeStack.push_front(std::make_shared<Shape>(shape));
	}

	std::deque<LightPtr> InstructionList::getLights()
	{
		return lightStack;
	}

	void InstructionList::pushLight(const Processing::Light &light)
	{
		using namespace Processing;
		lightStack.push_front(std::make_shared<Light>(light));
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
	int InstructionList::getMaxDepth()
	{
		return maxDepth;
	}
	void InstructionList::setMaxDepth(int maxDepth)
	{
		this->maxDepth = maxDepth;
	}
}