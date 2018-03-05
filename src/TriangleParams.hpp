#pragma once

#include <glm/glm.hpp>

struct TriangleParams
{
	glm::vec4 vertices[3];
	glm::vec3 color;
	float lineThickness;
	bool isWireframe;
};