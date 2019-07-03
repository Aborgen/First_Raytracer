#ifndef RAY_H
#define RAY_H
#pragma once

#include "../Utils/Vec3.h"
namespace Processing
{
	class Ray
	{
	public:
		enum class Type { PRIMARY, SHADOW, RECURSIVE };
		Ray() : type(Type::PRIMARY) {};
		Ray(Utils::Vec3 origin, Utils::Vec3 direction, Type type = Type::PRIMARY);
		Utils::Vec3 specificPoint(float t) const;
		Utils::Vec3 getOrigin() const;
		void setOrigin(float x, float y, float z);
		Utils::Vec3 getDirection() const;
		void setDirection(const Utils::Vec3 &direction);
		void setDirection(float x, float y, float z);
		Type getType() const;

	private:
		Utils::Vec3 origin;
		Utils::Vec3 direction;
		const Type type;
	};
}

#endif // !RAY_H
