#pragma once
#include <vector>
#include "../glm/glm.hpp"
using namespace std;
using namespace glm;
class FileReader
{
public:
	bool loadObj(const char * path, vector < vec3 > & out_vertices, vector < vec2 > & out_uvs, vector < vec3 > & out_normals);
	FileReader();
	~FileReader();
};

