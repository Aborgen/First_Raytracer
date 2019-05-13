#include "InstructionList.h"
#include "../Light/DirectionalLight.h"
#include "../Light/PointLight.h"
#include "../Geometry/Sphere.h"
#include "../Geometry/Triangle.h"

namespace IO
{
	InstructionList::InstructionList()
	{
		Utils::Mat4 identity(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		transformStack.push(identity);
	}

	std::deque<ShapePtr> InstructionList::getShapes()
	{
		return shapeStack;
	}

	template <typename SHAPE_T>
	void InstructionList::pushShape(const SHAPE_T &shape)
	{
		shapeStack.push_front(std::make_shared<SHAPE_T>(shape));
	}
	template void InstructionList::pushShape(const Geometry::Sphere &shape);
	template void InstructionList::pushShape(const Geometry::Triangle &shape);

	std::deque<LightPtr> InstructionList::getLights()
	{
		return lightStack;
	}

	template <typename LIGHT_T>
	void InstructionList::pushLight(const LIGHT_T &light)
	{
		lightStack.push_front(std::make_shared<LIGHT_T>(light));
	}
	template void InstructionList::pushLight<Processing::DirectionalLight>(const Processing::DirectionalLight &light);
	template void InstructionList::pushLight<Processing::PointLight>(const Processing::PointLight &light);

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