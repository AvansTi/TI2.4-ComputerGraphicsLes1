#pragma once

#include <vector>
#include <string>
#include "Vec3.h"

class ObjModel
{
public:
	class Face
	{
	public:
		int pos[3];
		int normal[3];
	};

	std::vector<Vec3> positions;
	std::vector<Vec3> normals;
	std::vector<Face> faces;

	ObjModel(const std::string& fileName);
};

