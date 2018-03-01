#pragma once

#include <glm/glm.hpp>

struct CubeParams
{
	glm::vec3 centerPoint;
	glm::vec3 extents;
	glm::vec2 color;
	bool isWireframe;
};