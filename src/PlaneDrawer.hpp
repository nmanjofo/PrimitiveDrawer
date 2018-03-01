#pragma once

#include "AbstractPrimitiveDrawer.hpp"
#include "PlaneParams.hpp"
#include "GLProgram.hpp"

class PlaneDrawer : public AbstractPrimitiveDrawer
{
public:
	void drawPrimitive(const Primitive& primitive, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
	bool init() override;
	void clear() override;

	static PlaneDrawer* getInstance();

protected:
	PlaneDrawer();
	~PlaneDrawer();

	bool _initProgram();
	void _initBuffers();

	PlaneParams _convertPrimitiveToPlaneParams(const Primitive& primitive);
	glm::mat4 _getPlaneModelMatrix(const PlaneParams& plane) const;

	void _drawPlane();

	GLProgram	_planeProgram;
	GLuint		_VAO;
	GLuint		_VBO;

	static PlaneDrawer* _instance;
};