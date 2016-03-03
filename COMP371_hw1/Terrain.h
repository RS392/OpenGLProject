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
	int intervals;
	int offset;

	vector<GLuint> wireFrameIndices;
	vector<GLuint> indicesForTriangles;
	vector<float> probabilities;
	vector<glm::vec3> initialPoints;//moved from translate for testing


public:
	Terrain();
	Terrain(vector<glm::vec3>, Vector3D);
	~Terrain();


	void setTranslateVector(double x, double y, double z);
	Vector3D getTranslateVector();

	void setVertices();
	vector<GLfloat> getVertices();

	//void setVertices2();
	//vector<Vector3D> getVertices2();

	void setWireFrameIndices(int);
	vector<GLuint> getWireFrameIndices();

	void setProbabilities(double, double, double);
	vector<float> getProbabilities();

	void setIntervals(int);
	int getIntervals();

	vector<GLuint> getIndicesForTriangles();
	glm::vec3 getPointInSector(int); //todo
	void setFirstSetOfVertices();
	vector<glm::vec3> Terrain::getLastVertices();
};

