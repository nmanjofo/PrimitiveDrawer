#include "LineDrawer.hpp"
#include "LineParams.hpp"

#include "Primitive.hpp"

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
	return _lineProgram.makeProgram(2, GL_VERTEX_SHADER, "shaders/simpleVS.glsl", GL_FRAGMENT_SHADER, "shaders/simpleFS.glsl");
}

void LineDrawer::_initBuffers()
{
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
	glGenBuffers(1, &_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void LineDrawer::drawPrimitive(const Primitive& primitive, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	if (primitive.primitiveType != PrimitiveType::LINE)
		return;

	const LineParams params = _convertPrimitiveToLineParams(primitive);

	_updateVBO(glm::vec4(params.from, 1), glm::vec4(params.to, 1));

	_lineProgram.bind();
	_lineProgram.updateUniform("color", params.color);
	_lineProgram.updateUniform("mvp", projectionMatrix * viewMatrix);

	_drawLine(params.thickness);

	_lineProgram.unbind();
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

LineParams LineDrawer::_convertPrimitiveToLineParams(const Primitive& primitive)
{
	LineParams p;
	p.from = glm::vec3(primitive.params[0]._float, primitive.params[1]._float, primitive.params[2]._float);
	p.to = glm::vec3(primitive.params[3]._float, primitive.params[4]._float, primitive.params[5]._float);
	p.color = glm::vec3(primitive.params[6]._float, primitive.params[7]._float, primitive.params[8]._float);
	p.thickness = primitive.params[9]._float;

	return p;
}

