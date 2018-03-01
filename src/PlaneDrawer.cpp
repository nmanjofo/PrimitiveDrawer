#include "PlaneDrawer.hpp"
#include "Primitive.hpp"
#include "Plane.hpp"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

PlaneDrawer* PlaneDrawer::_instance = nullptr;

PlaneDrawer* PlaneDrawer::getInstance()
{
	if (!_instance)
		_instance = new PlaneDrawer;

	return _instance;
}


PlaneDrawer::PlaneDrawer()
{
	_VBO = _VAO = 0;
}

PlaneDrawer::~PlaneDrawer()
{
	clear();
}

bool PlaneDrawer::init()
{
	if (!_initProgram())
		return false;

	_initBuffers();

	return true;
}

bool PlaneDrawer::_initProgram()
{
	return _planeProgram.makeProgram(2, GL_VERTEX_SHADER, "shaders/simpleVS.glsl", GL_FRAGMENT_SHADER, "shaders/simpleFS.glsl");
}

void PlaneDrawer::_initBuffers()
{
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
	glGenBuffers(1, &_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	const glm::vec4 arr[] = { glm::vec4(-0.5f, 0, 0.5, 1), glm::vec4(0.5f, 0, 0.5, 1), glm::vec4(0.5f, 0, -0.5, 1), glm::vec4(-0.5f, 0, 0.5, 1), glm::vec4(0.5f, 0, -0.5, 1), glm::vec4(-0.5f, 0, -0.5, 1) };
	glBufferData(GL_ARRAY_BUFFER, 2*3*4 * sizeof(float), arr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PlaneDrawer::clear()
{
	glDeleteBuffers(1, &_VBO);
	glDeleteVertexArrays(1, &_VAO);
}

void PlaneDrawer::drawPrimitive(const Primitive& primitive, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	if (primitive.primitiveType != PrimitiveType::PLANE)
		return;

	PlaneParams plane = _convertPrimitiveToPlaneParams(primitive);

	glm::mat4 modelMat = _getPlaneModelMatrix(plane);
	
	glm::mat4 mvp = projectionMatrix * viewMatrix * modelMat;

	_planeProgram.bind();
	_planeProgram.updateUniform("mvp", mvp);
	_planeProgram.updateUniform("color", plane.color);

	_drawPlane();

	_planeProgram.unbind();
}

PlaneParams PlaneDrawer::_convertPrimitiveToPlaneParams(const Primitive& primitive)
{
	PlaneParams plane;
	plane.plane.equation = glm::vec4(primitive.params[0]._float, primitive.params[1]._float, primitive.params[2]._float, primitive.params[3]._float);
	plane.plane.toHessianNormalForm();
	plane.color = glm::vec3(primitive.params[4]._float, primitive.params[5]._float, primitive.params[6]._float);
	plane.scale = primitive.params[7]._float;

	return plane;
}

glm::mat4 PlaneDrawer::_getPlaneModelMatrix(const PlaneParams& plane) const
{
	const glm::vec3 referencePlaneNormal = glm::vec3(0.0f, 1, 0);
	const glm::vec3 planeNormal = glm::normalize(glm::vec3(plane.plane.equation));

	const float angleRad = glm::acos(glm::dot(referencePlaneNormal, planeNormal));

	glm::mat4 rotMat;
	const glm::vec3 rotAxis = glm::cross(referencePlaneNormal, planeNormal);
	if (rotAxis.x == 0 && rotAxis.y == 0 && rotAxis.z == 0)
		rotMat = glm::mat4();
	else
		rotMat = glm::toMat4(glm::angleAxis(angleRad, glm::normalize(rotAxis)));

	const glm::mat4 scaleMat = glm::scale(glm::vec3(plane.scale, plane.scale, plane.scale));
	
	const glm::mat4 translMat = glm::translate(glm::vec3(plane.plane.equation) * (-plane.plane.equation.w));

	return translMat * rotMat * scaleMat;
}

void PlaneDrawer::_drawPlane()
{
	glBindVertexArray(_VAO);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
}




