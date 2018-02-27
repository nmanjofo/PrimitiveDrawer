#pragma once

#include <glm/glm.hpp>

class AbstractPrimitiveDrawer
{
public:

	virtual ~AbstractPrimitiveDrawer();

	virtual void drawPrimitive(void* arguments, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;
	virtual bool init() = 0;
	virtual void clear();
};