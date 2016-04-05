/*
Every feature( like a tree or a rock), will be an object therefore will have to inherit from this class.


*/

#pragma once
#include <vector>
#include "Vector3D.h"

using namespace std;
typedef vector<vec3> vertices;
typedef vector<vec2> UVs;

//typedef vector<vector<float>> vertsAndUvs; // first vxuvs option
typedef vector<float> vertsAndUvs; // second vxuvs option

class Object
{

private:
	
	
public:
	UVs uvs;
	void combineVXUvs();
	void combineVXUvs2();
	vertsAndUvs vxuvs;
	int vertSize;
	int uvsSize;
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
	vector<vec3> tangents;
	vector<vec3> bitangents;
	vector<vec3> normals;
	Object();
	~Object();
};

