#include "TriangleDrawer.hpp"

#include "Primitive.hpp"

TriangleDrawer* TriangleDrawer::_instance = nullptr;

TriangleDrawer* TriangleDrawer::getInstance()
{
	if(!_instance)
		_instance = new TriangleDrawer();

	return _instance;
}


void TriangleDrawer::_initBuffers()
{
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
	glGenBuffers(1, &_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TriangleDrawer::drawPrimitive(const Primitive& primitive, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	if (primitive.primitiveType != PrimitiveType::TRIANGLE)
		return;

	const TriangleParams params = _convertPrimitiveToTriangleParams(primitive);

	_updateVBO(params.vertices);

	_program.bind();
	_program.updateUniform("color", params.color);
	_program.updateUniform("mvp", projectionMatrix * viewMatrix);

	_drawTriangle(params.isWireframe, params.lineThickness);

	_program.unbind();
}

void TriangleDrawer::_updateVBO(const glm::vec4 (&vertices)[3])
{
	glNamedBufferData(_VBO, 12 * sizeof(float), vertices, GL_DYNAMIC_DRAW);
}

TriangleParams TriangleDrawer::_convertPrimitiveToTriangleParams(const Primitive& primitive)
{
	TriangleParams p;

	p.vertices[0] = glm::vec4(primitive.params[0]._float, primitive.params[1]._float, primitive.params[2]._float, 1);
	p.vertices[1] = glm::vec4(primitive.params[3]._float, primitive.params[4]._float, primitive.params[5]._float, 1);
	p.vertices[2] = glm::vec4(primitive.params[6]._float, primitive.params[7]._float, primitive.params[8]._float, 1);

	p.color = glm::vec3(primitive.params[9]._float, primitive.params[10]._float, primitive.params[11]._float);

	p.isWireframe = primitive.params[12]._char == 'w' ? true : false;

	p.lineThickness = primitive.params[13]._float;

	return p;
}

void TriangleDrawer::_drawTriangle(bool isWireframe, float lineThickness)
{
	glBindVertexArray(_VAO);

	if (isWireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(lineThickness);
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}