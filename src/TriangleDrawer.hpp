#pragma once

#include "AbstractPrimitiveDrawer.hpp"
#include "TriangleParams.hpp"

class TriangleDrawer : public AbstractPrimitiveDrawer
{
public:
	void drawPrimitive(const Primitive& primitive, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
	
	static TriangleDrawer* getInstance();
protected:
	TriangleDrawer() : AbstractPrimitiveDrawer() {}
	~TriangleDrawer() {}

	void _initBuffers() override;
	void _updateVBO(const glm::vec4(&vertices)[3]);

	TriangleParams _convertPrimitiveToTriangleParams(const Primitive& primitive);

	void _drawTriangle(bool isWireframe, float lineThickness);

	static TriangleDrawer* _instance;
};
