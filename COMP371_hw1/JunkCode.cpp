#include "stdafx.h"
#include "JunkCode.h"


JunkCode::JunkCode()
{
}


JunkCode::~JunkCode()
{
}

bool lorisJunk()
{

	/*
	Normal rendering

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*terrain->getVertices().size(), (&terrain->getVertices()[0]), GL_STATIC_DRAW);
	//cout << terrain->getVertices().size() << endl;
	glVertexAttribPointer(
	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	3,                  // size
	GL_FLOAT,           // type
	GL_FALSE,           // normalized?
	0,                  // stride
	(void*)0            // array buffer offset
	);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*terrain->getWireFrameIndices().size(), (&terrain->getWireFrameIndices()[0]), GL_STATIC_DRAW);
	glDrawElements(GL_LINES, terrain->getWireFrameIndices().size(), GL_UNSIGNED_INT, nullptr);//Terrain test
	//glDrawArrays(GL_POINTS, 0, (terrain->getVertices().size()/3));
	//glDrawArrays(GL_POINTS, 0, (terrain->getVertices().size()));
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat)*terrain->getIndicesForTriangles().size(), (&terrain->getIndicesForTriangles()[0]), GL_STATIC_DRAW);
	//glDrawElements(GL_TRIANGLES, terrain->getIndicesForTriangles().size(), GL_UNSIGNED_INT, nullptr);//Terrain test
	//cout << terrain->getVertices().size() << " size versus " << terrain->getIndicesForTriangles().size() << endl;
	//
	*/
	/*/
	void Terrain::setVertices()
	{

	int rowLength = initialPoints.size();
	for (int i = 0; i <vertices.size(); i++)
	{
	vertices.push_back(initialPoints[i].x);
	vertices.push_back(initialPoints[i].y);
	vertices.push_back(initialPoints[i].z);
	//cout << vertices[i].getX() << "," << vertices[i].getY() << "," << vertices[i].getZ() << endl;
	}
	glm::mat4 translateMatrix = glm::mat4(1.0f);
	for (int m = initialPoints[0].z; m < 0.5*getCameraPosition().z; m++)//from -.5*RADIUS to .5*RADIUS
	{
	translateMatrix = glm::translate(translateMatrix,
	glm::vec3(
	translateVector.getX(), translateVector.getY(), translateVector.getZ()));
	for (int i = 0; i < initialPoints.size(); i++) {

	glm::vec4 vertex(initialPoints[i].x, initialPoints[i].y, initialPoints[i].z, 1.0f);
	glm::vec4 newV = translateMatrix * vertex;
	vertices.push_back(newV.x);
	vertices.push_back(newV.y);
	vertices.push_back(newV.z);
	if (i == initialPoints.size() - 1)//if last translation, modify translation vector
	{
	float x = translateVector.getX();
	float y = translateVector.getY();
	float z = translateVector.getZ();
	srand(time(NULL));
	if (rand() / RAND_MAX> .5)//todo add probabilities
	{
	//translateVector.setX(x += 10);
	//translateVector.setY(y -= 0);
	translateVector.setZ(z += 10);
	srand(time(NULL));
	}
	else if (rand() / RAND_MAX < .15)
	{
	//translateVector.setY(y += 0);
	translateVector.setZ(z += 15);
	srand(time(NULL));
	}
	else if (rand() / RAND_MAX>.2 && rand() / RAND_MAX< .45)
	{
	//translateVector.setX(x -= 10);
	//translateVector.setY(y += 0);
	translateVector.setZ(z += 9);
	srand(time(NULL));
	}
	}

	}

	}
	//setLastPoints(); //todo
	setQuadIndices(rowLength);
	//setWireFrameIndices(rowLength);
	}

	//wireframe vertices
	/*wireFrameIndices.push_back(i);
	wireFrameIndices.push_back(i + 1); // (i, i+1)

	wireFrameIndices.push_back(i + 1);// (i, i+offset+1)
	wireFrameIndices.push_back(i + offset); // (i, i+offset)

	wireFrameIndices.push_back(i + offset);// (i, i+offset+1)
	wireFrameIndices.push_back(i);

	wireFrameIndices.push_back(i + 1);
	wireFrameIndices.push_back(i + offset + 1);// (i, i+offset+1)

	wireFrameIndices.push_back(i + offset + 1);// (i, i+offset+1)
	wireFrameIndices.push_back(i + offset);// (i, i+offset+1)

	wireFrameIndices.push_back(i + offset);// (i, i+offset+1)
	wireFrameIndices.push_back(i + 1); // (i, i+offset)
void Terrain::setLastPoints()
{
	//todo	
	for (int i = vertices.size() - offset * 3; i < vertices.size() - 3; i += 3)
	{
		lastVertices.push_back(glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]));
	}
	if (lastVertices.size() > 0)
	{
		waterVertices.push_back(lastVertices[0].x);
		waterVertices.push_back(-.01);
		waterVertices.push_back(lastVertices[0].z);

		waterVertices.push_back(lastVertices[lastVertices.size() - 1].x);
		waterVertices.push_back(-.01);
		waterVertices.push_back(lastVertices[lastVertices.size() - 1].z);
		setWaterIndices();
	}

}
vector<glm::vec3> Terrain::getLastPoints()
{
return lastVertices;
}
	*/
	return true;
}
