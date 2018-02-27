#include "PrimitiveRenderer.hpp"
#include <GL/glew.h>

#include "LineDrawer.hpp"

PrimitiveRenderer::PrimitiveRenderer()
{
	
}

PrimitiveRenderer::~PrimitiveRenderer()
{
	
}

void PrimitiveRenderer::onUpdate()
{
	
}

void PrimitiveRenderer::clear()
{
	for (auto drawer : _primitiveDrawers)
		if (drawer.first != nullptr)
			delete drawer.first;

	_primitiveDrawers.clear();
}

bool PrimitiveRenderer::init(unsigned int renderWidth, unsigned int renderHeight)
{
	glClearColor(0.02f, 0.6f, 0.95f, 1.0f);

	changeViewport(renderWidth, renderHeight);

	return _initDrawers();
}

bool PrimitiveRenderer::_initDrawers()
{
	_primitiveDrawers.resize(PrimitiveType::NUM_PRIMITIVE_TYPES);

	_primitiveDrawers[PrimitiveType::LINE] = LineDrawer::getInstance();
	
	if (!_primitiveDrawers[PrimitiveType::LINE]->init())
		return false;
}


void PrimitiveRenderer::addPrimitive(Primitive primitive)
{
	_primitiveDrawers[primitive.primitive].second.push_back(primitive);
}

void PrimitiveRenderer::changeViewport(unsigned int width, unsigned int height)
{
	glViewport(0, 0, width, height);
}

void PrimitiveRenderer::onWindowRedraw(const glm::mat4& viewMatrix, const glm::mat4& projMatrix)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(auto drawer : _primitiveDrawers)
	{
		for (auto primitive : drawer.second)
			drawer.first->drawPrimitive(&primitive, viewMatrix, projMatrix);
	}
}





