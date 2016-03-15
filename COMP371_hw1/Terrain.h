#pragma once
#include <vector>
#include "Vector3D.h"
#include "Vector4D.h"
#include <stdlib.h>

using namespace std;
class Terrain
{
private:
	Vector3D translateVector;
glm::vec3 cameraPosition;
	vector<GLfloat> vertices;
	vector<GLfloat> textureVertices;//x, y, z, u, v
	int offset;
	int intervals;
	vector<GLuint> wireFrameIndices;
	vector<GLuint> indicesForTriangles;
	vector<glm::vec3> initialPoints;
	vector<float> probabilities;
	vector<float> waterVertices;
	vector<GLuint> waterIndices;
	vector<glm::vec3> lastVertices;
	vector<glm::vec2> textureCoordinates;

public:
	Terrain(glm::vec3);
	~Terrain();

	void setTranslateVector(double, double, double);

	void setCameraPosition(glm::vec3 pos) { cameraPosition = pos; }
	glm::vec3 getCameraPosition() { return cameraPosition; }
	Vector3D getTranslateVector();

	
	void setVertices();
	vector<GLfloat> getVertices();


	vector<glm::vec3> getInitialPoints();
	void setInitialPoints();

	void setWireFrameIndices(int);
	vector<GLuint> getWireFrameIndices();

	void setProbabilities(double, double, double);
	vector<float> getProbabilities();

	void setIntervals(int);
	int getIntervals();

	vector<GLuint> getIndicesForTriangles();
	void setLastPoints();
	vector <glm::vec3> getLastPoints();
	
	vector<float> getWaterVertices();
	vector<GLuint> getWaterIndices();

	void setTextureVertices();
	void setWaterIndices();

	void setTextureCoordinates(float, float, float, float, float, float, float, float);
};

