#include "stdafx.h"
#include "Scene.h"
#include "Terrain.h"


Terrain::Terrain()
{
	setIntervals(10);
	setTranslateVector(0.0, 0.0, 100);
	setVertices();
}

Terrain::~Terrain()
{
}

vector<GLfloat> Terrain::getTest() 
{
	return test;
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
	

	//populate with number of points based on interval.
	for (int i = -10 * intervals; i < intervals*10; i++)//pushes back vertices with x values ranging from -1 to 0, 0 to 1
	{
		initialPoints.push_back((Vector3D(50*((i / (float)intervals)), 0.0, 200.0)));
	}
	int rowLength = initialPoints.size(); //for calculating indices
										  // Translate based on vector
	for (int j = 0; j < initialPoints.size(); j++)
	{
		vertices.push_back(initialPoints[j]);
	}
	glm::mat4 translateMatrix = glm::mat4(1.0f);
	for (int m = 0; m < intervals; m++) 
	{
		translateMatrix = glm::translate(translateMatrix,
			glm::vec3(
				translateVector.getX(), translateVector.getY(), translateVector.getZ()));
		for (int i = 0; i < initialPoints.size(); i++) {

			glm::vec4 vertex(initialPoints[i].getX(), initialPoints[i].getY(), initialPoints[i].getZ(), 1.0f);
			glm::vec4 newV = translateMatrix * vertex;
			vertices.push_back(Vector3D(newV.x, newV.y, newV.z));
			if (i == initialPoints.size()-1)//if last translation, modify translation vector 
			{
				float x = translateVector.getX();
				float y = translateVector.getY();
				float z = translateVector.getZ();
				srand(time(NULL));
				if (rand() / 100 > .5)//todo add probabilities
				{
					translateVector.setX(x += 51);
					translateVector.setY(y -= 10);
					translateVector.setZ(z += 10);
					srand(time(NULL));
				}
				else if (rand() / 100 < .15)
				{
					translateVector.setY(y += 10);
					translateVector.setZ(z += 25);
					srand(time(NULL));
				}
				else if (rand() / 100 >.2 && rand() / 100 < .45)
				{
					translateVector.setX(x -= 1);
					translateVector.setY(y += 5);
					translateVector.setZ(z += 25);
					srand(time(NULL));
				}
			}
			
		}
		
	}
	
	//all will increase in z
	//biggish variation in y
	//small variations in x
	setWireFrameIndices(rowLength);
}
vector<Vector3D> Terrain::getVertices()
{
	return vertices;
}

void Terrain::setDirt(double r, double g, double b, double a)
{
	dirt = Vector4D(r, g, b, a);
}
Vector4D Terrain::getDirt()
{
	return dirt;
}

void Terrain::setGrass(double r, double g, double b, double a)
{
	grass = Vector4D(r, g, b, a);
}
Vector4D Terrain::getGrass()
{
	return grass;
}

void Terrain::setWater(double r, double g, double b, double a)
{
	water = Vector4D(r, g, b, a);
}
Vector4D Terrain::getWater()
{
	return water;
}

void Terrain::setCurrentY(double y)
{
	currentY = y;
}
double Terrain::getCurrentY()
{
	return currentY;
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
/*
Populates vector indices in the format required for GL_POINTS (i.e. (i[v1], i[v2]) where two vertices are required to form a line)
Also populates vectors indicesForTriangles required for GL_TRIANGLES of the format (i.e. (i[v1], i[v2], i[v3]) where three vertices are required to form a triangle)
Does not connect with itself at the end of each "row" (where row represents a vertex rotated n (span) times)
*/
void Terrain::setWireFrameIndices(int initialSize)
{
	for (int i = 0; i <vertices.size(); i++)
	{
		test.push_back(vertices[i].getX());
		test.push_back(vertices[i].getY());
		test.push_back(vertices[i].getZ());
		//cout << vertices[i].getX() << "," << vertices[i].getY() << "," << vertices[i].getZ() << endl;
	}
	int offset = initialSize;
	
	int i = 0;
	for (int k = 0; k <test.size() - 3; k += 3) {//test
		i = k / 3;
		if (k < test.size() - offset*3 )// not the last set of translated points
		{

			if ((i%offset) != (offset - 1)) //not the last point of a set of translated points
			{
				wireFrameIndices.push_back(i);
				wireFrameIndices.push_back(i + 1); // (i, i+1)
				//std::cout << i << endl;
				//std::cout << "i, i+1: (" << i << "," << i + 1 << ")" << endl;

				wireFrameIndices.push_back(i + 1);// (i, i+offset+1)
				wireFrameIndices.push_back(i + offset); // (i, i+offset)

				//std::cout << "i + 1: (" << i + 1 << "," << i + offset << ")" << endl;

				wireFrameIndices.push_back(i + offset);// (i, i+offset+1)
				wireFrameIndices.push_back(i);

				//std::cout << "i + offset: (" << i + offset << "," << i << ")" << endl;

				wireFrameIndices.push_back(i + 1);
				wireFrameIndices.push_back(i + offset + 1);// (i, i+offset+1)
				//std::cout << "i+1, i+offset+1: (" << i + 1 << "," << i + offset + 1 << ")" << endl;

				wireFrameIndices.push_back(i + offset + 1);// (i, i+offset+1)
				wireFrameIndices.push_back(i + offset);// (i, i+offset+1)

				wireFrameIndices.push_back(i + offset);// (i, i+offset+1)
				wireFrameIndices.push_back(i + 1); // (i, i+offset)
				//std::cout << "i+offset+1,i: (" << i + offset + 1 << "," << i << ")" << endl;

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