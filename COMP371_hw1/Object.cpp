#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	//verts.push_back(vec3(0));
	xScale = 0;
	yScale = 0;
	zScale = 0;
	xTranslation = 0;
	zTranslation = 0;
	number = 0;
}


Object::~Object()
{
}
/*
vxuvs is under the form
v1 v2 v3 uv1 uv2
v1 v2 v3 uv1 uv2
...
v1 v2 v3 uv1 uv2 (the last ones)
*/
void Object::combineVXUvs() {
	/*
	for (int i = 0; i < verts.size(); ++i) {
		
		vector<float> comb(5);
		comb[0] = verts[i][0];
		comb[1] = verts[i][1];
		comb[2] = verts[i][2];

		comb[3] = uvs[i][0];
		comb[4] = uvs[i][1];
		vxuvs.push_back(comb);
		
	}
	for (int i = vxuvs.size() - 2; i < vxuvs.size(); ++i) {
		cout << vxuvs[i][0] << vxuvs[i][1] << vxuvs[i][2] << vxuvs[i][3] << vxuvs[i][4] << endl;
	}
	*/
}
/*
vxuvs here is under the form
v1 v2 v3
v1 v2 v3
...
v1 v2 v3 ( the last ones)
uv1 uv2
uv1 uv2
...
uv1 uv2 (the last ones)

USE ONLY ONE OF THESE METHODS NOT BOTH
*/
void Object::combineVXUvs2() {
	vertSize = verts.size();
	uvsSize = uvs.size();

	for (int i = 0; i < verts.size(); ++i) {
		vxuvs.push_back(verts[i][0]);
		vxuvs.push_back(verts[i][1]);
		vxuvs.push_back(verts[i][2]);
	}
	for (int i = 0; i < uvs.size(); ++i) {
		vxuvs.push_back(uvs[i][0]);
		vxuvs.push_back(uvs[i][1]);
	}
	
}