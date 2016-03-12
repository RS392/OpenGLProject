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
	vector<GLfloat> vertices;
	int offset;
	int intervals;
	vector<GLuint> wireFrameIndices;
	vector<GLuint> indicesForTriangles;
	vector<glm::vec3> initialPoints;
	vector<float> probabilities;
	


public:
	Terrain();
	~Terrain();

	void setTranslateVector(double x, double y, double z);
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
	vector <glm::vec3> getLastPoints();
};

