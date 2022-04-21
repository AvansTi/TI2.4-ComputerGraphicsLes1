#include "ObjModel.h"
#include <fstream>
#include <sstream>
#include <iostream>

ObjModel::ObjModel(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cerr << "Could not open file " << fileName << std::endl;
		return;
	}
	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);
		std::stringstream lineStream(line);

		std::string firstPart;
		lineStream >> firstPart;
		if (firstPart == "v")
		{
			Vec3 position(0, 0, 0);
			lineStream >> position.x;
			lineStream >> position.y;
			lineStream >> position.z;
			positions.push_back(position);
		}
		if (firstPart == "vn")
		{
			Vec3 normal(0, 0, 0);
			lineStream >> normal.x;
			lineStream >> normal.y;
			lineStream >> normal.z;
			normals.push_back(normal);
		}
		if (firstPart == "f")
		{
			Face face;
			for (int i = 0; i < 3; i++)
			{
				char junk;
				lineStream >> face.pos[i];
				lineStream >> junk;
				lineStream >> face.normal[i];
				lineStream >> junk;
				lineStream >> face.normal[i];
				face.pos[i]--;
				face.normal[i]--;
			}
			faces.push_back(face);
		}
	}
}
