#ifndef LIGHTPTR_H
#define LIGHTPTR_H
#pragma once

#include <deque>
#include <memory>

#include "../Light/Light.h"

typedef std::shared_ptr<Processing::Light> LightPtr;
typedef std::deque<LightPtr> LightDeque;

#endif // !LIGHTPTR_H
