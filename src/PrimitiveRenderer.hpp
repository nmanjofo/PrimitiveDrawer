#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Primitive.hpp"
#include "AbstractPrimitiveDrawer.hpp"

class PrimitiveRenderer
{
public:
	PrimitiveRenderer();
	~PrimitiveRenderer();

	bool init(unsigned int renderWidth, unsigned int renderHeight);
	void onUpdate();
	void onWindowRedraw(const glm::mat4& viewMatrix, const glm::mat4& projMatrix);

	void clear();

	void addPrimitive(const Primitive& primitive);

	void changeViewport(unsigned int width, unsigned int height);

protected:

	bool _initDrawers();

	std::vector<AbstractPrimitiveDrawer*>	_primitiveDrawers;
};