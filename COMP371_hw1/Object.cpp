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
void Object::combineVXUvs() {
	for (int i = 0; i < verts.size(); ++i) {
		vector<float> comb(5);
		comb[0] = verts[i][0];
		comb[1] = verts[i][1];
		comb[2] = verts[i][2];

		comb[3] = uvs[i][0];
		comb[4] = uvs[i][1];
		vxuvs.push_back(comb);

	}
}