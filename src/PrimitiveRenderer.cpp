#include "PrimitiveRenderer.hpp"
#include <GL/glew.h>

#include "LineDrawer.hpp"
#include "PlaneDrawer.hpp"

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
		if (drawer != nullptr)
			delete drawer;

	_primitiveDrawers.clear();
}

bool PrimitiveRenderer::init(unsigned int renderWidth, unsigned int renderHeight)
{
	glClearColor(0.02f, 0.6f, 0.95f, 1.0f);

	changeViewport(renderWidth, renderHeight);

	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	return _initDrawers();
}

bool PrimitiveRenderer::_initDrawers()
{
	_primitiveDrawers.resize(PrimitiveType::NUM_PRIMITIVE_TYPES);
	
	for (unsigned int i = 0; i < PrimitiveType::NUM_PRIMITIVE_TYPES; ++i)
		_primitiveDrawers[i] = nullptr;

	_primitiveDrawers[PrimitiveType::LINE] = LineDrawer::getInstance();
	_primitiveDrawers[PrimitiveType::PLANE] = PlaneDrawer::getInstance();

	for(auto drawer : _primitiveDrawers)
	{
		if (drawer != nullptr && !drawer->init())
			return false;
	}

	return true;
}


void PrimitiveRenderer::addPrimitive(const Primitive& primitive)
{
	_primitives.push_back(primitive);
}

void PrimitiveRenderer::changeViewport(unsigned int width, unsigned int height)
{
	glViewport(0, 0, width, height);
}

void PrimitiveRenderer::onWindowRedraw(const glm::mat4& viewMatrix, const glm::mat4& projMatrix)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(auto primitive : _primitives)
	{
		_primitiveDrawers[primitive.primitiveType]->drawPrimitive(primitive, viewMatrix, projMatrix);
	}
}



