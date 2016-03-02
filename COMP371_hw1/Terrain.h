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
	vector<Vector3D> vertices;
	Vector4D dirt;
	Vector4D grass;
	Vector4D water;
	int intervals;
	double currentY;
	vector<GLfloat> test;
	vector<GLuint> wireFrameIndices;
	vector<GLuint> indicesForTriangles;
	vector<float> probabilities;
	vector<Vector3D> initialPoints;//moved from translate for testing


public:
	Terrain();
	~Terrain();

	vector<GLfloat> getTest();
	void setTranslateVector(double x, double y, double z);
	Vector3D getTranslateVector();

	void setVertices();
	vector<Vector3D> getVertices();

	void setDirt(double, double, double, double);
	Vector4D getDirt();

	void setGrass(double, double, double, double);
	Vector4D getGrass();

	void setWater(double, double, double, double);
	Vector4D getWater();

	void setCurrentY(double);
	double getCurrentY();

	void setWireFrameIndices(int);
	vector<GLuint> getWireFrameIndices();

	void setProbabilities(double, double, double);
	vector<float> getProbabilities();

	void setIntervals(int);
	int getIntervals();

	vector<GLuint> getIndicesForTriangles();

};

