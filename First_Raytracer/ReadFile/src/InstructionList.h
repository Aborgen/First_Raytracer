#ifndef INSTRUCTIONLIST_H
#define INSTRUCTIONLIST_H
#pragma once

#include <memory>
#include <stack>

#include "../Camera/Camera.h"
#include "../Geometry/Shape.h"
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
		ShapeDeque getShapes();
		template <class SHAPE_T>
		void pushShape(const SHAPE_T &shape);

		LightDeque getLights();
		template <typename LIGHT_T>
		void pushLight(const LIGHT_T &light);

		std::string getOutputFilename();
		void setOutputFilename(std::string outputFilename);

		Screen getResolution();
		void setResolution(int width, int height);

		Processing::Camera getCamera();
		void setCamera(Processing::Camera camera);
		
		int getMaxDepth();
		void setMaxDepth(int maxDepth);


	private:
		ShapeDeque shapeStack;
		LightDeque lightStack;
		std::string outputFilename = "raytrace";
		Screen resolution = Screen(160, 120); // 160x120
		int maxDepth = 5;
		Processing::Camera camera;
	};
}

#endif // !INSTRUCTIONLIST_H
