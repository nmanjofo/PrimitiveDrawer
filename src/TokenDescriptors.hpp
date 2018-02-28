#pragma once

#include <string>
#include <vector>

#include "PrimitiveType.hpp"

enum class TokenType : unsigned int
{
	FLOAT,
	INT,
	CHAR,
};

struct PrimitiveTokenDescriptor
{
	PrimitiveType primitiveType;
	std::string primitiveName;
	std::vector<TokenType> parameters;
};
