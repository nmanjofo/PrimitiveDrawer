#pragma once

#include <glm/glm.hpp>
#include "GLProgram.hpp"

struct Primitive;

class AbstractPrimitiveDrawer
{
public:
	AbstractPrimitiveDrawer();
	virtual ~AbstractPrimitiveDrawer();

	virtual void drawPrimitive(const Primitive& primitive, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;
	
	virtual bool init();
	virtual void clear();

protected:
	virtual void _initBuffers() = 0;

	static GLProgram _program;
	static bool _isProgramOK;

	GLuint _VBO;
	GLuint _VAO;

private:
	void _initProgram();
};

