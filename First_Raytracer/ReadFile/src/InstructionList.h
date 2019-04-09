#ifndef INSTRUCTIONLIST_H
#define INSTRUCTIONLIST_H
#pragma once

#include <stack>

#include "../MaterialProps/MaterialProps.h"

namespace Processing
{
	class InstructionList
	{
	public:
		InstructionList();
		~InstructionList();
		std::stack<MaterialProps> getMaterialProps();
		void setMaterialProps(std::stack<MaterialProps> materialPropStack);
		void pushMaterialProps(MaterialProps materialProps);
		MaterialProps popMaterialProps();

	private:
		std::stack<MaterialProps> materialPropStack;
	};
}

#endif // !INSTRUCTIONLIST_H
