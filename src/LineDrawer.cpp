#include "LineDrawer.hpp"
#include "LineParams.hpp"

LineDrawer* LineDrawer::_instance = nullptr;

LineDrawer* LineDrawer::getInstance()
{
	if(!_instance)
		_instance = new LineDrawer;

	return _instance;
}

LineDrawer::LineDrawer() : AbstractPrimitiveDrawer()
{
	
}

LineDrawer::~LineDrawer()
{
	clear();
}

bool LineDrawer::init()
{
	if (!_initProgram())
		return false;

	_initBuffers();

	return true;
}

bool LineDrawer::_initProgram()
{
	return _lineProgram.makeProgram(2, GL_VERTEX_SHADER, "shadres/simpleVS.glsl", GL_FRAGMENT_SHADER, "shaders/simpleFS.glsl");
}

void LineDrawer::_initBuffers()
{
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	glGenBuffers(1, &_VBO);
	glNamedBufferData(_VBO, 8 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void LineDrawer::drawPrimitive(void* lineParams, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	const LineParams* params = reinterpret_cast<LineParams*>(lineParams);

	_updateVBO(glm::vec4(params->from, 1), glm::vec4(params->to, 1));

	_lineProgram.bind();
	_lineProgram.updateUniform("color", params->color);
	_lineProgram.updateUniform("viewProjectionMatrix", viewMatrix * projectionMatrix);

	_drawLine(params->thickness);
}

void LineDrawer::_drawLine(float thickness)
{
	glBindVertexArray(_VAO);
	
	glLineWidth(thickness);
	glDrawArrays(GL_LINES, 0, 2);

	glBindVertexArray(0);
}

void LineDrawer::_updateVBO(const glm::vec4& v1, const glm::vec4& v2)
{
	const glm::vec4 arr[2] = { v1, v2 };

	glNamedBufferData(_VBO, 8 * sizeof(float), arr, GL_DYNAMIC_DRAW);
}

void LineDrawer::clear()
{
	glDeleteBuffers(1, &_VBO);
	glDeleteVertexArrays(1, &_VAO);
}


