#pragma once

#include "Geometry.hpp"
#include "VertexData.h"

class GeometryHelper
{
public:
	static void CreateRectangle(std::shared_ptr<Geometry<VertexColorData>> geometry, Color color);
	static void CreateRectangle(std::shared_ptr<Geometry<VertexTextureData>> geometry);
};

