#ifndef INSTRUCTIONLIST_H
#define INSTRUCTIONLIST_H
#pragma once

#include <memory>
#include <stack>

#include "../Camera/Camera.h"
#include "../Geometry/Shape.h";
#include "../Light/Light.h"
#include "../MaterialProps/MaterialProps.h"
#include "../Screen/Screen.h"
#include "../Utils/Mat4.h"
#include "../Types/LightPtr.h"
#include "../Types/ShapePtr.h"

namespace IO
{
	class InstructionList
	{
	public:
		InstructionList() {};
		std::deque<ShapePtr> getShapes();
		void pushShape(const Geometry::Shape &shape);

		std::deque<LightPtr> getLights();
		void pushLight(const Processing::Light &light);

		std::stack<Utils::Mat4>& getTransforms();
		void pushTransform(const Utils::Mat4 &transformMatrix);
		Utils::Mat4 popTransform();
		void copyTransform();

		std::string getOutputFilename();
		void setOutputFilename(std::string outputFilename);

		Screen getResolution();
		void setResolution(int width, int height);

		Processing::Camera getCamera();
		void setCamera(Processing::Camera camera);
		
		int getMaxDepth();
		void setMaxDepth(int maxDepth);


	private:
		std::deque<ShapePtr> shapeStack;
		std::deque<LightPtr> lightStack;
		std::stack<Utils::Mat4> transformStack;
		std::string outputFilename = "raytrace";
		Screen resolution = Screen(160, 120); // 160x120
		int maxDepth = 5;
		Processing::Camera camera;
	};
}

#endif // !INSTRUCTIONLIST_H
