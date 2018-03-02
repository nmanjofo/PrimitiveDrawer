#pragma once

#include "Plane.hpp"

struct PlaneParams
{
	Plane plane;
	glm::vec3 color;
	float scale;
	bool isWireframe;
	float lineThickness;
};