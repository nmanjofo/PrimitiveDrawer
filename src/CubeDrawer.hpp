#pragma once

#include "AbstractPrimitiveDrawer.hpp"
#include "CubeParams.hpp"
#include "GLProgram.hpp"


class CubeDrawer : public AbstractPrimitiveDrawer
{
public:
	void drawPrimitive(const Primitive& primitive, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
	bool init() override;
	void clear() override;

	static CubeDrawer* getInstance();

protected:
	CubeDrawer();
	~CubeDrawer();

	CubeParams _convertPrimitiveToCubearams(const Primitive& primitive);
	glm::mat4  _getCubeWorldMatrix(const CubeParams& params);

	bool _initProgram();
	void _initBuffers();

	void _drawCube(bool isWireframe, float lineThickness);

	GLProgram			_program;
	GLuint				_VBO;
	GLuint				_VAO;

	static CubeDrawer* _instance;
};
