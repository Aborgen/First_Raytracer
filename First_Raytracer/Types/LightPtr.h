#ifndef LIGHTPTR_H
#define LIGHTPTR_H
#pragma once

#include <memory>

#include "../Light/Light.h"

typedef std::shared_ptr<Processing::Light> LightPtr;

#endif // !LIGHTPTR_H
