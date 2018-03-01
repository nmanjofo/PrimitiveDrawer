#pragma once

#include "AbstractPrimitiveDrawer.hpp"
#include "CubeParams.hpp"


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

	bool _initProgram();
	void _initBuffers();
};
