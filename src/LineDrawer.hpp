#pragma once

#include "AbstractPrimitiveDrawer.hpp"
#include "GLProgram.hpp"
#include "LineParams.hpp"

#include <glm/glm.hpp>

class LineDrawer : public AbstractPrimitiveDrawer
{
public:
	void drawPrimitive(const Primitive& primitive, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

	static LineDrawer* getInstance();

protected:
	LineDrawer();
	~LineDrawer();

	void _initBuffers() override;

	void _drawLine(float thickness);
	LineParams _convertPrimitiveToLineParams(const Primitive& primitive);

	void _updateVBO(const glm::vec4& v1, const glm::vec4& v2);

	static LineDrawer* _instance;
};
