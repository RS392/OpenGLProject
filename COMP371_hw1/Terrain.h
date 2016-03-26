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
	vector<GLfloat> test;
	vector<vec3> quadXYZs;
	vector<vec2> quadUvs;
	vector<GLuint> quadIndices;


public:
	Terrain(glm::vec3);
	~Terrain();

	void setTranslateVector(double, double, double);

	void setCameraPosition(glm::vec3 pos) { cameraPosition = pos; }
	glm::vec3 getCameraPosition() { return cameraPosition; }
	Vector3D getTranslateVector();

	void setTest() 
	{
		test.push_back(-100.0f);//x
		test.push_back(0.0f);//y
		test.push_back(5000.0f);//z
		test.push_back(0.0f);//u
		test.push_back(0.0f);//v

		test.push_back(1000.0f);//x
		test.push_back(0.0f);//y
		test.push_back(5000.0f);//z
		test.push_back(1.0f);//u
		test.push_back(0.0f);//v


		test.push_back(1000.0f);//x
		test.push_back(0.0f);//y
		test.push_back(5500.0f);//z
		test.push_back(1.0f);//u
		test.push_back(1.0f);//v

		test.push_back(-1000.0f);//x
		test.push_back(0.0f);//y
		test.push_back(5500.0f);//z
		test.push_back(0.0f);//u
		test.push_back(1.0f);//v


	}
	/*
		Simple quad
	*/
	vector<GLfloat> getTest() { 
		
		return test; }
	void setVertices();
	vector<GLfloat> getVertices();


	vector<glm::vec3> getInitialPoints();
	void setInitialPoints();

	vector<GLuint> getQuadIndices() { return quadIndices; }
	void setQuadIndices(int);
	void setWireFrameIndices(int);
	vector<GLuint> getWireFrameIndices();
	vector<vec2> getQuadUVs() { return quadUvs; }

	void setProbabilities(double, double, double);
	vector<float> getProbabilities();

	void setIntervals(int);
	int getIntervals();

	vector<GLuint> getIndicesForTriangles();
	void setLastPoints();
	vector <glm::vec3> getLastPoints();
	
	vector<float> getWaterVertices();
	vector<GLuint> getWaterIndices();

	
	vector<float> getTextureVertices() { return textureVertices; }
	void setWaterIndices();

	void setTextureCoordinates(float, float, float, float, float, float, float, float);
};

