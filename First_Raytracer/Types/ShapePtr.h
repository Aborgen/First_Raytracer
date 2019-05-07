#ifndef SHAPEPTR_H
#define SHAPEPTR_H
#pragma once

#include <deque>
#include <memory>

#include "../Geometry/Shape.h"

typedef std::shared_ptr<Geometry::Shape> ShapePtr;
typedef std::deque<ShapePtr> ShapeDeque;

#endif // !SHAPEPTR_H
