#pragma once

#include "AbstractPrimitiveDrawer.hpp"
#include "CubeParams.hpp"
#include "GLProgram.hpp"


class CubeDrawer : public AbstractPrimitiveDrawer
{
public:
	void drawPrimitive(const Primitive& primitive, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

	static CubeDrawer* getInstance();

protected:
	CubeDrawer();
	~CubeDrawer();

	CubeParams _convertPrimitiveToCubearams(const Primitive& primitive);
	glm::mat4  _getCubeWorldMatrix(const CubeParams& params);

	void _initBuffers() override;

	void _drawCube(bool isWireframe, float lineThickness);

	static CubeDrawer* _instance;
};
