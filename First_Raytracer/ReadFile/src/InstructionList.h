#ifndef INSTRUCTIONLIST_H
#define INSTRUCTIONLIST_H
#pragma once

#include <memory>
#include <stack>

#include "../Light/Light.h"
#include "../MaterialProps/MaterialProps.h"
#include "../Utils/Mat4.h"

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

		std::stack<Utils::Mat4>& getTransforms();
		void pushTransform(const Utils::Mat4 &transformMatrix);
		Utils::Mat4 popTransform();
		void copyTransform();

		std::stack<Attenuation> getAttenuationStack();
		void pushAttenuation(const Attenuation &attenuationStack);
		Attenuation popAttenuation();



	private:
		std::stack<Attenuation> attenuationStack;
		std::stack<LightPtr> lightStack;
		std::stack<MaterialProps> materialPropStack;
		std::stack<Utils::Mat4> transformStack;
	};
}

#endif // !INSTRUCTIONLIST_H
