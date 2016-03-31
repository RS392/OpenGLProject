#include "stdafx.h"
#include "Scene.h"
#include "Terrain.h"


Terrain::Terrain(glm::vec3 cameraPosition)
{
	setCameraPosition(cameraPosition);
	setIntervals(100);
	setTranslateVector(0.0, 0.0, 200.0);
	setTextureCoordinates(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	setInitialPoints();
	setVertices();
	setTest();
	setNormals();
}

Terrain::~Terrain()
{
}
void Terrain::setNormals()
{
	int numberVertices = vertices.size() / 3;
	for (int i = 0; i < numberVertices; i++)
	{
		normals.push_back(vec3(0.0f, 1.0f, 0.0f));
	}
}
void Terrain::setTranslateVector(double x, double y, double z)
{
	translateVector = Vector3D(x, y, z);
}
Vector3D Terrain::getTranslateVector()
{
	return translateVector;
}/*
	Uses first set of vertices and translates each point once.
 */
void Terrain::setVertices()
{

	int rowLength = initialPoints.size();
	for (int i = 0; i <initialPoints.size(); i++)
	{
		vertices.push_back(initialPoints[i].x);
		vertices.push_back(initialPoints[i].y);
		vertices.push_back(initialPoints[i].z);
	}
	glm::mat4 translateMatrix = glm::mat4(1.0f);
	
	translateMatrix = glm::translate(translateMatrix,
		glm::vec3(
			translateVector.getX(), translateVector.getY(), translateVector.getZ()));
	for (int i = 0; i < initialPoints.size(); i++) {//translate each point exactly once

		glm::vec4 vertex(initialPoints[i].x, initialPoints[i].y, initialPoints[i].z, 1.0f);
		glm::vec4 newV = translateMatrix * vertex;
		vertices.push_back(newV.x);
		vertices.push_back(newV.y);
		vertices.push_back(newV.z);
	}

	
	//setLastPoints(); //todo
	//setQuadIndices(rowLength);
	setWireFrameIndices(rowLength);//sets
}

/*
	sets vector of texture coordinates
	u1, v1: bottom left
	u2, v2: bottom right
	u3, v3: top left
	u4, v4: top right

*/
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
/*
	Sets initial points extending from  x= -RADIUS to x = RADIUS, which is centered around the initial x value of the camera position
*/
void Terrain::setInitialPoints()
{
	for (double i = -1.0*getCameraPosition().z; i < getCameraPosition().z; i+=100)//centered around camera
	{
		//initialPoints.push_back(glm::vec3((float)i, 0.0f, -1.0*getCameraPosition().z));//getCameraPosition().z is RADIUS
		initialPoints.push_back(glm::vec3((float)i, 0.0f, 0.0f));//getCameraPosition().z is RADIUS
	}
	/*waterVertices.push_back(initialPoints[0].x);
	waterVertices.push_back(-.01);
	waterVertices.push_back(initialPoints[0].z);

	waterVertices.push_back(initialPoints[initialPoints.size()-1].x);
	waterVertices.push_back(-.01);
	waterVertices.push_back(initialPoints[initialPoints.size() - 1].z);*/
}

/*
	Doesn't actually set wireframeindices...  todo: rename
	Instead assigns UV coordinates for each vertex to be rendered in a quad
*/
void Terrain::setWireFrameIndices(int initialSize)
{
	
	offset = initialSize;
	int i = 0;
	for (int k = 0; k < vertices.size() - 3; k += 3) {//test
		i = k / 3;
		if (k < vertices.size() - offset*3 )// not the last set of translated points
		{

			if ((i%offset) != (offset - 1)) //not the last point of a set of translated points
			{
				
				
				/* Add coordinates counter-clockwise */
				//Texture vertices of i: x, y, z, u, v
				textureVertices.push_back(vertices[k]);//x
				textureVertices.push_back(vertices[k + 1]);//y
				textureVertices.push_back(vertices[k + 2]);//z
				textureVertices.push_back(textureCoordinates[0].x);//bottom left/origin
				textureVertices.push_back(textureCoordinates[0].y);

				//Texture vertices of i + 1: x, y, z, u, v
				textureVertices.push_back(vertices[k + 3]);//x
				textureVertices.push_back(vertices[k + 4]);//y
				textureVertices.push_back(vertices[k + 5]);//z
				textureVertices.push_back(textureCoordinates[1].x);//bottom right
				textureVertices.push_back(textureCoordinates[1].y);

				//Texture vertices of i + offset + 1: x, y, z, u, v
				textureVertices.push_back(vertices[k + (offset * 3) + 3]);//x
				textureVertices.push_back(vertices[k + (offset * 3) + 4]);//y
				textureVertices.push_back(vertices[k + (offset * 3) + 5]);//z
				textureVertices.push_back(textureCoordinates[3].x);//top right
				textureVertices.push_back(textureCoordinates[3].y);
				/**/

				//Texture vertices of i + offset: x, y, z, u, v
				textureVertices.push_back(vertices[k + (offset * 3)]);//x
				textureVertices.push_back(vertices[k + (offset * 3) + 1]);//y
				textureVertices.push_back(vertices[k + (offset * 3) + 2]);//z
				textureVertices.push_back(textureCoordinates[2].x);//top left
				textureVertices.push_back(textureCoordinates[2].y);

				
			}

		}
	}
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

