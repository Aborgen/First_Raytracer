#include "InstructionList.h"

namespace IO
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
		return materialPropStack.pop();
	}
}