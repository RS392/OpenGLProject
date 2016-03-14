#include "stdafx.h"
#include "Scene.h"
#include "Terrain.h"


Terrain::Terrain()
{
	setIntervals(100);
	setTranslateVector(0.0, 0.0, 100.0);
	setInitialPoints();
	setVertices();
}
/*/ todo: first set of vertices = last
Terrain::Terrain(vector<glm::vec3> last, Vector3D lastTranslateVector)
{
	setIntervals(10);
	setTranslateVector(lastTranslateVector.getX(), lastTranslateVector.getY(),lastTranslateVector.getZ());
	setInitialPoints();
	setVertices();
}*/
Terrain::~Terrain()
{
}

void Terrain::setTranslateVector(double x, double y, double z)
{
	translateVector = Vector3D(x, y, z);
}
Vector3D Terrain::getTranslateVector()
{
	return translateVector;
}

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
	for (int m = 0; m < intervals; m++) 
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
			if (i == initialPoints.size()-1)//if last translation, modify translation vector 
			{
				float x = translateVector.getX();
				float y = translateVector.getY();
				float z = translateVector.getZ();
				srand(time(NULL));
				if (rand() / RAND_MAX> .5)//todo add probabilities
				{
					//translateVector.setX(x += 10);
					//translateVector.setY(y -= 0);
					translateVector.setZ(z += 1);
					srand(time(NULL));
				}
				else if (rand() / RAND_MAX < .15)
				{
					//translateVector.setY(y += 0);
					translateVector.setZ(z += 1);
					srand(time(NULL));
				}
				else if (rand() / RAND_MAX>.2 && rand() / RAND_MAX< .45)
				{
					//translateVector.setX(x -= 10);
					//translateVector.setY(y += 0);
					translateVector.setZ(z += 1);
					srand(time(NULL));
				}
			}
			
		}
		
	}

	setWireFrameIndices(rowLength);
}
vector<GLfloat> Terrain::getVertices()
{
	return vertices;
}


vector<GLuint> Terrain::getWireFrameIndices()
{
	return wireFrameIndices;
}

void Terrain::setProbabilities(double a, double b, double c)
{
	probabilities.push_back(a);
	probabilities.push_back(b);
	probabilities.push_back(c);
}
vector<float> Terrain::getProbabilities()
{
	return probabilities;
}
void Terrain::setIntervals(int number)
{
	intervals = number;
}
int Terrain::getIntervals()
{
	return intervals;
}
vector<glm::vec3> Terrain::getInitialPoints()
{
	return initialPoints;
}
void Terrain::setInitialPoints()
{
	for (int i = -1000*intervals; i < 1000*intervals-1000; i+=500)
	{
		//initialPoints.push_back(glm::vec3((i / (float)intervals), 0.0, -1.0));
		initialPoints.push_back(glm::vec3((float)i, 0.0, 1500.0));
	}


}
/*
Populates vector indices in the format required for GL_POINTS (i.e. (i[v1], i[v2]) where two vertices are required to form a line)
Also populates vectors indicesForTriangles required for GL_TRIANGLES of the format (i.e. (i[v1], i[v2], i[v3]) where three vertices are required to form a triangle)
Does not connect with itself at the end of each "row" (where row represents a vertex rotated n (span) times)
*/
void Terrain::setWireFrameIndices(int initialSize)
{
	
	offset = initialSize;
	
	int i = 0;
	for (int k = 0; k <vertices.size() - 3; k += 3) {//test
		i = k / 3;
		if (k < vertices.size() - offset*3 )// not the last set of translated points
		{

			if ((i%offset) != (offset - 1)) //not the last point of a set of translated points
			{
				wireFrameIndices.push_back(i);
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
				

			}

		}
		
		
	}
	for (int m = 0; m < wireFrameIndices.size() - 4; m += 4)
	{
		indicesForTriangles.push_back(wireFrameIndices[m]);
		indicesForTriangles.push_back(wireFrameIndices[m+1]);
		indicesForTriangles.push_back(wireFrameIndices[m+3]);
	}

}
vector<GLuint> Terrain::getIndicesForTriangles()
{
	return indicesForTriangles;
}

vector<glm::vec3> Terrain::getLastPoints()
{
	vector<glm::vec3> lastVertices;

	for (int i = vertices.size() - offset * 3; i < vertices.size() - 3; i += 3)
	{
		lastVertices.push_back(glm::vec3(vertices[i], vertices[i+1], vertices[i+2]));
	}
	return lastVertices;
}