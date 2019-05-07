#ifndef SHAPEPTR_H
#define SHAPEPTR_H
#pragma once

#include <memory>

#include "../Geometry/Shape.h"

typedef std::shared_ptr<Geometry::Shape> ShapePtr;

#endif // !SHAPEPTR_H
