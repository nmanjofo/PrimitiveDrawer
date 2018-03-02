#pragma once

#include <glm/glm.hpp>

struct CubeParams
{
	glm::vec3 centerPoint;
	glm::vec3 extents;
	glm::vec3 color;
	float wireframeLineWidth;
	bool isWireframe;
};