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
		return materialPropStack.top();
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
		return lightStack.top();
	}
}