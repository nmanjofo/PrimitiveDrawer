#include "CubeDrawer.hpp"
#include "Primitive.hpp"

#include <glm/gtx/transform.hpp>

CubeDrawer* CubeDrawer::_instance = nullptr;

CubeDrawer* CubeDrawer::getInstance()
{
	if (_instance == nullptr)
		_instance = new CubeDrawer();

	return _instance;
}

CubeDrawer::CubeDrawer() : AbstractPrimitiveDrawer()
{	
}

CubeDrawer::~CubeDrawer()
{
}

void CubeDrawer::_initBuffers()
{
	glGenVertexArrays(1, &_VAO);
	assert(glGetError() == GL_NO_ERROR);
	glBindVertexArray(_VAO);
	assert(glGetError() == GL_NO_ERROR);
	glGenBuffers(1, &_VBO);
	assert(glGetError() == GL_NO_ERROR);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	assert(glGetError() == GL_NO_ERROR);
	const glm::vec4 arr[] = { 
		//+X
		glm::vec4(0.5f, -0.5, 0.5, 1), 
		glm::vec4(0.5f, -0.5, -0.5, 1), 
		glm::vec4(0.5f, 0.5, -0.5, 1),
		glm::vec4(0.5f, -0.5, 0.5, 1),
		glm::vec4(0.5f, 0.5, -0.5, 1),
		glm::vec4(0.5f, 0.5, 0.5, 1),
		//-X
		glm::vec4(-0.5f, -0.5, 0.5, 1),
		glm::vec4(-0.5f, 0.5, -0.5, 1),
		glm::vec4(-0.5f, -0.5, -0.5, 1),
		glm::vec4(-0.5f, -0.5, 0.5, 1),
		glm::vec4(-0.5f, 0.5, 0.5, 1),
		glm::vec4(-0.5f, 0.5, -0.5, 1),
		//+Y
		glm::vec4(-0.5f, 0.5, 0.5, 1),
		glm::vec4(0.5f, 0.5, 0.5, 1),
		glm::vec4(0.5f, 0.5, -0.5, 1),
		glm::vec4(-0.5f, 0.5, 0.5, 1),
		glm::vec4(0.5f, 0.5, -0.5, 1),
		glm::vec4(-0.5f, 0.5, -0.5, 1),
		//-Y
		glm::vec4(-0.5f, -0.5, -0.5, 1),
		glm::vec4(0.5f, -0.5, -0.5, 1),
		glm::vec4(0.5f, -0.5, 0.5, 1),
		glm::vec4(-0.5f, -0.5, -0.5, 1),
		glm::vec4(0.5f, -0.5, 0.5, 1),
		glm::vec4(-0.5f, -0.5, 0.5, 1),
		//+Z
		glm::vec4(-0.5f, -0.5, 0.5, 1),
		glm::vec4(0.5f, -0.5, 0.5, 1),
		glm::vec4(0.5f, 0.5, 0.5, 1),
		glm::vec4(-0.5f, -0.5, 0.5, 1),
		glm::vec4(0.5f, 0.5, 0.5, 1),
		glm::vec4(-0.5f, 0.5, 0.5, 1),
		//-Z
		glm::vec4(0.5f, -0.5, -0.5, 1),
		glm::vec4(-0.5f, -0.5, -0.5, 1),
		glm::vec4(-0.5f, 0.5, -0.5, 1),
		glm::vec4(0.5f, -0.5, -0.5, 1),
		glm::vec4(-0.5f, 0.5, -0.5, 1),
		glm::vec4(0.5f, 0.5, -0.5, 1),
	};
	glBufferData(GL_ARRAY_BUFFER, 36 * 4 * sizeof(float), arr, GL_DYNAMIC_DRAW);
	
	assert(glGetError() == GL_NO_ERROR);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	assert(glGetError() == GL_NO_ERROR);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CubeDrawer::drawPrimitive(const Primitive& primitive, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	if (primitive.primitiveType != PrimitiveType::CUBE)
		return;

	CubeParams params = _convertPrimitiveToCubearams(primitive);

	if (params.isWireframe && params.wireframeLineWidth <= 0)
		return;

	glm::mat4 worldMat = _getCubeWorldMatrix(params);
	
	_program.bind();
	
	_program.updateUniform("mvp", projectionMatrix * viewMatrix * worldMat);
	_program.updateUniform("color", params.color);
	
	_drawCube(params.isWireframe, params.wireframeLineWidth);
	
	_program.unbind();
}

CubeParams CubeDrawer::_convertPrimitiveToCubearams(const Primitive& primitive)
{
	CubeParams params;
	params.centerPoint = glm::vec3(primitive.params[0]._float, primitive.params[1]._float, primitive.params[2]._float);
	params.extents = glm::vec3(primitive.params[3]._float, primitive.params[4]._float, primitive.params[5]._float);
	params.color = glm::vec3(primitive.params[6]._float, primitive.params[7]._float, primitive.params[8]._float);
	params.isWireframe = primitive.params[9]._char == 'w' ? true : false;
	params.wireframeLineWidth = primitive.params[10]._float;

	return params;
}

glm::mat4 CubeDrawer::_getCubeWorldMatrix(const CubeParams& params)
{
	glm::mat4 transMat = glm::translate(params.centerPoint);
	glm::mat4 scaleMat = glm::scale(params.extents);

	return transMat * scaleMat;
}

void CubeDrawer::_drawCube(bool isWireframe, float lineThickness)
{
	glBindVertexArray(_VAO);

	if (isWireframe)
	{
		assert(glGetError() == GL_NO_ERROR);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		assert(glGetError() == GL_NO_ERROR);
		glLineWidth(lineThickness);
		assert(glGetError() == GL_NO_ERROR);
	}

	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	glBindVertexArray(0);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


