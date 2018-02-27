#pragma once

#include "LineParams.hpp"
#include "PrimitiveType.hpp"

struct Primitive
{
	Primitive()
	{
		primitiveType = PrimitiveType::UNKNOWN;
	}

	PrimitiveType primitiveType;

	union
	{
		LineParams lineParams;

	};
};


