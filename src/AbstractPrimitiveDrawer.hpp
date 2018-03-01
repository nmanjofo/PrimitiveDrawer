#pragma once

#include <glm/glm.hpp>

struct Primitive;

class AbstractPrimitiveDrawer
{
public:

	virtual ~AbstractPrimitiveDrawer() {}

	virtual void drawPrimitive(const Primitive& primitive, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;
	virtual bool init() = 0;
	virtual void clear() = 0;
};