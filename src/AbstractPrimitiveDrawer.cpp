#include "AbstractPrimitiveDrawer.hpp"

bool AbstractPrimitiveDrawer::_isProgramOK = false;
GLProgram AbstractPrimitiveDrawer::_program;

AbstractPrimitiveDrawer::AbstractPrimitiveDrawer()
{
	_VBO = _VAO = 0;
	_initProgram();
}

AbstractPrimitiveDrawer::~AbstractPrimitiveDrawer()
{
	clear();
}

bool AbstractPrimitiveDrawer::init()
{
	if (!_isProgramOK)
		return false;

	_initBuffers();

	return true;
};

void AbstractPrimitiveDrawer::clear()
{
	glDeleteBuffers(1, &_VBO);
	glDeleteVertexArrays(1, &_VAO);
}

void AbstractPrimitiveDrawer::_initProgram()
{
	if (!_isProgramOK)
		_isProgramOK = _program.makeProgram(2, GL_VERTEX_SHADER, "shaders/simpleVS.glsl", GL_FRAGMENT_SHADER, "shaders/simpleFS.glsl");
}