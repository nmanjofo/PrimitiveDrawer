#include "Plane.hpp"


void Plane::createFromPointsCCW(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3)
{
	glm::vec3 normal = glm::normalize(glm::cross(glm::normalize(v3 - v2), glm::normalize(v1 - v2)));

	createFromPointNormalCCW(v2, normal);
}

void Plane::createFromPointNormalCCW(const glm::vec3& point, const glm::vec3& normalizedNormal)
{
	equation = glm::vec4(normalizedNormal, -point.x*normalizedNormal.x - point.y*normalizedNormal.y - point.z*normalizedNormal.z);
}

void Plane::toHessianNormalForm()
{
	equation = equation / (glm::sqrt(equation.x * equation.x + equation.y * equation.y + equation.z * equation.z));
}
