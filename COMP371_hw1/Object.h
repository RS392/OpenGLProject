/*
Every feature( like a tree or a rock), will be an object therefore will have to inherit from this class.


*/

#pragma once
#include <vector>
#include "Vector3D.h"

using namespace std;
typedef vector<vec3> vertices;
class Object
{

private:
	
	
public:
	int xScale;
	int yScale;
	int zScale;
	int xTranslation;
	int zTranslation;
	int number;
	vec3 position;
	vec3 boundingBox;
	string type;
	vertices verts;
	Object();
	~Object();
};

