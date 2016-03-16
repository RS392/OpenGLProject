#pragma once



#include "../glew/glew.h"		// include GL Extension Wrangler

#include "../glfw/glfw3.h"  // include GLFW helper library

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtc/constants.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <sstream>
#include "stdafx.h"
#include "FileReader.h"
#include "RandomAttributeGenerator.h"
#include "Terrain.h"
#include "ctime"
#include "Camera.h"
using namespace std;

class Scene
{
private:
	RandomAttributeGenerator* generator;
	objects originalObjects;
	objects objectsInMemory;
	objects objectsToDraw;
	objects objectsInTransit;
	clock_t time;
	int numberOfOriginalObjects;
	Terrain *terrain;
	vec3 oldPlayerPos;
	vec3 lastFrameCamPos;
	vector<vec3> treeNormals;
	vector<vec2> treeUvs;
	void renewObjectsToDraw();
	void handleCollisionWithCamera();
	void optimizeFromVBO();
	void constructEnvironment();
	vec3 getCameraPos();
	bool initializeOpenGL();
	bool initializeProgram();
	bool cleanUp();
	GLuint loadShaders(string vertex_shader_path, string fragment_shader_path);
	void test();
	void mouseCallBack(GLFWwindow* window, int xpos, int ypos);
	void makeOriginalObjects();
	void drawObjects();
	void drawEverything();
	void drawTerrain();
	void applyTexture();
public:
	Scene();
	~Scene();
	int runEngine();
};

