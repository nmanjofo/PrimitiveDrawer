#pragma once

#include "TokenDescriptors.hpp"

struct PrimitiveParam
{
	TokenType type;

	union
	{
		float _float;
		int _int;
		char _char;
	};
};