#ifndef INSTRUCTIONLIST_H
#define INSTRUCTIONLIST_H
#pragma once

#include <memory>
#include <stack>

#include "../MaterialProps/MaterialProps.h"
#include "../Light/Light.h"

namespace Processing
{
	typedef std::shared_ptr<Light> LightPtr;
	class InstructionList
	{
	public:
		InstructionList();
		~InstructionList();
		std::stack<MaterialProps> getMaterialProps();
		void setMaterialProps(std::stack<MaterialProps> materialPropStack);
		void pushMaterialProps(MaterialProps materialProps);
		MaterialProps popMaterialProps();

		std::stack<LightPtr> getLights();
		void pushLight(const Light &light);
		LightPtr popLight();

	private:
		std::stack<MaterialProps> materialPropStack;
		std::stack<LightPtr> lightStack;
	};
}

#endif // !INSTRUCTIONLIST_H
