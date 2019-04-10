#include "InstructionList.h"

namespace Processing
{
	std::stack<MaterialProps> InstructionList::getMaterialProps()
	{
		return materialPropStack;
	}

	void InstructionList::setMaterialProps(std::stack<MaterialProps> materialPropStack)
	{
		this->materialPropStack = materialPropStack;
	}

	void InstructionList::pushMaterialProps(MaterialProps materialProps)
	{
		materialPropStack.push(materialProps);
	}

	MaterialProps InstructionList::popMaterialProps()
	{
		MaterialProps materialProps = materialPropStack.top();
		materialPropStack.pop();
		return materialProps;
	}

	std::stack<LightPtr> InstructionList::getLights()
	{
		return lightStack;
	}

	void InstructionList::pushLight(const Light &light)
	{
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

	std::stack<Attenuation> InstructionList::getAttenuationStack()
	{
		return attenuationStack;
	}

	void InstructionList::pushAttenuation(const Attenuation &attenuation)
	{
		attenuationStack.push(attenuation);
	}

	Attenuation InstructionList::popAttenuation()
	{
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
}