#pragma once

#include "AbstractPrimitiveDrawer.hpp"
#include "GLProgram.hpp"

#include <glm/glm.hpp>


class LineDrawer : public AbstractPrimitiveDrawer
{
public:
	void drawPrimitive(void* lineParams, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
	bool init() override;
	void clear() override;

	static LineDrawer* getInstance();

protected:
	LineDrawer();
	~LineDrawer();

	bool _initProgram();
	void _initBuffers();
	void _drawLine(float thickness);

	void _updateVBO(const glm::vec4& v1, const glm::vec4& v2);

	GLProgram	_lineProgram;
	GLuint		_VAO;
	GLuint		_VBO;

	static LineDrawer* _instance;
};