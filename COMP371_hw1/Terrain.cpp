#include "stdafx.h"
#include "Scene.h"
#include "Terrain.h"

Terrain::Terrain()
{
	setIntervals(10);
	setTranslateVector(0.0, 0.0, 1);
	setFirstSetOfVertices();
	setVertices();
}
Terrain::Terrain(vector<glm::vec3> last, Vector3D lastTranslateVector)
{
	setIntervals(10);
	setTranslateVector(lastTranslateVector.getX(), lastTranslateVector.getY(), lastTranslateVector.getZ());
	setVertices();
}
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
void Terrain::setFirstSetOfVertices()
{
	//populate with number of points based on interval.
	for (int i = -10 * intervals; i < intervals * 10; i++)//pushes back vertices with x values ranging from -1 to 0, 0 to 1
	{
		initialPoints.push_back(glm::vec3(i / (float)intervals, 0.0, -1.0));
	}
}
void Terrain::setVertices()
{

	int rowLength = initialPoints.size(); //for calculating indices
										  // Translate based on vector
	for (int j = 0; j < initialPoints.size(); j++)
	{
		vertices.push_back(initialPoints[j].x);
		vertices.push_back(initialPoints[j].y);
		vertices.push_back(initialPoints[j].z);
	}
	glm::mat4 translateMatrix = glm::mat4(1.0f);
	for (int m = 0; m < intervals; m++)
	{
		srand(time(NULL));
		translateMatrix = glm::translate(translateMatrix,
			glm::vec3(
				translateVector.getX(), translateVector.getY(), translateVector.getZ()));
		for (int i = 0; i < initialPoints.size(); i++) {

			glm::vec4 vertex(initialPoints[i].x, initialPoints[i].y, initialPoints[i].z, 1.0f);
			glm::vec4 newV = translateMatrix * vertex;
			//vertices2.push_back(glm::vec3(newV.x, newV.y, newV.z));
			vertices.push_back(newV.x);
			vertices.push_back(newV.y);
			vertices.push_back(newV.z);
			if (i == initialPoints.size() - 1)//if last translation, modify translation vector 
			{
				float x = translateVector.getX();
				float y = translateVector.getY();
				float z = translateVector.getZ();

				cout << (float)rand() / RAND_MAX << endl;
				if ((float)rand() / RAND_MAX > .99)//todo add probabilities
				{
					//translateVector.setX(x += .51);
					if (translateVector.getY() < -0.5)
					{
						translateVector.setY(-0.25);
					}
					else
					{
						translateVector.setY(y -= .15);
					}
					translateVector.setZ(z += 1);
					//srand(time(NULL));
				}
				else if ((float)rand() / RAND_MAX > .5)
				{
					translateVector.setY(y += 0.15);
					translateVector.setZ(z += 0.25);
					//srand(time(NULL));
				}
				else if ((float)rand() / RAND_MAX >.2)
				{
					//translateVector.setX(x -= 1);
					translateVector.setY(y += 0.5);
					translateVector.setZ(z += 0.25);
					//srand(time(NULL));
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
/*
Populates vector indices in the format required for GL_POINTS (i.e. (i[v1], i[v2]) where two vertices are required to form a line)
Also populates vectors indicesForTriangles required for GL_TRIANGLES of the format (i.e. (i[v1], i[v2], i[v3]) where three vertices are required to form a triangle)
Does not connect with itself at the end of each "row" (where row represents a vertex rotated n (span) times)
*/
void Terrain::setWireFrameIndices(int initialSize)
{

	offset = initialSize;

	int i = 0;
	for (int k = 0; k < vertices.size() - 3; k += 3) {//test
		i = k / 3;
		if (k < vertices.size() - offset * 3)// not the last set of translated points
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
		indicesForTriangles.push_back(wireFrameIndices[m + 1]);
		indicesForTriangles.push_back(wireFrameIndices[m + 3]);
	}

}
vector<GLuint> Terrain::getIndicesForTriangles()
{
	return indicesForTriangles;
}
/*
Todo:  Given int from 1-3, return vector in that sector.  This way we don't have trees floating or sunken in water, and we can randomize
which part of the terrain is populated
*/
glm::vec3 Terrain::getPointInSector(int sector)//doesn't work right yet
{
	srand(time(NULL));
	double random = rand() / RAND_MAX;

	for (int i = 0; i <= vertices.size() - offset * 3; i += offset * 3)
	{

		if (i < i*offset * 3 + (offset))//S1
		{
			if (random  < .15)
			{
				return glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
			}
			//cout << "S1" << endl;
		}
		if ((i > i*offset * 3 + offset) && (i < i*offset * 3 + 2 * offset))//S2
		{
			if (random / 100 < .45)
			{
				return glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
			}
			//cout << "S2" << endl;
		}
		if ((i > i*offset * 3 + 2 * offset) && (i < i*offset * 3 + 3 * offset))//S2
		{

			return glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);

			//cout << "S3" << endl;
		}
	}


}

/*
Returns the last set of vertices so that they can be used to seamlessly transition between terrain objects
*/
vector<glm::vec3> Terrain::getLastVertices()
{
	vector<glm::vec3> lastVertices;
	for (int i = vertices.size() - offset * 3; i <= vertices.size() - 3; i += 3)//x, y z (float)
	{
		lastVertices.push_back(glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]));//vec3

	}
	return lastVertices;
}