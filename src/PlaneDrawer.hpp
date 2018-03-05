#pragma once

#include "AbstractPrimitiveDrawer.hpp"
#include "PlaneParams.hpp"
#include "GLProgram.hpp"

class PlaneDrawer : public AbstractPrimitiveDrawer
{
public:
	void drawPrimitive(const Primitive& primitive, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

	static PlaneDrawer* getInstance();

protected:
	PlaneDrawer();
	~PlaneDrawer();

	void _initBuffers() override;

	PlaneParams _convertPrimitiveToPlaneParams(const Primitive& primitive);
	glm::mat4 _getPlaneModelMatrix(const PlaneParams& plane) const;

	void _drawPlane(bool isWireframe, float lineThickness);

	static PlaneDrawer* _instance;
};