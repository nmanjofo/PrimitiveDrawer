#pragma once

#include <string>
#include <vector>

#include "PrimitiveType.hpp"

//Primitive param descriptors
enum class TokenTypes : unsigned int
{
	FLOAT,
	INT,
	CHAR,
	STRING
};

struct PrimitiveTokenDescriptor
{
	PrimitiveType primitiveType;
	std::string primitiveName;
	std::vector<TokenTypes> parameters;
};
