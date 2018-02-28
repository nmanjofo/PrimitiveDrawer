#pragma once

#include "LineParams.hpp"
#include "PrimitiveParam.hpp"

struct Primitive
{
	Primitive()
	{
		primitiveType = PrimitiveType::UNKNOWN;
	}

	PrimitiveType primitiveType;

	std::vector<PrimitiveParam> params;
};


