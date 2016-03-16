#include "stdafx.h"
#include "Scene.h"
#include "Terrain.h"


Terrain::Terrain(glm::vec3 cameraPosition)
{
	setCameraPosition(cameraPosition);
	setIntervals(100);
	setTranslateVector(0.0, 0.0, 100.0);
	setTextureCoordinates(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	setInitialPoints();
	setVertices();
	setTest();
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
	//setLastPoints(); //todo
	setWireFrameIndices(rowLength);
}

void Terrain::setTextureCoordinates(float u1, float v1, float u2, float v2, float u3 , float v3, float u4, float v4)
{
	textureCoordinates.push_back(glm::vec2(u1, v1));
	textureCoordinates.push_back(glm::vec2(u2, v2));
	textureCoordinates.push_back(glm::vec2(u3, v3));
	textureCoordinates.push_back(glm::vec2(u4, v4));
	

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
		initialPoints.push_back(glm::vec3((float)i, getCameraPosition().y-50, (float)getCameraPosition().z));
	}
	waterVertices.push_back(initialPoints[0].x);
	waterVertices.push_back(-.01);
	waterVertices.push_back(initialPoints[0].z);

	waterVertices.push_back(initialPoints[initialPoints.size()-1].x);
	waterVertices.push_back(-.01);
	waterVertices.push_back(initialPoints[initialPoints.size() - 1].z);
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

				//wireframe vertices
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
				
				//Texture vertices of i: x, y, z, u, v
				textureVertices.push_back(vertices[i]);//x
				textureVertices.push_back(vertices[i + 1]);//y
				textureVertices.push_back(vertices[i + 2]);//z
				textureVertices.push_back(textureCoordinates[0].x);//bottom left/origin
				textureVertices.push_back(textureCoordinates[0].y);

				//Texture vertices of i + 1: x, y, z, u, v
				textureVertices.push_back(vertices[i+3]);//x
				textureVertices.push_back(vertices[i + 4]);//y
				textureVertices.push_back(vertices[i + 5]);//z
				textureVertices.push_back(textureCoordinates[1].x);//bottom right
				textureVertices.push_back(textureCoordinates[1].y);

				//Texture vertices of i + offset + 1: x, y, z, u, v
				textureVertices.push_back(vertices[i + (offset * 3) + 3]);//x
				textureVertices.push_back(vertices[i + (offset * 3) + 4]);//y
				textureVertices.push_back(vertices[i + (offset * 3) + 5]);//z
				textureVertices.push_back(textureCoordinates[3].x);//top right
				textureVertices.push_back(textureCoordinates[3].y);

				//Texture vertices of i + offset: x, y, z, u, v
				textureVertices.push_back(vertices[i + (offset * 3)]);//x
				textureVertices.push_back(vertices[i + (offset * 3) + 1]);//y
				textureVertices.push_back(vertices[i + (offset * 3) + 2]);//z
				textureVertices.push_back(textureCoordinates[2].x);//top left
				textureVertices.push_back(textureCoordinates[2].y);
				/**/
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
vector<float> Terrain::getWaterVertices()
{
	return waterVertices;
}
vector<GLuint> Terrain::getWaterIndices()
{
	return waterIndices;
}

void Terrain::setWaterIndices()
{
	waterIndices.push_back(0);
	waterIndices.push_back(3);
	
	waterIndices.push_back(3);
	waterIndices.push_back(9);

	waterIndices.push_back(9);
	waterIndices.push_back(0);

	waterIndices.push_back(0);
	waterIndices.push_back(9);

	waterIndices.push_back(9);
	waterIndices.push_back(6);

	waterIndices.push_back(6);
	waterIndices.push_back(0);
}

